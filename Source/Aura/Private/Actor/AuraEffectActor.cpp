// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"


#include "Components/SphereComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	SphereComp = CreateDefaultSubobject<USphereComponent>("Sphere");
	SphereComp->SetupAttachment(GetRootComponent());

}

void AAuraEffectActor::OnBeginOverlap(UPrimitiveComponent* OverlappedCoomponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IAbilitySystemInterface* Interface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UAuraAttributeSet* AttributeSet = Cast<UAuraAttributeSet>(Interface->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass()));
		//TODO: Warning, this is a hack way to modify the properties by removing const
		UAuraAttributeSet* MutableAttributeSet = const_cast<UAuraAttributeSet*>(AttributeSet);
		MutableAttributeSet->SetHealth(AttributeSet->GetHealth() + 20.f);
	}
}

void AAuraEffectActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//if (IAbilitySystemInterface* Interface = Cast<IAbilitySystemInterface>(OtherActor))
	//{
	//	const UAuraAttributeSet* AttributeSet = Cast<UAuraAttributeSet>(Interface->GetAbilitySystemComponent()->GetAttributeSet(UAuraAttributeSet::StaticClass()));
	//	UAuraAttributeSet* MutableAttributeSet = const_cast<UAuraAttributeSet*>(AttributeSet);
	//	MutableAttributeSet->SetHealth(AttributeSet->GetHealth() - 20.f);
	//}
}


void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
	// Bind call back function
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::OnBeginOverlap);
	SphereComp->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::OnEndOverlap);
}

