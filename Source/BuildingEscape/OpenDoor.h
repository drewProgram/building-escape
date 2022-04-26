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

	bool OpenDoorSound;
	bool CloseDoorSound;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	FVector InitialPosition;
	float CurrentHeight;
	UPROPERTY(EditAnywhere, Category="Opening")
	float OpenHeight;

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
	float MassToOpenDoor;

	UPROPERTY()
	UAudioComponent* AudioComponent;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void OpenDoor(float DeltaTime);
	UFUNCTION()
	void CloseDoor(float DeltaTime);
	
	float CalcTotalMassOfActors() const;

	void FindAudioComponent();
	void FindPressurePlate();
};
