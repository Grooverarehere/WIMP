// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "WIMPScoutDroid.generated.h"

UENUM(BlueprintType)
enum class MovementType : uint8 {
	UP_START = 0 UMETA(DisplayName = "UP_START"),
	UP_END = 1 UMETA(DisplayName ="UP_END"),
	SLIDE_START = 2  UMETA(DisplayName = "SLIDE_START"),
	SLIDE_END = 3 UMETA(DisplayName = "SLIDE_END"),
	FRONT_START = 4 UMETA(DisplayName = "FRONT_START"),
	FRONT_END = 5 UMETA(DisplayName = "FRONT_END")

};

UENUM(BlueprintType)
enum class DroidType : uint8 {
	THREE_MOVEMENT = 0 UMETA(DisplayName = "THREE_MOVEMENT"),
	SLIDE_MOVEMENT = 1 UMETA(DisplayName = "SLIDE_MOVEMENT"),
	UP_MOVEMENT = 2 UMETA(DisplayName = "UP_MOVEMENT")
};

UCLASS()
class WIMP_API AWIMPScoutDroid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWIMPScoutDroid();

	UPROPERTY()
		class USceneComponent* SceneRoot;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Light;
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
		float Distance;
	UPROPERTY(EditAnywhere)
		UCurveFloat* MovementTimelineCurve;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* DroidDetection;
	UPROPERTY(EditAnywhere)
		DroidType E_Droid_Type;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* DroidHit;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UTimelineComponent* MovementTimelineComponent;
	FOnTimelineFloat UpdateFunctionFloat;
	FVector InitPosition;
	FVector EndPosition;
	FOnTimelineEventStatic FinishedFunctionFloat;
	MovementType E_Movement_Type;
	FVector ActivatePlasma;
	FVector DeactivatePlasma;
	bool bOnHit;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UFUNCTION()
		void UpdateTimelineFunction(float Output);
	UFUNCTION()
		void FinishedTimelineFunction();
	UFUNCTION()
		void ChangePlasma();
	UFUNCTION()
		void OnHit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnDetection(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnStopDetection(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
		void InitDroid();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
