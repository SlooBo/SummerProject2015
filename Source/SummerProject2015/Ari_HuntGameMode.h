// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Ari_GameMode.h"
#include "Ari_HuntGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SUMMERPROJECT2015_API AAri_HuntGameMode : public AAri_GameMode
{
	GENERATED_BODY()

public:
	AAri_HuntGameMode(const class FObjectInitializer& objectInitializer);

	virtual void StartMatch() override;
	virtual void PostLogin(APlayerController* newPlayer) override;

	// Event when player dies or is killed by other player
	//UFUNCTION(BlueprintNativeEvent, Meta = (FriendlyName = "On Player Death"), Category = "Gameplay|Player")
	//void OnPlayerDeath(APlayerController* player, APlayerController* killer = NULL);
	virtual void OnPlayerDeath_Implementation(APlayerController* player, APlayerController* killer = NULL);

	UFUNCTION(BlueprintCallable, Meta = (FriendlyName = "Set Random Hunt Target"), Category = "Gameplay")
	void SetRandomHuntTarget(APlayerController* player);

	
};
