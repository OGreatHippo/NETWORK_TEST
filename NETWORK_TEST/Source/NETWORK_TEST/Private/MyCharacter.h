// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stamina")
	float CurrentStamina = 100.0f;
	
	// Sets default values for this character's properties
	AMyCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//Movement Speed Values
	float WalkSpeed = 1000.0f;
	float SprintSpeed = 2000.0f;

	//Stamina Values
	float MaxStamina = 100.0f;
	float StaminaUsage = 10.0f;
	float StaminaRecharge = 10.0f;

	//Percentage Stam before can sprint again
	int ExhaustionThreshold = 40;
    	
	bool IsMoving = false;
	bool CanSprint = false;
	bool IsSprinting = false;
	bool Exhausted = false;
    	
	//Movement Axis
	void XMove(const float XValue);
	void ZMove(const float ZValue);
    
	//Character Functions
	void Sprint();
	void StopSprinting();
	void StaminaResources(float DeltaTime);

};
