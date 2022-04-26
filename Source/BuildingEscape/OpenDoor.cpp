// Fill out your copyright notice in the Description page of Project Settings.
#include "OpenDoor.h"

#include "Components/AudioComponent.h"
#include "Components/PrimitiveComponent.h"

#include "Engine/World.h"

#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
	:
	OpenDoorSound(false),
	CloseDoorSound(true),
	OpenHeight(90.f),
	DoorLastOpened(0.f),
	DoorOpenIntensity(2.f),
	PressurePlate(nullptr),
	DoorCloseDelay(0.5f),
	DoorCloseIntensity(2.5f),
	MassToOpenDoor(50.f),
	AudioComponent(nullptr)
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	InitialPosition = GetOwner()->GetActorLocation();
	CurrentHeight = InitialPosition.Z;
	OpenHeight += InitialPosition.Z;

	FindPressurePlate();

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("Pressure Plate from %s not set"), *GetOwner()->GetName());
	}

	FindAudioComponent();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
	//UE_LOG(LogTemp, Warning, TEXT("Yaw is: %f"), CurrentYaw);

	if (CalcTotalMassOfActors() >= MassToOpenDoor)
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
	CurrentHeight = GetOwner()->GetActorLocation().Z;
	// CurrentYaw, TargetYaw, DeltaTime, degrees per second
	//float NewDoorYaw = FMath::FInterpConstantTo(GetOwner()->GetActorRotation().Yaw, TargetYaw, DeltaTime, 45);
	float NewDoorHeight = FMath::FInterpTo(CurrentHeight, OpenHeight, DeltaTime, DoorOpenIntensity);
	FVector NewDoorPosition = { InitialPosition.X, InitialPosition.Y, NewDoorHeight };

	GetOwner()->SetActorLocation(NewDoorPosition);

	if (!AudioComponent)
	{
		return;
	}
	CloseDoorSound = false;
	if (!OpenDoorSound)
	{
		AudioComponent->Play();
		OpenDoorSound = true;
	}
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	CurrentHeight = GetOwner()->GetActorLocation().Z;

	float NewDoorHeight = FMath::FInterpTo(CurrentHeight, InitialPosition.Z, DeltaTime, DoorCloseIntensity);
	FVector NewDoorPosition = { InitialPosition.X, InitialPosition.Y, NewDoorHeight };
	

	GetOwner()->SetActorLocation(NewDoorPosition);

	if (!AudioComponent)
	{
		return;
	}
	OpenDoorSound = false;
	if (!CloseDoorSound)
	{
		AudioComponent->Play();
		CloseDoorSound = true;
	}
}

float UOpenDoor::CalcTotalMassOfActors() const
{
	float TotalMass = 0.f;

	if (!PressurePlate)
	{
		return TotalMass;
	}

	TArray<AActor*> OverlapingActors;
	PressurePlate->GetOverlappingActors(OverlapingActors);

	for (AActor* Actor : OverlapingActors)
	{
		if (!Actor)
		{
			UE_LOG
			(
				LogTemp, Error,
				TEXT("(%s) Overlaped Actor points to null at %s"),
				*GetOwner()->GetName(),
				*GetName()
			);
		}
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}

void UOpenDoor::FindAudioComponent()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
	if (!AudioComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("%s Missing audio component!"), *GetOwner()->GetName());
	}
}

void UOpenDoor::FindPressurePlate()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
	if (!AudioComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("%s Missing audio component!"), *GetOwner()->GetName());
	}
}
