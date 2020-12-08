// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"

// Sets default values for this component's properties
UEnemyController::UEnemyController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts
void UEnemyController::BeginPlay()
{
	Super::BeginPlay();
	
	meshRoot = Cast<USceneComponent>(GetOwner()->GetDefaultSubobjectByName(TEXT("meshRoot")));
	uiRoot = Cast<USceneComponent>(GetOwner()->GetDefaultSubobjectByName(TEXT("uiRoot")));

	GetOwner()->SetActorRotation(FRotator::ZeroRotator);
	meshRoot->SetWorldRotation(FRotator::ZeroRotator);
}


// Called every frame
void UEnemyController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	auto curPos = GetOwner()->GetActorLocation();
	auto nextFieldPos = NextMoveField->GetActorLocation();

	auto diff = nextFieldPos - curPos;

	if (diff.Size() > 3.0f)
	{
		diff.Normalize();

		auto newPos = diff * GetSpeed();
		auto nextPos = curPos + newPos * DeltaTime;

		GetOwner()->SetActorLocation(nextPos);
			
		FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(nextPos, curPos);		
		meshRoot->SetWorldRotation(Rotator);
	}
	else isMoveEnd = true;
}

void UEnemyController::Init()
{	
	this->NextMoveField = nullptr;
	this->moveFieldIndex = 0;
	this->isMoveEnd = false;
	this->defense = 0.0;
	this->speedWeight = 1.0f;
}

void UEnemyController::SetNextPos(ABaseField* field, int32 index)
{
	this->NextMoveField = field;
	this->moveFieldIndex = index;
	this->isMoveEnd = false;
}

void UEnemyController::Damage(float attack)
{
	hp -= (attack - defense);
}

float UEnemyController::GetHP()
{
	return hp;
}

float UEnemyController::GetMaxHP()
{
	return maxHp;
}

float UEnemyController::GetSpeed()
{
	return moveSpeed * speedWeight;
}

void UEnemyController::SetStat(float _hp, float _moveSpeed)
{
	this->hp = _hp;
	this->maxHp = _hp;
	this->moveSpeed = _moveSpeed;
}

void UEnemyController::SetTimer(float time, FTimerDelegate const& InDelegate)
{	
	GetOwner()->GetWorldTimerManager().SetTimer(timer, InDelegate, time, false);
}

void UEnemyController::ClearTimer()
{
	GetOwner()->GetWorldTimerManager().ClearTimer(timer);
}

void UEnemyController::ResetSpeedWeight()
{
	speedWeight = 1.0f;
}

void UEnemyController::ApplySlowEffect(float time)
{
	GetOwner()->GetWorldTimerManager().SetTimer(timer, this, &UEnemyController::EndSlowEffect, time, false);
}

void UEnemyController::EndSlowEffect()
{
	ResetSpeedWeight();
	ClearTimer();
}