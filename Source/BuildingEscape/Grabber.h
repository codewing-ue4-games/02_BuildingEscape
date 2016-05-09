// Copyright codewing.de 2016

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;


private:
	float Reach = 150.f;
	bool IsGrabbing = false;
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComp = nullptr;

	void FindPhysicsHandleComponent();
	void SetupInputComponent();

	void ExecuteGrab();
	void ReleaseGrab();
	void Grab();
	
	FHitResult GetFirstPhysicsBodyInReach();
	void GetTraceStartAndEnd(FVector &Start, FVector &End);

};
