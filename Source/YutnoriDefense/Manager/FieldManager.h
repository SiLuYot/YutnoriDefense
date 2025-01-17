// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "YutnoriDefense/Field/BaseField.h"
#include "YutnoriDefense/Field/TowerField.h"
#include "YutnoriDefense/Field/EnemyCreateField.h"
#include "YutnoriDefense/Field/EnemyMoveField.h"
#include "YutnoriDefense/Field/LifeField.h"
#include "YutnoriDefense/Controller/EnemyController.h"
#include "Containers/Queue.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "FieldManager.generated.h"

UCLASS()
class YUTNORIDEFENSE_API AFieldManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFieldManager();

	UPROPERTY(BlueprintReadWrite)
	int stage;

	UPROPERTY(BlueprintReadWrite)
	int deathCount;

	UPROPERTY(BlueprintReadWrite)
	int yut;

	UPROPERTY(BlueprintReadWrite)
	bool isRestTime;

	UPROPERTY(BlueprintReadWrite)
	bool isPlayBattleBGM;

	UPROPERTY(BlueprintReadWrite)
	bool isClear;

	UPROPERTY(EditAnywhere)
	float enemySpawnTimer;

	UPROPERTY(EditAnywhere)
	float waveRestTimer;

	UPROPERTY(EditAnywhere)
	float enemySpawnTime;

	UPROPERTY(EditAnywhere)
	float waveRestTime;

	UPROPERTY(EditAnywhere)
	AEnemyCreateField* enemyCreateField;

	UPROPERTY(EditAnywhere)
	TArray<AEnemyMoveField*> enemyMoveFieldArray;

	UPROPERTY(EditAnywhere)
	ALifeField* lifeField;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> enemyPawn_BP;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> enemyRook_BP;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> enemyKnight_BP;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> enemyBishop_BP;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> enemyQueen_BP;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> enemyKing_BP;

	TQueue<UClass*> spawnEnemyQueue;
	
	TArray<UEnemyController*> fieldEnemyArray;
	TArray<UEnemyController*> fieldEnemyRemoveArray;	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void EnemyCreateStart(UClass* uClass);

	void Wave1Start();
	void Wave2Start();
	void Wave3Start();
	void Wave4Start();

	UFUNCTION(BlueprintCallable)
	int GetCurrentEnemyCount();

	UFUNCTION(BlueprintCallable)
	bool IsLeftSpawnEnemy();
};