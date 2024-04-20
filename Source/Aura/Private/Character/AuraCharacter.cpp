// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerState.h"
//#include "GameFramework/SpringArmComponent.h"
//#include "Camera/CameraComponent.h"


AAuraCharacter::AAuraCharacter()
{

	//SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	//SpringArmComp->bUsePawnControlRotation = false;
	//SpringArmComp->SetupAttachment(RootComponent);


	//CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	//CameraComp->SetupAttachment(SpringArmComp);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 300.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true; // Force the character to move at the plane
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AAuraCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Init for the server
void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitPlayerState();
}

// Init for the client
void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitPlayerState();
}

// Init ASC and AS from player state
void AAuraCharacter::InitPlayerState()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AbilitySystemComp = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();
	AbilitySystemComp->InitAbilityActorInfo(AuraPlayerState, this);
}
