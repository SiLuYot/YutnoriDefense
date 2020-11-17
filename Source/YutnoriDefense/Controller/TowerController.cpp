// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerController.h"

// Sets default values for this component's properties
UTowerController::UTowerController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTowerController::BeginPlay()
{
	Super::BeginPlay();
	
	GetOwner()->AddActorLocalRotation(FRotator(0, 90, 0));	
}


// Called every frame
void UTowerController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	timer += DeltaTime;

	for (TActorIterator<AActor> It(GetWorld()); It; ++It)
	{
		AActor* findActor = *It;
		if (findActor->ActorHasTag(FName(TEXT("Enemy"))))
		{
			auto distance = GetOwner()->GetDistanceTo(findActor);

			if (distance <= attackDistance)
			{								
				auto curPos = GetOwner()->GetActorLocation();
				auto targetPos = findActor->GetActorLocation();

				FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(targetPos, curPos);
				GetOwner()->SetActorRotation(Rotator);
				GetOwner()->AddActorLocalRotation(FRotator(0, 90, 0));
				
				if (timer >= attackSpeed)
				{
					timer = 0;
					Attack(findActor->FindComponentByClass<UEnemyController>());
				}

				/*UE_LOG(LogTemp, Log, TEXT("Find Enemy Name :: %s / dis :: %f"), *findActor->GetName(), distance);
				UE_LOG(LogTemp, Log, TEXT("pos1 :: %s pos2 :: %s"), *curPos.ToString(), *targetPos.ToString());*/

				break;
			}			
		}
	}
}

void UTowerController::Init() 
{
	this->attack = 1.0f;
	this->attackSpeed = 1.0f;
	this->attackDistance = 200.0f;
	this->timer = 0;
}

void UTowerController::Attack(UEnemyController* enemy)
{
	enemy->Damage(attack);
}
