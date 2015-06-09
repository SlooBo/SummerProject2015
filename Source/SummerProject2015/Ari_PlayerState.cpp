// Fill out your copyright notice in the Description page of Project Settings.

#include "SummerProject2015.h"
#include "Ari_PlayerState.h"

AAri_PlayerState::AAri_PlayerState(const FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{

}

uint8 AAri_PlayerState::GetTeam()
{
	return team;
}