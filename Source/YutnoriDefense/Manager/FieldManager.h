// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "YutnoriDefense/Field/BaseField.h"
#include "YutnoriDefense/Field/TowerField.h"
#include "YutnoriDefense/Field/EnemyCreateField.h"
#include "YutnoriDefense/Field/EnemyMoveField.h"
#include "YutnoriDefense/Field/LifeField.h"
#include "Engine/World.h"
#include "FieldManager.generated.h"

UCLASS()
class YUTNORIDEFENSE_API AFieldManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFieldManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> towerField_BP;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> lifeField_BP;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> enemyCreateField_BP;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> enemyMoveField_BP;
};
