// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Containers/Array.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "WIMPActivateDoor.generated.h"

UCLASS()
class WIMP_API AWIMPActivateDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWIMPActivateDoor();
	UPROPERTY()
		class USceneComponent* SceneRoot;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* ActivatorCollision;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* SM_Laser_1;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* SM_Laser_2;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		UParticleSystem* PS_Laser;
	UPROPERTY(EditAnywhere)
		bool Active;
	TArray<UParticleSystemComponent*>LaserArray;
protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ActivateActivator();
};
