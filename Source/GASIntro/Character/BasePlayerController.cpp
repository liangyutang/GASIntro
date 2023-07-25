// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayerController.h"

#include "BaseCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "InputModifiers.h"


void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ABasePlayerController::Move(const FInputActionValue& Value)
{
	const FVector2d MovementVector=Value.Get<FVector2d>();
	MyPawn=GetPawn();
	if (MyPawn)
	{
		MyPawn->AddMovementInput(MyPawn->GetActorForwardVector(),MovementVector.X);
		MyPawn->AddMovementInput(MyPawn->GetActorRightVector(),MovementVector.Y);
	}
	
}

void ABasePlayerController::Look(const FInputActionValue& Value)
{
	const FVector2d LookVector=Value.Get<FVector2d>();
	MyPawn=GetPawn();
	if (MyPawn)
	{
		MyPawn->AddControllerYawInput(-LookVector.X);
		
		/*UE_LOG(LogTemp,Error,TEXT("%f"),GetDeprecatedInputPitchScale());*/
		//视角度数限定
		const float ViewAngle=LookVector.Y*GetDeprecatedInputPitchScale()+GetControlRotation().Pitch;
		/*if ((ViewAngle>300 && ViewAngle<=999) || (ViewAngle>=-999 && ViewAngle<=45))*/
		if (!(ViewAngle>45 && ViewAngle<300))
		{
			MyPawn->AddControllerPitchInput(LookVector.Y);
		}
	}
}

void ABasePlayerController::OnJump(const FInputActionValue& Value)
{
	if (ABaseCharacter* BaseCharacter=Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)))
	{
		BaseCharacter->Jump();
	}
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (const APlayerController* PlayerController=Cast<APlayerController>(this))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem=ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext,0);
		}
	}
	
	if (UEnhancedInputComponent* EnhancedInputComponent=CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		if (IA_Move)
		{
			EnhancedInputComponent->BindAction(IA_Move,ETriggerEvent::Triggered,this,&ABasePlayerController::Move);
		}
		if (IA_Jump)
		{
			EnhancedInputComponent->BindAction(IA_Jump,ETriggerEvent::Triggered,this,&ABasePlayerController::OnJump);
		}
		if (IA_Look)
		{
			EnhancedInputComponent->BindAction(IA_Look,ETriggerEvent::Triggered,this,&ABasePlayerController::Look);
		}
	}
}
