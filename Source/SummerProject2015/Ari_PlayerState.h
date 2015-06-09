// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
	
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	uint8 GetTeam();

	// 0 = Everyone/Deathmatch, 1-4 = Teams
	UPROPERTY(EditAnywhere, Meta = (DisplayName = "Team Number"))
	uint8 team;
};
