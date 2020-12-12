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
	auto skillData1 = FSkillData(0, SkillType::OneShoot, 15.0f, 1.0f, 1.0f, 0, 0, 0, 0, 0);
	auto skillData2 = FSkillData(0, SkillType::OneShoot, 18.0f, 1.0f, 1.0f, 0, 0, 0, 0, 1);
	auto skillData3 = FSkillData(0, SkillType::OneShoot, 21.0f, 1.0f, 1.0f, 0, 0, 0, 0, 1);
	//얼음 공격
	auto skillData4 = FSkillData(4, SkillType::TraceAndExplosion, 18.0f,  0.5f, 2.0f, 0, 1, 0.2f, 2,    0);
	auto skillData5 = FSkillData(4, SkillType::TraceAndExplosion, 24.0f,  0.5f, 2.0f, 0, 1, 0.3f, 2.5f, 0);
	auto skillData6 = FSkillData(4, SkillType::TraceAndExplosion, 30.0f, 0.5f, 2.0f, 0, 1, 0.4f, 3,    0);
	//전기 공격
	auto skillData7 = FSkillData(1, SkillType::OneShoot, 8.75f, 1.0f, 2.0f, 2,    2, 0.2f, 2,    0);
	auto skillData8 = FSkillData(1, SkillType::OneShoot, 13.75f, 1.0f, 2.5f, 2.5f, 2, 0.3f, 2.5f, 0);
	auto skillData9 = FSkillData(1, SkillType::OneShoot, 18.75f, 1.0f, 3.0f, 3,    2, 0.4f, 3,    0);
	//불, 믹스 공격
	auto skillData10 = FSkillData(2, SkillType::TraceAndExplosion, 10.0f,  1.0f, 2.0f, 3,    0, 0, 0, 0);
	auto skillData11 = FSkillData(2, SkillType::TraceAndExplosion, 17.75f,  1.0f, 2.5f, 3.5f, 0, 0, 0, 0);
	auto skillData12 = FSkillData(6, SkillType::TraceAndExplosion, 25.0f, 1.0f, 3.0f, 4,    0, 0, 0, 0);
	//회오리 공격
	auto skillData13 = FSkillData(8, SkillType::OneShoot, 13.75f,   1.0f, 2.0f, 3,    0, 0,     0, 0);
	auto skillData14 = FSkillData(9, SkillType::OneShoot, 21.25f,   1.0f, 2.5f, 3.5f, 0, 0,     0, 0);
	auto skillData15 = FSkillData(10, SkillType::OneShoot, 31.25f, 1.0f, 3.0f, 4,    3, 0.05f, 0, 0);

	//도 타워 1강 2강 3강
	towerDataArray.Add(FTowerData(0, 0, 0, tower_Do_BP, skillData1));
	towerDataArray.Add(FTowerData(1, 0, 1, tower_Do_BP_2, skillData2));
	towerDataArray.Add(FTowerData(2, 0, 2, tower_Do_BP_3, skillData3));
	//개 타워 1강 2강 3강
	towerDataArray.Add(FTowerData(3, 1, 0, tower_Gae_BP, skillData4));
	towerDataArray.Add(FTowerData(4, 1, 1, tower_Gae_BP_2, skillData5));
	towerDataArray.Add(FTowerData(5, 1, 2, tower_Gae_BP_3, skillData6));
	//걸 타워 1강 2강 3강
	towerDataArray.Add(FTowerData(6, 2, 0, tower_Geol_BP, skillData7));
	towerDataArray.Add(FTowerData(7, 2, 1, tower_Geol_BP_2, skillData8));
	towerDataArray.Add(FTowerData(8, 2, 2, tower_Geol_BP_3, skillData9));
	//웇 타워 1강 2강 3강
	towerDataArray.Add(FTowerData(9, 3, 0, tower_Yut_BP, skillData10));
	towerDataArray.Add(FTowerData(10, 3, 1, tower_Yut_BP_2, skillData11));
	towerDataArray.Add(FTowerData(11, 3, 2, tower_Yut_BP_3, skillData12));
	//모 타워 1강 2강 3강
	towerDataArray.Add(FTowerData(12, 4, 0, tower_Mo_BP, skillData13));
	towerDataArray.Add(FTowerData(13, 4, 1, tower_Mo_BP_2, skillData14));
	towerDataArray.Add(FTowerData(14, 4, 2, tower_Mo_BP_3, skillData15));
}

bool ATowerManager::ClickFieldEvent(ABaseField* field, FTowerData data)
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

			auto findData = data;

			//타워가 설치 가능하고
			if (towerField->IsCanInstallType(findData.type))
			{
				//이미 설치된 타워와 같은 타입일때
				if (towerField->IsSameType(findData.type))
				{
					auto originID = towerField->towerData.index;
					auto originType = towerField->towerData.type;

					int nextID = originID + 1;
					//다음 ID가 배열 범위 안에 있을때
					if (nextID < towerDataArray.Num())
					{
						auto newData = towerDataArray[nextID];
						//다음 데이터가 같은 타입일때
						if (newData.type == originType)
						{
							UE_LOG(LogTemp, Log, TEXT("Upgrade Tower [origin : %d new : %d]"), originID, nextID);

							//기존에 생성된 타워 파괴
							towerField->DestroyTower();

							//타워 생성 후 초기화
							auto newActor = world->SpawnActor<AActor>(newData.towerBP, SpawnLocation, rotator, SpawnParams);
							auto newActorControll = newActor->FindComponentByClass<UTowerController>();
							newActorControll->Init(newData.skillData);

							//타워필드에 생성한 타워 설치
							towerField->InstallTower(newData, newActorControll);

							return true;
						}
					}
				}
				//타워 설치가 가능하지만 타입이 다를때 (타워 미설치 상태)
				else
				{
					UE_LOG(LogTemp, Log, TEXT("Create New Tower ID : %d"), findData.index);

					//타워 생성 후 초기화
					auto newActor = world->SpawnActor<AActor>(findData.towerBP, SpawnLocation, rotator, SpawnParams);
					auto newActorControll = newActor->FindComponentByClass<UTowerController>();
					newActorControll->Init(findData.skillData);

					//타워필드에 생성한 타워 설치
					towerField->InstallTower(findData, newActorControll);

					return true;
				}
			}
		}
	}

	return false;
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

