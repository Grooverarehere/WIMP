// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "WIMPMovableFloor.generated.h"

UENUM(BlueprintType)
enum class FloorMovementType : uint8 {
	FRONT = 0 UMETA(DisplayName = "FRONT"),
	SLIDE = 1  UMETA(DisplayName = "SLIDE")

};

UCLASS()
class WIMP_API AWIMPMovableFloor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWIMPMovableFloor();

	UPROPERTY()
		class USceneComponent* SceneRoot;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere)
		float Distance;
	UPROPERTY(EditAnywhere)
		UCurveFloat* MovementTimelineCurve;
	UPROPERTY(EditAnywhere)
		FloorMovementType E_Movement_Type;
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
