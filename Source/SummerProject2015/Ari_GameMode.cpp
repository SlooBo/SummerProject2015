// Fill out your copyright notice in the Description page of Project Settings.

#include "SummerProject2015.h"

#include "Ari_GameMode.h"
#include "Ari_PlayerStart.h"
#include "Ari_GameState.h"
#include "Ari_PlayerState.h"

#include "Engine.h"

AAri_GameMode::AAri_GameMode(const FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{
	// defaults for game mode

	static ConstructorHelpers::FClassFinder<APawn> playerPawn(TEXT("/Game/OfficeWars/Blueprints/OfficeRat"));

	if (playerPawn.Class != NULL)
		DefaultPawnClass = playerPawn.Class;

	GameStateClass = AAri_GameState::StaticClass();
	PlayerStateClass = AAri_PlayerState::StaticClass();
}

AActor* AAri_GameMode::ChoosePlayerStart(AController* player)
{
	AAri_PlayerStart* best = NULL;
	TArray<AAri_PlayerStart*> spawns;
	int numSpawns = 0;
	int spawn = 0;
	int team = 0;
	
	// get player's current team
	AAri_PlayerState* playerState = static_cast<AAri_PlayerState*>(player->PlayerState);
	if (playerState != NULL)
		team = playerState->GetTeam();

	// find team spawns
	for (TActorIterator<AAri_PlayerStart> iter(GetWorld()); iter; ++iter)
	{
		int spawnTeam = (*iter)->GetTeam();
		if (spawnTeam == team)
			spawns.Add(*iter);
	}

	// no prefered team spawns found, fallback to deathmatch spawn points
	if (spawns.Num() == 0 && team != 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("No team spawn points were found, falling back to deathmatch spawns"));

		for (TActorIterator<AAri_PlayerStart> iter(GetWorld()); iter; ++iter)
			if ((*iter)->GetTeam() == 0)
				spawns.Add(*iter);
	}

	// choose the random spawn
	int random = FMath::RandRange(0, spawns.Num() - 1);
	if (spawns.IsValidIndex(random))
		best = spawns[random];

	if (best == NULL)
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::White, TEXT("Error: No spawn"));

	return (AActor*)best;
}

void AAri_GameMode::StartPlay()
{
	Super::StartPlay();
}

void AAri_GameMode::StartMatch()
{
	Super::StartMatch();

	if (mapTimelimit > 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(mapTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(mapTimerHandle, this, &AAri_GameMode::MapTimeout, 1.0f*mapTimelimit/**60.0f*/);
	}

	OnStartMatch();
}

APlayerController* AAri_GameMode::Login(class UPlayer* newPlayer, const FString& portal, const FString& options,
	const TSharedPtr<class FUniqueNetId>& uniqueId, FString& errorMessage)
{
	// player has succesfully logged in the server
	return Super::Login(newPlayer, portal, options, uniqueId, errorMessage);
}

void AAri_GameMode::PostLogin(APlayerController* newPlayer)
{
	players.Add(newPlayer);

	Super::PostLogin(newPlayer);

	RestartPlayer(newPlayer);
}

void AAri_GameMode::Logout(AController* exiting)
{
	Super::Logout(exiting);

	APlayerController* player = static_cast<APlayerController*>(exiting);
	if (player != NULL)
		players.Remove(player);
}

void AAri_GameMode::RestartPlayer(AController* newPlayer)
{
	Super::RestartPlayer(newPlayer);
}

bool AAri_GameMode::ShouldSpawnAtStartSpot(AController* player)
{
	return false;
}

bool AAri_GameMode::ShouldReset(AActor* actorToReset)
{
	return true;
}

FString AAri_GameMode::InitNewPlayer(APlayerController* newPlayerController, const TSharedPtr<FUniqueNetId>& uniqueId,
	const FString& options, const FString& portal)
{
	return Super::InitNewPlayer(newPlayerController, uniqueId, options, portal);
}

UClass* AAri_GameMode::GetDefaultPawnClassForController(AController* controller)
{
	return DefaultPawnClass;
}

void AAri_GameMode::MapTimeout()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, TEXT("Map timelimit reached"));

	OnMapTimeout();
}

float AAri_GameMode::MapTimeleft()
{
	return GetWorld()->GetTimerManager().GetTimerRemaining(mapTimerHandle);
}

float AAri_GameMode::MapTimeElapsed()
{
	return GetWorld()->GetTimerManager().GetTimerElapsed(mapTimerHandle);
}

void AAri_GameMode::PlayerDeath(APlayerController* player, APlayerController* killer)
{
	OnPlayerDeath(player, killer);
}

void AAri_GameMode::OnPlayerDeath_Implementation(APlayerController* player, APlayerController* killer)
{
	AAri_PlayerState* playerState = static_cast<AAri_PlayerState*>(player->PlayerState);
	AAri_PlayerState* killerState = (killer != NULL) ? static_cast<AAri_PlayerState*>(killer->PlayerState) : NULL;

	if (killerState != NULL)
	{
		killerState->frags += 1;
		killerState->Score += 1;
	}

	playerState->deaths--;

	if (killer != NULL)
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, player->GetName() + TEXT(" killed ") + killer->GetName());
	else
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, player->GetName() + TEXT(" died"));

	// reset character state to defaults
	player->GetPawn()->Reset();

	RestartPlayer(player);
}