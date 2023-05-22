// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AMyCharacter::XMove(const float xValue)
{
	AddMovementInput(GetActorRightVector() * xValue);
}

void AMyCharacter::ZMove(const float zValue)
{
	AddMovementInput(GetActorForwardVector() * zValue);
}

void AMyCharacter::Sprint()
{
	GetCharacterMovement()->MaxWalkSpeed = sprintSpeed;
	isSprinting = true;
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Sprinting is %s"), (isSprinting ? "true" : "false")));
}

void AMyCharacter::StopSprinting()
{
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
	isSprinting = false;
}

void AMyCharacter::StaminaResources(float deltaTime)
{
	if(!isSprinting)
	{
		if(currentStamina < maxStamina)
		{
			currentStamina += staminaRecharge * deltaTime;
		}
		else
		{
			currentStamina = maxStamina;
		}
	}
	
	else
	{
		if(currentStamina > 0 && canSprint && GetCharacterMovement()->Velocity.Length() > 0)
		{
			currentStamina -= staminaUsage * deltaTime;
		}
		
		else
		{
			isExhausted = true;
			StopSprinting();
		}
	}

	if(isExhausted)
	{
		canSprint = false;

		if(currentStamina >= (maxStamina * 0.01) * exhaustionThreshold)
		{
			isExhausted = false;
		}
	}
	else
	{
		canSprint = true;
	}
}

void AMyCharacter::Crouch()
{
	GetCharacterMovement()->Crouch(true);
}

void AMyCharacter::StopCrouching()
{
	GetCharacterMovement()->UnCrouch(true);
}

void AMyCharacter::Heal(float healValue)
{
	if(currentHealth + healValue < maxHealth)
	{
		currentHealth += healValue;
		UE_LOG(LogTemp, Warning, TEXT("Heal Amount = %f"), healValue);
	}

	else
	{
		currentHealth = maxHealth;
	}
}

void AMyCharacter::TakeDamage(float damageValue)
{
	currentHealth -= damageValue;
}

float AMyCharacter::GetHealthPercentage()
{
	return currentHealth / 100;
}

float AMyCharacter::GetStaminaPercentage()
{
	return currentStamina / 100;
}

bool AMyCharacter::GetIsSprinting()
{
	return isSprinting;
}

float AMyCharacter::GetSpeed()
{
	return GetMovementComponent()->Velocity.Length();
}

//Test Functions

void AMyCharacter::TestHeal()
{
	currentHealth += 10;
}

void AMyCharacter::TestDamage()
{
	currentHealth -= 10;
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	StaminaResources(DeltaTime);
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	//Movement
	PlayerInputComponent->BindAxis(TEXT("XMove"), this, &AMyCharacter::XMove);
	PlayerInputComponent->BindAxis(TEXT("ZMove"), this, &AMyCharacter::ZMove);

	//Camera Movement
	PlayerInputComponent->BindAxis(TEXT("XLook"), this, &AMyCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("YLook"), this, &AMyCharacter::AddControllerPitchInput);

	//Actions
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AMyCharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &AMyCharacter::Sprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &AMyCharacter::StopSprinting);
	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Pressed, this, &AMyCharacter::Crouch);
	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Released, this, &AMyCharacter::StopCrouching);
	PlayerInputComponent->BindAction(TEXT("Heal"), IE_Pressed, this, &AMyCharacter::TestHeal);
	PlayerInputComponent->BindAction(TEXT("Damage"), IE_Pressed, this, &AMyCharacter::TestDamage);
}

