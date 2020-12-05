// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CustomStruct.generated.h"

UCLASS()
class YUTNORIDEFENSE_API ACustomStruct : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACustomStruct();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

UENUM(BlueprintType)
enum class SkillType : uint8
{
	OneShoot = 0,
	TraceAndExplosion = 1
};

USTRUCT(Atomic, BlueprintType)
struct FSkillData
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int id;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	SkillType type;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float attack;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float attackSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float range;

	FSkillData() {}
	FSkillData(int id, SkillType type, float attack, float attackSpeed, float range)
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
	FSkillData data;

	SkillCreateData() {}
	SkillCreateData(FSkillData data, FVector createPos, FRotator createRotate, AActor* targetActor)
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

USTRUCT(Atomic, BlueprintType)
struct FTowerData
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int index;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int type;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int rank;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TSubclassOf<class AActor> towerBP;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FSkillData skillData;

	FTowerData() { }

	FTowerData(int index, int type, int rank, TSubclassOf<class AActor> towerBP, FSkillData skillData)
	{
		this->index = index;
		this->type = type;
		this->rank = rank;
		this->towerBP = towerBP;
		this->skillData = skillData;
	}
};