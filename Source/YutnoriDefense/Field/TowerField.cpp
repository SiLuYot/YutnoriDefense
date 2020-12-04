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
	//��ġ�� Ÿ���� ������ �ٷ� ��ġ ����
	if (installTower == NULL)
		return true;

	//��ġ�� Ÿ���� Ÿ���� ������ ��ġ ����
	return IsSameType(type);
}

bool ATowerField::IsSameType(int type)
{
	//��ġ�� Ÿ���� ������ false
	if (installTower == NULL)
		return false;
	
	//��ġ�� Ÿ���� Ÿ���� ���ٸ�
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