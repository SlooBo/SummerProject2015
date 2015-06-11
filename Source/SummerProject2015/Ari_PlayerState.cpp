// Fill out your copyright notice in the Description page of Project Settings.

#include "SummerProject2015.h"
#include "Ari_PlayerState.h"

AAri_PlayerState::AAri_PlayerState(const FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{
	huntTarget = MAX_uint32;
}

void AAri_PlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAri_PlayerState, team);
	DOREPLIFETIME(AAri_PlayerState, huntTarget);
	DOREPLIFETIME(AAri_PlayerState, kills);
};

uint8 AAri_PlayerState::GetTeam()
{
	return team;
}

int32 AAri_PlayerState::GetKills()
{
	return kills;
}