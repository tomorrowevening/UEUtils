// Copyright Tomorrow Evening, all rights reserved.

#include "Tween.h"
#include "GenericPlatform/GenericPlatformTime.h"
#include "../utils/MathUtil.h"

void UTween::Setup(double duration, double delay, float x0, float y0, float x1, float y1) {
	double now = FPlatformTime::Seconds();
	startTime = now + delay;
	endTime = startTime + duration;
	easeX0 = x0;
	easeY0 = y0;
	easeX1 = x1;
	easeY1 = y1;
}

bool UTween::Update(double now) {
	 float progress = UMathUtil::Normalize(startTime, endTime, now);
	 if(progress == 0.0f && OnStart.IsBound()) OnStart.Broadcast(0.0);

	 float eased = UMathUtil::CubicBezierEase(easeX0, easeY0, easeX1, easeY1, progress);
	 if(OnUpdate.IsBound()) OnUpdate.Broadcast(eased);

	 bool complete = progress == 1.0f;
	 if (complete && OnComplete.IsBound()) OnComplete.Broadcast(1.0);
	 return complete;
}
