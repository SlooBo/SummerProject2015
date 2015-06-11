// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Officerat.generated.h"

UCLASS()
class SUMMERPROJECT2015_API AOfficerat : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AOfficerat();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UFUNCTION(FUNC_BlueprintCallable)
	bool RemoveStamina(float Fatigue);
	UFUNCTION(FUNC_BlueprintCallable)
	void AddStamina(float Stamina);
	UFUNCTION(FUNC_BlueprintCallable)
	void AddHealth(float Health);
	UFUNCTION(BlueprintPure)
	void RemoveHealth(float Damage);
	UFUNCTION(FUNC_BlueprintPure)
	void WallJump();
	UFUNCTION(FUNC_BlueprintCallable)
	void Dash(float InputForward, float InputRight);

private:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
		USpringArmComponent* CameraSpringComponent;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
		UCameraComponent* CameraComp;

	void WallCheck();

	bool WallTouch;
	float Stamina_Max;
	float Stamina_Current;
	float Health_Max;
	float Health_Current;

	float Dash_Multiplier;
	FVector WallJumpNormal;
};
