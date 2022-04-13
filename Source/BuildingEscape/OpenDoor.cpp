// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"

#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
	:
	OpenAngle(90.f),
	PressurePlate(nullptr),
	ActorThatOpens(nullptr),
	DoorLastOpened(0.f),
	DoorCloseDelay(0.5f),
	DoorOpenIntensity(2.f),
	DoorCloseIntensity(2.5f)
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	OpenAngle += InitialYaw;

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("Pressure Plate from %s not set"), *GetOwner()->GetName());
	}

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
	//UE_LOG(LogTemp, Warning, TEXT("Yaw is: %f"), CurrentYaw);

	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else if (GetWorld()->GetTimeSeconds() - DoorLastOpened >= DoorCloseDelay)
	{
		CloseDoor(DeltaTime);
	}
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	// CurrentYaw, TargetYaw, DeltaTime, degrees per second
	//float NewDoorYaw = FMath::FInterpConstantTo(GetOwner()->GetActorRotation().Yaw, TargetYaw, DeltaTime, 45);
	float NewDoorYaw = FMath::FInterpTo(CurrentYaw, OpenAngle, DeltaTime, DoorOpenIntensity);
	FRotator NewDoorRotator = { 0.f, NewDoorYaw, 0.f };

	GetOwner()->SetActorRotation(NewDoorRotator);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	float NewDoorYaw = FMath::FInterpTo(CurrentYaw, InitialYaw, DeltaTime, DoorCloseIntensity);
	FRotator NewDoorRotation = { 0.f, NewDoorYaw, 0.f };

	GetOwner()->SetActorRotation(NewDoorRotation);
}