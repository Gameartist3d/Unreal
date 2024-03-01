// Copyright Epic Games, Inc. All Rights Reserved.
//3DNomad LLC

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "StatsComponent.h"
#include "InventoryComponent.h"
#include "Components/WidgetComponent.h"
#include "SPCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ASPCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/**UWidgetComponent*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Wiget, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* WidgetComponent;

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

	/**Menu Input Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MenuAction;

public:
	ASPCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Playuur", meta = (AllowPrivateAccess = "true"))
	class UInventoryComponent* PlayuurInventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Playuur")
	class UStatsComponent* PlayuurStatsComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	class USPAttackComponent* AttackComponent;

	UFUNCTION(BlueprintCallable, Category = "Items")
	void UseItem(class UBaseItem* Item);
	

protected:

	//Bool To Track when the Playuur has started to fall 
	bool bIsFalling;

	bool bIsSprinting;

	//variable to store vault start height
	float VaultStartHeight;

	//variable to store fall start height
	float FallStartHeight;

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

	void Sprint(const FInputActionValue& Value);
	void StopSprinting(const FInputActionValue& Value);

	void Crouch(const FInputActionValue& Value);
	void OnCrouchHoldStart(const FInputActionValue& Value);
	void OnCrouchHoldComplete(const FInputActionValue& Value);

	void Slide(class ACharacter& Character);

	void Interact(const FInputActionValue& Value);
	void OnInteractHoldStart(const FInputActionValue& Value);
	void OnInteractHoldComplete(const FInputActionValue& Value);

	void ToggleMenu(const FInputActionValue& Value);

	void UseLeftHand(const FInputActionValue& Value);
	void OnLhandHoldStart(const FInputActionValue& Value);
	void OnLhandHoldComplete(const FInputActionValue& Value);

	void UseRightHand(const FInputActionValue& Value);
	void OnRhandHoldStart(const FInputActionValue& Value);
	void OnRhandHoldComplete(const FInputActionValue& Value);

	
	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			

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

private:
	// Variable to store the Z location from the last frame
	float PreviousZloc;

	//Variable to check the playuur's velocity
	float PreviousVerticalVelocity = 0.0f;

	//Bool to check for jump peak
	bool bReachedJumpPeak = false;
};
