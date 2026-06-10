// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserChatWidget.h"

#include "Components/EditableTextBox.h"
#include "MyPlayerController.h"


void UMyUserChatWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (chatInput)
	{
		chatInput->OnTextCommitted.AddDynamic(this, &UMyUserChatWidget::OnChatTextCommitted);
		chatInput->SetKeyboardFocus();
	}
}

void UMyUserChatWidget::OnChatTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod != ETextCommit::OnEnter)
	{
		return;
	}

	const FString Message = Text.ToString().TrimStartAndEnd();

	if (Message.IsEmpty())
	{
		return;
	}

	AMyPlayerController* MyPlayerController = Cast<AMyPlayerController>(GetOwningPlayer());

	if (MyPlayerController)
	{
		MyPlayerController->SetChatMessageString(Message);
	}

	if (chatInput)
	{
		chatInput->SetText(FText::GetEmpty());
	}
}