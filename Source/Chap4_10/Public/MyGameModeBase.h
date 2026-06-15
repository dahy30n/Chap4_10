// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

UCLASS()
class CHAP4_10_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyGameModeBase();

	virtual void BeginPlay() override;	

	FString RunBaseballTurn(AController* PlayerController, const FString& Input);

	virtual void PostLogin(APlayerController* NewPlayer) override;

private:
	int32 PlayerNumber = 1;

	TArray<int32> AnswerNumbers;

	void GenerateAnswerNumbers();

	bool IsValidInput(const FString& Input, FString& ErrorMessage) const;

	FString CheckAnswer(const FString& Input) const;
};