// Copyright Tomorrow Evening, all rights reserved.

#include "TweenController.h"
#include "GenericPlatform/GenericPlatformTime.h"

UTweenController* UTweenController::_instance = nullptr;

UTweenController::UTweenController() {
	_instance = this;
	UE_LOG(LogTemp, Log, TEXT("TweenController created"));
}

UTweenController* UTweenController::Get() {
	return _instance;
}

void UTweenController::Update() {
	double now = FPlatformTime::Seconds();
  for(int32 i = Tweens.Num() - 1; i >= 0; --i) {
    UTween* Tween = Tweens[i];
    if(Tween->Update(now)) Tweens.RemoveAt(i);
  }
}

UTween* UTweenController::AddTween(double duration, double delay, float x0, float y0, float x1, float y1) {
	UTween* Tween = NewObject<UTween>(this, UTween::StaticClass());
	Tween->Setup(duration, delay, x0, y0, x1, y1);
	Tweens.Add(Tween);
	return Tween;
}
