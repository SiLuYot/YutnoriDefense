// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerManager.h"

// Sets default values
ATowerManager::ATowerManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UBlueprint> doTower(TEXT("Blueprint'/Game/Blueprints/Character/Tower/Tower_Do_BP.Tower_Do_BP'"));
	if (doTower.Object)
	{
		tower_Do_BP = (UClass*)doTower.Object->GeneratedClass;
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint> gaeTower(TEXT("Blueprint'/Game/Blueprints/Character/Tower/Tower_Gae_BP.Tower_Gae_BP'"));
	if (gaeTower.Object)
	{
		tower_Gae_BP = (UClass*)gaeTower.Object->GeneratedClass;
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint> geolTower(TEXT("Blueprint'/Game/Blueprints/Character/Tower/Tower_Geol_BP.Tower_Geol_BP'"));
	if (geolTower.Object)
	{
		tower_Geol_BP = (UClass*)geolTower.Object->GeneratedClass;
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint> yutTower(TEXT("Blueprint'/Game/Blueprints/Character/Tower/Tower_Yut_BP.Tower_Yut_BP'"));
	if (yutTower.Object)
	{
		tower_Yut_BP = (UClass*)yutTower.Object->GeneratedClass;
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint> moTower(TEXT("Blueprint'/Game/Blueprints/Character/Tower/Tower_Mo_BP.Tower_Mo_BP'"));
	if (moTower.Object)
	{
		tower_Mo_BP = (UClass*)moTower.Object->GeneratedClass;
	}

	clickCount = 0;
	towerDataArray.Add(new TowerData(tower_Do_BP, SkillData(0, SkillType::OneShoot)));
	towerDataArray.Add(new TowerData(tower_Gae_BP, SkillData(0, SkillType::OneShoot)));
	towerDataArray.Add(new TowerData(tower_Geol_BP, SkillData(1, SkillType::TraceAndExplosion)));
	towerDataArray.Add(new TowerData(tower_Yut_BP, SkillData(0, SkillType::OneShoot)));
	towerDataArray.Add(new TowerData(tower_Mo_BP, SkillData(0, SkillType::OneShoot)));
}

void ATowerManager::ClickFieldEvent(ABaseField* field)
{
	UE_LOG(LogTemp, Log, TEXT("Click FieldName :: %s"), *field->GetActorLabel());

	auto towerField = Cast<ATowerField>(field);
	if (towerField)
	{
		FActorSpawnParameters SpawnParams;
		FRotator rotator;
		FVector  SpawnLocation;

		UWorld* world = GetWorld();
		if (world)
		{
			SpawnParams.Owner = this;
			SpawnLocation = field->GetActorLocation();
			
			auto findData = towerDataArray[clickCount];

			clickCount += 1;
			if (clickCount >= towerDataArray.Num())
				clickCount = 0;

			auto newActor = world->SpawnActor<AActor>(findData->towerBP, SpawnLocation, rotator, SpawnParams);
			auto newActorControll = newActor->FindComponentByClass<UTowerController>();
			newActorControll->Init(findData->skillData);
		}
	}
}

// Called when the game starts or when spawned
void ATowerManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATowerManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

