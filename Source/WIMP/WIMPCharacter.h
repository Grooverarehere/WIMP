// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "WIMPCharacter.generated.h"

UCLASS(Blueprintable)
class AWIMPCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AWIMPCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	UPROPERTY(EditAnywhere)
		UCurveFloat* MaterializeTimelineCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Speed, meta = (AllowPrivateAccess = "true"))
		float m_WalkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Speed, meta = (AllowPrivateAccess = "true"))
		float m_RunSpeed;
	UPROPERTY(EditAnywhere)
		class UNiagaraSystem* SpawnEffect;
	UPROPERTY(EditAnywhere)
		UAudioComponent* RespawnSound;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
		UTimelineComponent* DestroyTimelineComponent;
	UPROPERTY(EditAnywhere)
		UCurveFloat* DestroyTimelineCurve;
private:
	/** Top down camera */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* ZoomCameraComponent;
	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere)
		UTimelineComponent* MaterializeTimelineComponent;
	FOnTimelineFloat UpdateFunctionFloat;
	FOnTimelineEventStatic FinishedFunctionFloat;
	
	UMaterialInstanceDynamic* Hair;
	UMaterialInstanceDynamic* Skin;
	UMaterialInstanceDynamic* Outfit;
	virtual void BeginPlay() override;

	UFUNCTION()
		void UpdateTimelineFunction(float Output);
	UFUNCTION()
		void FinishedTimelineFunction();
	
};

