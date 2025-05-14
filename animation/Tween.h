// Copyright Tomorrow Evening, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Tween.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTweenUpdate, const float&, progress);

/**
 * A single tween
 */
UCLASS()
class UTween : public UObject {
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, Category = "Animation|Tween") FOnTweenUpdate OnStart;
	UPROPERTY(BlueprintAssignable, Category = "Animation|Tween") FOnTweenUpdate OnUpdate;
	UPROPERTY(BlueprintAssignable, Category = "Animation|Tween") FOnTweenUpdate OnComplete;

	UFUNCTION(BlueprintCallable, Category = "Animation|Tween") void Setup(double duration, double delay, float x0, float y0, float x1, float y1);
	bool Update(double now);

private:

	double startTime;
	double endTime;
	float easeX0;
	float easeY0;
	float easeX1;
	float easeY1;

};
