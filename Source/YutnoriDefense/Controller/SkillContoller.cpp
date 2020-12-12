// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillContoller.h"

SkillContoller::SkillContoller(UWorld* uWorld)
{
	this->world = uWorld;

	UBlueprint* iceBlitz = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/FX/IceBlitzParticle.iceBlitzParticle'")));
	if (iceBlitz)
	{
		iceBlitzParticle = (UClass*)iceBlitz->GeneratedClass;
	}

	UBlueprint* fireBall = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/FX/fireBallParticle.fireBallParticle'")));
	if (fireBall)
	{
		fireBallParticle = (UClass*)fireBall->GeneratedClass;
	}

	UBlueprint* explosion = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/FX/explosionParticle.explosionParticle'")));
	if (explosion)
	{
		explosionParticle = (UClass*)explosion->GeneratedClass;
	}

	UBlueprint* iceBall = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/FX/iceBallParticle.iceBallParticle'")));
	if (iceBall)
	{
		iceBallParticle = (UClass*)iceBall->GeneratedClass;
	}

	UBlueprint* iceBallExplosion = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/FX/iceexplosionParticle.iceExplosionParticle'")));
	if (iceBallExplosion)
	{
		iceBallExplosionParticle = (UClass*)iceBallExplosion->GeneratedClass;
	}

	UBlueprint* mixedBall = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/FX/mixedBallParticle.mixedBallParticle'")));
	if (mixedBall)
	{
		mixedBallParticle = (UClass*)mixedBall->GeneratedClass;
	}

	UBlueprint* mixedExplosion = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/FX/mixedExplosionParticle.mixedExplosionParticle'")));
	if (mixedExplosion)
	{
		mixedExplosionParticle = (UClass*)mixedExplosion->GeneratedClass;
	}

	UBlueprint* vortex = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/FX/VortexParticle.vortexParticle'")));
	if (vortex)
	{
		vortexParticle = (UClass*)vortex->GeneratedClass;
	}

	UBlueprint* lightingVortex = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/FX/LightingVortexParticle.lightingVortexParticle'")));
	if (lightingVortex)
	{
		lightingVortexParticle = (UClass*)lightingVortex->GeneratedClass;
	}

	UBlueprint* fireVortex = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/FX/fireVortexParticle.fireVortexParticle'")));
	if (fireVortex)
	{
		fireVortexParticle = (UClass*)fireVortex->GeneratedClass;
	}

	particleArray.Add(NULL);					//0 도
	particleArray.Add(iceBlitzParticle);		//1 걸
	particleArray.Add(fireBallParticle);		//2 윷
	particleArray.Add(explosionParticle);
	particleArray.Add(iceBallParticle);			//4 개
	particleArray.Add(iceBallExplosionParticle);
	particleArray.Add(mixedBallParticle);		//6 윷
	particleArray.Add(mixedExplosionParticle);
	particleArray.Add(vortexParticle);			//8 모
	particleArray.Add(lightingVortexParticle);	//9 모
	particleArray.Add(fireVortexParticle);		//10 모
}

SkillContoller::~SkillContoller()
{

}

void SkillContoller::CreateParticle(SkillCreateData skillCreateData)
{
	int id = skillCreateData.data.id;

	auto particle = particleArray[id];
	auto newActor = world->SpawnActor<AActor>(particle, skillCreateData.createPos, skillCreateData.createRotate);

	auto newSkillActor = SkillActor(skillCreateData, newActor);
	skillActorArray.Add(newSkillActor);

	//애니매이션 플레이 시작
	skillCreateData.instance->Montage_Play(skillCreateData.attackMontage);
}

void SkillContoller::Update(float DeltaTime)
{
	for (int i = 0; i < skillActorArray.Num(); i++)
	{
		auto skill = skillActorArray[i];

		switch (skill.createData.data.type)
		{
		case SkillType::OneShoot:
			//없음
			break;
		case SkillType::TraceAndExplosion:
			if (skill.actor != nullptr)
			{
				auto curSkillPos = skill.actor->GetActorLocation();
				auto targetSkillPos = skill.createData.targetActor->GetActorLocation() + FVector(0, 0, 70);

				auto diff = targetSkillPos - curSkillPos;

				if (skill.createData.targetActor == NULL || 
					!skill.createData.targetActor->IsValidLowLevel())
				{
					skill.actor->Destroy();
					skill.actor = nullptr;
					removeArray.Add(i);
				}
				else if (diff.Size() > 3.0f)
				{
					diff.Normalize();

					auto newPos = diff * 500.0f;
					auto nextPos = curSkillPos + newPos * DeltaTime;

					skill.actor->SetActorLocation(nextPos);
				}
				else
				{
					auto location = skill.actor->GetActorLocation();
					auto rotation = skill.actor->GetActorRotation();

					Attack(skill);
					skill.actor->Destroy();
					skill.actor = nullptr;
					removeArray.Add(i);

					int explosionIndex = skill.createData.data.id + 1;
					if (particleArray[explosionIndex] != nullptr)
					{
						world->SpawnActor<AActor>(particleArray[explosionIndex], location, rotation);
					}
				}
			}
			break;
		}
	}

	if (removeArray.Num() > 0)
	{
		for (int i = 0; i < removeArray.Num(); i++)
		{
			skillActorArray.RemoveAt(removeArray[i]);
		}
		removeArray.Reset();
	}

}

void SkillContoller::Attack(SkillActor skill)
{
	float attack = skill.createData.data.attack;
	AActor* targetActor = skill.createData.targetActor;

	if (targetActor != NULL &&
		targetActor->IsValidLowLevel() && 
		targetActor->GetOwner() != NULL &&
		targetActor->GetOwner()->IsValidLowLevel())
	{
		auto targetObj = targetActor->FindComponentByClass<UEnemyController>();

		//추가 이펙트 없음
		if (skill.createData.data.effectType == 0)
		{
			//광역 범위 있음
			if (skill.createData.data.effectArea != 0)
			{
				for (TActorIterator<AActor> It(targetActor->GetWorld()); It; ++It)
				{
					AActor* findActor = *It;
					if (findActor == nullptr)
					{
						continue;
					}

					//범위 안 적 찾기
					if (findActor->ActorHasTag(FName(TEXT("Enemy"))))
					{
						auto distance = targetActor->GetDistanceTo(findActor);

						//범위 안에 있다면
						auto skillRange = skill.createData.data.effectArea * EFFECT_DISTANCE;
						//범위가 너무 작은 경우 조금 넓혀줌
						skillRange = skillRange <= 130 ? 150 : skillRange;

						if (distance <= skillRange)
						{
							auto target = findActor->FindComponentByClass<UEnemyController>();

							if (target != nullptr)
								target->Damage(attack);
						}
					}
				}
			}
			//단일
			else
			{
				if (targetObj != nullptr)
					targetObj->Damage(attack);
			}
		}
		//단일 슬로우
		else if (skill.createData.data.effectType == 1)
		{
			targetObj->speedWeight = (1.0f - skill.createData.data.effectValue);
			targetObj->ApplySlowEffect(skill.createData.data.applyEffectTime);

			if (targetObj != nullptr)
				targetObj->Damage(attack);
		}
		//광역 슬로우
		else if (skill.createData.data.effectType == 2)
		{
			//월드의 모든 액터 검색
			for (TActorIterator<AActor> It(targetActor->GetWorld()); It; ++It)
			{
				AActor* findActor = *It;
				if (findActor == nullptr)
				{
					continue;
				}

				//범위 안 적 찾기
				if (findActor->ActorHasTag(FName(TEXT("Enemy"))))
				{
					auto distance = targetActor->GetDistanceTo(findActor);

					//범위 안에 있다면
					auto skillRange = skill.createData.data.effectArea * EFFECT_DISTANCE;
					//범위가 너무 작은 경우 조금 넓혀줌
					skillRange = skillRange <= 130 ? 150 : skillRange;

					if (distance <= skillRange)
					{
						auto target = findActor->FindComponentByClass<UEnemyController>();

						target->speedWeight = (1 - skill.createData.data.effectValue);
						target->ApplySlowEffect(skill.createData.data.applyEffectTime);

						if (target != nullptr)
							target->Damage(attack);
					}
				}
			}
		}
		//최대 체력 % 데미지
		else if (skill.createData.data.effectType == 3)
		{
			//월드의 모든 액터 검색
			for (TActorIterator<AActor> It(targetActor->GetWorld()); It; ++It)
			{
				AActor* findActor = *It;
				if (findActor == nullptr)
				{
					continue;
				}

				//범위 안 적 찾기
				if (findActor->ActorHasTag(FName(TEXT("Enemy"))))
				{
					auto distance = targetActor->GetDistanceTo(findActor);

					//범위 안에 있다면
					auto skillRange = skill.createData.data.effectArea * EFFECT_DISTANCE;
					//범위가 너무 작은 경우 조금 넓혀줌
					skillRange = skillRange <= 130 ? 150 : skillRange;

					if (distance <= skillRange)
					{
						auto target = findActor->FindComponentByClass<UEnemyController>();
						
						auto finalAttack = attack + (target->GetMaxHP() * skill.createData.data.effectValue);
						if (target != nullptr)
							target->Damage(finalAttack);
					}
				}
			}			
		}
	}	
}

void SkillContoller::AttackStartEvent()
{
	for (int i = 0; i < skillActorArray.Num(); i++)
	{
		auto skill = skillActorArray[i];

		switch (skill.createData.data.type)
		{
		case SkillType::OneShoot:
			Attack(skill);
			break;
		case SkillType::TraceAndExplosion:
			//없음
			break;
		}
	}
}

void SkillContoller::AttackEndEvent()
{
	for (int i = 0; i < skillActorArray.Num(); i++)
	{
		auto skill = skillActorArray[i];

		switch (skill.createData.data.type)
		{
		case SkillType::OneShoot:
			if (skill.actor != nullptr)
			{
				skill.actor->Destroy();
				skill.actor = nullptr;
			}			
			removeArray.Add(i);
			break;
		case SkillType::TraceAndExplosion:
			//없음
			break;
		}
	}
}

void SkillContoller::DestroyAll()
{
	for (int i = 0; i < skillActorArray.Num(); i++)
	{
		auto skill = skillActorArray[i];

		if (skill.actor != nullptr)
		{
			skill.actor->Destroy();
			skill.actor = nullptr;
		}
		removeArray.Add(i);
	}
	
	if (removeArray.Num() > 0)
	{
		for (int i = 0; i < removeArray.Num(); i++)
		{
			skillActorArray.RemoveAt(removeArray[i]);
		}
		removeArray.Reset();
	}
	skillActorArray.Reset();
}