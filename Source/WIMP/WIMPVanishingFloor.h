// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "WIMPVanishingFloor.generated.h"

UCLASS()
class WIMP_API AWIMPVanishingFloor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWIMPVanishingFloor();

	UPROPERTY()
		class USceneComponent* SceneRoot;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere)
		UCurveFloat* MaterializeTimelineCurve;
	UPROPERTY(EditAnywhere)
		float TimeToVanish;
	UPROPERTY(EditAnywhere)
		float TimeToVisible;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UTimelineComponent* MaterializeTimelineComponent;
	FOnTimelineFloat UpdateFunctionFloat;
	UMaterialInstanceDynamic* MID;
	FTimerHandle VanishHandle;
	FTimerHandle VisibleHandle;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void UpdateTimelineFunction(float Output);
	void Vanish();
	void Visible();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
