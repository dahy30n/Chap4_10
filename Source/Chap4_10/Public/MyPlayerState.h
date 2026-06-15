#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"

UCLASS()
class CHAP4_10_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AMyPlayerState();

	int32 GetCurrentTryCount() const;
	int32 GetMaxTryCount() const;

	void AddTryCount();
	void ResetTryCount();

	bool CanTry() const;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UPROPERTY(Replicated) //replication
	int32 CurrentTryCount;

	UPROPERTY()
	int32 MaxTryCount;
};