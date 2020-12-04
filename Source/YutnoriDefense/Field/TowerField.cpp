// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerField.h"

ATowerField::ATowerField()
{
	installTower = NULL;
}

void ATowerField::BeginPlay()
{
	Super::BeginPlay();
}

void ATowerField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATowerField::InstallTower(TowerData* tower, UTowerController* install)
{
	this->towerData = tower;
	this->installTower = install;
}

bool ATowerField::IsCanInstallType(int type)
{
	//설치된 타워가 없으면 바로 설치 가능
	if (installTower == NULL)
		return true;

	//설치된 타워와 타입이 같을때 설치 가능
	return IsSameType(type);
}

bool ATowerField::IsSameType(int type)
{
	//설치된 타워가 없으면 false
	if (installTower == NULL)
		return false;
	
	//설치된 타워와 타입이 같다면
	return towerData->type == type;
}

void ATowerField::DestroyTower()
{
	if (installTower != NULL &&
		installTower->IsValidLowLevel() &&
		installTower->GetOwner() != NULL &&
		installTower->GetOwner()->IsValidLowLevel())
	{
		installTower->GetOwner()->Destroy();
		installTower = NULL;
		towerData = NULL;
	}
}