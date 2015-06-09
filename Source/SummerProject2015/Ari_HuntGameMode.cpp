// Fill out your copyright notice in the Description page of Project Settings.

#include "SummerProject2015.h"
#include "Ari_HuntGameMode.h"
#include "Ari_PlayerState.h"

#include "Engine.h"

AAri_HuntGameMode::AAri_HuntGameMode(const FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{

}

void AAri_HuntGameMode::StartPlay()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, TEXT("Hunt mode"));

	Super::StartPlay();
}

void AAri_HuntGameMode::PostLogin(APlayerController* newPlayer)
{
	// team testing stuff
	
	int team1 = 0, team2 = 0;
	for (APlayerController* player : players)
	{
		AAri_PlayerState* playerState = static_cast<AAri_PlayerState*>(player->PlayerState);
		if (playerState == NULL)
			continue;
		else if (playerState->team == 1)
			team1++;
		else if (playerState->team == 2)
			team2++;
	}

	AAri_PlayerState* playerState = static_cast<AAri_PlayerState*>(newPlayer->PlayerState);
	if (playerState != NULL)
	{
		// team autobalance
		if (team1 <= team2)
			playerState->team = 1;
		else
			playerState->team = 2;

		//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::White, TEXT("Team: ") + FString::FromInt(playerState->team));
	}

	Super::PostLogin(newPlayer);
}


