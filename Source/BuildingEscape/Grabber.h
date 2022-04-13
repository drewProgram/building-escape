// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PhysicsEngine/PhysicsHandleComponent.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

private:
	UPROPERTY(EditAnywhere)
	float Reach;
	
	UPROPERTY()
	UPhysicsHandleComponent* PhysicsHandle;
	UPROPERTY()
	UInputComponent* InputComponent;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void FindPhysicsHandle();
	void SetupInputComponent();

	FHitResult GetFirstPhysicsBodyInReach() const;

	FVector GetPlayersReach() const;

	FVector GetPlayersWorldPos() const;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Grab();
	void Release();
};
