// Copyright Tomorrow Evening, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Tween.h"
#include "Tickable.h"
#include "Subsystems/WorldSubsystem.h"
#include "TweenSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class TELIBRARY_API UTweenSubsystem : public UTickableWorldSubsystem {
	GENERATED_BODY()

public:

	void AddTween(UTween* Tween) {
		ActiveTweens.Add(Tween);
	}

	void RemoveTween(UTween* Tween) {
		ActiveTweens.Remove(Tween);
	}

	// UTickableWorldSubsystem
	virtual void Tick(float DeltaTime) override {
		for(int32 i = ActiveTweens.Num() - 1; i >= 0; --i) {
			UTween *tween = ActiveTweens[i];
			if(tween) {
				if (tween->Tick(DeltaTime)) RemoveTween(tween);
			}
		}
	}

	virtual bool IsTickable() const override {
		return ActiveTweens.Num() > 0;
	}

	virtual TStatId GetStatId() const override {
		RETURN_QUICK_DECLARE_CYCLE_STAT(UTweenSubsystem, STATGROUP_Tickables);
	}

private:

	TArray<UTween*> ActiveTweens;
	
};
