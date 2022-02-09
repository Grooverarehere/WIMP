// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "WIMPScoutDroid.generated.h"

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
	UPROPERTY(EditAnywhere)
		float Distance;
	UPROPERTY(EditAnywhere)
		UCurveFloat* MovementTimelineCurve;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UTimelineComponent* MovementTimelineComponent;
	FOnTimelineFloat UpdateFunctionFloat;
	FVector InitPosition;
	FVector EndPosition;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UFUNCTION()
		void UpdateTimelineFunction(float Output);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
