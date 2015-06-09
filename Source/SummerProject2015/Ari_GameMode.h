// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "Ari_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class SUMMERPROJECT2015_API AAri_GameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AAri_GameMode(const class FObjectInitializer& objectInitializer);

	virtual AActor* ChoosePlayerStart(AController* player);
	virtual void StartMatch() override;
	virtual void StartPlay() override;

	virtual APlayerController* Login(class UPlayer* newPlayer, const FString& portal, const FString& options,
		const TSharedPtr<class FUniqueNetId>& uniqueId, FString& errorMessage) override;
	virtual void PostLogin(APlayerController* newPlayer) override;
	virtual void Logout(AController* exiting) override;
	virtual void RestartPlayer(AController* newPlayer) override;
	virtual bool ShouldSpawnAtStartSpot(AController* player) override;
	virtual FString InitNewPlayer(APlayerController* newPlayerController, const TSharedPtr<FUniqueNetId>& uniqueId,
		const FString& options, const FString& portal) override;

protected:
	TArray<APlayerController*> players;
};
