// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include"WIMPGate.h"
#include "WIMPActivateDoor.generated.h"

UCLASS()
class WIMP_API AWIMPActivateDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWIMPActivateDoor();
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* ActivatorCollision;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
		AWIMPGate* OperationGate;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
