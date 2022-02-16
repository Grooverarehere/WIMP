// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "WIMPProjectile.h"
#include "WIMPBattleDroid.generated.h"

UCLASS()
class WIMP_API AWIMPBattleDroid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWIMPBattleDroid();

	UPROPERTY()
		class USceneComponent* SceneRoot;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Jet_Front;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Jet_Front_Right;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Jet_Front_Left;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Jet_Back;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Jet_Back_Right;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Jet_Back_Left;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UParticleSystemComponent* PS_Jet_Front;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UParticleSystemComponent* PS_Jet_Front_Right;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UParticleSystemComponent* PS_Jet_Front_Left;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UParticleSystemComponent* PS_Jet_Back;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UParticleSystemComponent* PS_Jet_Back_Right;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UParticleSystemComponent* PS_Jet_Back_Left;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UParticleSystemComponent* PS_Tesla_Top;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UParticleSystemComponent* PS_Tesla_Bottom;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UParticleSystemComponent* PS_Tesla_Back;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UParticleSystemComponent* PS_Tesla_Right;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UParticleSystemComponent* PS_Tesla_Left;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UParticleSystemComponent* PS_Lighting;
	UPROPERTY(EditAnywhere)
		float RateCharge;
protected:
	FTimerHandle LaunchHandle;
	FTimerHandle ChargeHandle;
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AWIMPProjectile> ProjectileClass;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Charge();
	void LaunchProjectile();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
