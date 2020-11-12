// Fill out your copyright notice in the Description page of Project Settings.


#include "FieldManager.h"


// Sets default values
AFieldManager::AFieldManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	enemySpawnTimer = 0;
	enemySpawnTime = 1.0f;

	static ConstructorHelpers::FObjectFinder<UBlueprint> enemyPawn(TEXT("Blueprint'/Game/Blueprints/Character/Enemy_Pawn_BP.Enemy_Pawn_BP'"));
	if (enemyPawn.Object)
	{
		enemyPawn_BP = (UClass*)enemyPawn.Object->GeneratedClass;
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint> enemyRook(TEXT("Blueprint'/Game/Blueprints/Character/Enemy_Rook_BP.Enemy_Rook_BP'"));
	if (enemyRook.Object)
	{
		enemyRook_BP = (UClass*)enemyRook.Object->GeneratedClass;
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint> enemyKnight(TEXT("Blueprint'/Game/Blueprints/Character/Enemy_Knight_BP.Enemy_Knight_BP'"));
	if (enemyKnight.Object)
	{
		enemyKnight_BP = (UClass*)enemyKnight.Object->GeneratedClass;
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint> enemyBishop(TEXT("Blueprint'/Game/Blueprints/Character/Enemy_Bishop_BP.Enemy_Bishop_BP'"));
	if (enemyBishop.Object)
	{
		enemyBishop_BP = (UClass*)enemyBishop.Object->GeneratedClass;
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint> enemyQueen(TEXT("Blueprint'/Game/Blueprints/Character/Enemy_Queen_BP.Enemy_Queen_BP'"));
	if (enemyQueen.Object)
	{
		enemyQueen_BP = (UClass*)enemyQueen.Object->GeneratedClass;
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint> enemyKing(TEXT("Blueprint'/Game/Blueprints/Character/Enemy_King_BP.Enemy_King_BP'"));
	if (enemyKing.Object)
	{
		enemyKing_BP = (UClass*)enemyKing.Object->GeneratedClass;
	}

	spawnEnemyQueue.Enqueue(enemyPawn_BP);
	spawnEnemyQueue.Enqueue(enemyRook_BP);
	spawnEnemyQueue.Enqueue(enemyKnight_BP);
	spawnEnemyQueue.Enqueue(enemyBishop_BP);
	spawnEnemyQueue.Enqueue(enemyQueen_BP);
	spawnEnemyQueue.Enqueue(enemyKing_BP);
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
		auto newActorControll = newActor->FindComponentByClass<UEnemyControll>();

		newActorControll->Init(enemyMoveFieldArray[0], 0);
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

	for (int i = 0; i < fieldEnemyArray.Num(); i++)
	{
		if (fieldEnemyArray[i]->isMoveEnd)
		{
			int newIndex = fieldEnemyArray[i]->moveFieldIndex + 1;
			if (enemyMoveFieldArray.IsValidIndex(newIndex))
			{
				fieldEnemyArray[i]->Init(enemyMoveFieldArray[newIndex], newIndex);
			}
			else
			{
				fieldEnemyArray[i]->Init(lifeField, newIndex);
			}
		}
	}
}

