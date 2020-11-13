// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseField.h"
#include "TowerField.generated.h"

/**
 * 
 */
UCLASS()
class YUTNORIDEFENSE_API ATowerField : public ABaseField
{
	GENERATED_BODY()
	
public:
	ATowerField();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
