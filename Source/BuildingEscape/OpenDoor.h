// Copyright codewing.de 2016

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

private:
	AActor* Owner;

	UPROPERTY(VisibleAnywhere)
	float OpenAngle = 90.f;

	UPROPERTY(VisibleAnywhere)
	float DoorCloseDelay = 0.6f;
	
	float DoorOpenedTime = 0.0f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	float TriggerMass = 25.0f;

	float GetTotalMassOfObjectsInTrigger();

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;

	void SetDoorOpen(bool);

	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
	
};
