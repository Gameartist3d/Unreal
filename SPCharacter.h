// Copyright Epic Games, Inc. All Rights Reserved.
//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "StatsComponent.h"
#include "InventoryComponent.h"
#include "SPCrosshairWidget.h"
#include "Engine/Engine.h"
#include "InteractionComponent.h"
#include "SPSpell.h"
#include "WeaponItem.h"
#include "Components/WidgetComponent.h"
#include "SPCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UENUM(BlueprintType)
enum class EPlayuurMode : uint8
{
	Adventure,
	Combat,
	Climbing,
	Dead
};

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config = Game)
class ASPCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	// Skeletal mesh component for the first weapon mesh
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* FirstWeaponMeshComponent;

	// Skeletal mesh component for the second weapon mesh
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* SecondWeaponMeshComponent;

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

public:
	ASPCharacter();

	/**UWidgetComponent*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Widget)
	UWidgetComponent* InventoryWidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	UInteractionComponent* FocusedInteractionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Playuur", meta = (AllowPrivateAccess = "true"))
	class UInventoryComponent* PlayuurInventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Playuur")
	class UStatsComponent* PlayuurStatsComponent;

	//Reload Anim Montage
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	UAnimMontage* ReloadAnimMontage;

	//Enum for setting the Playuur Mode
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayuurMode")
	EPlayuurMode PlayuurMode;

	// widget class for the interaction
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	TSubclassOf<UInteractionMenuWidget> InteractionMenuWidgetClass;

	//Function for using Items
	UFUNCTION(BlueprintCallable, Category = "Items")
	void UseItem(class ASPBaseItem* Item);

	//Function for Unarmed Striking
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void UnarmedStrike(FString strikinghand);

	//Function for picking up items
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void PickupItem(class ASPBaseItem* item);

	//Function for equipping picked up item
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void EquipWeaponItem(class AWeaponItem* item);

	//Function for stealing an item
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void StealItem(class ASPBaseItem* item);

	//Function for updating the crosshair widget on the playuur controller
	UFUNCTION(BlueprintCallable, Category = "Crosshair")
	void UpdateCrosshairWidget(FName crosshairname);


	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Crosshair")
	FVector2D CrosshairScreenLocation;*/


protected:

	//Bool To Track when the Playuur has started to fall 
	bool bIsFalling;

	//Bool to Track when the Playuur is sprinting
	bool bIsSprinting;

	//Bool to Track when the Playurr is sliding
	bool bIsSliding;

	//Bool to Track when the Playuur is climbing
	bool bIsClimbing;

	//Bool to Track when the Playuur is vaulting
	bool bIsVaulting;

	//Bool to Track which hand is dominant
	bool bIsLhandDominant;

	//variable to store vault start height
	float VaultStartHeight;

	//variable to store fall start height
	float FallStartHeight;

	//Bool to Track if the Left hand is guarding
	bool bIsLhandGuarding;

	//Bool to Track if the Right hand is guarding
	bool bIsRhandGuarding;

	//Fvector to store Combat Camera boom Socket offset location
	FVector CombatCameraBoomOffset;

	//Fvector to store Adventure Camera boom Socket offset location
	FVector AdventureCameraBoomOffset;

	//FVector to store Combat Camera boom socket offset location for left hand dominant
	FVector LHandCombatCameraBoomOffset;

	//FVector to store Adventure Camera boom socket offset location for left hand dominant
	FVector LHandAdventureCameraBoomOffset;

	//OriginalMaxWalkSpeed variable to preserve original walkspeed during calculations
	float OriginalWalkSpeed;

	//Time handle for tracking sprint time
	float SprintTimeStart = 0.0f;

	//function to calculate and grant exp based on vault height
	void ExponVaultHeight();

	//function to calculate and grant exp based on fall height
	void ExponFallHeight();

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	//Input Function to handle Sprinting
	void Sprint(const FInputActionValue& Value);
	void StopSprinting(const FInputActionValue& Value);

	//Input Function to handle Crouching, there is an additional function to handle the hold start and hold complete
	void Crouch(const FInputActionValue& Value);
	void OnCrouchHoldStart(const FInputActionValue& Value);
	void OnCrouchHoldComplete(const FInputActionValue& Value);

	//Function to handle middle mouse scolling
	void MiddleMouseScroll(const FInputActionValue& Value);

	//Function to handle Sliding
	void Slide();

	//Input Function to handle Interacting with objects, there is an additional function to handle the hold start and hold complete actions
	void Interact(const FInputActionValue& Value);
	void OnInteractHoldStart(const FInputActionValue& Value);
	void OnInteractHoldComplete(const FInputActionValue& Value);

	//Input Function to handle Menu toggling
	void ToggleMenu(const FInputActionValue& Value);

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

	//Function to handle combing the left and right hand actions
	void CombineHandActions();

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

	//Function to handle Combining Spells when both hand spells are being held
	void CombineHandSpells(USPSpell lhandspell, USPSpell rhandspell);

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

	//Trace distance for viewport cursor
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Viewport")
	float TraceDistance;


protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay();
	virtual void Tick(float DeltaTime) override;

	//override the landing event
	virtual void Landed(const FHitResult& Hit) override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	virtual void Jump() override;

	//Function to handle the Playuur's death
	void Death();

private:
	// Variable to store the Z location from the last frame
	float PreviousZloc;

	//Variable to check the playuur's velocity
	float PreviousVerticalVelocity = 0.0f;

	//Bool to check for jump peak
	bool bReachedJumpPeak = false;
};

