// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPosition.h"

#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();

	//FString Log = TEXT("Hello!");
	//FString* LogPtr = &Log;

	//// * operator is overloaded on this macro
	//UE_LOG(LogTemp, Warning, TEXT("%s"), **LogPtr);

	FString ActorName;
	GetOwner()->GetName(ActorName);
	FString ActorPosition = GetOwner()->GetActorLocation().ToString();
	//FVector ActorPosition = GetOwner()->GetActorLocation();

	FString ComponentName = GetName();

	UE_LOG(LogTemp, Warning,
		TEXT("Component %s is owned by Actor %s."),
		*ComponentName,
		*ActorName
	);
	/*UE_LOG(LogTemp, Warning,
		TEXT("%s is located at X: %f Y: %f Z: %f"),
		*ActorName,
		ActorPosition.X,
		ActorPosition.Y,
		ActorPosition.Z
	);*/
	UE_LOG(LogTemp, Warning,
		TEXT("%s is located at %s"),
		*ActorName,
		*ActorPosition
	);
}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

