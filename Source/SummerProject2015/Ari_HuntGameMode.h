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

	virtual void StartPlay() override;
	
	virtual void PostLogin(APlayerController* newPlayer) override;
};
