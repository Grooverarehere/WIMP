// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/TimelineComponent.h"
#include "WIMPElevator.generated.h"

UCLASS()
class WIMP_API AWIMPElevator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWIMPElevator();

	UPROPERTY()
		class USceneComponent* SceneRoot;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* ElavatorCollision;
	UPROPERTY(EditAnywhere)
	float Altitude;
	UPROPERTY(EditAnywhere)
		UCurveFloat* ElevatorTimelineCurve;
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UTimelineComponent* ElevatorTimelineComponent;
		FOnTimelineFloat UpdateFunctionFloat;
		FVector InitPosition;
		FVector EndPosition;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void UpdateTimelineFunction(float Output);
	UFUNCTION()
		void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
