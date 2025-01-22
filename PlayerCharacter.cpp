// Copyright Epic Games, Inc. All Rights Reserved.
//3DNomad LLC

#include "PlayerCharacter.h"

#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "PickupClass.h"
#include "PlayerHUD.h"
#include "SPItem.h"
#include "Camera/CameraComponent.h"
#include "Components/TimelineComponent.h"

APlayerCharacter::APlayerCharacter()
{
	Inventory = (CreateDefaultSubobject<UPlayerInventoryComponent>(TEXT("Inventory")));
	StatsComponent = (CreateDefaultSubobject<UPlayerStatsComponent>(TEXT("PlayerStatsComponent")));
	//Set z loc for vaulting calculations
	PreviousZloc = GetActorLocation().Z;
	BaseEyeHeight = 65.0f;
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 380.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	MainHandStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MainHandStaticMesh"));
	MainHandStaticMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "spine_HolsterSocket_r");
	MainHandStaticMesh->SetVisibility(false);
	MainHandSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MainHandSkeletalMesh"));
	MainHandSkeletalMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "spine_HolsterSocket_r");
	MainHandSkeletalMesh->SetVisibility(false);
	OffHandStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OffHandStaticMesh"));
	OffHandStaticMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "spine_HolsterSocket_l");
	OffHandStaticMesh->SetVisibility(false);
	OffHandSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("OffHandSkeletalMesh"));
	OffHandSkeletalMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "spine_HolsterSocket_l");
	OffHandSkeletalMesh->SetVisibility(false);
	ThrowableStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ThrowableStaticMesh"));
	ThrowableStaticMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "attach_rthighSocket");
	ThrowableStaticMesh->SetVisibility(false);

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	AdventureAimCameraTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("AdventureAimCameraTimeline"));
	DefaultCameraLocation = FVector(0.0f, 0.0f, 65.0f);
	AdventureAimCameraLocation = FVector(175.0f, 50.0f, 55.0f);
	CombatAimCameraLocation = FVector(200.0f, 50.0f, 55.0f);
	ClimbingAimCameraLocation = FVector(175.0f, 50.0f, 55.0f);
	CameraBoom->SocketOffset = DefaultCameraLocation;

	//Set initial animation montage values in ActionAnimations TMap
	ActionAnimations.Add(EActionAnimationName::Grab, nullptr);
	ActionAnimations.Add(EActionAnimationName::Reload, nullptr);
	ActionAnimations.Add(EActionAnimationName::Holster, nullptr);
	ActionAnimations.Add(EActionAnimationName::UnarmedStrike, nullptr);
	ActionAnimations.Add(EActionAnimationName::SpellCast, nullptr);
	ActionAnimations.Add(EActionAnimationName::UseProjectileWeapon, nullptr);
	ActionAnimations.Add(EActionAnimationName::UseMartialWeapon, nullptr);
	ActionAnimations.Add(EActionAnimationName::Slide, nullptr);
	ActionAnimations.Add(EActionAnimationName::ChangeStance, nullptr);
	ActionAnimations.Add(EActionAnimationName::Climb, nullptr);
	ActionAnimations.Add(EActionAnimationName::Swim, nullptr);
	ActionAnimations.Add(EActionAnimationName::Fall, nullptr);
	ActionAnimations.Add(EActionAnimationName::Vault, nullptr);
	ActionAnimations.Add(EActionAnimationName::Sit, nullptr);
	ActionAnimations.Add(EActionAnimationName::Lounge, nullptr);
	ActionAnimations.Add(EActionAnimationName::Talk, nullptr);
	ActionAnimations.Add(EActionAnimationName::Throw, nullptr);
	ActionAnimations.Add(EActionAnimationName::Medical, nullptr);
	ActionAnimations.Add(EActionAnimationName::Grapple, nullptr);
	ActionAnimations.Add(EActionAnimationName::Cover, nullptr);
	ActionAnimations.Add(EActionAnimationName::Ride, nullptr);
	ActionAnimations.Add(EActionAnimationName::Drive, nullptr);
}
// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
	if (ASPPlayerController* PlayerController = Cast<ASPPlayerController>(Controller))
	{
		EnableInput(PlayerController);
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	PlayerHUD = Cast<APlayerHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	FOnTimelineFloat AimLerpAlphaValue;
	FOnTimelineEvent TimeLineFinishedEvent;
	AimLerpAlphaValue.BindUFunction(this, FName("UpdateCameraTimeline"));
	TimeLineFinishedEvent.BindUFunction(this, FName("CameraTimelineEnd"));

	if (AdventureAimCameraTimeline && AdvAimCameraCurve)
	{
		AdventureAimCameraTimeline->AddInterpFloat(AdvAimCameraCurve, AimLerpAlphaValue);
		AdventureAimCameraTimeline->SetTimelineFinishedFunc(TimeLineFinishedEvent);
	}
	
	PreviousZloc = GetActorLocation().Z;
	//Get a pointer to the player controller
	PlayerControllerInst = Cast<ASPPlayerController>(GetController());
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

		//MiddleMouseScrolling
		EnhancedInputComponent->BindAction(MiddleMouseScrollAction, ETriggerEvent::Triggered, this, &APlayerCharacter::MiddleMouseScroll);

		//Sprinting
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &APlayerCharacter::Sprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &APlayerCharacter::StopSprinting);

		//Crouching
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Crouch);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &APlayerCharacter::OnCrouchHoldStart);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &APlayerCharacter::OnCrouchHoldComplete);

		//Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &APlayerCharacter::InteractStart);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &APlayerCharacter::InteractEnd);

		//Use Left Hand
		EnhancedInputComponent->BindAction(LhandAction, ETriggerEvent::Triggered, this, &APlayerCharacter::UseLeftHand);
		EnhancedInputComponent->BindAction(LhandAction, ETriggerEvent::Started, this, &APlayerCharacter::OnLhandHoldStart);
		EnhancedInputComponent->BindAction(LhandAction, ETriggerEvent::Completed, this, &APlayerCharacter::OnLhandHoldComplete);

		//Use Right Hand
		EnhancedInputComponent->BindAction(RhandAction, ETriggerEvent::Triggered, this, &APlayerCharacter::UseRightHand);
		EnhancedInputComponent->BindAction(RhandAction, ETriggerEvent::Started, this, &APlayerCharacter::OnRhandHoldStart);
		EnhancedInputComponent->BindAction(RhandAction, ETriggerEvent::Completed, this, &APlayerCharacter::OnRhandHoldComplete);

		//ToggleMenus
		EnhancedInputComponent->BindAction(MenuAction, ETriggerEvent::Triggered, this, &APlayerCharacter::ToggleMenu);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);

		//Reload
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Reload);

		//Holster
		EnhancedInputComponent->BindAction(HolsterAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Holster);

		//Switch Dominant Hand
		EnhancedInputComponent->BindAction(SwitchDominantHandAction, ETriggerEvent::Triggered, this, &APlayerCharacter::SwitchDominantHand);

		//Left Hand Spell
		EnhancedInputComponent->BindAction(LhandSpellAction, ETriggerEvent::Triggered, this, &APlayerCharacter::CastLhandSpell);
		EnhancedInputComponent->BindAction(LhandSpellAction, ETriggerEvent::Started, this, &APlayerCharacter::OnLhandSpellHoldStart);
		EnhancedInputComponent->BindAction(LhandSpellAction, ETriggerEvent::Completed, this, &APlayerCharacter::OnLhandSpellHoldComplete);

		//Right Hand Spell
		EnhancedInputComponent->BindAction(RhandSpellAction, ETriggerEvent::Triggered, this, &APlayerCharacter::CastRhandSpell);
		EnhancedInputComponent->BindAction(RhandSpellAction, ETriggerEvent::Started, this, &APlayerCharacter::OnRhandSpellHoldStart);
		EnhancedInputComponent->BindAction(RhandSpellAction, ETriggerEvent::Completed, this, &APlayerCharacter::OnRhandSpellHoldComplete);

		//Activate Toolbelt
		EnhancedInputComponent->BindAction(ToolbeltAction, ETriggerEvent::Triggered, this, &APlayerCharacter::ActivateToolbelt);

		//Toggle Map
		EnhancedInputComponent->BindAction(ToggleMapAction, ETriggerEvent::Triggered, this, &APlayerCharacter::ToggleMap);

		//Toggle Flashlight
		EnhancedInputComponent->BindAction(ToggleFlashlightAction, ETriggerEvent::Triggered, this, &APlayerCharacter::ToggleFlashlight);

		//Use Throwable
		EnhancedInputComponent->BindAction(ThrowableAction, ETriggerEvent::Triggered, this, &APlayerCharacter::ThrowThrowable);
		EnhancedInputComponent->BindAction(ThrowableAction, ETriggerEvent::Started, this, &APlayerCharacter::OnThrowHoldStart);
		EnhancedInputComponent->BindAction(ThrowableAction, ETriggerEvent::Completed, this, &APlayerCharacter::OnThrowHoldComplete);

		//Hotkey 1
		EnhancedInputComponent->BindAction(Hotkey1Action, ETriggerEvent::Triggered, this, &APlayerCharacter::Hotkey1);

		//Hotkey 2
		EnhancedInputComponent->BindAction(Hotkey2Action, ETriggerEvent::Triggered, this, &APlayerCharacter::Hotkey2);

		//Hotkey 3
		EnhancedInputComponent->BindAction(Hotkey3Action, ETriggerEvent::Triggered, this, &APlayerCharacter::Hotkey3);

		//Hotkey 4
		EnhancedInputComponent->BindAction(Hotkey4Action, ETriggerEvent::Triggered, this, &APlayerCharacter::Hotkey4);

		//Hotkey 5
		EnhancedInputComponent->BindAction(Hotkey5Action, ETriggerEvent::Triggered, this, &APlayerCharacter::Hotkey5);

		//Hotkey 6
		EnhancedInputComponent->BindAction(Hotkey6Action, ETriggerEvent::Triggered, this, &APlayerCharacter::Hotkey6);

		//Hotkey 7
		EnhancedInputComponent->BindAction(Hotkey7Action, ETriggerEvent::Triggered, this, &APlayerCharacter::Hotkey7);

		//Hotkey 8
		EnhancedInputComponent->BindAction(Hotkey8Action, ETriggerEvent::Triggered, this, &APlayerCharacter::Hotkey8);

		//Hotkey 9
		EnhancedInputComponent->BindAction(Hotkey9Action, ETriggerEvent::Triggered, this, &APlayerCharacter::Hotkey9);

		//Hotkey 0
		EnhancedInputComponent->BindAction(Hotkey0Action, ETriggerEvent::Triggered, this, &APlayerCharacter::Hotkey0);
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->TimeSince(InteractionData.LastInteractionCheckTime) > InteractionCheckFrequency)
	{
		PerformInteractionCheck();
	}

	//Update Vertical movement variables
	float CurrentVerticalVelocity = GetCharacterMovement()->Velocity.Z;

	if (bIsSprinting && GetWorld()->TimeSince(LastSprintExpTick) > 0.5f) {
		StatsComponent->AddSkillExp(ESkillName::Sprinting, 2.0f);
		LastSprintExpTick = GetWorld()->GetTimeSeconds();
	}

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
	
}

// Called when the player lands after jumping or falling
void APlayerCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	ExponFallHeight();
}

void APlayerCharacter::Jump()
{
	if (CanJump())
	{
		VaultStartHeight = GetActorLocation().Z;
		bIsVaulting = true;
	}

	Super::Jump();
}

void APlayerCharacter::Move(const FInputActionValue& Value)
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

void APlayerCharacter::Sprint(const FInputActionValue& Value)
{
	if (GetCharacterMovement())
	{
		if (OriginalWalkSpeed == 0.f)
		{
			OriginalWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
		}
		GetCharacterMovement()->MaxWalkSpeed = OriginalWalkSpeed * (14.4f);
		bIsSprinting = true;

	}
}

void APlayerCharacter::StopSprinting(const FInputActionValue& Value)
{
	if (GetCharacterMovement())
	{
		//reset maxwalkspeed to original speed
		GetCharacterMovement()->MaxWalkSpeed = OriginalWalkSpeed;
		//reset OriginalWalkspeed
		OriginalWalkSpeed = 0.f;
	}
	bIsSprinting = false;
}

void APlayerCharacter::Crouch(const FInputActionValue& Value)
{
}

void APlayerCharacter::OnCrouchHoldStart(const FInputActionValue& Value)
{
}

void APlayerCharacter::OnCrouchHoldComplete(const FInputActionValue& Value)
{
}

void APlayerCharacter::MiddleMouseScroll(const FInputActionValue& Value)
{
}

void APlayerCharacter::ToggleMenu(const FInputActionValue& Value)
{
	PlayerHUD->ToggleMenu();
}

void APlayerCharacter::Aim()
{
	if(!PlayerHUD->bIsMenusVisible)
	{
		SetIsAiming(true);
		bUseControllerRotationYaw = true;
		GetCharacterMovement()->MaxWalkSpeed /= 2.0f;
		PlayerHUD->ShowCrosshair();

		if (AdventureAimCameraTimeline)
			AdventureAimCameraTimeline->PlayFromStart();
	}
}

void APlayerCharacter::StopAiming()
{
	if(bAiming)
	{
		SetIsAiming(false);
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->MaxWalkSpeed *= 2.0f;
		PlayerHUD->HideCrosshair();

		if (AdventureAimCameraTimeline)
			AdventureAimCameraTimeline->Reverse();
	}
}

void APlayerCharacter::UpdateCameraTimeline(const float TimeLineValue) const
{
	const FVector CameraLocation = FMath::Lerp(DefaultCameraLocation, AdventureAimCameraLocation, TimeLineValue);
	CameraBoom->SocketOffset = CameraLocation;
}

void APlayerCharacter::CameraTimelineEnd()
{
	if (AdventureAimCameraTimeline)
	{
		if(AdventureAimCameraTimeline->GetPlaybackPosition() != 0.0f)
		{
			PlayerHUD->ShowCrosshair();
		}
	}
}

void APlayerCharacter::Holster(const FInputActionValue& Value)
{
	if (bIsHolstered == true)
	{
		SetbIsHolstered(false);
		MainHandSkeletalMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("attach_rhandSocket"));
		MainHandStaticMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("attach_rhandSocket"));
		OffHandSkeletalMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("attach_lhandSocket"));
		OffHandStaticMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("attach_lhandSocket"));
		PlayAnimMontage(UnHolsterAnimMontage);
	}
	else
	{
		SetbIsHolstered(true);
		MainHandSkeletalMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("spine_HolsterSocket_r"));
		MainHandStaticMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("spine_HolsterSocket_r"));
		OffHandSkeletalMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("spine_HolsterSocket_l"));
		OffHandStaticMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("spine_HolsterSocket_l"));
		PlayAnimMontage(HolsterAnimMontage);
	}
}

void APlayerCharacter::UseLeftHand(const FInputActionValue& Value)
{
}

void APlayerCharacter::OnLhandHoldStart(const FInputActionValue& Value)
{
}

void APlayerCharacter::OnLhandHoldComplete(const FInputActionValue& Value)
{
}

void APlayerCharacter::UseRightHand(const FInputActionValue& Value)
{
	if (Inventory->EquippedItems[EItemSlots::MainHand])
	{
		
	}
}

void APlayerCharacter::OnRhandHoldStart(const FInputActionValue& Value)
{
	if (Inventory->EquippedItems[EItemSlots::MainHand])
	{
		
	}
	else
	{
		Aim();
	}
}

void APlayerCharacter::OnRhandHoldComplete(const FInputActionValue& Value)
{
	if (IsAiming())
	{
		StopAiming();
	}
	
}

void APlayerCharacter::SwitchDominantHand(const FInputActionValue& Value)
{
}

void APlayerCharacter::CastLhandSpell(const FInputActionValue& Value)
{
	if (LeftHandSpell)
	{
		LeftHandSpell->CastSpell(this);
	}
}

void APlayerCharacter::OnLhandSpellHoldStart(const FInputActionValue& Value)
{
	if (LeftHandSpell)
	{
		LeftHandSpell->ChannelSpell(this);
	}
}

void APlayerCharacter::OnLhandSpellHoldComplete(const FInputActionValue& Value)
{
	if (LeftHandSpell)
	{
		LeftHandSpell->CastSpell(this);
	}
}

void APlayerCharacter::CastRhandSpell(const FInputActionValue& Value)
{
	if (RightHandSpell)
	{
		RightHandSpell->CastSpell(this);
	}
}

void APlayerCharacter::OnRhandSpellHoldStart(const FInputActionValue& Value)
{
	if (RightHandSpell)
	{
		RightHandSpell->ChannelSpell(this);
	}
}

void APlayerCharacter::OnRhandSpellHoldComplete(const FInputActionValue& Value)
{
	if (RightHandSpell)
	{
		RightHandSpell->CastSpell(this);
	}
}

void APlayerCharacter::ActivateToolbelt(const FInputActionValue& Value)
{
}

void APlayerCharacter::ToggleMap(const FInputActionValue& Value)
{
}

void APlayerCharacter::ToggleFlashlight(const FInputActionValue& Value)
{
}

void APlayerCharacter::ThrowThrowable(const FInputActionValue& Value)
{
}

void APlayerCharacter::OnThrowHoldStart(const FInputActionValue& Value)
{
}

void APlayerCharacter::OnThrowHoldComplete(const FInputActionValue& Value)
{
}

void APlayerCharacter::Hotkey1(const FInputActionValue& Value)
{
}

void APlayerCharacter::Hotkey2(const FInputActionValue& Value)
{
}

void APlayerCharacter::Hotkey3(const FInputActionValue& Value)
{
}

void APlayerCharacter::Hotkey4(const FInputActionValue& Value)
{
}

void APlayerCharacter::Hotkey5(const FInputActionValue& Value)
{
}

void APlayerCharacter::Hotkey6(const FInputActionValue& Value)
{
}

void APlayerCharacter::Hotkey7(const FInputActionValue& Value)
{
}

void APlayerCharacter::Hotkey8(const FInputActionValue& Value)
{
}

void APlayerCharacter::Hotkey9(const FInputActionValue& Value)
{
}

void APlayerCharacter::Hotkey0(const FInputActionValue& Value)
{
}

void APlayerCharacter::Look(const FInputActionValue& Value)
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

void APlayerCharacter::Reload(const FInputActionValue& Value)
{
}

void APlayerCharacter::DropItem(USPItem* ItemToDrop, const int32 QuantityToDrop)
{
	if (Inventory->FindMatchingItem(ItemToDrop))
	{
		//create parameters for pickup item
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.bNoFail = true;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		
		const FVector SpawnLocation{GetActorLocation() + (GetActorForwardVector() * 50.0f)};
		const FTransform SpawnTransform(GetActorRotation(), SpawnLocation);
		const int32 RemovedQuantity = Inventory->RemoveAmountOfItem(ItemToDrop, QuantityToDrop);

		//spawn pickup item
		APickupClass* Pickup = GetWorld()->SpawnActor<APickupClass>(APickupClass::StaticClass(), SpawnTransform, SpawnParams);

		//Set pickup item data and amount 
		Pickup->InitializeDrop(ItemToDrop, RemovedQuantity);
		UE_LOG(LogTemp, Display, TEXT("Dropped item was: {0}"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Item dropped was NULL:Z"));
	}
}

void APlayerCharacter::ExponVaultHeight()
{
	float VaultHeight = GetActorLocation().Z - VaultStartHeight;

	float ExperiencePoints = FMath::RoundToFloat(VaultHeight / 100.0f);

	StatsComponent->AddSkillExp(ESkillName::Vaulting, ExperiencePoints);
}

void APlayerCharacter::ExponFallHeight()
{
	float FallHeight = FallStartHeight - GetActorLocation().Z;

	float ExperiencePoints = FMath::RoundToFloat(FallHeight / 140.0f);

	StatsComponent->AddSkillExp(ESkillName::Vaulting, ExperiencePoints);
}

void APlayerCharacter::PerformInteractionCheck()
{
	InteractionData.LastInteractionCheckTime = GetWorld()->GetTimeSeconds();
	FVector TraceStart;
	if (!bAiming)
	{
		InteractionCheckDistance = 210.f;
		TraceStart = GetPawnViewLocation();
	}
	else
	{
		InteractionCheckDistance = 250.0f;
		TraceStart = FollowCamera->GetComponentLocation();
	}
	FVector TraceEnd{TraceStart + (GetViewRotation().Vector() * InteractionCheckDistance)};

	float LookDirection = FVector::DotProduct(GetActorForwardVector(), GetViewRotation().Vector());

	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Turquoise, false, 1.0f, 0, 2.0f);
	
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, QueryParams))
	{
		if (HitResult.GetActor()->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
		{
			//const float Distance = (TraceStart - HitResult.ImpactPoint).Size();

			if (HitResult.GetActor() != InteractionData.CurrentInteractor)
			{
				FoundInteractable(HitResult.GetActor());
				return;
			}

			if (HitResult.GetActor() == InteractionData.CurrentInteractor)
			{
				return;
			}
		}
		FVector2D NewPosition;
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			PlayerController->ProjectWorldLocationToScreen(HitResult.Location, NewPosition);
		}
		PlayerHUD->UpdateCrosshairLocation(NewPosition);
	}
	NoInteractableFound();
}

void APlayerCharacter::UpdateInteractionWidget() const
{
	if (IsValid(TargetInteractable.GetObject()))
	{
		PlayerHUD->UpdateInteractionMenu(&TargetInteractable->InteractableData);
	}
}

void APlayerCharacter::FoundInteractable(AActor* NewInteractable)
{
	if (IsInteracting())
	{
		InteractEnd();
	}

	if (InteractionData.CurrentInteractor)
	{
		TargetInteractable = InteractionData.CurrentInteractor;
		TargetInteractable->EndFocus();
	}

	InteractionData.CurrentInteractor = NewInteractable;
	TargetInteractable = NewInteractable;

	PlayerHUD->UpdateInteractionMenu(&TargetInteractable->InteractableData);

	TargetInteractable->BeginFocus();
}

void APlayerCharacter::NoInteractableFound()
{
	if (IsInteracting())
	{
		GetWorldTimerManager().ClearTimer(Th_Interaction);
	}

	if (InteractionData.CurrentInteractor)
	{
		if (IsValid(TargetInteractable.GetObject()))
		{
			TargetInteractable->EndFocus();
		}

		PlayerHUD->HideInteractionMenu();

		InteractionData.CurrentInteractor = nullptr;
		TargetInteractable = nullptr;
	}
}

void APlayerCharacter::InteractStart()
{
	PerformInteractionCheck();

	if (InteractionData.CurrentInteractor)
	{
		if (IsValid(TargetInteractable.GetObject()))
		{
			TargetInteractable->InteractStart();
			if (FMath::IsNearlyZero(TargetInteractable->InteractableData.InteractionDuration, 0.1f))
			{
				Interact();
			}
			else
			{
				GetWorldTimerManager().SetTimer(Th_Interaction, this, &APlayerCharacter::Interact, TargetInteractable->InteractableData.InteractionDuration, false);
			}
		}
	}
}

void APlayerCharacter::InteractEnd()
{
		GetWorldTimerManager().ClearTimer(Th_Interaction);
		if (IsValid(TargetInteractable.GetObject()))
		{
			TargetInteractable->InteractEnd();
		}
}

void APlayerCharacter::Interact()
{
	GetWorldTimerManager().ClearTimer(Th_Interaction);
	if (IsValid(TargetInteractable.GetObject()))
	{
		TargetInteractable->Interact(this);
	}
}
