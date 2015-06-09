// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerStart.h"
#include "Ari_PlayerStart.generated.h"

/**
 * 
 */
UCLASS()
class SUMMERPROJECT2015_API AAri_PlayerStart : public APlayerStart
{
	GENERATED_BODY()

public:

	AAri_PlayerStart(const FObjectInitializer& objectInitializer);

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	uint8 GetTeam();

private:
	// 0 = Everyone/Deathmatch, 1-4 = Teams
	UPROPERTY(EditAnywhere, Meta = (DisplayName = "Team Number"))
	uint8 team;
};
