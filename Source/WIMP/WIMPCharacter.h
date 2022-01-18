// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"
#include "WIMPCharacter.generated.h"

UCLASS(Blueprintable)
class AWIMPCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AWIMPCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return AbsoluteCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* AbsoluteCameraComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* ZoomCameraComponent;
	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UTimelineComponent* ZoomTimelineComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UTimelineComponent* PCTimelineComp;

	FOnTimelineFloat UpdateZoomFloat;

	FOnTimelineFloat UpdatePositionFloat;

	float m_InitOrthoWidth;

	bool bZoom;
	
	FVector AbsoluteCameraPos;

	FVector ZoomCameraPos;

	FOnTimelineEventStatic OnTimelinePositionFinished;
	
	virtual void BeginPlay() override;

	UFUNCTION()
		void UpdateZoomComp(float Output);
	UFUNCTION()
		void UpdateTimelinePosition(float Output);
	UFUNCTION()
		void FinishedTimelinePosition();
public:
	UPROPERTY(EditAnywhere)
		UCurveFloat* ZoomTimeLineCurve;
	UPROPERTY(EditAnywhere)
		UCurveFloat* PositionTimelineCurve;
	void ChangeCamera();
};

