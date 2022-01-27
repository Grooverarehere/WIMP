// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
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
	UPROPERTY(EditAnywhere)
		float TimeToOpen;
protected:
	FTimerHandle OpenHandle;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent)
		void CloseDoor();
	UFUNCTION(BlueprintImplementableEvent)
	void OpenDoor();
};
