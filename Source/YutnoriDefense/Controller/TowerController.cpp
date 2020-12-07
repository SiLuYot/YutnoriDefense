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

	static ConstructorHelpers::FObjectFinder<UAnimMontage> doubleAttack(TEXT("AnimMontage'/Game/ModularAnimalKnightsPolyart/Animations/ComboAttack.ComboAttack'"));
	if (doubleAttack.Succeeded())
	{
		doubleAttackMontage = doubleAttack.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundWave>doSound1(TEXT("SoundWave'/Game/Sound/Skill/Unit1_Attack1.Unit1_Attack1'"));
	if (doSound1.Succeeded())
	{
		doSound = doSound1.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundWave>gaeSound1(TEXT("SoundWave'/Game/Sound/Skill/Unit2_Attack.Unit2_Attack'"));
	if (gaeSound1.Succeeded())
	{
		gaeSound = gaeSound1.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundWave>geolSound1(TEXT("SoundWave'/Game/Sound/Skill/Unit3_Attack.Unit3_Attack'"));
	if (geolSound1.Succeeded())
	{
		geolSound = geolSound1.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundWave>yutSound1(TEXT("SoundWave'/Game/Sound/Skill/Unit4_Attack1.Unit4_Attack1'"));
	if (yutSound1.Succeeded())
	{
		yutSound = yutSound1.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundWave>moSound1(TEXT("SoundWave'/Game/Sound/Skill/Unit5_Attack.Unit5_Attack'"));
	if (moSound1.Succeeded())
	{
		moSound = moSound1.Object;
	}

	audio = CreateDefaultSubobject<UAudioComponent>(TEXT("SOUND"));
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

	//공격 가능한 시간이 됐을때
	if (timer > skillData.attackSpeed)
	{
		//타이머 초기화
		timer = 0;

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
				if (distance <= skillData.range * ATTACK_DISTANCE)
				{
					//대상 갱신
					target = findActor->FindComponentByClass<UEnemyController>();

					if (target->GetHP() <= 0)
					{
						//이미 죽은 대상
						target = nullptr;
						break;
					}

					//애니매이션 플레이 시작
					//animRoot->Montage_Play(attackMontage);

					UAnimMontage* montage = NULL;
					if (skillData.montageType == 0)
						montage = attackMontage;
					else if (skillData.montageType == 1)
						montage = doubleAttackMontage;

					//스킬 이펙트 생성
					FVector location = FVector::ZeroVector;

					if (skillData.type == SkillType::OneShoot)
						location = target->GetOwner()->GetActorLocation();

					else if (skillData.type == SkillType::TraceAndExplosion)
						location = shootRoot->GetComponentLocation();

					FRotator rotator = FRotator::ZeroRotator;

					SkillCreateData skillCreateData = SkillCreateData(animRoot, montage, skillData, location, rotator, findActor);
					if (skillController != nullptr)
					{
						skillController->CreateParticle(skillCreateData);
					}
					break;
				}
			}
		}
	}

	//찾은 적이 있을때
	if (target != NULL &&
		target->IsValidLowLevel() &&
		target->GetOwner() != NULL &&
		target->GetOwner()->IsValidLowLevel())
	{
		//타워가 적을 바라보게 회전
		auto curPos = GetOwner()->GetActorLocation();
		auto targetPos = target->GetOwner()->GetActorLocation();

		FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(targetPos, curPos);
		GetOwner()->SetActorRotation(Rotator);
		GetOwner()->AddActorLocalRotation(FRotator(0, 90, 0));
	}

	//스킬 업데이트
	if (skillController != nullptr)
	{
		skillController->Update(DeltaTime);
	}
}

void UTowerController::Init(FSkillData data)
{
	this->timer = data.attackSpeed;
	this->skillController = new SkillContoller(GetWorld());
	this->skillData = data;
}

void UTowerController::EffectStart()
{
	if (audio->IsValidLowLevelFast())
		audio->Stop();

	switch (skillData.id)
	{
	case 0:
		audio->SetSound(doSound);
		break;
	case 4:
		audio->SetSound(gaeSound);
		break;
	case 1:
		audio->SetSound(geolSound);
		break;
	case 2:
		audio->SetSound(yutSound);
		break;
	case 6:
		audio->SetSound(yutSound);
		break;
	case 10:
		audio->SetSound(moSound);
		break;
	}

	if (audio->IsValidLowLevelFast())
		audio->Play();
}

void UTowerController::AttackStart()
{
	if (skillController != nullptr)
	{
		skillController->AttackStartEvent();
	}
}

void UTowerController::AttackEnd()
{
	//타겟 초기화
	target = nullptr;

	if (skillController != nullptr)
	{
		skillController->AttackEndEvent();
	}
}