// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseField.h"
#include "YutnoriDefense/Controller/TowerController.h"
#include "YutnoriDefense/Manager/CustomStruct.h"
#include "TowerField.generated.h"

/**
 * 
 */
UCLASS()
class YUTNORIDEFENSE_API ATowerField : public ABaseField
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
	FTowerData towerData;

	UTowerController* installTower;	
	
	ATowerField();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void InstallTower(FTowerData tower, UTowerController* install);
	bool IsCanInstallType(int type);
	bool IsSameType(int type);
	void DestroyTower();
};
