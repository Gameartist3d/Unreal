// Copyright Epic Games, Inc. All Rights Reserved.
//3DNomad LLC

#include "SPCharacter.h"
#include "SPPlayuurController.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"
#include "SPPlayuurController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameFramework/HUD.h"
#include "InteractionMenuWidget.h"
#include "SPBaseItem.h"
#include "SPGameMode.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ASPCharacter

ASPCharacter::ASPCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	// Initialize variables
	VaultStartHeight = 0.0f;
	FallStartHeight = 0.0f;
	bIsFalling = false;
	TraceDistance = 1000.0f;
	CombatCameraBoomOffset = FVector(300.0f, 50.0f, 85.0f);
	AdventureCameraBoomOffset = FVector(40.0f, 25.0f, 30.0f);
	LHandCombatCameraBoomOffset = FVector(300.0f, -50.0f, 85.0f);
	LHandAdventureCameraBoomOffset = FVector(40.0f, -25.0f, 30.0f);
	PlayuurMode = EPlayuurMode::Adventure;
	bIsCrouched = false;
	bIsLhandGuarding = false;
	bIsRhandGuarding = false;
	bIsLhandDominant = false;
	FocusedInteractionComponent = nullptr;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	//Create inventorywidgetcomponent
	InventoryWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Menu Widget"));
	InventoryWidgetComponent->SetupAttachment(RootComponent);
	InventoryWidgetComponent->SetWidgetSpace(EWidgetSpace::World);
	InventoryWidgetComponent->SetDrawSize(FVector2D(192, 108));
	InventoryWidgetComponent->SetRelativeLocation(FVector(0, 0, 0));
	InventoryWidgetComponent->SetRelativeRotation(FRotator(0, 0, 0));

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	PlayuurStatsComponent = CreateDefaultSubobject<UStatsComponent>("Playuur Stats");
	PlayuurInventoryComponent = CreateDefaultSubobject<UInventoryComponent>("Playuur Inventory");
	PlayuurInventoryComponent->InventoryCapacity = 100;
	FirstWeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("FirstWeaponMeshComponent");
	SecondWeaponMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SecondWeaponMeshComponent");

}

void ASPCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (ASPPlayuurController* PlayerController = Cast<ASPPlayuurController>(Controller))
	{
		EnableInput(PlayerController);
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	PreviousZloc = GetActorLocation().Z;
	
}

void ASPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	float CurrentVerticalVelocity = GetCharacterMovement()->Velocity.Z;

	if (PreviousVerticalVelocity > 0 && CurrentVerticalVelocity <= 0)
	{
		if (!bReachedJumpPeak)
		{
			bReachedJumpPeak = true;
			FallStartHeight = GetActorLocation().Z;
			ExponVaultHeight();
		}

	}
	else if (CurrentVerticalVelocity > 0)
	{
		bReachedJumpPeak = false;
	}

	PreviousVerticalVelocity = CurrentVerticalVelocity;

	//Get Playuur's View Point
	FVector StartLocation;
	FRotator ViewRotation;
	GetController()->GetPlayerViewPoint(StartLocation, ViewRotation);

	//Calculate the end location of the line trace
	FVector EndLocation = StartLocation + (ViewRotation.Vector() * TraceDistance);

	//Draw the line trace
	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params)) {
		//If the trace hit something draw a crosshair
		DrawDebugPoint(GetWorld(), HitResult.Location, 15.0f, FColor::Red);
		
		//check if the actor has an interaction component
		AActor* HitActor = HitResult.GetActor();
		if (HitActor) {
			UInteractionComponent* InteractionComponent = Cast<UInteractionComponent>(HitActor->GetComponentByClass(UInteractionComponent::StaticClass()));
			if (InteractionComponent) {
				FocusedInteractionComponent = InteractionComponent;
				//UE_LOG(LogTemp, Log, TEXT("Focused Interaction Component: %s"), *FocusedInteractionComponent->GetOwner()->GetName());
				FName crossname = "Interact";
				UpdateCrosshairWidget(crossname);
			}
			else {
				FName crossname = "Default";
				UpdateCrosshairWidget(crossname);
				FocusedInteractionComponent = nullptr;
			}
		}
		else {
			FName crossname = "Default";
			UpdateCrosshairWidget(crossname);
			FocusedInteractionComponent = nullptr;
		}
	}
	//UE_LOG(LogTemplateCharacter, Log, TEXT("Focused Interaction Component: %s"), FocusedInteractionComponent);
}

//////////////////////////////////////////////////////////////////////////
// Input

void ASPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASPCharacter::Move);

		//MiddleMouseScrolling
		EnhancedInputComponent->BindAction(MiddleMouseScrollAction, ETriggerEvent::Triggered, this, &ASPCharacter::MiddleMouseScroll);

		//Sprinting
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &ASPCharacter::Sprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ASPCharacter::StopSprinting);

		//Crouching
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &ASPCharacter::Crouch);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &ASPCharacter::OnCrouchHoldStart);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &ASPCharacter::OnCrouchHoldComplete);

		//Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ASPCharacter::Interact);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ASPCharacter::OnInteractHoldStart);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &ASPCharacter::OnInteractHoldComplete);

		//Use Left Hand
		EnhancedInputComponent->BindAction(LhandAction, ETriggerEvent::Triggered, this, &ASPCharacter::UseLeftHand);
		EnhancedInputComponent->BindAction(LhandAction, ETriggerEvent::Started, this, &ASPCharacter::OnLhandHoldStart);
		EnhancedInputComponent->BindAction(LhandAction, ETriggerEvent::Completed, this, &ASPCharacter::OnLhandHoldComplete);

		//Use Right Hand
		EnhancedInputComponent->BindAction(RhandAction, ETriggerEvent::Triggered, this, &ASPCharacter::UseRightHand);
		EnhancedInputComponent->BindAction(RhandAction, ETriggerEvent::Started, this, &ASPCharacter::OnRhandHoldStart);
		EnhancedInputComponent->BindAction(RhandAction, ETriggerEvent::Completed, this, &ASPCharacter::OnRhandHoldComplete);

		//ToggleMenus
		EnhancedInputComponent->BindAction(MenuAction, ETriggerEvent::Triggered, this, &ASPCharacter::ToggleMenu);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASPCharacter::Look);

		//Reload
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Triggered, this, &ASPCharacter::Reload);

		//Holster
		EnhancedInputComponent->BindAction(HolsterAction, ETriggerEvent::Triggered, this, &ASPCharacter::Holster);

		//Switch Dominant Hand
		EnhancedInputComponent->BindAction(SwitchDominantHandAction, ETriggerEvent::Triggered, this, &ASPCharacter::SwitchDominantHand);

		//Left Hand Spell
		EnhancedInputComponent->BindAction(LhandSpellAction, ETriggerEvent::Triggered, this, &ASPCharacter::CastLhandSpell);
		EnhancedInputComponent->BindAction(LhandSpellAction, ETriggerEvent::Started, this, &ASPCharacter::OnLhandSpellHoldStart);
		EnhancedInputComponent->BindAction(LhandSpellAction, ETriggerEvent::Completed, this, &ASPCharacter::OnLhandSpellHoldComplete);

		//Right Hand Spell
		EnhancedInputComponent->BindAction(RhandSpellAction, ETriggerEvent::Triggered, this, &ASPCharacter::CastRhandSpell);
		EnhancedInputComponent->BindAction(RhandSpellAction, ETriggerEvent::Started, this, &ASPCharacter::OnRhandSpellHoldStart);
		EnhancedInputComponent->BindAction(RhandSpellAction, ETriggerEvent::Completed, this, &ASPCharacter::OnRhandSpellHoldComplete);

		//Activate Toolbelt
		EnhancedInputComponent->BindAction(ToolbeltAction, ETriggerEvent::Triggered, this, &ASPCharacter::ActivateToolbelt); 

		//Toggle Map
		EnhancedInputComponent->BindAction(ToggleMapAction, ETriggerEvent::Triggered, this, &ASPCharacter::ToggleMap);

		//Toggle Flashlight
		EnhancedInputComponent->BindAction(ToggleFlashlightAction, ETriggerEvent::Triggered, this, &ASPCharacter::ToggleFlashlight);

		//Use Throwable
		EnhancedInputComponent->BindAction(ThrowableAction, ETriggerEvent::Triggered, this, &ASPCharacter::ThrowThrowable);
		EnhancedInputComponent->BindAction(ThrowableAction, ETriggerEvent::Started, this, &ASPCharacter::OnThrowHoldStart);
		EnhancedInputComponent->BindAction(ThrowableAction, ETriggerEvent::Completed, this, &ASPCharacter::OnThrowHoldComplete);

		//Hotkey 1
		EnhancedInputComponent->BindAction(Hotkey1Action, ETriggerEvent::Triggered, this, &ASPCharacter::Hotkey1);

		//Hotkey 2
		EnhancedInputComponent->BindAction(Hotkey2Action, ETriggerEvent::Triggered, this, &ASPCharacter::Hotkey2);

		//Hotkey 3
		EnhancedInputComponent->BindAction(Hotkey3Action, ETriggerEvent::Triggered, this, &ASPCharacter::Hotkey3);

		//Hotkey 4
		EnhancedInputComponent->BindAction(Hotkey4Action, ETriggerEvent::Triggered, this, &ASPCharacter::Hotkey4);

		//Hotkey 5
		EnhancedInputComponent->BindAction(Hotkey5Action, ETriggerEvent::Triggered, this, &ASPCharacter::Hotkey5);

		//Hotkey 6
		EnhancedInputComponent->BindAction(Hotkey6Action, ETriggerEvent::Triggered, this, &ASPCharacter::Hotkey6);

		//Hotkey 7
		EnhancedInputComponent->BindAction(Hotkey7Action, ETriggerEvent::Triggered, this, &ASPCharacter::Hotkey7);

		//Hotkey 8
		EnhancedInputComponent->BindAction(Hotkey8Action, ETriggerEvent::Triggered, this, &ASPCharacter::Hotkey8);

		//Hotkey 9
		EnhancedInputComponent->BindAction(Hotkey9Action, ETriggerEvent::Triggered, this, &ASPCharacter::Hotkey9);

		//Hotkey 0
		EnhancedInputComponent->BindAction(Hotkey0Action, ETriggerEvent::Triggered, this, &ASPCharacter::Hotkey0);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ASPCharacter::UseItem(ASPBaseItem* Item)
{
	if (Item) {
		Item->Use(this);
		Item->OnUse(this); //BP version
	}
}

void ASPCharacter::UnarmedStrike(FString strikinghand)
{
	

}

void ASPCharacter::PickupItem(ASPBaseItem* item)
{
	//TODO add an animation for picking up  items
	if (item)
	{
		PlayuurInventoryComponent->AddItem(item);
	}
}

void ASPCharacter::EquipWeaponItem(AWeaponItem* item)
{
	if (item) {
		if (item->bIsTwoHanded == true) {
			PlayuurInventoryComponent->EquippedItems.Add(ESPEquipmentSlot::RightHand, item);
			PlayuurInventoryComponent->EquippedItems.Add(ESPEquipmentSlot::LeftHand, item);
			SecondWeaponMeshComponent->SetSkeletalMesh(nullptr);
			FirstWeaponMeshComponent->SetSkeletalMesh(item->WeaponMesh);
		}
		else if (item->bIsTwoHanded == false) {
			if (bIsLhandDominant) {
				PlayuurInventoryComponent->EquippedItems.Add(ESPEquipmentSlot::LeftHand, item);
				FirstWeaponMeshComponent->SetSkeletalMesh(item->WeaponMesh);
			}
			else {
				PlayuurInventoryComponent->EquippedItems.Add(ESPEquipmentSlot::RightHand, item);
				FirstWeaponMeshComponent->SetSkeletalMesh(item->WeaponMesh);
			}
		}
}
}

void ASPCharacter::StealItem(ASPBaseItem* item)
{
}

void ASPCharacter::UpdateCrosshairWidget(FName crosshairname)
{ 
	ASPPlayuurController* playerController = Cast<ASPPlayuurController>(GetController());
	if (playerController && playerController->CrosshairWidget)
	{
		// Find the Blueprint function
		playerController->CrosshairWidget->SetCrosshairTexture(crosshairname);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("playercontroller is null"));
	}
}

void ASPCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ASPCharacter::Sprint(const FInputActionValue& Value)
{
	if (GetCharacterMovement())
	{
		if (OriginalWalkSpeed == 0.f)
		{
			OriginalWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
		}
		GetCharacterMovement()->MaxWalkSpeed = OriginalWalkSpeed + (14.4f * PlayuurStatsComponent->GetSkilllvl(ESPSkillNames::Sprinting));
		SprintTimeStart = GetWorld()->GetTimeSeconds();
		bIsSprinting = true;
		
	}
}

void ASPCharacter::StopSprinting(const FInputActionValue& Value)
{
	float newsprinttime = GetWorld()->GetTimeSeconds();
	if (GetCharacterMovement())
	{
		//reset maxwalkspeed to original speed
		GetCharacterMovement()->MaxWalkSpeed = OriginalWalkSpeed;
		//reset OriginalWalkspeed
		OriginalWalkSpeed = 0.f;
		PlayuurStatsComponent->AddSkillExp(ESPSkillNames::Sprinting, 0.5f * (newsprinttime - SprintTimeStart));

	}
}

void ASPCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ASPCharacter::Jump()
{
	if (CanJump())
	{
		VaultStartHeight = GetActorLocation().Z;
		bIsVaulting = true;
	}

	Super::Jump();
}

void ASPCharacter::Crouch(const FInputActionValue& Value)
{
	if (Value.GetMagnitude() > 0)
	{
		Super::Crouch();

		bIsCrouched = true;

		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			/**UYourAnimtaionBlueprintClassName* MyAnimBP = Cast<UYourAnimationBlueprintClassName>(AnimInstance);
			if (MyAnimBP != nullptr)
			{
			MyAnimBP->SetisCrouching(true);
			}
			*/
		}
		UE_LOG(LogTemplateCharacter, Log, TEXT("Crouch Triggered"));
	}
	else
	{
		Super::UnCrouch();

		bIsCrouched = false;

		/**UYourAnimtaionBlueprintClassName* MyAnimBP = Cast<UYourAnimationBlueprintClassName>(AnimInstance);
			if (MyAnimBP != nullptr)
			{
			MyAnimBP->SetisCrouching(false);
			}
			*/
	}
}

void ASPCharacter::OnCrouchHoldStart(const FInputActionValue& Value)
{

}

void ASPCharacter::OnCrouchHoldComplete(const FInputActionValue& Value)
{

}

void ASPCharacter::MiddleMouseScroll(const FInputActionValue& Value)
{
}

void ASPCharacter::Slide()
{
	 bIsSliding = true;
}

void ASPCharacter::Interact(const FInputActionValue& Value)
{
	
	if (FocusedInteractionComponent)
	{
		FocusedInteractionComponent->bIsBusy = true;
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		ASPPlayuurController* micontroller = Cast<ASPPlayuurController>(PlayerController);
		if (PlayerController && InteractionMenuWidgetClass)
		{
			if (!micontroller->InteractionMenuWidget) {
				UInteractionMenuWidget* interactionMenuWidget = CreateWidget<UInteractionMenuWidget>(PlayerController, InteractionMenuWidgetClass);
				micontroller->InteractionMenuWidget = interactionMenuWidget;
				if (interactionMenuWidget)
				{
					interactionMenuWidget->AddToViewport();

					// Get owner of the FocusedInteractionComponent
					AActor* buddyweRfocuson = FocusedInteractionComponent->GetOwner();
					// If the focused interaction component is attached to an SPcharacter
					if (ASPCharacter* character = Cast<ASPCharacter>(buddyweRfocuson)) {
						UE_LOG(LogTemplateCharacter, Log, TEXT("Character Info Sent to MenuWidget"));
						interactionMenuWidget->SendCharInfo2Menu(character, FocusedInteractionComponent);
						FocusedInteractionComponent->OnCharInteractUpdate.Broadcast(character);
					}
					// Else if the focused interaction component is attached to an SPBaseItem
					else if (ASPBaseItem* item = Cast<ASPBaseItem>(buddyweRfocuson)) {
						UE_LOG(LogTemplateCharacter, Log, TEXT("Item Info Sent to MenuWidget"));
						interactionMenuWidget->SendItemInfo2Menu(item, FocusedInteractionComponent);
						FocusedInteractionComponent->OnItemInteractUpdate.Broadcast(item);
					}
					//Else just return the interaction types available
					else {
						UE_LOG(LogTemplateCharacter, Log, TEXT("Default Info Sent to MenuWidget"));
						for (EInteractionTypes inttype : FocusedInteractionComponent->InteractionTypes) {
							interactionMenuWidget->InteractionTypes.Add(inttype);
							FocusedInteractionComponent->OnactorInteractUpdate.Broadcast(buddyweRfocuson);
						}
					}
					FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
					FVector2D CenterPosition = ViewportSize / 2.0f;
					interactionMenuWidget->SetPositionInViewport(CenterPosition);
					interactionMenuWidget->SetAlignmentInViewport(FVector2D(0.5f, 0.5f));
				}
			}
			else {
				micontroller->InteractionMenuWidget->ActivateFocusedInteractionBox(FocusedInteractionComponent);
				FocusedInteractionComponent->bIsBusy = false;
			}
		}
	}
	else {
		FocusedInteractionComponent = nullptr;
	}
	
	UE_LOG(LogTemplateCharacter, Log, TEXT("Interact Triggered"));
}

void ASPCharacter::OnInteractHoldStart(const FInputActionValue& Value)
{
	UE_LOG(LogTemplateCharacter, Log, TEXT("Interact Hold Start"));
}

void ASPCharacter::OnInteractHoldComplete(const FInputActionValue& Value)
{
	UE_LOG(LogTemplateCharacter, Log, TEXT("Interact Hold Complete"));
}

void ASPCharacter::UseLeftHand(const FInputActionValue& Value)
{
	if (PlayuurInventoryComponent->EquippedItems.Contains(ESPEquipmentSlot::LeftHand))
	{
		UseItem(PlayuurInventoryComponent->EquippedItems[ESPEquipmentSlot::LeftHand]);
	}
	else if (PlayuurMode == EPlayuurMode::Adventure){
		PlayuurMode = EPlayuurMode::Combat;
	}
	else if (PlayuurMode == EPlayuurMode::Combat) {
		bIsLhandGuarding = false;
		UnarmedStrike("Left");
	}
	UE_LOG(LogTemplateCharacter, Log, TEXT("Left Hand Triggered"));
}

void ASPCharacter::OnLhandHoldStart(const FInputActionValue& Value)
{
	bIsLhandGuarding = false;
	UE_LOG(LogTemplateCharacter, Log, TEXT("Left Hand Hold Start"));
}

void ASPCharacter::OnLhandHoldComplete(const FInputActionValue& Value)
{
	bIsLhandGuarding = true;
	UE_LOG(LogTemplateCharacter, Log, TEXT("Left Hand Hold Complete"));
}

void ASPCharacter::UseRightHand(const FInputActionValue& Value)
{
	if (PlayuurInventoryComponent->EquippedItems.Contains(ESPEquipmentSlot::RightHand))
	{
		UseItem(PlayuurInventoryComponent->EquippedItems[ESPEquipmentSlot::RightHand]);
	}
	else if (PlayuurMode == EPlayuurMode::Adventure) {
		PlayuurMode = EPlayuurMode::Combat;
	}
	else if (PlayuurMode == EPlayuurMode::Combat) {
		bIsRhandGuarding = false;
		UnarmedStrike("Right");
	}
	UE_LOG(LogTemplateCharacter, Log, TEXT("Right Hand Triggered"));
}

void ASPCharacter::OnRhandHoldStart(const FInputActionValue& Value)
{
	bIsRhandGuarding = false;
	UE_LOG(LogTemplateCharacter, Log, TEXT("Right Hand Hold Start"));
}

void ASPCharacter::OnRhandHoldComplete(const FInputActionValue& Value)
{
	bIsRhandGuarding = true;
	UE_LOG(LogTemplateCharacter, Log, TEXT("Right Hand Hold Complete"));
}

void ASPCharacter::CombineHandActions()
{
}

void ASPCharacter::SwitchDominantHand(const FInputActionValue& Value)
{
	if (bIsLhandDominant) {
		if (PlayuurMode == EPlayuurMode::Adventure) {
			CameraBoom->SocketOffset = AdventureCameraBoomOffset;
			ASPBaseItem* tempitem = PlayuurInventoryComponent->EquippedItems[ESPEquipmentSlot::RightHand];
			PlayuurInventoryComponent->EquippedItems[ESPEquipmentSlot::RightHand] = PlayuurInventoryComponent->EquippedItems[ESPEquipmentSlot::LeftHand];
			PlayuurInventoryComponent->EquippedItems[ESPEquipmentSlot::LeftHand] = tempitem;
		}
		else if (PlayuurMode == EPlayuurMode::Combat || PlayuurMode == EPlayuurMode::Climbing) {
			CameraBoom->SocketOffset = CombatCameraBoomOffset;
			ASPBaseItem* tempitem = PlayuurInventoryComponent->EquippedItems[ESPEquipmentSlot::RightHand];
			PlayuurInventoryComponent->EquippedItems[ESPEquipmentSlot::RightHand] = PlayuurInventoryComponent->EquippedItems[ESPEquipmentSlot::LeftHand];
			PlayuurInventoryComponent->EquippedItems[ESPEquipmentSlot::LeftHand] = tempitem;
		}
		else {
			return;
		}
		bIsLhandDominant = false;
	}
	else {
		if (PlayuurMode == EPlayuurMode::Adventure) {
			CameraBoom->SocketOffset = LHandAdventureCameraBoomOffset;
			ASPBaseItem* tempitem = PlayuurInventoryComponent->EquippedItems[ESPEquipmentSlot::RightHand];
			PlayuurInventoryComponent->EquippedItems[ESPEquipmentSlot::RightHand] = PlayuurInventoryComponent->EquippedItems[ESPEquipmentSlot::LeftHand];
			PlayuurInventoryComponent->EquippedItems[ESPEquipmentSlot::LeftHand] = tempitem;
		}
		else if (PlayuurMode == EPlayuurMode::Combat || PlayuurMode == EPlayuurMode::Climbing) {
			CameraBoom->SocketOffset = LHandCombatCameraBoomOffset;
			ASPBaseItem* tempitem = PlayuurInventoryComponent->EquippedItems[ESPEquipmentSlot::RightHand];
			PlayuurInventoryComponent->EquippedItems[ESPEquipmentSlot::RightHand] = PlayuurInventoryComponent->EquippedItems[ESPEquipmentSlot::LeftHand];
			PlayuurInventoryComponent->EquippedItems[ESPEquipmentSlot::LeftHand] = tempitem;
		}
		else {
			return;
		}
		bIsLhandDominant = true;
	}
}

void ASPCharacter::CastLhandSpell(const FInputActionValue& Value)
{
}

void ASPCharacter::OnLhandSpellHoldStart(const FInputActionValue& Value)
{
}

void ASPCharacter::OnLhandSpellHoldComplete(const FInputActionValue& Value)
{
}

void ASPCharacter::CastRhandSpell(const FInputActionValue& Value)
{
}

void ASPCharacter::OnRhandSpellHoldStart(const FInputActionValue& Value)
{
}

void ASPCharacter::OnRhandSpellHoldComplete(const FInputActionValue& Value)
{
}

void ASPCharacter::CombineHandSpells(USPSpell lhandspell, USPSpell rhandspell)
{
}

void ASPCharacter::ActivateToolbelt(const FInputActionValue& Value)
{
}

void ASPCharacter::ToggleMap(const FInputActionValue& Value)
{
}

void ASPCharacter::ToggleFlashlight(const FInputActionValue& Value)
{
}

void ASPCharacter::ThrowThrowable(const FInputActionValue& Value)
{
}

void ASPCharacter::OnThrowHoldStart(const FInputActionValue& Value)
{
}

void ASPCharacter::OnThrowHoldComplete(const FInputActionValue& Value)
{
}

void ASPCharacter::Hotkey1(const FInputActionValue& Value)
{
}

void ASPCharacter::Hotkey2(const FInputActionValue& Value)
{
}

void ASPCharacter::Hotkey3(const FInputActionValue& Value)
{
}

void ASPCharacter::Hotkey4(const FInputActionValue& Value)
{
}

void ASPCharacter::Hotkey5(const FInputActionValue& Value)
{
}

void ASPCharacter::Hotkey6(const FInputActionValue& Value)
{
}

void ASPCharacter::Hotkey7(const FInputActionValue& Value)
{
}

void ASPCharacter::Hotkey8(const FInputActionValue& Value)
{
}

void ASPCharacter::Hotkey9(const FInputActionValue& Value)
{
}

void ASPCharacter::Hotkey0(const FInputActionValue& Value)
{
}

void ASPCharacter::ToggleMenu(const FInputActionValue& Value)
{
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(10, 5.f, FColor::Red, TEXT("Menu Triggered"));
	}
}

void ASPCharacter::Holster(const FInputActionValue& Value)
{
	if (PlayuurMode == EPlayuurMode::Adventure) {
		PlayuurMode = EPlayuurMode::Combat;
		bUseControllerRotationYaw = true;
		if (!bIsLhandDominant) {
			CameraBoom->SocketOffset = CombatCameraBoomOffset;
		}
		else {
			CameraBoom->SocketOffset = LHandCombatCameraBoomOffset;
		}
		bIsLhandGuarding = true;
		bIsRhandGuarding = true;
	}	
	else if (PlayuurMode == EPlayuurMode::Combat) {
		PlayuurMode = EPlayuurMode::Adventure;
		bUseControllerRotationYaw = false;
		if (!bIsLhandDominant) {}
		CameraBoom->SocketOffset = AdventureCameraBoomOffset;
	}
	else {
		CameraBoom->SocketOffset = LHandAdventureCameraBoomOffset;
	}
		bIsLhandGuarding = false;
		bIsRhandGuarding = false;
}

void ASPCharacter::Reload(const FInputActionValue& Value) {

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(11, 5.f, FColor::Red, TEXT("Reload Triggered"));
	}
}

void ASPCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	ExponFallHeight();
}

void ASPCharacter::ExponVaultHeight()
{
	float VaultHeight = GetActorLocation().Z - VaultStartHeight;

	float ExperiencePoints = FMath::RoundToFloat(VaultHeight / 100);

	PlayuurStatsComponent->AddSkillExp(ESPSkillNames::Vaulting, ExperiencePoints);

}

void ASPCharacter::ExponFallHeight()
{
	float FallHeight = FallStartHeight - GetActorLocation().Z;

	float ExperiencePoints = FMath::RoundToFloat(FallHeight/100);

	PlayuurStatsComponent->AddSkillExp(ESPSkillNames::Vaulting, ExperiencePoints);
}

void ASPCharacter::Death()
{
	PlayuurMode = EPlayuurMode::Dead;
	DisableInput( Cast<APlayerController>(GetController()));
	DetachFromControllerPendingDestroy();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->WakeAllRigidBodies();
	PlayuurStatsComponent->AggroAmount = 0.0f;
	ASPGameMode* gamemode = GetWorld()->GetAuthGameMode<ASPGameMode>();
	if (gamemode != nullptr) {
		gamemode->PawnKilled(this);
	}
}
