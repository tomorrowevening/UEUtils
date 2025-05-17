// Copyright Tomorrow Evening, all rights reserved.

#include "ApolloTweenController.h"

void UApolloTweenController::AddTween(UApolloTween* Tween) {
	ActiveTweens.Add(Tween);
}

void UApolloTweenController::RemoveTween(UApolloTween* Tween) {
	ActiveTweens.Remove(Tween);
}

void UApolloTweenController::Tick(float DeltaTime) {
	for(int32 i = ActiveTweens.Num() - 1; i >= 0; --i) {
		UApolloTween *tween = ActiveTweens[i];
		if (tween) {
		 	if (tween->Tick(DeltaTime)) RemoveTween(tween);
		}
	}
}
