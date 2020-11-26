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
#include "TowerController.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class YUTNORIDEFENSE_API UTowerController : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTowerController();

	UPROPERTY(VisibleAnywhere)
	float attack;

	UPROPERTY(VisibleAnywhere)
	float attackSpeed;

	UPROPERTY(VisibleAnywhere)
	float attackDistance;

	UPROPERTY(VisibleAnywhere)
	float timer;

	UPROPERTY(VisibleAnywhere)
	UAnimMontage* attackMontage;

	UPROPERTY(VisibleAnywhere)
	TSubclassOf<class AActor> iceBlitzParticle;

	UPROPERTY(VisibleAnywhere)
	TSubclassOf<class AActor> fireBallParticle;

	UPROPERTY(VisibleAnywhere)
	TSubclassOf<class AActor> explosionParticle;

	AActor* skillParticle;
	UEnemyController* target;

	USkeletalMeshComponent* meshRoot;
	UAnimInstance* animRoot;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FTimerHandle CountdownTimerHandle;

	void Init();
	
	void Attack(UEnemyController* enemy);

	UFUNCTION(BlueprintCallable)
	void AttackStart();

	UFUNCTION(BlueprintCallable)
	void AttackEnd();
};
