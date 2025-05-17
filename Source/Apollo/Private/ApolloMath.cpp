// Copyright Tomorrow Evening, all rights reserved.

#include "Math/UnrealMathUtility.h"
#include "Apollo.h"
#include "ApolloMath.h"

UApolloMath::UApolloMath(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	//
}

float UApolloMath::SmoothStep(float Edge0, float Edge1, float Value) {
	float t = FMath::Clamp((Value - Edge0) / (Edge1 - Edge0), 0.0f, 1.0f);
	return t * t * (3.0f - 2.0f * t);
}

static bool IsLinear(float X0, float Y0, float X1, float Y1) {
	return X0 == Y0 && X1 == Y1;
}

static float SlopeFromT(float T, float A, float B, float C) {
	return 1.0f / (3.0f * A * T * T + 2.0f * B * T + C);
}

static float XFromT(float T, float A, float B, float C, float D) {
	return A * T * T * T + B * T * T + C * T + D;
}

static float YFromT(float T, float E, float F, float G, float H) {
	const float TT = T * T;
	return E * TT * T + F * TT + G * T + H;
}

float UApolloMath::CubicBezierEase(float X0, float Y0, float X1, float Y1, float Percent) {
	if(Percent <= 0.0f)		return 0.0f;
	if(Percent >= 1.0f)		return 1.0f;
	if(IsLinear(X0, Y0, X1, Y1)) {
		return Percent;
	}

	// set up our bezier coefficients
	const float X0a = 0.0f, Y0a = 0.0f;
	const float X1a = X0, Y1a = Y0;
	const float X2a = X1, Y2a = Y1;
	const float X3a = 1.0f, Y3a = 1.0f;

	const float A = X3a - 3.0f * X2a + 3.0f * X1a - X0a;
	const float B = 3.0f * X2a - 6.0f * X1a + 3.0f * X0a;
	const float C = 3.0f * X1a - 3.0f * X0a;
	const float D = X0a;

	const float E = Y3a - 3.0f * Y2a + 3.0f * Y1a - Y0a;
	const float F = 3.0f * Y2a - 6.0f * Y1a + 3.0f * Y0a;
	const float G = 3.0f * Y1a - 3.0f * Y0a;
	const float H = Y0a;

	// Newton‑Raphson to find t for our given x = Percent
	float Current = Percent;
	for(int32 i = 0; i < 5; ++i) {
		const float CurrentX = XFromT(Current, A, B, C, D);
		float			 CurrentSlope = SlopeFromT(Current, A, B, C);

		if(!FMath::IsFinite(CurrentSlope)) {
			// fallback if derivative is zero / infinite
			CurrentSlope = Percent;
		}

		Current -= (CurrentX - Percent) * CurrentSlope;
		Current = FMath::Clamp(Current, 0.0f, 1.0f);
	}

	// finally return y(t)
	return YFromT(Current, E, F, G, H);
}

/*
// Helpers for cubic Bezier
static float SampleCurve(float a1, float a2, float t) {
	// cubic Bezier: 3*(1-t)^2*t*a1 + 3*(1-t)*t^2*a2 + t^3
	float u = 1.0f - t;
	return 3.0f * u * u * t * a1 + 3.0f * u * t * t * a2 + t * t * t;
}

static float SampleCurveDerivative(float a1, float a2, float t) {
	// derivative of cubic Bezier for x: 3*(1-t)^2*a1 + 6*(1-t)*t*(a2 - a1) + 3*t^2*(1 - a2)
	float u = 1.0f - t;
	return 3.0f * (u * u * a1 + 2.0f * u * t * (a2 - a1) + t * t * (1.0f - a2));
}

static float SolveCurveT(float x1, float x2, float x) {
	// Newton-Raphson iteration
	float t = x;
	for(int i = 0; i < 5; ++i) {
		float xEst = SampleCurve(x1, x2, t) - x;
		float dEst = SampleCurveDerivative(x1, x2, t);
		if(FMath::Abs(dEst) < KINDA_SMALL_NUMBER) break;
		t -= xEst / dEst;
		t = FMath::Clamp(t, 0.0f, 1.0f);
	}
	return t;
}

float UApolloMath::CubicBezierEase(float X1, float Y1, float X2, float Y2, float Value) {
	float ClampedT = FMath::Clamp(Value, 0.0f, 1.0f);
	float solvedT = SolveCurveT(X1, X2, ClampedT);
	return SampleCurve(Y1, Y2, solvedT);
}
*/

float UApolloMath::Normalize(float Min, float Max, float Value) {
	float Range = Max - Min;
	if(FMath::Abs(Range) < 1e-12) return 0.0;
	float Normalized = (Value - Min) / Range;
	return FMath::Clamp(Normalized, 0.0, 1.0);
}
