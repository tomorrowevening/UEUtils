// Copyright Tomorrow Evening, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ApolloTween.h"
#include "ApolloTweenController.generated.h"

/**
 * Tween Controller
 */
UCLASS()
class UApolloTweenController : public UTickableWorldSubsystem {
	GENERATED_BODY()

public:

	void AddTween(UApolloTween* Tween);
	void RemoveTween(UApolloTween* Tween);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Tell the engine that we should always tick
	virtual ETickableTickType GetTickableTickType() const override {
		return ETickableTickType::Always;
	}

	// This pure‐virtual *must* be implemented
	virtual TStatId GetStatId() const override {
		// Registers a cycle counter under the STATGROUP_Tickables group
		RETURN_QUICK_DECLARE_CYCLE_STAT(UMyTickableSubsystem, STATGROUP_Tickables);
	}

	// Optional: only tick when world is not paused, etc.
	virtual bool IsTickableWhenPaused() const override { return false; }

private:

	TArray<UApolloTween*> ActiveTweens;
	
};
