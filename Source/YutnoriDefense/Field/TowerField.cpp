// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerField.h"

ATowerField::ATowerField()
{
	PrimaryActorTick.bCanEverTick = true;

	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	//tempMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	
}

void ATowerField::BeginPlay()
{
	Super::BeginPlay();
}

void ATowerField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}