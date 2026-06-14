// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

#include "EngineUtils.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/KismetSystemLibrary.h"

AMyPlayerController::AMyPlayerController()
{
	bShowMouseCursor = true;
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FString NetModeString; 
	switch (GetNetMode()) 
	{ 
		case NM_Standalone: NetModeString = TEXT("Standalone"); 
			break; 
		case NM_Client: NetModeString = TEXT("Client"); 
			break; 
		case NM_ListenServer: NetModeString = TEXT("ListenServer"); 
			break; 
		case NM_DedicatedServer: NetModeString = TEXT("DedicatedServer"); 
			break; 
		default: NetModeString = TEXT("Unknown"); 
			break; 
	} 
	UE_LOG(LogTemp, Warning, TEXT("[PlayerController BeginPlay] Name: %s / NetMode: %s / IsLocalController: %s"), *GetName(), *NetModeString, IsLocalController() ? TEXT("true") : TEXT("false"));

	if (!IsLocalController()) return;

	if (IsLocalController() && ChatInputWidgetClass)
	{
		ChatInputWidget = CreateWidget<UUserWidget>(this, ChatInputWidgetClass);
		if (ChatInputWidget)
		{
			ChatInputWidget->AddToViewport();
		}
	}

	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputMode);

	bShowMouseCursor = true;
}

void AMyPlayerController::SetChatMessageString(const FString& NewMessage)
{
	ChatMessageString = NewMessage;

	if (!IsLocalController()) return;
	ServerSendChatMessage(ChatMessageString);

}

void AMyPlayerController::PrintChatMessageString(const FString& ChatMessage)
{
	if (ChatMessage.IsEmpty())
	{
		return;
	}

	UKismetSystemLibrary::PrintString(
		this,
		ChatMessage,
		true,
		true,
		FLinearColor::Green,
		5.0f
	);
}

void AMyPlayerController::ClientPrintChatMessage_Implementation(const FString& ChatMessage)
{
	PrintChatMessageString(ChatMessage);
}

void AMyPlayerController::ServerSendChatMessage_Implementation(const FString& ChatMessage) 
{
	if (ChatMessage.IsEmpty()) return;

	UWorld* World = GetWorld();
	if (World == nullptr) return;

	for (TActorIterator<AMyPlayerController> It(World); It; ++It)
	{
		AMyPlayerController* PC = *It;
		if (IsValid(PC)) 
		{
			PC->ClientPrintChatMessage(ChatMessage);
		}
	}
}

