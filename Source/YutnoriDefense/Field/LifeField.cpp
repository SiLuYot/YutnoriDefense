// Fill out your copyright notice in the Description page of Project Settings.


#include "LifeField.h"
#include "YutnoriDefense/EnemyControll/EnemyControll.h"

void ALifeField::NotifyActorBeginOverlap(AActor* OtherActor)
{    
    auto actorControll = OtherActor->FindComponentByClass<UEnemyControll>();
    if (actorControll != nullptr)
    {
        OtherActor->Destroy();
    }
}

void ALifeField::NotifyActorEndOverlap(AActor* OtherActor)
{
    
}