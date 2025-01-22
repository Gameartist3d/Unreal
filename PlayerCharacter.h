// Copyright Epic Games, Inc. All Rights Reserved.
//3DNomad LLC

#pragma once
// engine includes
#include "CoreMinimal.h"
#include "TimerManager.h"
// SP includes
#include "DefaultCharacter.h"
#include "SPPlayerController.h"
#include "PlayerStatsComponent.h"
#include "InteractionInterface.h"
#include "PlayerInventoryComponent.h"
#include "PlayerCharacter.generated.h"

class UTimelineComponent;
class APlayerHUD;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class USpringArmComponent;
class UCameraComponent;
class AOutfit;

//Enum for Hotkey Names
UENUM(BlueprintType)
enum class EHotKeySlot : uint8
{
	SpellLeftHand UMETA(DisplayName = "SpellLeftHand"),
	SpellRightHand UMETA(DisplayName = "SpellRightHand"),
	SpellPet UMETA(DisplayName = "SpellPet"),
	Toolbelt01 UMETA(DisplayName = "Toolbelt"),
	Toolbelt02 UMETA(DisplayName = "Toolbelt"),
	Toolbelt03 UMETA(DisplayName = "Toolbelt"),
	Toolbelt04 UMETA(DisplayName = "Toolbelt"),
	Toolbelt05 UMETA(DisplayName = "Toolbelt"),
	Toolbelt06 UMETA(DisplayName = "Toolbelt"),
	Hotkey01 UMETA(DisplayName = "Hotkey"),
	Hotkey02 UMETA(DisplayName = "Hotkey"),
	Hotkey03 UMETA(DisplayName = "Hotkey"),
	Hotkey04 UMETA(DisplayName = "Hotkey"),
	Hotkey05 UMETA(DisplayName = "Hotkey"),
	Hotkey06 UMETA(DisplayName = "Hotkey"),
	Hotkey07 UMETA(DisplayName = "Hotkey"),
	Hotkey08 UMETA(DisplayName = "Hotkey"),
	Hotkey09 UMETA(DisplayName = "Hotkey"),
	Hotkey00 UMETA(DisplayName = "Hotkey")
};

//Enum for Action AnimationMontage Names
UENUM(BlueprintType)
enum class EActionAnimationName : uint8
{
	Grab UMETA(DisplayName = "Grab"),
	Reload UMETA(DisplayName = "Reload"),
	Holster UMETA(DisplayName = "Holster"),
	UnarmedStrike UMETA(DisplayName = "UnarmedStrike"),
	SpellCast UMETA(DisplayName = "Spellcast"),
	UseProjectileWeapon UMETA(DisplayName = "UseProjectileWeapon"),
	UseMartialWeapon UMETA(DisplayName = "UseMartialWeapon"),
	Slide UMETA(DisplayName = "Slide"),
	ChangeStance UMETA(DisplayName = "ChangeStance"),
	Climb UMETA(DisplayName = "Climb"),
	Swim UMETA(DisplayName = "Swim"),
	Fall UMETA(DisplayName = "Fall"),
	Vault UMETA(DisplayName = "Vault"),
	Sit UMETA(DisplayName = "Sit"),
	Lounge UMETA(DisplayName = "Lounge"),
	Talk UMETA(DisplayName = "Talk"),
	Throw UMETA(DisplayName = "Throw"),
	Medical UMETA(DisplayName = "Medical"),
	Grapple UMETA(DisplayName = "Grapple"),
	Cover UMETA(DisplayName = "Cover"),
	Ride UMETA(DisplayName = "Ride"),
	Drive UMETA(DisplayName = "Drive")

};

/**
 * 
 */

UENUM(BlueprintType)
enum class EPlayerMode : uint8
{
	Adventure,
	Combat,
	Climbing,
	Dead
};

USTRUCT(BlueprintType)
struct FInteractionData
{
	GENERATED_BODY()

	FInteractionData() : CurrentInteractor(nullptr), LastInteractionCheckTime(0.0f)
	{

	};

	UPROPERTY()
	AActor* CurrentInteractor;

	UPROPERTY()
	float LastInteractionCheckTime;
};

UCLASS(config = Game)
class SPV1_API APlayerCharacter : public ADefaultCharacter
{
	GENERATED_BODY()

public:
	/*Variables*/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPlayerStatsComponent* StatsComponent;
	
	//player inventory component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPlayerInventoryComponent* Inventory;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	//Animation Montage for Holstering
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* HolsterAnimMontage;

	//Animation Montage for Un-Holstering
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* UnHolsterAnimMontage;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/**Sprint/parkour Input Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SprintAction;

	/**Crouch Input Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* CrouchAction;

	/**Left-Hand Input Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LhandAction;

	/**Right-Hand Input Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* RhandAction;

	/**Interact Input Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/* Middle Mouse Scroll Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MiddleMouseScrollAction;

	/**Menu Input Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MenuAction;

	/**Holster Input Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* HolsterAction;

	/**Reload Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ReloadAction;

	/**Switch Dominant Hand Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SwitchDominantHandAction;

	/**Left-Hand Spell Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LhandSpellAction;

	/**Right-Hand Spell Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* RhandSpellAction;

	/**Toolbelt Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ToolbeltAction;

	/**Toggle Map Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ToggleMapAction;

	/**Toggle Flashlight Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ToggleFlashlightAction;

	/**Throwable Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ThrowableAction;

	/**Hotkey 1 Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Hotkey1Action;

	/**Hotkey 2 Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Hotkey2Action;

	/**Hotkey 3 Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Hotkey3Action;

	/**Hotkey 4 Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Hotkey4Action;

	/**Hotkey 5 Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Hotkey5Action;

	/**Hotkey 6 Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Hotkey6Action;

	/**Hotkey 7 Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Hotkey7Action;

	/**Hotkey 8 Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Hotkey8Action;

	/**Hotkey 9 Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Hotkey9Action;

	/**Hotkey 0 Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Hotkey0Action;

	//Bool To Track when the Playuur has started to fall
	UPROPERTY(VisibleAnywhere)
	bool bIsFalling = false;

	//Bool to Track when the Playuur is sprinting
	UPROPERTY(VisibleAnywhere)
	bool bIsSprinting = false;

	//Bool to Track when the Playurr is sliding
	UPROPERTY(VisibleAnywhere)
	bool bIsSliding = false;

	//Bool to Track when the Playuur is climbing
	UPROPERTY(VisibleAnywhere)
	bool bIsClimbing = false;

	//Bool to Track when the Playuur is vaulting
	UPROPERTY(VisibleAnywhere)
	bool bIsVaulting = false;

	//Bool to Track which hand is dominant
	UPROPERTY(VisibleAnywhere)
	bool bIsLhandDominant = false;

	//Bool to Track if the Left hand is guarding
	UPROPERTY(VisibleAnywhere)
	bool bIsLhandGuarding = false;

	//Bool to Track if the Right hand is guarding
	UPROPERTY(VisibleAnywhere)
	bool bIsRhandGuarding = false;

	//Bool to Track if the character is busy
	UPROPERTY(VisibleAnywhere)
	bool bIsCharacterBusy = false;

	/*Functions*/

	APlayerCharacter();

	void UpdateInteractionWidget() const;
	
	FORCEINLINE bool IsInteracting() const { return GetWorldTimerManager().IsTimerActive(Th_Interaction); };

	UFUNCTION(BlueprintCallable, Category = "Character")
	FORCEINLINE bool IsHolstered() const { return bIsHolstered;};

	UFUNCTION(BlueprintCallable, Category = "Character")
	FORCEINLINE void SetbIsHolstered(const bool IsHolstered) {bIsHolstered = IsHolstered;};

	//Getter for MainHand Skeletal Mesh
	UFUNCTION(BlueprintCallable, Category = "Mesh")
	FORCEINLINE USkeletalMeshComponent* GetMainHandSkeletalMeshComponent() const {return MainHandSkeletalMesh;}

	//Setter for MainHand Skeletal Mesh
	UFUNCTION(BlueprintCallable, Category = "Mesh")
	FORCEINLINE void SetMainHandSkeletalMesh(USkeletalMesh* NewSkeletalMesh) {MainHandSkeletalMesh->SetSkeletalMesh(NewSkeletalMesh);};

	//Setter for MainHand Skeletal Mesh visibility
	UFUNCTION(BlueprintCallable, Category = "Mesh")
	FORCEINLINE void SetMainHandSkeletalMVisibility(const bool NewVisibility) {MainHandSkeletalMesh->SetVisibility(NewVisibility);};

	//Getter for OffHand Skeletal Mesh
	UFUNCTION(BlueprintCallable, Category = "Mesh")
	FORCEINLINE USkeletalMeshComponent* GetOffHandSkeletalMeshComponent() const {return OffHandSkeletalMesh;}

	//Setter for OffHand Skeletal Mesh
	UFUNCTION(BlueprintCallable, Category = "Mesh")
	FORCEINLINE void SetOffHandSkeletalMesh(USkeletalMesh* NewSkeletalMesh) {OffHandSkeletalMesh->SetSkeletalMesh(NewSkeletalMesh);};

	//Setter for OffHand Skeletal Mesh visibility
	UFUNCTION(BlueprintCallable, Category = "Mesh")
	FORCEINLINE void SetOffHandSkeletalMVisibility(const bool NewVisibility) {OffHandSkeletalMesh->SetVisibility(NewVisibility);};

	//Getter for MainHand Static Mesh
	UFUNCTION(BlueprintCallable, Category = "Mesh")
	FORCEINLINE UStaticMeshComponent* GetMainHandStaticMeshComponent() const {return MainHandStaticMesh;}

	//Setter for MainHand Static Mesh
	UFUNCTION(BlueprintCallable, Category = "Mesh")
	FORCEINLINE void SetMainHandStaticMesh(UStaticMesh* NewStaticMesh) {MainHandStaticMesh->SetStaticMesh(NewStaticMesh);};

	//Setter for MainHand Static Mesh visibility
	UFUNCTION(BlueprintCallable, Category = "Mesh")
	FORCEINLINE void SetMainHandStaticMVisibility(const bool NewVisibility) {MainHandStaticMesh->SetVisibility(NewVisibility);};

	//Getter for OffHand Static Mesh
	UFUNCTION(BlueprintCallable, Category = "Mesh")
	FORCEINLINE UStaticMeshComponent* GetOffHandStaticMeshComponent() const {return OffHandStaticMesh;}

	//Setter for OffHand Static Mesh
	UFUNCTION(BlueprintCallable, Category = "Mesh")
	FORCEINLINE void SetOffHandStaticMesh(UStaticMesh* NewStaticMesh) {OffHandStaticMesh->SetStaticMesh(NewStaticMesh);};

	//Setter for OffHand Static Mesh visibility
	UFUNCTION(BlueprintCallable, Category = "Mesh")
	FORCEINLINE void SetOffHandStaticMVisibility(const bool NewVisibility) {OffHandStaticMesh->SetVisibility(NewVisibility);};

	//Getter for Throwable Static Mesh
	UFUNCTION(BlueprintCallable, Category = "Mesh")
	FORCEINLINE UStaticMeshComponent* GetThrowableStaticMeshComponent() const {return ThrowableStaticMesh;}

	//Setter for Throwable Static Mesh
	UFUNCTION(BlueprintCallable, Category = "Mesh")
	FORCEINLINE void SetThrowableStaticMesh(UStaticMesh* NewStaticMesh) {ThrowableStaticMesh->SetStaticMesh(NewStaticMesh);};

	//Setter for Throwable Static Mesh visibility
	UFUNCTION(BlueprintCallable, Category = "Mesh")
	FORCEINLINE void SetThrowableStaticMVisibility(const bool NewVisibility) {ThrowableStaticMesh->SetVisibility(NewVisibility);};

	//Getter for bAiming
	UFUNCTION(BlueprintCallable, Category = "Character")
	FORCEINLINE bool IsAiming() const {return bAiming;};

	//Setter for bAiming
	UFUNCTION(BlueprintCallable, Category = "Character")
	FORCEINLINE void SetIsAiming(const bool NewIsAiming) {bAiming = NewIsAiming;};

	//Getter for bIsMainHandEquipped
	UFUNCTION(BlueprintCallable, Category = "Character")
	FORCEINLINE bool IsMainHandEquipped() const {return bIsMainHandEquipped;};

	//Setter for bIsMainHandEquipped
	UFUNCTION(BlueprintCallable, Category = "Character")
	FORCEINLINE void SetIsMainHandEquipped(const bool NewIsMainHandEquipped) {bIsMainHandEquipped = NewIsMainHandEquipped;};

	//Getter for bIsOffHandEquipped
	UFUNCTION(BlueprintCallable, Category = "Character")
	FORCEINLINE bool IsOffHandEquipped() const {return bIsOffHandEquipped;};

	//Setter for bIsOffHandEquipped
	UFUNCTION(BlueprintCallable, Category = "Character")
	FORCEINLINE void SetIsOffHandEquipped(const bool NewIsOffHandEquipped) {bIsOffHandEquipped = NewIsOffHandEquipped;};

	//Getter for bIsThrowableEquipped
	UFUNCTION(BlueprintCallable, Category = "Character")
	FORCEINLINE bool IsThrowableEquipped() const {return bIsThrowableEquipped;};

	//Setter for bIsThrowableEquipped
	UFUNCTION(BlueprintCallable, Category = "Character")
	FORCEINLINE void SetIsThrowableEquipped(const bool NewIsThrowableEquipped) {bIsThrowableEquipped = NewIsThrowableEquipped;};

	FORCEINLINE UPlayerInventoryComponent* GetInventory() const { return Inventory; };

	void DropItem(USPItem* ItemToDrop, const int32 QuantityToDrop);

	/*Overrides*/

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Overrides the jump functionality
	virtual void Jump() override;

	void Sprint(const FInputActionValue& Value);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
protected:
	/*Variables*/

	UPROPERTY()
	APlayerHUD* PlayerHUD;

	//MainHand Static Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	UStaticMeshComponent* MainHandStaticMesh;

	//MainHand Skeletal Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	USkeletalMeshComponent* MainHandSkeletalMesh;

	//OffHand Static Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	UStaticMeshComponent* OffHandStaticMesh = nullptr;

	//OffHand Skeletal Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TObjectPtr<USkeletalMeshComponent> OffHandSkeletalMesh = nullptr;

	//Throwable Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TObjectPtr<UStaticMeshComponent> ThrowableStaticMesh = nullptr;

	//Pet Actor
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TObjectPtr<AActor> PetActor = nullptr;

	//Left Hand Spell
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TObjectPtr<USpell> LeftHandSpell = nullptr;

	//Right Hand Spell
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TObjectPtr<USpell> RightHandSpell = nullptr;

	//bool to check if the player can interact
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	bool bCanInteract = true;

	//OriginalMaxWalkSpeed variable to preserve original walk speed during calculations
	float OriginalWalkSpeed = 0.0f;

	//Outfit component
	UPROPERTY(VisibleAnywhere, Category = "Outfit")
	AOutfit* Outfit;

	//variable to store vault start height
	float VaultStartHeight = 0.0f;

	//variable to store fall start height
	float FallStartHeight = 0.0f;

	//Time handle for tracking sprint time
	float SprintTimeStart = 0.0f;

	//float for the length of time channeled for the left hand
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spell")
	float LhChannelHoldTime = 0.0f;

	//float for the length of time channeled for the right hand
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spell")
	float RhChannelHoldTime = 0.0f;

	//Trace distance for viewport cursor
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Viewport")
	float TraceDistance = 1000.0f;

	//float to track the last time sprint exp was gained
	float LastSprintExpTick = 0.0f;

	UPROPERTY(VisibleAnywhere, Category = "Interaction")
	TScriptInterface<IInteractionInterface> TargetInteractable;

	//Distance to check for interactions
	UPROPERTY(VisibleAnywhere, Category = "Interaction")
	float InteractionCheckDistance = 280.0f;

	float InteractionCheckFrequency = 0.1f;

	FInteractionData InteractionData;

	FTimerHandle Th_Interaction;

	//timeline properties used for camera aiming transition
	UPROPERTY(VisibleAnywhere, Category = "Character | Camera")
	FVector DefaultCameraLocation;
	UPROPERTY(VisibleAnywhere, Category = "Character | Camera")
	FVector AdventureAimCameraLocation;
	UPROPERTY(VisibleAnywhere, Category = "Character | Camera")
	FVector CombatAimCameraLocation;
	UPROPERTY(VisibleAnywhere, Category = "Character | Camera")
	FVector ClimbingAimCameraLocation;

	TObjectPtr<UTimelineComponent> AdventureAimCameraTimeline;

	UPROPERTY(EditDefaultsOnly, Category= "Character | AimTimeline")
	UCurveFloat* AdvAimCameraCurve;

	//Enum for setting the Player Mode
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayuurMode")
	EPlayerMode PlayerMode = EPlayerMode::Adventure;

	//TMap of EActionAnimationName and animation montages for action animations
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	TMap<EActionAnimationName, UAnimMontage*> ActionAnimations;

	//TMap of slots and equipped abilities
	UPROPERTY()
	TMap<EHotKeySlot, TObjectPtr<UObject>> EquippedHotkeys;

	//Bool to Track if the character has holstered their weapon
	UPROPERTY(VisibleAnywhere, Category = "Character")
	bool bIsHolstered = true;

	//bool for relating when the Player Character has started aiming
	UPROPERTY(VisibleAnywhere, Category = "Character")
	bool bAiming = false;

	//bool to track if the player is channeling with the LeftHand
	UPROPERTY(VisibleAnywhere, Category = "Spell")
	bool bIsLhChanneling = false;

	//bool to track if the player is casting with the LeftHand
	UPROPERTY(VisibleAnywhere, Category = "Spell")
	bool bIsLhCasting = false;

	//bool to track if the player is channeling with the RightHand
	UPROPERTY(VisibleAnywhere, Category = "Spell")
	bool bIsRhChanneling = false;

	//bool to track if the player is casting with the RightHand
	UPROPERTY(VisibleAnywhere, Category = "Spell")
	bool bIsRhCasting = false;

	/*Functions*/

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	//Input Function to handle Sprinting
	void StopSprinting(const FInputActionValue& Value);

	//Input Function to handle Crouching, there is an additional function to handle the hold start and hold complete
	void Crouch(const FInputActionValue& Value);
	void OnCrouchHoldStart(const FInputActionValue& Value);
	void OnCrouchHoldComplete(const FInputActionValue& Value);

	//Function to handle middle mouse scrolling
	void MiddleMouseScroll(const FInputActionValue& Value);

	//Input Function to handle Menu toggling
	void ToggleMenu(const FInputActionValue& Value);

	void Aim();
	void StopAiming();
	UFUNCTION()
	void UpdateCameraTimeline(float TimeLineValue) const;
	UFUNCTION()
	void CameraTimelineEnd();

	//Input Function to handle Holstering weapons/switching to Combat mode
	void Holster(const FInputActionValue& Value);

	//Input Function to handle using the left hand and additionally, there are functions to handle the hold start and hold complete actions
	void UseLeftHand(const FInputActionValue& Value);
	void OnLhandHoldStart(const FInputActionValue& Value);
	void OnLhandHoldComplete(const FInputActionValue& Value);

	//Input Function to handle using the right hand and additionally, there are functions to handle the hold start and hold complete actions
	void UseRightHand(const FInputActionValue& Value);
	void OnRhandHoldStart(const FInputActionValue& Value);
	void OnRhandHoldComplete(const FInputActionValue& Value);

	//Input Function to handle switching the dominant hand
	void SwitchDominantHand(const FInputActionValue& Value);

	//Input Function for casting Left hand spell and aditionally, there are functions to handle the spell hold start and hold complete actions
	void CastLhandSpell(const FInputActionValue& Value);
	void OnLhandSpellHoldStart(const FInputActionValue& Value);
	void OnLhandSpellHoldComplete(const FInputActionValue& Value);

	//Input Function for casting Right hand spell and aditionally, there are functions to handle the spell hold start and hold complete actions
	void CastRhandSpell(const FInputActionValue& Value);
	void OnRhandSpellHoldStart(const FInputActionValue& Value);
	void OnRhandSpellHoldComplete(const FInputActionValue& Value);

	//Input Function to Activate Toolbelt
	void ActivateToolbelt(const FInputActionValue& Value);

	//Input Function to toggle the Map
	void ToggleMap(const FInputActionValue& Value);

	//Input Function to Toggle the Flashlight
	void ToggleFlashlight(const FInputActionValue& Value);

	//Input Function to Throw Throwable or by holding, to cook the throwable and aim
	void ThrowThrowable(const FInputActionValue& Value);
	void OnThrowHoldStart(const FInputActionValue& Value);
	void OnThrowHoldComplete(const FInputActionValue& Value);

	//Input Function to handle Hotkey 1
	void Hotkey1(const FInputActionValue& Value);

	//Input Function to handle Hotkey 2
	void Hotkey2(const FInputActionValue& Value);

	//Input Function to handle Hotkey 3
	void Hotkey3(const FInputActionValue& Value);

	//Input Function to handle Hotkey 4
	void Hotkey4(const FInputActionValue& Value);

	//Input Function to handle Hotkey 5
	void Hotkey5(const FInputActionValue& Value);

	//Input Function to handle Hotkey 6
	void Hotkey6(const FInputActionValue& Value);

	//Input Function to handle Hotkey 7
	void Hotkey7(const FInputActionValue& Value);

	//Input Function to handle Hotkey 8
	void Hotkey8(const FInputActionValue& Value);

	//Input Function to handle Hotkey 9
	void Hotkey9(const FInputActionValue& Value);

	//Input Function to handle Hotkey 0
	void Hotkey0(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	//Input Function to handle Reloading
	void Reload(const FInputActionValue& Value);

	//function to calculate and grant exp based on vault height
	void ExponVaultHeight();

	//function to calculate and grant exp based on fall height
	void ExponFallHeight();

	void PerformInteractionCheck();
	void FoundInteractable(AActor* NewInteractable);
	void NoInteractableFound();
	void InteractStart();
	void InteractEnd();
	void Interact();

	/*Overrides*/

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//override the landing event
	virtual void Landed(const FHitResult& Hit) override;

private:

	/*Variables*/

	// Variable to store the Z location from the last frame
	float PreviousZloc = 0.0f;

	//Variable to check the player's velocity
	float PreviousVerticalVelocity = 0.0f;

	//Bool to check for jump peak
	bool bReachedJumpPeak = false;

	//Bool for checking if the cursor is on an actor
	bool bCursorOnActor = false;

	//Timer for Interaction Widget Removal
	FTimerHandle InteractionWidgetTimer;
	
	//Pointer to the player controller
	ASPPlayerController* PlayerControllerInst;

};
