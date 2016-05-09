// Copyright codewing.de 2016

#include "BuildingEscape.h"
#include "Grabber.h"

#define OUT


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UGrabber::ExecuteGrab() {
	UE_LOG(LogTemp, Warning, TEXT("Grabbing..."))
}

void UGrabber::ReleaseGrab() {
	UE_LOG(LogTemp, Warning, TEXT("Releasing..."))
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	InputComp = GetOwner()->FindComponentByClass<UInputComponent>();

	if (PhysicsHandle) {

	} else {
		UE_LOG(LogTemp, Error, TEXT("%s: No Physics Handle attached"), *GetOwner()->GetName());
	}

	if (InputComp) {
		InputComp->BindAction("Grab", IE_Pressed, this, &UGrabber::ExecuteGrab);
		InputComp->BindAction("Grab", IE_Released, this, &UGrabber::ReleaseGrab);
	} else {
		UE_LOG(LogTemp, Error, TEXT("%s: No InputComponent attached"), *GetOwner()->GetName());
	}
	
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	FVector PlayerLocation;
	FRotator PlayerRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerLocation, 
		OUT PlayerRotation
	);

	FVector LineTraceEnd = PlayerLocation + PlayerRotation.Vector() * Reach;

	DrawDebugLine(GetWorld(), PlayerLocation, LineTraceEnd, FColor(255, 0, 0), false, .0f, 0, 10.f);

	FHitResult HitResult;
	FCollisionQueryParams TraceParams (FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult, PlayerLocation, LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams);

	AActor* ActorHit = HitResult.GetActor();
	if (ActorHit) {
		UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *(ActorHit->GetName()));
	}
}