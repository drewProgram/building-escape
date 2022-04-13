// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/TriggerVolume.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void OpenDoor(float DeltaTime);
	UFUNCTION()
	void CloseDoor(float DeltaTime);

private:
	float InitialYaw;
	float CurrentYaw;
	UPROPERTY(EditAnywhere, Category="Opening")
	float OpenAngle;

	float DoorLastOpened;
	UPROPERTY(EditAnywhere, Category = "Opening")
	float DoorOpenIntensity;

	UPROPERTY(EditAnywhere, Category="Closing")
	float DoorCloseDelay;
	UPROPERTY(EditAnywhere, Category = "Closing")
	float DoorCloseIntensity;

	UPROPERTY(EditAnywhere, Category="Triggers")
	ATriggerVolume* PressurePlate;
	UPROPERTY(EditAnywhere, Category="Triggers")
	AActor* ActorThatOpens;
};
