// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class GASINTRO_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)
	APawn* MyPawn;
	
protected:
	virtual void BeginPlay() override;
	
	void Move(const FInputActionValue &Value);

	void Look(const FInputActionValue &Value);

	void OnJump(const FInputActionValue &Value);
	
public:
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Input|Context",meta=(AllowPrivateAccess="true"))
	const UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Input|Action",meta=(AllowPrivateAccess="true"))
	UInputAction* IA_Move;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Input|Action",meta=(AllowPrivateAccess="true"))
	UInputAction* IA_Jump;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Input|Action",meta=(AllowPrivateAccess="true"))
	UInputAction* IA_Look;
};
