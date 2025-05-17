// Copyright Tomorrow Evening, all rights reserved.

#pragma once

#ifndef WITH_TELIB_JSON
#define WITH_TELIB_JSON 0
#endif

#ifndef WITH_TELIB_WEBSOCKETS
#define WITH_TELIB_WEBSOCKETS 0
#endif

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#if WITH_TELIB_WEBSOCKETS
#include "IWebSocket.h"
#endif

#if WITH_TELIB_JSON
#include "Dom/JsonObject.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#endif

#include "ApolloWebSockets.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSocketMessage, const FString&, JsonString);

/**
 * Websocket event dispatcher
 */
UCLASS()
class UApolloWebSockets : public UObject {
	GENERATED_BODY()

public:

	UApolloWebSockets();

#if WITH_TELIB_WEBSOCKETS
	TSharedPtr<IWebSocket> WebSocket;
#endif

	// Properties
	UPROPERTY(BlueprintAssignable, Category = "Apollo|WebSocket") FOnSocketMessage OnConnected;
	UPROPERTY(BlueprintAssignable, Category = "Apollo|WebSocket") FOnSocketMessage OnMessage;
	UPROPERTY(BlueprintAssignable, Category = "Apollo|WebSocket") FOnSocketMessage OnClosed;
	UPROPERTY(BlueprintAssignable, Category = "Apollo|WebSocket") FOnSocketMessage OnError;

	// Functions
	UFUNCTION(BlueprintCallable, Category = "Apollo|WebSocket") void connect(FString socketURL);
	UFUNCTION(BlueprintCallable, Category = "Apollo|WebSocket") void disconnect();
	UFUNCTION(BlueprintCallable, Category = "Apollo|WebSocket") void send(FString message);
	UFUNCTION(BlueprintCallable, Category = "Apollo|WebSocket") static UApolloWebSockets* Get();

	// JSON
#if WITH_TELIB_JSON
	void sendJSON(TSharedPtr<FJsonObject> JsonObject);
#endif

protected:

	static UApolloWebSockets* _instance;
	bool isConnected;
	
};
