// Copyright Epic Games, Inc. All Rights Reserved.
//3DNomad LLC

#include "SPCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "BaseItem.h"

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

	//Create a widgetcomponent
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Menu Widget"));
	WidgetComponent->SetupAttachment(RootComponent);
	WidgetComponent->SetWidgetSpace(EWidgetSpace::World);
	WidgetComponent->SetDrawSize(FVector2D(192, 108));
	WidgetComponent->SetRelativeLocation(FVector(0, 0, 0));
	WidgetComponent->SetRelativeRotation(FRotator(0, 0, 0));

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	PlayuurStatsComponent = CreateDefaultSubobject<UStatsComponent>("Playuur Stats");
	PlayuurInventoryComponent = CreateDefaultSubobject<UInventoryComponent>("Playuur Inventory");
	PlayuurInventoryComponent->InventoryCapacity = 100;
	AttackComponent = CreateDefaultSubobject<USPAttackComponent>("PlayuurAttackComponent");

}

void ASPCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
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
}

//////////////////////////////////////////////////////////////////////////
// Input

void ASPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASPCharacter::Move);

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
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ASPCharacter::UseItem(UBaseItem* Item)
{
	if (Item) {
		Item->Use(this);
		Item->OnUse(this); //BP version
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

void ASPCharacter::Slide()
{

}

void ASPCharacter::Interact(const FInputActionValue& Value)
{

}

void ASPCharacter::OnInteractHoldStart(const FInputActionValue& Value)
{

}

void ASPCharacter::OnInteractHoldComplete(const FInputActionValue& Value)
{

}

void ASPCharacter::UseLeftHand(const FInputActionValue& Value)
{

}

void ASPCharacter::OnLhandHoldStart(const FInputActionValue& Value)
{

}

void ASPCharacter::OnLhandHoldComplete(const FInputActionValue& Value)
{

}

void ASPCharacter::UseRightHand(const FInputActionValue& Value)
{

}

void ASPCharacter::OnRhandHoldStart(const FInputActionValue& Value)
{

}

void ASPCharacter::OnRhandHoldComplete(const FInputActionValue& Value)
{

}

void ASPCharacter::ToggleMenu(const FInputActionValue& Value)
{

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
