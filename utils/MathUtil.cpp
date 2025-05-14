// Copyright Tomorrow Evening, all rights reserved.

#include "MathUtil.h"
#include "Math/UnrealMathUtility.h"

float UMathUtil::SmoothStep(float Edge0, float Edge1, float Value) {
  float t = FMath::Clamp((Value - Edge0) / (Edge1 - Edge0), 0.0f, 1.0f);
  return t * t * (3.0f - 2.0f * t);
}

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

float UMathUtil::CubicBezierEase(float X1, float Y1, float X2, float Y2, float Value) {
  float ClampedT = FMath::Clamp(Value, 0.0f, 1.0f);
  float solvedT = SolveCurveT(X1, X2, ClampedT);
  return SampleCurve(Y1, Y2, solvedT);
}

float UMathUtil::Normalize(float Min, float Max, float Value) {
  float Range = Max - Min;
  if(FMath::Abs(Range) < 1e-12) return 0.0;
  float Normalized = (Value - Min) / Range;
  return FMath::Clamp(Normalized, 0.0, 1.0);
}
