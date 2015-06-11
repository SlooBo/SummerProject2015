// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UnrealNetwork.h"

#include "GameFramework/PlayerState.h"
#include "Ari_PlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SUMMERPROJECT2015_API AAri_PlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	AAri_PlayerState(const FObjectInitializer& objectInitializer);

	UFUNCTION(BlueprintCallable, Meta = (DisplayName = "Get Team Number"), Category = "Gameplay")
	uint8 GetTeam();

	UFUNCTION(BlueprintCallable, Meta = (DisplayName = "Get Frags"), Category = "Gameplay")
	int32 GetFrags();

	UFUNCTION(BlueprintCallable, Meta = (DisplayName = "Get Deaths"), Category = "Gameplay")
	int32 GetDeaths();

//private:

	// 0 = Everyone/Deathmatch, 1-4 = Teams
	UPROPERTY(Replicated, EditAnywhere, Meta = (DisplayName = "Team Number"))
	uint8 team;

	// Hunt Target
	UPROPERTY(Replicated, EditAnywhere, Meta = (DisplayName = "Hunt Target"))
	uint32 huntTarget;

	// Player Frags
	UPROPERTY(Replicated, Meta = (DisplayName = "Player Frags"))
	int32 frags;

	// Player Deaths
	UPROPERTY(Replicated, Meta = (DisplayName = "Player Deaths"))
	int32 deaths;
};
