// Fill out your copyright notice in the Description page of Project Settings.


#include "FieldManager.h"
#include "YutnoriDefense/EnemyControll/EnemyControll.h"
#include "CoreUObject/Public/UObject/ConstructorHelpers.h"

// Sets default values
AFieldManager::AFieldManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UBlueprint> enemyKing(TEXT("Blueprint'/Game/Blueprints/Character/Enemy_King_BP.Enemy_King_BP'"));
	if (enemyKing.Object)
	{
		enemyKing_BP = (UClass*)enemyKing.Object->GeneratedClass;
	}
}

void AFieldManager::EnemyCreateStart()
{
	FActorSpawnParameters SpawnParams;
	FRotator rotator;
	FVector  SpawnLocation;

	UWorld* world = GetWorld();
	if (world)
	{
		SpawnParams.Owner = this;
		SpawnLocation = enemyCreateField->GetActorLocation();

		auto newActor = world->SpawnActor<AActor>(enemyKing_BP, SpawnLocation, rotator, SpawnParams);
		auto newActorControll = newActor->FindComponentByClass<UEnemyControll>();

		newActorControll->Init(enemyMoveFieldArray[0], 0);
		enemyArray.Add(newActorControll);
	}
}

// Called when the game starts or when spawned
void AFieldManager::BeginPlay()
{
	Super::BeginPlay();

	EnemyCreateStart();
}

// Called every frame
void AFieldManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (int i = 0; i < enemyArray.Num(); i++)
	{
		if (enemyArray[i]->isMoveEnd)
		{
			int newIndex = enemyArray[i]->moveFieldIndex + 1;
			if (enemyMoveFieldArray.IsValidIndex(newIndex))
			{
				enemyArray[i]->Init(enemyMoveFieldArray[newIndex], newIndex);
			}
			else 
			{
				enemyArray[i]->Init(lifeField, newIndex);
			}
		}
	}
}

