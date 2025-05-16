// Copyright Tomorrow Evening, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Tween.generated.h"

// Delegate signatures for callbacks
DECLARE_DYNAMIC_DELEGATE_OneParam(FTweenUpdateSignature, float, Value);
DECLARE_DYNAMIC_DELEGATE(FTweenCompleteSignature);

UENUM(BlueprintType)
enum class ETweenEaseType : uint8 {
	Linear UMETA(DisplayName = "Linear"),
	CubicBezier UMETA(DisplayName = "CubicBezier"),
	EaseCircIn UMETA(DisplayName = "CircIn"),
	EaseCircInOut UMETA(DisplayName = "CircInOut"),
	EaseCircOut UMETA(DisplayName = "CircOut"),
	EaseCubicIn UMETA(DisplayName = "CubicIn"),
	EaseCubicInOut UMETA(DisplayName = "CubicInOut"),
	EaseCubicOut UMETA(DisplayName = "CubicOut"),
	EaseExpoIn UMETA(DisplayName = "ExpoIn"),
	EaseExpoInOut UMETA(DisplayName = "ExpoInOut"),
	EaseExpoOut UMETA(DisplayName = "ExpoOut"),
	EaseQuadIn UMETA(DisplayName = "QuadIn"),
	EaseQuadInOut UMETA(DisplayName = "QuadInOut"),
	EaseQuadOut UMETA(DisplayName = "QuadOut"),
	EaseQuartIn UMETA(DisplayName = "QuartIn"),
	EaseQuartInOut UMETA(DisplayName = "QuartInOut"),
	EaseQuartOut UMETA(DisplayName = "QuartOut"),
	EaseQuintIn UMETA(DisplayName = "QuintIn"),
	EaseQuintInOut UMETA(DisplayName = "QuintInOut"),
	EaseQuintOut UMETA(DisplayName = "QuintOut"),
	EaseSineIn UMETA(DisplayName = "SineIn"),
	EaseSineInOut UMETA(DisplayName = "SineInOut"),
	EaseSineOut UMETA(DisplayName = "SineOut"),
	EaseSinWave UMETA(DisplayName = "SinWave")
};

UCLASS(BlueprintType)
class TELIBRARY_API UTween : public UObject {
	GENERATED_BODY()

public:

	UFUNCTION(
		BlueprintCallable,
		meta = (
			WorldContext = "Target",
			DisplayName = "Tween",
			AutoCreateRefTerm = "CubicBezier"
		),
		Category = "Tween"
	)
	static UTween* Tween(UObject* Target, float Duration, float Delay = 0.0f, ETweenEaseType EaseType = ETweenEaseType::Linear, float X0 = 0.33f, float Y0 = 0.33f, float X1 = 0.67f, float Y1 = 0.67f);

	// Callbacks
	UFUNCTION(BlueprintCallable, Category = "Tween")
	void SetOnUpdate(const FTweenUpdateSignature& Callback);

	UFUNCTION(BlueprintCallable, Category = "Tween")
	void SetOnComplete(const FTweenCompleteSignature& Callback);

	// Internal tick
	bool Tick(float DeltaTime);

private:

	float Delay;
	float Duration;
	float Elapsed;
	float X0;
	float Y0;
	float X1;
	float Y1;
	ETweenEaseType EaseType;
	FTweenUpdateSignature OnUpdate;
	FTweenCompleteSignature OnComplete;
	
};
