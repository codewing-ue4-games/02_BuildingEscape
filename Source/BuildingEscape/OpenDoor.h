// Copyright codewing.de 2016

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenRequest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseRequest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

private:
	AActor* Owner = nullptr;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	float TriggerMass = 25.0f;

	float GetTotalMassOfObjectsInTrigger();

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintAssignable)
	FOnOpenRequest OnOpenRequest;

	UPROPERTY(BlueprintAssignable)
	FOnCloseRequest OnCloseRequest;

	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
	
};
