// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Classes/GameFramework/Actor.h"
#include "Engine/World.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "YutnoriDefense/Controller/EnemyController.h"

enum SkillType
{
	OneShoot = 0,
	TraceAndExplosion = 1
};

struct SkillData
{
	int id;
	SkillType type;

	float attack;
	float attackSpeed;
	float range;

	SkillData() {}
	SkillData(int id, SkillType type, float attack, float attackSpeed, float range)
	{
		this->id = id;
		this->type = type;
		this->attack = attack;
		this->attackSpeed = attackSpeed;
		this->range = range;
	}
};

struct SkillCreateData
{
	FVector createPos;
	FRotator createRotate;
	AActor* targetActor;
	SkillData data;

	SkillCreateData() {}
	SkillCreateData(SkillData data, FVector createPos, FRotator createRotate, AActor* targetActor)
	{
		this->data = data;
		this->createPos = createPos;
		this->createRotate = createRotate;
		this->targetActor = targetActor;
	}
};

struct SkillActor
{
	SkillCreateData createData;
	AActor* actor;

	SkillActor() {}
	SkillActor(SkillCreateData createData, AActor* actor)
	{
		this->createData = createData;
		this->actor = actor;
	}
};

class YUTNORIDEFENSE_API SkillContoller
{
public:
	UPROPERTY(VisibleAnywhere)
	TSubclassOf<class AActor> iceBlitzParticle;

	UPROPERTY(VisibleAnywhere)
	TSubclassOf<class AActor> fireBallParticle;

	UPROPERTY(VisibleAnywhere)
	TSubclassOf<class AActor> explosionParticle;

	UPROPERTY(VisibleAnywhere)
	TSubclassOf<class AActor> iceBallParticle;

	UPROPERTY(VisibleAnywhere)
	TSubclassOf<class AActor> iceBallExplosionParticle;

	UPROPERTY(VisibleAnywhere)
	TSubclassOf<class AActor> mixedBallParticle;

	UPROPERTY(VisibleAnywhere)
	TSubclassOf<class AActor> mixedExplosionParticle;

	UPROPERTY(VisibleAnywhere)
	TSubclassOf<class AActor> vortexParticle;

	UPROPERTY(VisibleAnywhere)
	TSubclassOf<class AActor> lightingVortexParticle;

	UPROPERTY(VisibleAnywhere)
	TSubclassOf<class AActor> fireVortexParticle;

	UWorld* world;
	TArray<TSubclassOf<class AActor>> particleArray;
	TArray<int> removeArray;

public:
	SkillContoller(UWorld* uWorld);
	~SkillContoller();

	void CreateParticle(SkillCreateData skillData);
	void Update(float DeltaTime);
	void Attack(AActor* targetActor, float attack);
	void AttackStartEvent();
	void AttackEndEvent();
	void DestroyAll();

	TArray<SkillActor> skillActorArray;
};