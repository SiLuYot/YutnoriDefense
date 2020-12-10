// Fill out your copyright notice in the Description page of Project Settings.


#include "LifeField.h"

void ALifeField::BeginPlay() 
{
    Super::BeginPlay();

    playerHP = 20;
}

void ALifeField::NotifyActorBeginOverlap(AActor* OtherActor)
{    
    auto actorControll = OtherActor->FindComponentByClass<UEnemyController>();
    if (actorControll != nullptr)
    {
        //OtherActor->Destroy();
        actorControll->GetOwner()->Destroy();

        playerHP -= 1;
        UE_LOG(LogTemp, Log, TEXT("���� ��� : %d"), playerHP);
        if (playerHP <= 0)
        {
            //���� �й�
            UE_LOG(LogTemp, Log, TEXT("Game End"));
        }
    }
}

void ALifeField::NotifyActorEndOverlap(AActor* OtherActor)
{
    
}