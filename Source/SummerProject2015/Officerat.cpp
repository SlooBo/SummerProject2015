// Fill out your copyright notice in the Description page of Project Settings.

#include "SummerProject2015.h"
#include "Officerat.h"


// Sets default values
AOfficerat::AOfficerat()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FObjectInitializer initializer;
	CameraSpringComponent = initializer.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("CameraSpring"));
	//Maybe bUsePawnControlRotation = true
	CameraSpringComponent->bUseControllerViewRotation = true;
	CameraSpringComponent->AttachParent = GetRootComponent();

	CameraComp = initializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("Camera"));
	CameraComp->AttachParent = CameraSpringComponent;

	Health_Max = 100;
	Health_Current = Health_Max;

	Stamina_Max = 100;
	Stamina_Current = Stamina_Max;

	WallTouch = false;
	Dash_Multiplier = 0;
}

// Called when the game starts or when spawned
void AOfficerat::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOfficerat::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	WallCheck();
	FKey E("E");
	AOfficerat::EditorKeyPressed(E, EInputEvent::IE_Pressed);
}

// Called to bind functionality to input
void AOfficerat::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void AOfficerat::WallCheck()
{
	FRotator ActorRotation = this->GetActorRotation();
	FRotator ActorYaw(0, ActorRotation.Yaw, 0);
	//This line needs checking!!!
	FVector ForwardVector = ActorYaw.Vector();
	FVector ActorLocation = this->GetActorLocation();

	FVector ForwardCheckVector = ForwardVector * 100;
	ForwardCheckVector = ActorLocation + ForwardCheckVector;

	//https://goo.gl/pN6vYF
	FCollisionQueryParams  TraceParams = FCollisionQueryParams(FName(TEXT("RV_TRACE")), false, this);
	TraceParams.bTraceComplex = false;
	TraceParams.bTraceAsyncScene = false;
	TraceParams.bReturnPhysicalMaterial = false;

	FHitResult RV_Hit(ForceInit);
	//Forward check
	GetWorld()->LineTraceSingle(
		RV_Hit,//result
		ActorLocation,//start of line trace
		ForwardCheckVector,//end of line trace
		ECC_Pawn,//collision channel, maybe wrong
		TraceParams);
	if (RV_Hit.bBlockingHit == true)
	{
		WallTouch = true;
		WallJumpNormal = RV_Hit.ImpactNormal;
		return;
	}
	
	FVector RightCheckVector = ForwardVector.RotateAngleAxis(90, FVector(0, 1, 0));
	RightCheckVector = RightCheckVector * 100;
	//Right check
	GetWorld()->LineTraceSingle(
		RV_Hit,//result
		ActorLocation,//start of line trace
		RightCheckVector,//end of line trace
		ECC_Pawn,//collision channel, maybe wrong
		TraceParams);

	if (RV_Hit.bBlockingHit == true)
	{
		WallTouch = true;
		WallJumpNormal = RV_Hit.ImpactNormal;
		return;
	}

	FVector LeftCheckVector = LeftCheckVector.RotateAngleAxis(270, FVector(0, 1, 0));
	LeftCheckVector = LeftCheckVector * 100;
	//Left check
	GetWorld()->LineTraceSingle(
		RV_Hit,//result
		ActorLocation,//start of line trace
		LeftCheckVector,//end of line trace
		ECC_Pawn,//collision channel, maybe wrong
		TraceParams);

	if (RV_Hit.bBlockingHit == true)
	{
		WallTouch = true;
		WallJumpNormal = RV_Hit.ImpactNormal;
		return;
	}
	else
	WallTouch = false;
}

void AOfficerat::WallJump()
{
	if (WallTouch == true)
	{
		if (this->CharacterMovement->IsFalling() == true)
		{
			//To disable ever increasing falling speed
			this->CharacterMovement->Velocity = FVector(0, 0, 0);

			FRotator ControllerRotation = GetControlRotation();
			FRotator ControllerYaw(0, ControllerRotation.Yaw, 0);
			//This line needs checking!!!
			FVector ForwardVector = ControllerYaw.Vector();
			FVector Result = ForwardVector.MirrorByVector(WallJumpNormal);
			Result = Result + FVector(0, 0, 1000);

			LaunchCharacter(Result, false, false);
			//Hox!
			RemoveStamina(25);
		}
	}
}

void AOfficerat::Dash(float InputForward, float InputRight)
{
	if (this->CharacterMovement->IsFalling() == true)
	{
		Dash_Multiplier = 1000;
	}
	else
	{
		Dash_Multiplier = 5000;
	}

	FVector Forward = this->GetActorForwardVector();
	FVector Right = this->GetActorRightVector();
	FVector ForwardResult = Forward + InputForward;
	FVector RightResult = Right + InputRight;
	FVector Result = ForwardResult + RightResult;
	Result.Normalize();
	Result = Result * Dash_Multiplier;
	this->LaunchCharacter(Result, false, false);
}

bool AOfficerat::RemoveStamina(float Fatigue)
{
	if (Stamina_Current - Fatigue <= 0)
	{
		return false;
	}
	else
	{
		Stamina_Current = Stamina_Current - Fatigue;
		return true;
	}
}

void AOfficerat::AddStamina(float Stamina)
{
	if (Stamina_Current + Stamina > Stamina_Max)
		Stamina_Current = Stamina_Max;
	else
		Stamina_Current = Stamina_Current + Stamina;
}

void AOfficerat::RemoveHealth(float Damage)
{
	Health_Current = Health_Current - Damage;
}

void AOfficerat::AddHealth(float Health)
{
	if (Health_Current + Health > Health_Max)
		Health_Current = Health_Max;
	else
		Health_Current = Health_Current + Health;
}