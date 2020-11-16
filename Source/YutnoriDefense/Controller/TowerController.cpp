// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerController.h"

// Sets default values for this component's properties
UTowerController::UTowerController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTowerController::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UTowerController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for (TActorIterator<AActor> It(GetWorld()); It; ++It)
	{
		AActor* findActor = *It;
		if (findActor->ActorHasTag(FName(TEXT("Enemy"))))
		{
			auto distance = GetOwner()->GetDistanceTo(findActor);

			if (distance <= 150.0f)
			{
				UE_LOG(LogTemp, Log, TEXT("Find Enemy Name :: %s / dis :: %f"), *findActor->GetName(), distance);
			}
			
		}
	}
}

