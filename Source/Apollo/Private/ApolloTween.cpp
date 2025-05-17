// Copyright Tomorrow Evening, all rights reserved.

#include "ApolloTween.h"
#include "ApolloMath.h"
#include "ApolloTweenController.h"

UApolloTween* UApolloTween::ApolloTween(
	UObject* Target,
	float InDuration,
	float InDelay,
	float InStartValue,
	float InEndValue,
	EApolloTweenEaseType InEase,
	float InX0,
	float InY0,
	float InX1,
	float InY1
) {
	// Create ApolloTween as a subobject of the calling Blueprint
	UApolloTween* ApolloTween = NewObject<UApolloTween>(Target);
	ApolloTween->Duration = InDuration;
	ApolloTween->Delay = InDelay;
	ApolloTween->StartValue = InStartValue;
	ApolloTween->EndValue = InEndValue;
	ApolloTween->Elapsed = 0.0f;
	ApolloTween->EaseType = InEase;
	ApolloTween->X0 = InX0;
	ApolloTween->Y0 = InY0;
	ApolloTween->X1 = InX1;
	ApolloTween->Y1 = InY1;
	ApolloTween->tweenStarted = false;

	if(UWorld* World = GEngine->GetWorldFromContextObjectChecked(Target)) {
		if(UApolloTweenController* tweenController = World->GetSubsystem<UApolloTweenController>()) {
			tweenController->AddTween(ApolloTween);
		}
	}

	return ApolloTween;
}

bool UApolloTween::Tick(float DeltaTime) {
	Elapsed += DeltaTime;
	float localTime = Elapsed - Delay;
	if (localTime < 0.0f) return false;

	if(!tweenStarted) {
		tweenStarted = true;
		OnStart.Broadcast();
	}

	float percent = FMath::Clamp(localTime / Duration, 0.0f, 1.0f);
	float ease = getEase(percent);
	float value = FMath::Lerp(StartValue, EndValue, ease);
	OnUpdate.Broadcast(value);

	if(localTime >= Duration) {
		OnComplete.Broadcast();
		return true;
	}

	return false;
}

float UApolloTween::getEase(float value) {
	float ease = value;
	switch (EaseType) {
		// Linear
		case EApolloTweenEaseType::Linear:
		default:
			break;

		// Cubic Bezier
		case EApolloTweenEaseType::CubicBezier:
			ease = UApolloMath::CubicBezierEase(X0, Y0, X1, Y1, value);
			break;

		// Circ
		case EApolloTweenEaseType::EaseCircIn:
			ease = 1.0f - FMath::Sqrt(1.0f - value * value);
			break;
		case EApolloTweenEaseType::EaseCircOut:
			ease = FMath::Sqrt(1.0f - FMath::Square(value - 1.0f));
			break;
		case EApolloTweenEaseType::EaseCircInOut:
			if (value < 0.5f) {
				ease = (1.0f - FMath::Sqrt(1.0f - 4.0f * value * value)) * 0.5f;
			} else {
				ease = (FMath::Sqrt(1.0f - FMath::Square(-2.0f * value + 2.0f)) + 1.0f) * 0.5f;
			}
			break;

		// Cubic
		case EApolloTweenEaseType::EaseCubicIn:
			ease = value * value * value;
			break;
		case EApolloTweenEaseType::EaseCubicOut:
			ease = 1.0f - FMath::Pow(1.0f - value, 3);
			break;
		case EApolloTweenEaseType::EaseCubicInOut:
			if (value < 0.5f) {
				ease = 4.0f * value * value * value;
			} else {
				ease = 1.0f - FMath::Pow(-2.0f * value + 2.0f, 3) / 2.0f;
			}
			break;

		// Expo
		case EApolloTweenEaseType::EaseExpoIn:
			ease = (value == 0.0f) ? 0.0f : FMath::Pow(2.0f, 10.0f * value - 10.0f);
			break;
		case EApolloTweenEaseType::EaseExpoOut:
			ease = (value == 1.0f) ? 1.0f : 1.0f - FMath::Pow(2.0f, -10.0f * value);
			break;
		case EApolloTweenEaseType::EaseExpoInOut:
			if (value == 0.0f) {
				ease = 0.0f;
			} else if (value == 1.0f) {
				ease = 1.0f;
			} else if (value < 0.5f) {
				ease = FMath::Pow(2.0f, 20.0f * value - 10.0f) * 0.5f;
			} else {
				ease = (2.0f - FMath::Pow(2.0f, -20.0f * value + 10.0f)) * 0.5f;
			}
			break;

		// Quad
		case EApolloTweenEaseType::EaseQuadIn:
			ease = value * value;
			break;
		case EApolloTweenEaseType::EaseQuadOut:
			ease = value * (2.0f - value);
			break;
		case EApolloTweenEaseType::EaseQuadInOut:
			if (value < 0.5f) {
				ease = 2.0f * value * value;
			} else {
				ease = 1.0f - FMath::Pow(-2.0f * value + 2.0f, 2) * 0.5f;
			}
			break;

		// Quart
		case EApolloTweenEaseType::EaseQuartIn:
			ease = value * value * value * value;
			break;
		case EApolloTweenEaseType::EaseQuartOut:
			ease = 1.0f - FMath::Pow(1.0f - value, 4);
			break;
		case EApolloTweenEaseType::EaseQuartInOut:
			if (value < 0.5f) {
				ease = 8.0f * value * value * value * value;
			} else {
				ease = 1.0f - FMath::Pow(-2.0f * value + 2.0f, 4) * 0.5f;
			}
			break;

		// Quint
		case EApolloTweenEaseType::EaseQuintIn:
			ease = value * value * value * value * value;
			break;
		case EApolloTweenEaseType::EaseQuintOut:
			ease = 1.0f - FMath::Pow(1.0f - value, 5);
			break;
		case EApolloTweenEaseType::EaseQuintInOut:
			if (value < 0.5f) {
				ease = 16.0f * FMath::Pow(value, 5);
			} else {
				ease = 1.0f - FMath::Pow(-2.0f * value + 2.0f, 5) * 0.5f;
			}
			break;

		// Sine
		case EApolloTweenEaseType::EaseSineIn:
			ease = 1.0f - FMath::Cos((value * PI) / 2.0f);
			break;
		case EApolloTweenEaseType::EaseSineOut:
			ease = FMath::Sin((value * PI) / 2.0f);
			break;
		case EApolloTweenEaseType::EaseSineInOut:
			ease = -(FMath::Cos(PI * value) - 1.0f) * 0.5f;
			break;
		case EApolloTweenEaseType::EaseSineWave:
			ease = FMath::Sin(value * PI);
			break;
	}

	return FMath::Clamp(ease, 0.0f, 1.0f);
}
