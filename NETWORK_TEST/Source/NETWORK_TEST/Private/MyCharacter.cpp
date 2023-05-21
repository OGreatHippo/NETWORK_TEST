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

void AMyCharacter::XMove(const float XValue)
{
	AddMovementInput(GetActorRightVector() * XValue);
}

void AMyCharacter::ZMove(const float ZValue)
{
	AddMovementInput(GetActorForwardVector() * ZValue);
}

void AMyCharacter::Sprint()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	IsSprinting = true;
}

void AMyCharacter::StopSprinting()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	IsSprinting = false;
}

void AMyCharacter::StaminaResources(float DeltaTime)
{
	if(!IsSprinting)
	{
		if(CurrentStamina < MaxStamina)
		{
			CurrentStamina += StaminaRecharge * DeltaTime;
		}
		else
		{
			CurrentStamina = MaxStamina;
		}
	}
	
	else
	{
		if(CurrentStamina > 0 && CanSprint && GetCharacterMovement()->Velocity.Length() > 0)
		{
			CurrentStamina -= StaminaUsage * DeltaTime;
		}
		
		else
		{
			Exhausted = true;
			StopSprinting();
		}
	}

	if(Exhausted)
	{
		CanSprint = false;

		if(CurrentStamina >= (MaxStamina * 0.01) * ExhaustionThreshold)
		{
			Exhausted = false;
		}
	}
	else
	{
		CanSprint = true;
	}
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
}

