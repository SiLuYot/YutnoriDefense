// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerController.h"
#include <Runtime\Engine\Classes\Animation\SkeletalMeshActor.h>

// Sets default values for this component's properties
UTowerController::UTowerController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
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
}

void UTowerController::Init()
{
	this->attack = 1.0f;
	this->attackSpeed = 1.0f;
	this->attackDistance = 200.0f;
	this->timer = 0;
}

void UTowerController::Attack(UEnemyController* enemy)
{
	if (enemy != nullptr)
		enemy->Damage(attack);
}

void UTowerController::AttackStart()
{
	Attack(target);
}

void UTowerController::AttackEnd()
{
	//Ÿ�̸� �ʱ�ȭ
	timer = 0;
	//Ÿ�� �ʱ�ȭ
	target = nullptr;
}