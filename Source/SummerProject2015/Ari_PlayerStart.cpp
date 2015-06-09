// Fill out your copyright notice in the Description page of Project Settings.

#include "SummerProject2015.h"
#include "Ari_PlayerStart.h"

AAri_PlayerStart::AAri_PlayerStart(const FObjectInitializer& objectInitializer)
	: Super(objectInitializer)
{

}

uint8 AAri_PlayerStart::GetTeam()
{
	return team;
}