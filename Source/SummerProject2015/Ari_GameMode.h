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
	virtual void StartPlay() override;
	virtual void StartMatch() override;
	virtual APlayerController* Login(class UPlayer* newPlayer, const FString& portal, const FString& options,
		const TSharedPtr<class FUniqueNetId>& uniqueId, FString& errorMessage) override;
	virtual void PostLogin(APlayerController* newPlayer) override;
	virtual void Logout(AController* exiting) override;
	virtual void RestartPlayer(AController* newPlayer) override;
	virtual bool ShouldSpawnAtStartSpot(AController* player) override;
	virtual bool ShouldReset(AActor* actorToReset) override;
	virtual FString InitNewPlayer(APlayerController* newPlayerController, const TSharedPtr<FUniqueNetId>& uniqueId,
		const FString& options, const FString& portal) override;
	virtual UClass* GetDefaultPawnClassForController(AController* controller) override;

	void MapTimeout();

	UFUNCTION(BlueprintCallable, Meta = (FriendlyName = "Map Time Left"), Category = "Gameplay")
	float MapTimeleft();

	UFUNCTION(BlueprintCallable, Meta = (FriendlyName = "Map Time Elapsed"), Category = "Gameplay")
	float MapTimeElapsed();

	UFUNCTION(BlueprintCallable, Meta = (FriendlyName = "Player Death"), Category = "Gameplay")
	void PlayerDeath(APlayerController* player, APlayerController* killer = NULL);

	// Events
	// ----------------

	// Event when match has started
	UFUNCTION(BlueprintImplementableEvent, Meta = (FriendlyName = "On Start Match"), Category = "Gameplay")
	virtual void OnStartMatch();

	// Event when map time has reached zero
	UFUNCTION(BlueprintImplementableEvent, Meta = (FriendlyName = "On Map Timeout"), Category = "Gameplay")
	virtual void OnMapTimeout();

	// Event when player dies or is killed by other player
	UFUNCTION(BlueprintNativeEvent, Meta = (FriendlyName = "On Player Death"), Category = "Gameplay")
	void OnPlayerDeath(APlayerController* player, APlayerController* killer = NULL);

	// Properties
	// ----------------

	// Timelimit in minutes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (DisplayName = "Map Timelimit"))
	int32 mapTimelimit;

protected:
	TArray<APlayerController*> players;
	FTimerHandle mapTimerHandle;

};
