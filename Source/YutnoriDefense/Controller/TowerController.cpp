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

	//���� ����� ������
	if (target == nullptr)
	{
		//������ ��� ���� �˻�
		for (TActorIterator<AActor> It(GetWorld()); It; ++It)
		{
			AActor* findActor = *It;
			if (findActor == nullptr)
			{
				continue;
			}

			//���� �� �� ã��
			if (findActor->ActorHasTag(FName(TEXT("Enemy"))))
			{
				auto distance = GetOwner()->GetDistanceTo(findActor);

				//���� �ȿ� �ִٸ�
				if (distance <= attackDistance)
				{
					//��� ����
					target = findActor->FindComponentByClass<UEnemyController>();

					//�ִϸ��̼� �÷��� ����
					animRoot->Montage_Play(attackMontage);

					//��ų ����Ʈ ����
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

	//���� �� ���� ������
	if (target != nullptr)
	{
		//Ÿ���� ���� �ٶ󺸰� ȸ��
		auto curPos = GetOwner()->GetActorLocation();
		auto targetPos = target->GetOwner()->GetActorLocation();

		FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(targetPos, curPos);
		GetOwner()->SetActorRotation(Rotator);
		GetOwner()->AddActorLocalRotation(FRotator(0, 90, 0));
	}

	//��ų ������Ʈ
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
	//Ÿ�̸� �ʱ�ȭ
	timer = 0;
	//Ÿ�� �ʱ�ȭ
	target = nullptr;

	skillController->AttackEndEvent();
}