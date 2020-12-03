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

	//이펙트 없는 기본 공격
	auto skillData1 = SkillData(0, SkillType::OneShoot, 5.0f, 1.0f, 1.0f);
	auto skillData2 = SkillData(0, SkillType::OneShoot, 6.0f, 1.0f, 1.0f);
	auto skillData3 = SkillData(0, SkillType::OneShoot, 7.0f, 1.0f, 1);
	//얼음 공격
	auto skillData4 = SkillData(4, SkillType::TraceAndExplosion, 6.0f, 0.5f, 2.0f);
	auto skillData5 = SkillData(4, SkillType::TraceAndExplosion, 8.0f, 0.5f, 2.0f);
	auto skillData6 = SkillData(4, SkillType::TraceAndExplosion, 10.0f, 0.5f, 2.0f);
	//전기 공격
	auto skillData7 = SkillData(1, SkillType::OneShoot, 35.0f, 1.0f, 2.0f);
	auto skillData8 = SkillData(1, SkillType::OneShoot, 55.0f, 1.0f, 2.5f);
	auto skillData9 = SkillData(1, SkillType::OneShoot, 75.0f, 1.0f, 3.0f);
	//불, 믹스 공격
	auto skillData10 = SkillData(2, SkillType::TraceAndExplosion, 40.0f, 1.0f, 2.0f);
	auto skillData11 = SkillData(2, SkillType::TraceAndExplosion, 70.0f, 1.0f, 2.5f);
	auto skillData12 = SkillData(6, SkillType::TraceAndExplosion, 100.0f, 1.0f, 3.0f);
	//회오리 공격
	auto skillData13 = SkillData(10, SkillType::OneShoot, 55.0f, 1.0f, 2.0f);
	auto skillData14 = SkillData(10, SkillType::OneShoot, 85.0f, 1.0f, 2.5f);
	auto skillData15 = SkillData(10, SkillType::OneShoot, 125.0f, 1.0f, 3.0f);

	//도 타워 1강 2강 3강
	towerDataArray.Add(new TowerData(tower_Do_BP, skillData1));
	towerDataArray.Add(new TowerData(tower_Do_BP, skillData2));
	towerDataArray.Add(new TowerData(tower_Do_BP, skillData3));
	//개 타워 1강 2강 3강
	towerDataArray.Add(new TowerData(tower_Gae_BP, skillData4));
	towerDataArray.Add(new TowerData(tower_Gae_BP, skillData5));
	towerDataArray.Add(new TowerData(tower_Gae_BP, skillData6));
	//걸 타워 1강 2강 3강
	towerDataArray.Add(new TowerData(tower_Geol_BP, skillData7));
	towerDataArray.Add(new TowerData(tower_Geol_BP, skillData8));
	towerDataArray.Add(new TowerData(tower_Geol_BP, skillData9));
	//웇 타워 1강 2강 3강
	towerDataArray.Add(new TowerData(tower_Yut_BP, skillData10));
	towerDataArray.Add(new TowerData(tower_Yut_BP, skillData11));
	towerDataArray.Add(new TowerData(tower_Yut_BP, skillData12));
	//모 타워 1강 2강 3강
	towerDataArray.Add(new TowerData(tower_Mo_BP, skillData13));
	towerDataArray.Add(new TowerData(tower_Mo_BP, skillData14));
	towerDataArray.Add(new TowerData(tower_Mo_BP, skillData15));
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
			
			//타워 데이터 임시로 랜덤 데이터 가져옴
			auto rand = FMath::RandRange(0, towerDataArray.Num() - 1);
			auto findData = towerDataArray[rand];

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

