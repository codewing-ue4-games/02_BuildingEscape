// Copyright codewing.de 2016

#include "BuildingEscape.h"
#include "Grabber.h"

#define OUT


// Sets default values for this component's properties
UGrabber::UGrabber() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	SetupInputComponent();
	FindPhysicsHandleComponent();
}


void UGrabber::FindPhysicsHandleComponent() {
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle) {
	} else {
		UE_LOG(LogTemp, Error, TEXT("%s: No Physics Handle attached"), *GetOwner()->GetName());
	}
}

void UGrabber::ExecuteGrab() {
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	if (HitResult.GetActor()) {
		PhysicsHandle->GrabComponent(HitResult.GetComponent(), NAME_None, HitResult.GetActor()->GetActorLocation(), true);
	}
}

void UGrabber::ReleaseGrab() {
	if (PhysicsHandle->GrabbedComponent) {
		PhysicsHandle->ReleaseComponent();
	}
}

void UGrabber::Grab() {

	if (!PhysicsHandle) {return;}

	if (IsGrabbing) {
		ReleaseGrab();
	} else {
		ExecuteGrab();
	}
	IsGrabbing = !IsGrabbing;
}


void UGrabber::SetupInputComponent() {
	InputComp = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComp) {
		InputComp->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	} else {
		UE_LOG(LogTemp, Error, TEXT("%s: No InputComponent attached"), *GetOwner()->GetName());
	}
}

// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (!PhysicsHandle) {return;}

	if (PhysicsHandle->GrabbedComponent) {
		FVector PlayerLocation;
		FVector LineTraceEnd;
		GetTraceStartAndEnd(PlayerLocation, LineTraceEnd);

		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() {
	FVector PlayerLocation;
	FVector LineTraceEnd;

	GetTraceStartAndEnd(PlayerLocation, LineTraceEnd);

	FHitResult HitResult;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult, PlayerLocation, LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams);

	AActor* ActorHit = HitResult.GetActor();
	if (ActorHit) {
		UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *(ActorHit->GetName()));
	}

	return HitResult;
}

void UGrabber::GetTraceStartAndEnd(FVector &Start, FVector &End) {
	FVector PlayerLocation;
	FRotator PlayerRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerLocation,
		OUT PlayerRotation
		);

	FVector LineTraceEnd = PlayerLocation + PlayerRotation.Vector() * Reach;

	Start = PlayerLocation;
	End = LineTraceEnd;
}
