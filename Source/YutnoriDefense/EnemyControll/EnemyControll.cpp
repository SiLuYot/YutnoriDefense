// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyControll.h"

// Sets default values for this component's properties
UEnemyControll::UEnemyControll()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UEnemyControll::BeginPlay()
{
	Super::BeginPlay();

	GetOwner()->SetActorRotation(FRotator::ZeroRotator);	
}

// Called every frame
void UEnemyControll::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	auto curPos = GetOwner()->GetActorLocation();
	auto nextFieldPos = NextMoveField->GetActorLocation();

	auto diff = nextFieldPos - curPos;

	if (diff.Size() > 1.0f)
	{
		diff.Normalize();

		auto newPos = diff * moveSpeed;
		auto nextPos = curPos + newPos * DeltaTime;

		GetOwner()->SetActorLocation(nextPos);		

		FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(nextPos, curPos);
		GetOwner()->SetActorRotation(Rotator);
	}
	else isMoveEnd = true;
}

void UEnemyControll::Init(ABaseField* field, int32 index)
{
	this->NextMoveField = field;
	this->moveFieldIndex = index;
	this->isMoveEnd = false;
}

