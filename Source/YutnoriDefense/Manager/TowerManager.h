// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "YutnoriDefense/Field/BaseField.h"
#include "YutnoriDefense/Field/TowerField.h"
#include "YutnoriDefense/Controller/TowerController.h"
#include "CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "TowerManager.generated.h"

UCLASS()
class YUTNORIDEFENSE_API ATowerManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATowerManager();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> tower_Do_BP;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> tower_Gae_BP;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> tower_Geol_BP;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> tower_Yut_BP;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> tower_Mo_BP;

	TArray<TowerData*> towerDataArray;

	int clickCount;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void ClickFieldEvent(ABaseField* field);
};
