// Fill out your copyright notice in the Description page of Project Settings.


#include "FieldManager.h"

// Sets default values
AFieldManager::AFieldManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UBlueprint> towerField(TEXT("Blueprint'/Game/Blueprints/Character/TowerField_BP.TowerField_BP'"));
	if (towerField.Object)
	{
		towerField_BP = (UClass*)towerField.Object->GeneratedClass;
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint> lifeField(TEXT("Blueprint'/Game/Blueprints/Character/LifeField_BP.LifeField_BP'"));
	if (lifeField.Object)
	{
		lifeField_BP = (UClass*)lifeField.Object->GeneratedClass;
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint> enemyCreateField(TEXT("Blueprint'/Game/Blueprints/Character/EnemyCreateField_BP.EnemyCreateField_BP'"));
	if (enemyCreateField.Object)
	{
		enemyCreateField_BP = (UClass*)enemyCreateField.Object->GeneratedClass;
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint> myMoveField(TEXT("Blueprint'/Game/Blueprints/Character/EnemyMoveField_BP.EnemyMoveField_BP'"));
	if (myMoveField.Object)
	{
		enemyMoveField_BP = (UClass*)myMoveField.Object->GeneratedClass;
	}
}

// Called when the game starts or when spawned
void AFieldManager::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters SpawnParams;
	FRotator rotator;
	FVector  SpawnLocation;

	UWorld* world = GetWorld();
	if (world)
	{
		UE_LOG(LogTemp, Log, TEXT("towerField_BP"));
		SpawnParams.Owner = this;
		SpawnLocation = GetActorLocation();
		SpawnLocation.Y -= 100.0f;
		world->SpawnActor<AActor>(towerField_BP, SpawnLocation, rotator, SpawnParams);

		UE_LOG(LogTemp, Log, TEXT("lifeField_BP"));
		SpawnParams.Owner = this;
		SpawnLocation = GetActorLocation();
		SpawnLocation.Y -= 200.0f;
		world->SpawnActor<AActor>(lifeField_BP, SpawnLocation, rotator, SpawnParams);

		UE_LOG(LogTemp, Log, TEXT("enemyCreateField_BP"));
		SpawnParams.Owner = this;
		SpawnLocation = GetActorLocation();
		SpawnLocation.Y -= 300.0f;
		world->SpawnActor<AActor>(enemyCreateField_BP, SpawnLocation, rotator, SpawnParams);

		UE_LOG(LogTemp, Log, TEXT("enemyMoveField_BP"));
		SpawnParams.Owner = this;
		SpawnLocation = GetActorLocation();
		SpawnLocation.Y -= 400.0f;
		world->SpawnActor<AActor>(enemyMoveField_BP, SpawnLocation, rotator, SpawnParams);
	}

}

// Called every frame
void AFieldManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

