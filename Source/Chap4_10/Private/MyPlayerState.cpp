// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerState.h"

AMyPlayerState::AMyPlayerState()
{
	CurrentTryCount = 0;
	MaxTryCount = 3;
}

int32 AMyPlayerState::GetCurrentTryCount() const
{
	return CurrentTryCount;
}

int32 AMyPlayerState::GetMaxTryCount() const
{
	return MaxTryCount;
}

void AMyPlayerState::AddTryCount()
{
	CurrentTryCount++;
}

void AMyPlayerState::ResetTryCount()
{
	CurrentTryCount = 0;
}

bool AMyPlayerState::CanTry() const
{
	return CurrentTryCount < MaxTryCount;
}