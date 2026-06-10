// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CHAP4_10_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public: 
	AMyPlayerController();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Chat")
	void SetChatMessageString(const FString& NewMessage);
	
	UFUNCTION(BlueprintCallable, Category = "Chat")
	void PrintChatMessageString();

	bool bShowMouseCursor;
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Chat")
	TSubclassOf<UUserWidget> ChatInputWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UUserWidget> ChatInputWidget;

private: 
	UPROPERTY(VisibleAnywhere, Category = "Chat")
	FString ChatMessageString;

};
