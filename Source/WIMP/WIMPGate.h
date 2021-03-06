// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "WIMPActivateDoor.h"
#include "WIMPGate.generated.h"

UCLASS()
class WIMP_API AWIMPGate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWIMPGate();

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* SK_DoorFrame;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* SM_DoorFrame_1;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* SM_DoorFrame_2;
	bool bClosed;
	UPROPERTY(EditAnywhere)
		AWIMPActivateDoor* ActivatorDoor_1;
	UPROPERTY(EditAnywhere)
		AWIMPActivateDoor* ActivatorDoor_2;
protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
		void OnActivatorOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent)
		void CloseDoor();
	UFUNCTION(BlueprintImplementableEvent)
		void OpenDoor();
};
