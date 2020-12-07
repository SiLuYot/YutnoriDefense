// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/Animation/AnimInstance.h"
#include "CoreUObject/Public/UObject/UObjectIterator.h"
#include "Engine/Public/EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "YutnoriDefense/Controller/EnemyController.h"
#include "YutnoriDefense/Controller/SkillContoller.h"
#include "Components/AudioComponent.h"
#include "TowerController.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class YUTNORIDEFENSE_API UTowerController : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTowerController();

	const float ATTACK_DISTANCE = 130.0f;

	UPROPERTY(VisibleAnywhere)
	float timer;

	UPROPERTY(VisibleAnywhere)
	UAnimMontage* attackMontage;

	UPROPERTY(VisibleAnywhere)
	USoundWave* doSound;

	UPROPERTY(VisibleAnywhere)
	USoundWave* gaeSound;

	UPROPERTY(VisibleAnywhere)
	USoundWave* geolSound;

	UPROPERTY(VisibleAnywhere)
	USoundWave* yutSound;

	UPROPERTY(VisibleAnywhere)
	USoundWave* moSound;

	UEnemyController* target;

	USkeletalMeshComponent* meshRoot;
	UAnimInstance* animRoot;
	USceneComponent* shootRoot;

	FSkillData skillData;
	SkillContoller* skillController;
	UAudioComponent* audio;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FTimerHandle CountdownTimerHandle;

	void Init(FSkillData skillData);

	UFUNCTION(BlueprintCallable)
	void AttackStart();

	UFUNCTION(BlueprintCallable)
	void AttackEnd();

	UFUNCTION(BlueprintCallable)
	void EffectStart();
};
