// Copyright Tomorrow Evening, all rights reserved.

#include "ApolloWebSockets.h"
#if WITH_TELIB_WEBSOCKETS
#include "WebSocketsModule.h"
#endif

UApolloWebSockets* UApolloWebSockets::_instance = nullptr;

UApolloWebSockets::UApolloWebSockets() {
	_instance = this;
	isConnected = false;
}

UApolloWebSockets* UApolloWebSockets::Get() {
	return _instance;
}

// Socket

void UApolloWebSockets::connect(FString socketURL) {
	if(isConnected) return;

#if WITH_TELIB_WEBSOCKETS
	if(FModuleManager::Get().IsModuleLoaded("WebSockets")) {
		FModuleManager::Get().LoadModule("WebSockets");
	}

	UApolloWebSockets* instance = this;
	WebSocket = FWebSocketsModule::Get().CreateWebSocket(socketURL);

	WebSocket->OnConnected().AddLambda([instance]() {
		instance->isConnected = true;
		instance->OnConnected.Broadcast("Connected to socket");
	});

	WebSocket->OnMessage().AddLambda([instance](const FString& MessageString) {
		instance->OnMessage.Broadcast(MessageString);
	});

	WebSocket->OnConnectionError().AddLambda([instance](const FString& ErrorMsg) {
		instance->OnError.Broadcast(ErrorMsg);
	});

	WebSocket->OnClosed().AddLambda([instance](int32 StatusCode, const FString& Reason, bool bWasClean) {
		instance->isConnected = false;
		instance->OnClosed.Broadcast(Reason);
	});

	// Connect
	WebSocket->Connect();
#endif
}

void UApolloWebSockets::disconnect() {
	isConnected = false;
#if WITH_TELIB_WEBSOCKETS
	if(WebSocket->IsConnected()) WebSocket->Close();
#endif
}

void UApolloWebSockets::send(FString message) {
	if(!isConnected) return;

#if WITH_TELIB_WEBSOCKETS
	if(WebSocket->IsConnected()) {
		WebSocket->Send(message);
	}
#endif
}

#if WITH_TELIB_JSON
void UApolloWebSockets::sendJSON(TSharedPtr<FJsonObject> JsonObject) {
	FString OutputString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
	send(OutputString);
}
#endif
