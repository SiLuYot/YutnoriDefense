// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "YutnoriDefense/Field/EnemyMoveField.h"
#include "Kismet/KismetMathLibrary.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Engine/Public/EngineUtils.h"
#include "EnemyController.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class YUTNORIDEFENSE_API UEnemyController : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEnemyController();

	UPROPERTY(BlueprintReadWrite)
	float hp;

	UPROPERTY(BlueprintReadWrite)
	float maxHp;

	UPROPERTY(BlueprintReadWrite)
	float moveSpeed;

	UPROPERTY(BlueprintReadWrite)
	float speedWeight;

	UPROPERTY(BlueprintReadWrite)
	float defense;

	UPROPERTY(VisibleAnywhere)
	int32 moveFieldIndex;

	UPROPERTY(VisibleAnywhere)
	bool isMoveEnd;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Array)
	ABaseField* NextMoveField;

	UFUNCTION(BlueprintCallable)
	float GetHP();

	UFUNCTION(BlueprintCallable)
	float GetMaxHP();

	UFUNCTION(BlueprintCallable)
	float GetSpeed();

	UFUNCTION(BlueprintCallable)
	void SetStat(float _hp, float _moveSpeed);

	UPROPERTY()
	USceneComponent* meshRoot;

	UPROPERTY()
	USceneComponent* uiRoot;

	FTimerHandle timer;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Init();

	void SetNextPos(ABaseField* field, int index);

	void Damage(float attack);

	void SetTimer(float time, FTimerDelegate const& InDelegate);
	void ClearTimer();
	void ResetSpeedWeight();
	void ResetHealWeight();
	void ResetDefenseWeight();

	UFUNCTION(BlueprintCallable)
	void SpeedAura();

	UFUNCTION(BlueprintCallable)
	void HealAura();

	UFUNCTION(BlueprintCallable)
	void DefenseAura();

	UFUNCTION(BlueprintCallable)
	void InvincibleAura();


	void ApplySlowEffect(float time);
	void ApplyHealEffect(float time);
	void ApplyDefenseEffect(float time);

	void EndSlowEffect();
	void EndHealEffect();
	void EndDefenseEffect();
};
