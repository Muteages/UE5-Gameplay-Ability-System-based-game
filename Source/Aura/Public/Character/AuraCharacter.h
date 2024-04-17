// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */

 //class UCameraComponent;
 //class USpringArmComponent;

UCLASS()
class AURA_API AAuraCharacter : public ACharacterBase
{
	GENERATED_BODY()
	
public:
	AAuraCharacter();
protected:
	virtual void BeginPlay();
private:
	
	//UPROPERTY(EditAnywhere, Category = "CameraComponent")
	//TObjectPtr<UCameraComponent> CameraComp;

	//UPROPERTY(EditAnywhere, Category = "CameraComponent")
	//TObjectPtr<USpringArmComponent> SpringArmComp;
};
