// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillContoller.h"

SkillContoller::SkillContoller(UWorld* uWorld)
{
	this->world = uWorld;

	UBlueprint* iceBlitz = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), NULL, TEXT("Blueprint'/Game/Blueprints/FX/IceBlitzParticle.IceBlitzParticle'")));
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

	particleArray.Add(NULL);					//0
	particleArray.Add(iceBlitzParticle);		//1
	particleArray.Add(fireBallParticle);		//2
	particleArray.Add(explosionParticle);
	particleArray.Add(mixedBallParticle);		//4
	particleArray.Add(mixedExplosionParticle);
	particleArray.Add(vortexParticle);			//6
	particleArray.Add(lightingVortexParticle);	//7
	particleArray.Add(fireVortexParticle);		//8
}

SkillContoller::~SkillContoller()
{

}

void SkillContoller::CreateParticle(SkillCreateData skillCreateData)
{
	int id = skillCreateData.data.id;
	//0 이면 이펙트 없음
	if (id != 0)
	{
		auto particle = particleArray[id];
		auto newActor = world->SpawnActor<AActor>(particle, skillCreateData.createPos, skillCreateData.createRotate);

		auto newSkillActor = SkillActor(skillCreateData, newActor);
		skillActorArray.Add(newSkillActor);
	}
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
			auto curSkillPos = skill.actor->GetActorLocation();
			auto targetSkillPos = skill.createData.targetActor->GetActorLocation() + FVector(0, 0, 70);

			auto diff = targetSkillPos - curSkillPos;

			if (diff.Size() > 3.0f)
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

				Attack(skill.createData.targetActor, skill.createData.attackValue);
				skill.actor->Destroy();
				skill.actor = nullptr;
				removeArray.Add(i);

				int explosionIndex = skill.createData.data.id + 1;
				if (particleArray[explosionIndex] != nullptr)
				{
					world->SpawnActor<AActor>(particleArray[explosionIndex], location, rotation);
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

void SkillContoller::Attack(AActor* targetActor, float attack)
{
	auto targetObj = targetActor->FindComponentByClass<UEnemyController>();

	if (targetObj != nullptr)
		targetObj->Damage(attack);
}


void SkillContoller::AttackStartEvent()
{	
	for (int i = 0; i < skillActorArray.Num(); i++)
	{
		auto skill = skillActorArray[i];

		switch (skill.createData.data.type)
		{
		case SkillType::OneShoot:
			Attack(skill.createData.targetActor, skill.createData.attackValue);
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
			skill.actor->Destroy();
			skill.actor = nullptr;
			removeArray.Add(i);
			break;
		case SkillType::TraceAndExplosion:
			//없음
			break;
		}
	}
}