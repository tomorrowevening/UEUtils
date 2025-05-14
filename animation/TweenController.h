// Copyright Tomorrow Evening, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Tween.h"
#include "TweenController.generated.h"

/**
 * Tweening
 */
UCLASS()
class UTweenController : public UObject {
	GENERATED_BODY()

public:

	TArray<UTween*> Tweens;

	UTweenController();
	UFUNCTION(BlueprintCallable, Category = "Tween") UTween* AddTween(double duration, double delay, float x0, float y0, float x1, float y1);
	UFUNCTION(BlueprintCallable, Category = "Tween") void Update();
	UFUNCTION(BlueprintCallable, Category = "Tween") static UTweenController* Get();

private:

	static UTweenController* _instance;
	
};
