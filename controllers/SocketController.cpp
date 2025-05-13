// Copyright Tomorrow Evening, all rights reserved.

#include "SocketController.h"
#if WITH_TELIB_WEBSOCKETS
#include "WebSocketsModule.h"
#endif

USocketController* USocketController::_instance = nullptr;

USocketController::USocketController() {
	_instance = this;
	isConnected = false;
}

USocketController* USocketController::Get() {
	return _instance;
}

// Socket

void USocketController::connect(FString socketURL) {
	if(isConnected) return;

#if WITH_TELIB_WEBSOCKETS
	if(FModuleManager::Get().IsModuleLoaded("WebSockets")) {
		FModuleManager::Get().LoadModule("WebSockets");
	}

	USocketController* instance = this;
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

void USocketController::disconnect() {
	isConnected = false;
#if WITH_TELIB_WEBSOCKETS
	if(WebSocket->IsConnected()) WebSocket->Close();
#endif
}

void USocketController::send(FString message) {
	if(!isConnected) return;

#if WITH_TELIB_WEBSOCKETS
	if(WebSocket->IsConnected()) {
		WebSocket->Send(message);
	}
#endif
}

#if WITH_TELIB_JSON
void USocketController::sendJSON(TSharedPtr<FJsonObject> JsonObject) {
	FString OutputString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
	send(OutputString);
}
#endif
