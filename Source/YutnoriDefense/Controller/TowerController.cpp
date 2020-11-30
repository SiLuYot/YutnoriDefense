// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerController.h"
#include <Runtime\Engine\Classes\Animation\SkeletalMeshActor.h>

// Sets default values for this component's properties
UTowerController::UTowerController()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> attackClass(TEXT("AnimMontage'/Game/ModularAnimalKnightsPolyart/Animations/Attack01Anim_Montage.Attack01Anim_Montage'"));
	if (attackClass.Succeeded())
	{
		attackMontage = attackClass.Object;
	}
}


// Called when the game starts
void UTowerController::BeginPlay()
{
	Super::BeginPlay();

	auto root = Cast<ASkeletalMeshActor>(GetOwner());
	meshRoot = root->GetSkeletalMeshComponent();
	animRoot = meshRoot->GetAnimInstance();
	shootRoot = Cast<USceneComponent>(GetOwner()->GetDefaultSubobjectByName(TEXT("shootRoot")));

	GetOwner()->SetActorRotation(FRotator::ZeroRotator);
	GetOwner()->AddActorLocalRotation(FRotator(0, 90, 0));
}


// Called every frame
void UTowerController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	timer += DeltaTime;

	//공격 대상이 없을때
	if (target == nullptr)
	{
		//월드의 모든 액터 검색
		for (TActorIterator<AActor> It(GetWorld()); It; ++It)
		{
			AActor* findActor = *It;
			if (findActor == nullptr)
			{
				continue;
			}

			//범위 안 적 찾기
			if (findActor->ActorHasTag(FName(TEXT("Enemy"))))
			{
				auto distance = GetOwner()->GetDistanceTo(findActor);

				//범위 안에 있다면
				if (distance <= attackDistance)
				{
					//대상 갱신
					target = findActor->FindComponentByClass<UEnemyController>();

					//애니매이션 플레이 시작
					animRoot->Montage_Play(attackMontage);

					//스킬 이펙트 생성
					FVector location = FVector::ZeroVector;

					if (skillData.type == SkillType::OneShoot)
						location = target->GetOwner()->GetActorLocation();

					else if (skillData.type == SkillType::TraceAndExplosion)
						location = shootRoot->GetComponentLocation();

					FRotator rotator = FRotator::ZeroRotator;

					SkillCreateData skillCreateData = SkillCreateData(skillData, location, rotator, findActor, attack);
					skillController->CreateParticle(skillCreateData);

					break;
				}
			}
		}
	}

	//범위 안 적이 있을때
	if (target != nullptr)
	{
		//타워가 적을 바라보게 회전
		auto curPos = GetOwner()->GetActorLocation();
		auto targetPos = target->GetOwner()->GetActorLocation();

		FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(targetPos, curPos);
		GetOwner()->SetActorRotation(Rotator);
		GetOwner()->AddActorLocalRotation(FRotator(0, 90, 0));
	}

	//스킬 업데이트
	skillController->Update(DeltaTime);
}

void UTowerController::Init(SkillData data)
{
	this->attack = 1.0f;
	this->attackSpeed = 1.0f;
	this->attackDistance = 200.0f;
	this->timer = 0;
	this->skillController = new SkillContoller(GetWorld());
	this->skillData = data;
}

void UTowerController::Attack(UEnemyController* enemy)
{
	if (enemy != nullptr)
		enemy->Damage(attack);
}

void UTowerController::AttackStart()
{
	skillController->AttackStartEvent();
}

void UTowerController::AttackEnd()
{
	//타이머 초기화
	timer = 0;
	//타겟 초기화
	target = nullptr;

	skillController->AttackEndEvent();
}