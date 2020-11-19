// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseField.h"
#include "YutnoriDefense/Controller/EnemyController.h"
#include "LifeField.generated.h"

/**
 *
 */
UCLASS()
class YUTNORIDEFENSE_API ALifeField : public ABaseField
{
	GENERATED_BODY()

    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
    virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

public:
    UPROPERTY(VisibleAnywhere)
    int playerHP;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
};
