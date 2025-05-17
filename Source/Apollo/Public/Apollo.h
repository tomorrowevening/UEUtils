// Copyright Tomorrow Evening, all rights reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FApolloModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
