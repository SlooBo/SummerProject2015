// Fill out your copyright notice in the Description page of Project Settings.

#include "SummerProject2015.h"
#include "Ari_HuntGameMode.h"
#include "Ari_PlayerState.h"

#include "Engine.h"

AAri_HuntGameMode::AAri_HuntGameMode(const FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{

}

void AAri_HuntGameMode::StartMatch()
{
	Super::StartMatch();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::White, TEXT("Hunt mode ") + FString::FromInt(players.Num()));

	for (auto player : players)
		SetRandomHuntTarget(player);
}

void AAri_HuntGameMode::PostLogin(APlayerController* newPlayer)
{
	// team testing stuff
	
	// count team members
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

	// assign new team for the player
	AAri_PlayerState* playerState = static_cast<AAri_PlayerState*>(newPlayer->PlayerState);
	if (playerState != NULL)
	{
		// team autobalance
		if (team1 <= team2)
			playerState->team = 1;
		else
			playerState->team = 2;

		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::White, TEXT("Team: ") + FString::FromInt(playerState->team));
	}
	
	Super::PostLogin(newPlayer);

	// hunt target
	for (auto player : players)
	{
		AAri_PlayerState* playerState = static_cast<AAri_PlayerState*>(player->PlayerState);
		if (playerState == NULL)
			continue;

		if (playerState->huntTarget == MAX_uint32)
			SetRandomHuntTarget(player);
	}
}

void AAri_HuntGameMode::SetRandomHuntTarget(APlayerController* player)
{
	if (players.Num() > 2)
	{
		APlayerController* target = NULL;
		uint32 targetId = 0;

		do
		{
			int j = FMath::RandRange(0, players.Num() - 1);
			target = players[j];
		} while (player == target);
		
		AAri_PlayerState* playerState = static_cast<AAri_PlayerState*>(player->PlayerState);
		AAri_PlayerState* targetState = static_cast<AAri_PlayerState*>(target->PlayerState);

		if (targetState != NULL && playerState != NULL)
			playerState->huntTarget = targetState->GetUniqueID();

		GEngine->AddOnScreenDebugMessage(-1, 100.0f, FColor::Red, player->GetName() + TEXT(" Hunts ") + target->GetName());
	}
}

void AAri_HuntGameMode::OnPlayerDeath_Implementation(APlayerController* player, APlayerController* killer)
{
	AAri_PlayerState* playerState = static_cast<AAri_PlayerState*>(player->PlayerState);
	AAri_PlayerState* killerState = (killer != NULL) ? static_cast<AAri_PlayerState*>(killer->PlayerState) : NULL;
	uint32 playerUniqueID = playerState->GetUniqueID();

	if (killerState != NULL)
	{
		if (killerState->huntTarget == playerUniqueID)
		{
			// correct target died
			killerState->frags += 1;
			killerState->Score += 1;
		}
		else
			killerState->Score -= 2;
	}

	playerState->deaths--;

	if (killer != NULL)
	{
		if (killerState->huntTarget == playerUniqueID)
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, player->GetName() + TEXT(" killed ") + killer->GetName());
		else
			GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, player->GetName() + TEXT(" killed ") + killer->GetName());
	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, player->GetName() + TEXT(" died"));

	// assign new hunt target for target and target's hunters
	for (auto p : players)
	{
		AAri_PlayerState* pState = static_cast<AAri_PlayerState*>(p->PlayerState);
		if (pState->huntTarget == playerUniqueID || pState->GetUniqueID() == playerUniqueID)
			SetRandomHuntTarget(p);
	}

	// reset character state to defaults
	player->GetPawn()->Reset();

	RestartPlayer(player);
}
