// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Classes/GameFramework/Actor.h"
#include "Engine/World.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "YutnoriDefense/Manager/CustomStruct.h"
#include "Engine/World.h"
#include "CoreUObject/Public/UObject/UObjectIterator.h"
#include "Engine/Public/EngineUtils.h"
#include "YutnoriDefense/Controller/EnemyController.h"

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

	const float EFFECT_DISTANCE = 130.0f;

public:
	SkillContoller(UWorld* uWorld);
	~SkillContoller();

	void CreateParticle(SkillCreateData skillData);
	void Update(float DeltaTime);
	void Attack(SkillActor skill);
	void AttackStartEvent();
	void AttackEndEvent();
	void DestroyAll();

	TArray<SkillActor> skillActorArray;
};