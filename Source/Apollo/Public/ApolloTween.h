// Copyright Tomorrow Evening, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ApolloTween.generated.h"

// Delegate signatures for callbacks
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FApolloTweenUpdate, float, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FApolloTweenCallback);

/**
 * Easing types
 */
UENUM(BlueprintType)
enum class EApolloTweenEaseType : uint8 {
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
	EaseSineWave UMETA(DisplayName = "SineWave")
};

/**
 * Tweening
 */
UCLASS(BlueprintType)
class UApolloTween : public UObject {
	GENERATED_BODY()

public:

	UFUNCTION(
		BlueprintCallable,
		meta = (
			WorldContext = "Target",
			DisplayName = "Tween",
			AutoCreateRefTerm = "CubicBezier"
		),
		Category = "Apollo|Tween"
	)
	static UApolloTween* ApolloTween(
		UObject* Target,
		float Duration,
		float Delay = 0.0f,
		float StartValue = 0.0f,
		float EndValue = 1.0f,
		EApolloTweenEaseType EaseType = EApolloTweenEaseType::Linear,
		float X0 = 0.33f,
		float Y0 = 0.33f,
		float X1 = 0.67f,
		float Y1 = 0.67f
	);

	UPROPERTY(BlueprintAssignable, Category="Apollo|Tween")
	FApolloTweenCallback OnStart;
	UPROPERTY(BlueprintAssignable, Category="Apollo|Tween")
	FApolloTweenUpdate OnUpdate;
	UPROPERTY(BlueprintAssignable, Category="Apollo|Tween")
	FApolloTweenCallback OnComplete;

	bool Tick(float DeltaTime);

private:

	float Delay;
	float Duration;
	float Elapsed;
	float StartValue;
	float EndValue;
	float X0;
	float Y0;
	float X1;
	float Y1;
	EApolloTweenEaseType EaseType;
	bool tweenStarted;

	float getEase(float value);
	
};
