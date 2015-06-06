// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "SummerProject2015.h"
#include "SummerProject2015GameMode.h"
#include "SummerProject2015Character.h"

ASummerProject2015GameMode::ASummerProject2015GameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
