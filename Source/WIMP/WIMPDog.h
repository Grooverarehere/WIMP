// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SphereComponent.h"
#include "WIMPDog.generated.h"

UCLASS()
class WIMP_API AWIMPDog : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AWIMPDog();
	/*UPROPERTY()
		class USceneComponent* SceneRoot;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* Mesh;*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* WakeUpCollision;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};
