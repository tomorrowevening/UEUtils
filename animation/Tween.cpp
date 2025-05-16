// Copyright Tomorrow Evening, all rights reserved.

#include "Tween.h"
#include "TweenSubsystem.h"
#include "../utils/MathUtil.h"

UTween* UTween::Tween(
	UObject* Target,
	float InDuration,
	float InDelay,
	ETweenEaseType InEase,
	float InX0,
	float InY0,
	float InX1,
	float InY1
) {
	// Create tween as a subobject of the calling Blueprint
	UTween* Tween = NewObject<UTween>(Target);
	Tween->Duration = InDuration;
	Tween->Delay = InDelay;
	Tween->Elapsed = 0.0f;
	Tween->EaseType = InEase;
	Tween->X0 = InX0;
	Tween->Y0 = InY0;
	Tween->X1 = InX1;
	Tween->Y1 = InY1;

	if(UWorld* World = GEngine->GetWorldFromContextObjectChecked(Target)) {
		if(UTweenSubsystem* Subsystem = World->GetSubsystem<UTweenSubsystem>()) {
			Subsystem->AddTween(Tween);
		}
	}

	return Tween;
}

void UTween::SetOnUpdate(const FTweenUpdateSignature& Callback) {
	OnUpdate = Callback;
}

void UTween::SetOnComplete(const FTweenCompleteSignature& Callback) {
	OnComplete = Callback;
}

bool UTween::Tick(float DeltaTime) {
	Elapsed += DeltaTime;
	float localTime = Elapsed - Delay;
	if (localTime < 0.0f) return false;

	float value = FMath::Clamp(localTime / Duration, 0.0f, 1.0f);
	float ease = value;

	switch (ease) {
		// Circ
		case ETweenEaseType::EaseCircIn:
			ease = UMathUtil::CubicBezierEase(0.6f, 0.04f, 0.98f, 0.335f, value);
			break;
		case ETweenEaseType::EaseCircInOut:
			ease = UMathUtil::CubicBezierEase(0.785f, 0.135f, 0.150f, 0.860f, value);
			break;
		case ETweenEaseType::EaseCircOut:
			ease = UMathUtil::CubicBezierEase(0.075f, 0.820f, 0.165f, 1.000f, value);
			break;
			
		// Cubic
		case ETweenEaseType::EaseCubicIn:
			ease = UMathUtil::CubicBezierEase(0.550, 0.055, 0.675, 0.190, value);
			break;
		case ETweenEaseType::EaseCubicInOut:
			ease = UMathUtil::CubicBezierEase(0.645, 0.045, 0.355, 1.000, value);
			break;
		case ETweenEaseType::EaseCubicOut:
			ease = UMathUtil::CubicBezierEase(0.215, 0.610, 0.355, 1.000, value);
			break;
			
		// Expo
		case ETweenEaseType::EaseExpoIn:
			ease = UMathUtil::CubicBezierEase(0.950, 0.050, 0.795, 0.035, value);
			break;
		case ETweenEaseType::EaseExpoInOut:
			ease = UMathUtil::CubicBezierEase(1.000, 0.000, 0.000, 1.000, value);
			break;
		case ETweenEaseType::EaseExpoOut:
			ease = UMathUtil::CubicBezierEase(0.190, 1.000, 0.220, 1.000, value);
			break;
			
		// Quad
		case ETweenEaseType::EaseQuadIn:
			ease = UMathUtil::CubicBezierEase(0.550, 0.085, 0.680, 0.530, value);
			break;
		case ETweenEaseType::EaseQuadInOut:
			ease = UMathUtil::CubicBezierEase(0.455, 0.030, 0.515, 0.955, value);
			break;
		case ETweenEaseType::EaseQuadOut:
			ease = UMathUtil::CubicBezierEase(0.250, 0.460, 0.450, 0.940, value);
			break;
			
		// Quart
		case ETweenEaseType::EaseQuartIn:
			ease = UMathUtil::CubicBezierEase(0.895, 0.030, 0.685, 0.220, value);
			break;
		case ETweenEaseType::EaseQuartInOut:
			ease = UMathUtil::CubicBezierEase(0.860, 0.000, 0.070, 1.000, value);
			break;
		case ETweenEaseType::EaseQuartOut:
			ease = UMathUtil::CubicBezierEase(0.230, 1.000, 0.320, 1.000, value);
			break;
			
		// Quint
		case ETweenEaseType::EaseQuintIn:
			ease = UMathUtil::CubicBezierEase(0.755, 0.050, 0.855, 0.060, value);
			break;
		case ETweenEaseType::EaseQuintInOut:
			ease = UMathUtil::CubicBezierEase(0.770, 0.000, 0.175, 1.000, value);
			break;
		case ETweenEaseType::EaseQuintOut:
			ease = UMathUtil::CubicBezierEase(0.165, 0.840, 0.440, 1.000, value);
			break;
			
		// Sine
		case ETweenEaseType::EaseSineIn:
			ease = UMathUtil::CubicBezierEase(0.470, 0.000, 0.745, 0.715, value);
			break;
		case ETweenEaseType::EaseSineInOut:
			ease = UMathUtil::CubicBezierEase(0.445, 0.050, 0.550, 0.950, value);
			break;
		case ETweenEaseType::EaseSineOut:
			ease = UMathUtil::CubicBezierEase(0.390, 0.575, 0.565, 1.000, value);
			break;
		case ETweenEaseType::EaseSinWave:
			ease = Mathf::Sin(value * PI);
			break;
			
		// Linear
		case ETweenEaseType::EaseLinear:
		default:
			ease = UMathUtil::CubicBezierEase(0.333f, 0.333f, 0.667f, 0.667f);
			break;
	}

	OnUpdate.ExecuteIfBound(ease);

	if(localTime >= Duration) {
		OnComplete.ExecuteIfBound();
		return true;
	}

	return false;
}
