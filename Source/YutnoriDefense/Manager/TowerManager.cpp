// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerManager.h"

// Sets default values
ATowerManager::ATowerManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TSubclassOf<class AActor> tower_Do_BP;
	static ConstructorHelpers::FObjectFinder<UBlueprint> doTower1(TEXT("Blueprint'/Game/Blueprints/Character/Tower/Tower_Do_BP.Tower_Do_BP'"));
	if (doTower1.Object)
	{
		tower_Do_BP = (UClass*)doTower1.Object->GeneratedClass;
	}

	TSubclassOf<class AActor> tower_Do_BP_2;
	static ConstructorHelpers::FObjectFinder<UBlueprint> doTower2(TEXT("Blueprint'/Game/Blueprints/Character/Tower/Tower_Do_BP_2.Tower_Do_BP_2'"));
	if (doTower2.Object)
	{
		tower_Do_BP_2 = (UClass*)doTower2.Object->GeneratedClass;
	}

	TSubclassOf<class AActor> tower_Do_BP_3;
	static ConstructorHelpers::FObjectFinder<UBlueprint> doTower3(TEXT("Blueprint'/Game/Blueprints/Character/Tower/Tower_Do_BP_3.Tower_Do_BP_3'"));
	if (doTower3.Object)
	{
		tower_Do_BP_3 = (UClass*)doTower3.Object->GeneratedClass;
	}


	TSubclassOf<class AActor> tower_Gae_BP;
	static ConstructorHelpers::FObjectFinder<UBlueprint> gaeTower1(TEXT("Blueprint'/Game/Blueprints/Character/Tower/Tower_Gae_BP.Tower_Gae_BP'"));
	if (gaeTower1.Object)
	{
		tower_Gae_BP = (UClass*)gaeTower1.Object->GeneratedClass;
	}

	TSubclassOf<class AActor> tower_Gae_BP_2;
	static ConstructorHelpers::FObjectFinder<UBlueprint> gaeTower2(TEXT("Blueprint'/Game/Blueprints/Character/Tower/Tower_Gae_BP_2.Tower_Gae_BP_2'"));
	if (gaeTower2.Object)
	{
		tower_Gae_BP_2 = (UClass*)gaeTower2.Object->GeneratedClass;
	}

	TSubclassOf<class AActor> tower_Gae_BP_3;
	static ConstructorHelpers::FObjectFinder<UBlueprint> gaeTower3(TEXT("Blueprint'/Game/Blueprints/Character/Tower/Tower_Gae_BP_3.Tower_Gae_BP_3'"));
	if (gaeTower3.Object)
	{
		tower_Gae_BP_3 = (UClass*)gaeTower3.Object->GeneratedClass;
	}


	TSubclassOf<class AActor> tower_Geol_BP;
	static ConstructorHelpers::FObjectFinder<UBlueprint> geolTower1(TEXT("Blueprint'/Game/Blueprints/Character/Tower/Tower_Geol_BP.Tower_Geol_BP'"));
	if (geolTower1.Object)
	{
		tower_Geol_BP = (UClass*)geolTower1.Object->GeneratedClass;
	}

	TSubclassOf<class AActor> tower_Geol_BP_2;
	static ConstructorHelpers::FObjectFinder<UBlueprint> geolTower2(TEXT("Blueprint'/Game/Blueprints/Character/Tower/Tower_Geol_BP_2.Tower_Geol_BP_2'"));
	if (geolTower2.Object)
	{
		tower_Geol_BP_2 = (UClass*)geolTower2.Object->GeneratedClass;
	}

	TSubclassOf<class AActor> tower_Geol_BP_3;
	static ConstructorHelpers::FObjectFinder<UBlueprint> geolTower3(TEXT("Blueprint'/Game/Blueprints/Character/Tower/Tower_Geol_BP_3.Tower_Geol_BP_3'"));
	if (geolTower3.Object)
	{
		tower_Geol_BP_3 = (UClass*)geolTower3.Object->GeneratedClass;
	}

	TSubclassOf<class AActor> tower_Yut_BP;
	static ConstructorHelpers::FObjectFinder<UBlueprint> yutTower1(TEXT("Blueprint'/Game/Blueprints/Character/Tower/Tower_Yut_BP.Tower_Yut_BP'"));
	if (yutTower1.Object)
	{
		tower_Yut_BP = (UClass*)yutTower1.Object->GeneratedClass;
	}

	TSubclassOf<class AActor> tower_Yut_BP_2;
	static ConstructorHelpers::FObjectFinder<UBlueprint> yutTower2(TEXT("Blueprint'/Game/Blueprints/Character/Tower/Tower_Yut_BP_2.Tower_Yut_BP_2'"));
	if (yutTower2.Object)
	{
		tower_Yut_BP_2 = (UClass*)yutTower2.Object->GeneratedClass;
	}

	TSubclassOf<class AActor> tower_Yut_BP_3;
	static ConstructorHelpers::FObjectFinder<UBlueprint> yutTower3(TEXT("Blueprint'/Game/Blueprints/Character/Tower/Tower_Yut_BP_3.Tower_Yut_BP_3'"));
	if (yutTower3.Object)
	{
		tower_Yut_BP_3 = (UClass*)yutTower3.Object->GeneratedClass;
	}

	TSubclassOf<class AActor> tower_Mo_BP;
	static ConstructorHelpers::FObjectFinder<UBlueprint> moTower1(TEXT("Blueprint'/Game/Blueprints/Character/Tower/Tower_Mo_BP.Tower_Mo_BP'"));
	if (moTower1.Object)
	{
		tower_Mo_BP = (UClass*)moTower1.Object->GeneratedClass;
	}

	TSubclassOf<class AActor> tower_Mo_BP_2;
	static ConstructorHelpers::FObjectFinder<UBlueprint> moTower2(TEXT("Blueprint'/Game/Blueprints/Character/Tower/Tower_Mo_BP_2.Tower_Mo_BP_2'"));
	if (moTower2.Object)
	{
		tower_Mo_BP_2 = (UClass*)moTower2.Object->GeneratedClass;
	}

	TSubclassOf<class AActor> tower_Mo_BP_3;
	static ConstructorHelpers::FObjectFinder<UBlueprint> moTower3(TEXT("Blueprint'/Game/Blueprints/Character/Tower/Tower_Mo_BP_3.Tower_Mo_BP_3'"));
	if (moTower3.Object)
	{
		tower_Mo_BP_3 = (UClass*)moTower3.Object->GeneratedClass;
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
	towerDataArray.Add(new TowerData(0, 0, tower_Do_BP, skillData1));
	towerDataArray.Add(new TowerData(1, 0, tower_Do_BP_2, skillData2));
	towerDataArray.Add(new TowerData(2, 0, tower_Do_BP_3, skillData3));
	//개 타워 1강 2강 3강
	towerDataArray.Add(new TowerData(3, 1, tower_Gae_BP, skillData4));
	towerDataArray.Add(new TowerData(4, 1, tower_Gae_BP_2, skillData5));
	towerDataArray.Add(new TowerData(5, 1, tower_Gae_BP_3, skillData6));
	//걸 타워 1강 2강 3강
	towerDataArray.Add(new TowerData(6, 2, tower_Geol_BP, skillData7));
	towerDataArray.Add(new TowerData(7, 2, tower_Geol_BP_2, skillData8));
	towerDataArray.Add(new TowerData(8, 2, tower_Geol_BP_3, skillData9));
	//웇 타워 1강 2강 3강
	towerDataArray.Add(new TowerData(9, 3, tower_Yut_BP, skillData10));
	towerDataArray.Add(new TowerData(10, 3, tower_Yut_BP_2, skillData11));
	towerDataArray.Add(new TowerData(11, 3, tower_Yut_BP_3, skillData12));
	//모 타워 1강 2강 3강
	towerDataArray.Add(new TowerData(12, 4, tower_Mo_BP, skillData13));
	towerDataArray.Add(new TowerData(13, 4, tower_Mo_BP_2, skillData14));
	towerDataArray.Add(new TowerData(14, 4, tower_Mo_BP_3, skillData15));
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

			//타워 데이터 임시로 랜덤으로 가져옴 (각 타워 1단계들만)
			auto rand = FMath::RandRange(0, 4) * 3;
			auto findData = towerDataArray[rand];

			//타워가 설치 가능하고
			if (towerField->IsCanInstallType(findData->type))
			{
				//이미 설치된 타워와 같은 타입일때
				if (towerField->IsSameType(findData->type))
				{
					auto originID = towerField->towerData->index;
					auto originType = towerField->towerData->type;					
										
					int nextID = originID + 1;
					//다음 ID가 배열 범위 안에 있을때
					if (nextID < towerDataArray.Num()) 
					{
						auto newData = towerDataArray[nextID];
						//다음 데이터가 널이 아니고 같은 타입일때
						if (newData != NULL && newData->type == originType)
						{
							UE_LOG(LogTemp, Log, TEXT("Upgrade Tower [origin : %d new : %d]"), originID, nextID);

							//기존에 생성된 타워 파괴
							towerField->DestroyTower();

							//타워 생성 후 초기화
							auto newActor = world->SpawnActor<AActor>(newData->towerBP, SpawnLocation, rotator, SpawnParams);
							auto newActorControll = newActor->FindComponentByClass<UTowerController>();
							newActorControll->Init(newData->skillData);

							//타워필드에 생성한 타워 설치
							towerField->InstallTower(newData, newActorControll);
						}
					}
				}
				//타워 설치가 가능하지만 타입이 다를때 (타워 미설치 상태)
				else
				{
					UE_LOG(LogTemp, Log, TEXT("Create New Tower ID : %d"), findData->index);

					//타워 생성 후 초기화
					auto newActor = world->SpawnActor<AActor>(findData->towerBP, SpawnLocation, rotator, SpawnParams);
					auto newActorControll = newActor->FindComponentByClass<UTowerController>();
					newActorControll->Init(findData->skillData);

					//타워필드에 생성한 타워 설치
					towerField->InstallTower(findData, newActorControll);
				}
			}
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

