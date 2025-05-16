// Copyright Tomorrow Evening, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MathUtil.generated.h"

#ifndef PI
#define PI 3.14159265358979323846f
#endif

#ifndef TAU
#define TAU 6.28318530717958647692f
#endif

/**
 * Blueprint-accessible math utility functions
 */
UCLASS()
class TELIBRARY_API UMathUtil : public UBlueprintFunctionLibrary {
	GENERATED_BODY()
	
public:

	/**
	 * Performs a smooth Hermite interpolation between 0 and 1 over the range [Edge0, Edge1].
	 * Equivalent to GLSL/HLSL smoothstep.
	 * @param Edge0 The lower edge of the transition.
	 * @param Edge1 The upper edge of the transition.
	 * @param Value The input value to interpolate.
	 * @return A value between 0 and 1 after smoothstep interpolation.
	 */
	UFUNCTION(BlueprintPure, Category = "Math|Interpolation")
	static float SmoothStep(float Edge0, float Edge1, float Value);

	/**
	 * Performs cubic Bezier easing with control points (0,0), (X1,Y1), (X2,Y2), (1,1).
	 * @param X1 The x-coordinate of the first control point.
	 * @param Y1 The y-coordinate of the first control point.
	 * @param X2 The x-coordinate of the second control point.
	 * @param Y2 The y-coordinate of the second control point.
	 * @param T  The input parameter, usually between 0 and 1.
	 * @return The eased value between 0 and 1.
	 */
	UFUNCTION(BlueprintPure, Category = "Math|Interpolation")
	static float CubicBezierEase(float X1, float Y1, float X2, float Y2, float Value);

	UFUNCTION(BlueprintPure, Category = "Math")
	static float Normalize(float Min, float Max, float Value);
};
