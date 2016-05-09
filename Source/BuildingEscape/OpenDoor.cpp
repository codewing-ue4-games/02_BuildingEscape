// Copyright codewing.de 2016

#include "BuildingEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
}

void UOpenDoor::SetDoorOpen(bool open) {
	FRotator NewRotation;
	if (open) {
		NewRotation = FRotator(.0f, OpenAngle, .0f);
		DoorOpenedTime = GetWorld()->GetTimeSeconds();
	} else {
		NewRotation = FRotator(.0f, 0.0f, .0f);
	}
	Owner->SetActorRotation(NewRotation);
}


float UOpenDoor::GetTotalMassOfObjectsInTrigger() {
	float TotalMass = 0.f;
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OverlappingActors);

	for (const auto& Actor : OverlappingActors) {
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	
	return TotalMass;
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (GetTotalMassOfObjectsInTrigger() > TriggerMass) {
		SetDoorOpen(true);
	}

	if (DoorOpenedTime + DoorCloseDelay < GetWorld()->GetTimeSeconds()) {
		SetDoorOpen(false);
	}
}

