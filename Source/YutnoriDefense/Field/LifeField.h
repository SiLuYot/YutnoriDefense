// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseField.h"
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
};
