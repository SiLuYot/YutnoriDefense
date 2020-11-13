// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "YutnoriDefense/Field/EnemyMoveField.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnemyController.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class YUTNORIDEFENSE_API UEnemyController : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEnemyController();

	UPROPERTY(EditAnywhere)
	float moveSpeed;

	UPROPERTY(VisibleAnywhere)
	int32 moveFieldIndex;

	UPROPERTY(VisibleAnywhere)
	bool isMoveEnd;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Array)
	ABaseField* NextMoveField;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Init(ABaseField* field, int index);
};
