// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "YutnoriDefense/Field/BaseField.h"
#include "YutnoriDefense/Field/TowerField.h"
#include "YutnoriDefense/Field/EnemyCreateField.h"
#include "YutnoriDefense/Field/EnemyMoveField.h"
#include "YutnoriDefense/Field/LifeField.h"
#include "YutnoriDefense/EnemyControll/EnemyControll.h"
#include "Engine/World.h"
#include "FieldManager.generated.h"

UCLASS()
class YUTNORIDEFENSE_API AFieldManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFieldManager();

	UPROPERTY(EditAnywhere)
	AEnemyCreateField* enemyCreateField;

	UPROPERTY(EditAnywhere)
	TArray<AEnemyMoveField*> enemyMoveFieldArray;

	UPROPERTY(EditAnywhere)
	ALifeField* lifeField;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> enemyKing_BP;
	
	UPROPERTY(VisibleAnywhere)
	TArray<UEnemyControll*> enemyArray;

	AActor* testActor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void EnemyCreateStart();

	//UPROPERTY(EditAnywhere)
	//TSubclassOf<class AActor> towerField_BP;

	//UPROPERTY(EditAnywhere)
	//TSubclassOf<class AActor> lifeField_BP;

	//UPROPERTY(EditAnywhere)
	//TSubclassOf<class AActor> enemyCreateField_BP;

	//UPROPERTY(EditAnywhere)
	//TSubclassOf<class AActor> enemyMoveField_BP;
};
