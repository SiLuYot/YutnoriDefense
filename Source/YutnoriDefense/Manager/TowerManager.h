// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "YutnoriDefense/Field/BaseField.h"
#include "YutnoriDefense/Field/TowerField.h"
#include "CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "TowerManager.generated.h"

UCLASS()
class YUTNORIDEFENSE_API ATowerManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATowerManager();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> testTower_BP;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void ClickFieldEvent(ABaseField* field);
};