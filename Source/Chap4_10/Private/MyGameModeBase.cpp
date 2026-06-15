// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameModeBase.h"
#include "MyPlayerState.h"

#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/Controller.h"


AMyGameModeBase::AMyGameModeBase()
{
	PlayerStateClass = AMyPlayerState::StaticClass();
}

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	GenerateAnswerNumbers();
}	

void AMyGameModeBase::GenerateAnswerNumbers()
{
	AnswerNumbers.Empty();

	while (AnswerNumbers.Num() < 3)
	{
		int32 RandomNumber = FMath::RandRange(1, 9);

		if (!AnswerNumbers.Contains(RandomNumber))
		{
			AnswerNumbers.Add(RandomNumber);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Answer: %d%d%d"),
		AnswerNumbers[0],
		AnswerNumbers[1],
		AnswerNumbers[2]);
}

bool AMyGameModeBase::IsValidInput(const FString& Input, FString& ErrorMessage) const
{
	if (Input.Len() != 3) //length of fstring over 3
	{
		ErrorMessage = TEXT("3자리 숫자를 입력해주세요.");
		return false;
	}

	TArray<TCHAR> UsedChars;

	for (int32 i = 0; i < Input.Len(); i++)
	{
		TCHAR CurrentChar = Input[i];

		if (!FChar::IsDigit(CurrentChar)) //isnumber
		{
			ErrorMessage = TEXT("숫자만 입력해주세요.");
			return false;
		}

		if (CurrentChar == TEXT('0'))
		{
			ErrorMessage = TEXT("1부터 9까지의 숫자만 입력해주세요.");
			return false;
		}

		if (UsedChars.Contains(CurrentChar))
		{
			ErrorMessage = TEXT("중복되지 않은 숫자를 입력해주세요.");
			return false;
		}

		UsedChars.Add(CurrentChar);
	}

	return true;
}

FString AMyGameModeBase::CheckAnswer(const FString& Input) const
{
	int32 StrikeCount = 0;
	int32 BallCount = 0;

	for (int32 i = 0; i < 3; i++)
	{
		int32 InputNumber = Input[i] - TEXT('0');

		if (AnswerNumbers[i] == InputNumber)
		{
			StrikeCount++;
		}
		else if (AnswerNumbers.Contains(InputNumber))
		{
			BallCount++;
		}
	}

	if (StrikeCount == 0 && BallCount == 0)
	{
		return TEXT("OUT");
	}

	return FString::Printf(TEXT("%dS%dB"), StrikeCount, BallCount);
}

FString AMyGameModeBase::RunBaseballTurn(AController* PlayerController, const FString& Input)
{
	if (!PlayerController)
	{
		return TEXT("PlayerController가 없습니다.");
	}

	AMyPlayerState* MyPlayerState = PlayerController->GetPlayerState<AMyPlayerState>();

	if (!MyPlayerState)
	{
		return TEXT("PlayerState가 없습니다.");
	}

	if (!MyPlayerState->CanTry())
	{
		return TEXT("이미 기회를 모두 사용했습니다.");
	}

	FString ErrorMessage;

	if (!IsValidInput(Input, ErrorMessage))
	{
		return ErrorMessage;
	}

	MyPlayerState->AddTryCount();

	FString Result = CheckAnswer(Input);

	if (Result == TEXT("3S0B"))
	{
		//전체 리셋
		if (GameState)
		{
			for (APlayerState* PlayerState : GameState->PlayerArray)
			{
				AMyPlayerState* MyPS = Cast<AMyPlayerState>(PlayerState);

				if (MyPS)
				{
					MyPS->ResetTryCount();
				}
			}
		}

		GenerateAnswerNumbers();

		return TEXT("\n\nWIN! 게임을 다시 시작합니다.");
	}

	//draw
	bool bIsDraw = true;

	if (GameState)
	{
		for (APlayerState* PlayerState : GameState->PlayerArray)
		{
			AMyPlayerState* MyPS = Cast<AMyPlayerState>(PlayerState);

			if (MyPS && MyPS->CanTry())
			{
				bIsDraw = false;
				break;
			}
		}
	}

	if (bIsDraw)
	{
		//전체 리셋
		if (GameState)
		{
			for (APlayerState* PlayerState : GameState->PlayerArray)
			{
				AMyPlayerState* MyPS = Cast<AMyPlayerState>(PlayerState);

				if (MyPS)
				{
					MyPS->ResetTryCount();
				}
			}
		}

		GenerateAnswerNumbers();

		return Result + TEXT("\n\nDRAW! 게임을 다시 시작합니다.");
	}

	return Result;
}

void AMyGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (!NewPlayer) return; 

	APlayerState* PS = NewPlayer->PlayerState;

	if (!PS) return;

	FString NewName = FString::Printf(TEXT("Player %d"), PlayerNumber);
	PS->SetPlayerName(NewName);

	PlayerNumber++;

	UE_LOG(LogTemp, Warning, TEXT("New Player Name: %s"), *PS->GetPlayerName());
}