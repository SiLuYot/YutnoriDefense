// Fill out your copyright notice in the Description page of Project Settings.


#include "FieldManager.h"

// Sets default values
AFieldManager::AFieldManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UWorld* const World = GetWorld();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = Instigator;	

	World->SpawnActor<ATowerField>(SpawnObject, SpawnParams);
}

// Called when the game starts or when spawned
void AFieldManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFieldManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

