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

	particleArray.Add(iceBlitzParticle);
	particleArray.Add(fireBallParticle);
	particleArray.Add(explosionParticle);
}

SkillContoller::~SkillContoller()
{

}

void SkillContoller::CreateParticle(SkillCreateData skillCreateData)
{
	auto particle = particleArray[skillCreateData.data.id];
	auto newActor = world->SpawnActor<AActor>(particle, skillCreateData.createPos, skillCreateData.createRotate);

	auto newSkillActor = SkillActor(skillCreateData, newActor);
	skillActorArray.Add(newSkillActor);
}

void SkillContoller::Update(float DeltaTime)
{
	for (int i = 0; i < skillActorArray.Num(); i++)
	{
		auto skill = skillActorArray[i];		

		switch (skill.createData.data.type)
		{
		case SkillType::OneShoot:
			//����
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

				world->SpawnActor<AActor>(explosionParticle, location, rotation);
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
			//����
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
			//����
			break;
		}
	}
}