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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	float currentHealth = 100.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stamina")
	float currentStamina = 100.0f;
	
	// Sets default values for this character's properties
	AMyCharacter();

	// Called every frame
	virtual void Tick(float deltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//HUD
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercentage();
	UFUNCTION(BlueprintPure, Category = "Stamina")
	float GetStaminaPercentage();

	//Animations
	UFUNCTION(BlueprintPure, Category = "Speed")
	bool GetIsSprinting();
	UFUNCTION(BlueprintPure, Category = "Speed")
	float GetSpeed();

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//Movement Speed Values
	float walkSpeed = 1000.0f;
	float sprintSpeed = 2000.0f;

	//Stamina Values
	
	float maxStamina = 100.0f;
	float staminaUsage = 10.0f;
	float staminaRecharge = 10.0f;
	float staminaPercent;
	
	//Percentage Stam before can sprint again
	int exhaustionThreshold = 40;
	
	bool canSprint = false;
	bool isSprinting = false;
	bool isExhausted = false;

	//Health
	
	float maxHealth = 100.0f;
	float healthPercent;
	
	
	//Movement Axis
	void XMove(const float xValue);
	void ZMove(const float zValue);
    
	//Character Functions
	void Sprint();
	void StopSprinting();
	void StaminaResources(float deltaTime);
	void Crouch();
	void StopCrouching();
	void Heal(float healValue);
	void TakeDamage(float damageValue);
	
	//Test Functions
	void TestHeal();
	void TestDamage();
};
