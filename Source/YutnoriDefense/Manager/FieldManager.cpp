// Fill out your copyright notice in the Description page of Project Settings.


#include "FieldManager.h"
#include <functional>


// Sets default values
AFieldManager::AFieldManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UBlueprint> enemyPawn(TEXT("Blueprint'/Game/Blueprints/Character/Enemy/Enemy_Pawn_BP.Enemy_Pawn_BP'"));
	if (enemyPawn.Object)
	{
		enemyPawn_BP = (UClass*)enemyPawn.Object->GeneratedClass;
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint> enemyRook(TEXT("Blueprint'/Game/Blueprints/Character/Enemy/Enemy_Rook_BP.Enemy_Rook_BP'"));
	if (enemyRook.Object)
	{
		enemyRook_BP = (UClass*)enemyRook.Object->GeneratedClass;
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint> enemyKnight(TEXT("Blueprint'/Game/Blueprints/Character/Enemy/Enemy_Knight_BP.Enemy_Knight_BP'"));
	if (enemyKnight.Object)
	{
		enemyKnight_BP = (UClass*)enemyKnight.Object->GeneratedClass;
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint> enemyBishop(TEXT("Blueprint'/Game/Blueprints/Character/Enemy/Enemy_Bishop_BP.Enemy_Bishop_BP'"));
	if (enemyBishop.Object)
	{
		enemyBishop_BP = (UClass*)enemyBishop.Object->GeneratedClass;
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint> enemyQueen(TEXT("Blueprint'/Game/Blueprints/Character/Enemy/Enemy_Queen_BP.Enemy_Queen_BP'"));
	if (enemyQueen.Object)
	{
		enemyQueen_BP = (UClass*)enemyQueen.Object->GeneratedClass;
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint> enemyKing(TEXT("Blueprint'/Game/Blueprints/Character/Enemy/Enemy_King_BP.Enemy_King_BP'"));
	if (enemyKing.Object)
	{
		enemyKing_BP = (UClass*)enemyKing.Object->GeneratedClass;
	}

	stage = 0;
	enemySpawnTimer = 0;
	waveRestTimer = 10;
	enemySpawnTime = 1.0f;
	waveRestTime = 10.0f;
	deathCount = 0;
	yut = 0;
	isRestTime = false;
}

void AFieldManager::Wave1Start()
{
	for (int i = 0; i < 45; i++)
	{
		spawnEnemyQueue.Enqueue(enemyPawn_BP);
	}	
}

void AFieldManager::Wave2Start()
{
	for (int i = 0; i < 15; i++)
	{
		spawnEnemyQueue.Enqueue(enemyPawn_BP);
		spawnEnemyQueue.Enqueue(enemyBishop_BP);
		spawnEnemyQueue.Enqueue(enemyRook_BP);
	}
}

void AFieldManager::Wave3Start()
{
	for (int i = 0; i < 9; i++)
	{
		spawnEnemyQueue.Enqueue(enemyPawn_BP);
		spawnEnemyQueue.Enqueue(enemyBishop_BP);
		spawnEnemyQueue.Enqueue(enemyRook_BP);
		spawnEnemyQueue.Enqueue(enemyKnight_BP);
		spawnEnemyQueue.Enqueue(enemyQueen_BP);
	}
}

void AFieldManager::Wave4Start()
{	
	for (int i = 0; i < 9; i++)
	{
		spawnEnemyQueue.Enqueue(enemyPawn_BP);
		spawnEnemyQueue.Enqueue(enemyBishop_BP);
		spawnEnemyQueue.Enqueue(enemyRook_BP);
		spawnEnemyQueue.Enqueue(enemyKnight_BP);
		spawnEnemyQueue.Enqueue(enemyQueen_BP);

		if (i == 0)
			spawnEnemyQueue.Enqueue(enemyKing_BP);
	}
}

void AFieldManager::EnemyCreateStart(UClass* uClass)
{
	if (uClass == nullptr)
		return;

	FActorSpawnParameters SpawnParams;
	FRotator rotator;
	FVector  SpawnLocation;

	UWorld* world = GetWorld();
	if (world)
	{
		SpawnParams.Owner = this;
		SpawnLocation = enemyCreateField->GetActorLocation();

		auto newActor = world->SpawnActor<AActor>(uClass, SpawnLocation, rotator, SpawnParams);
		//auto newActor = world->SpawnActor<AActor>(AEnemy::StaticClass(), SpawnLocation, rotator, SpawnParams);
		newActor->Tags.Add("Enemy");

		auto newActorControll = newActor->FindComponentByClass<UEnemyController>();
		newActorControll->Init();
		newActorControll->SetNextPos(enemyMoveFieldArray[0], 0);

		fieldEnemyArray.Add(newActorControll);
	}
}

// Called when the game starts or when spawned
void AFieldManager::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void AFieldManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (spawnEnemyQueue.IsEmpty() && fieldEnemyArray.Num() <= 0)
	{
		isRestTime = true;
		waveRestTimer += DeltaTime;
		if (waveRestTimer > waveRestTime)
		{
			isRestTime = false;
			//타이머 초기화
			waveRestTimer = 0;
			//다음 스테이지
			stage += 1;

			if (stage == 1) 
			{
				Wave1Start();
			}
			else if (stage == 2)
			{
				Wave2Start();
			}
			else if (stage == 3)
			{
				Wave3Start();
			}
			else if (stage == 4)
			{
				Wave4Start();
			}
			else 
			{
				//클리어
			}
		}
	}
	else 
	{
		enemySpawnTimer += DeltaTime;
		if (enemySpawnTimer > enemySpawnTime)
		{
			enemySpawnTimer = 0;

			if (!spawnEnemyQueue.IsEmpty())
			{
				UClass* uclass = nullptr;
				spawnEnemyQueue.Dequeue(uclass);
				EnemyCreateStart(uclass);
			}
		}
	}

	for (int i = 0; i < fieldEnemyArray.Num(); i++)
	{
		if (fieldEnemyArray[i] != NULL)
		{
			if (fieldEnemyArray[i]->isMoveEnd)
			{
				int newIndex = fieldEnemyArray[i]->moveFieldIndex + 1;
				if (enemyMoveFieldArray.IsValidIndex(newIndex))
				{
					fieldEnemyArray[i]->SetNextPos(enemyMoveFieldArray[newIndex], newIndex);
				}
				else
				{
					//마지막 라이프 필드로 이동
					fieldEnemyArray[i]->SetNextPos(lifeField, -1);
				}
			}
			
			if (fieldEnemyArray[i]->GetHP() <= 0)
			{
				deathCount++;
				if (deathCount >= 10)
				{
					deathCount = 0;
					yut++;
				}
				fieldEnemyRemoveArray.Add(fieldEnemyArray[i]);
			}
		}
	}

	if (fieldEnemyRemoveArray.Num() > 0)
	{
		for (int i = 0; i < fieldEnemyRemoveArray.Num(); i++)
		{
			fieldEnemyArray.Remove(fieldEnemyRemoveArray[i]);
			fieldEnemyRemoveArray[i]->GetOwner()->Destroy();
			fieldEnemyRemoveArray[i] = NULL;
		}
		fieldEnemyRemoveArray.Reset();
	}
}

int AFieldManager::GetCurrentEnemyCount()
{
	return fieldEnemyArray.Num();
}

bool AFieldManager::IsLeftSpawnEnemy()
{
	return !spawnEnemyQueue.IsEmpty();
}
