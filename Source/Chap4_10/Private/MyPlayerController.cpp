// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/KismetSystemLibrary.h"

AMyPlayerController::AMyPlayerController()
{
	bShowMouseCursor = true;
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

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
	PrintChatMessageString();
}

void AMyPlayerController::PrintChatMessageString()
{
	if (ChatMessageString.IsEmpty())
	{
		return;
	}

	UKismetSystemLibrary::PrintString(
		this,
		ChatMessageString,
		true,
		true,
		FLinearColor::Green,
		5.0f
	);
}