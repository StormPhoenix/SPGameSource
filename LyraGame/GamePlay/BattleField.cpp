// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleField.h"
#include "GameModes/LyraGameState.h"
#include "GameModes/LyraExperienceDefinition.h"
#include "GameModes/LyraExperienceManagerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/LyraPlayerBotController.h"


// Sets default values
ABattleField::ABattleField()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ABattleField::BeginPlay()
{
	Super::BeginPlay();

	if (ALyraGameState* GameState = Cast<ALyraGameState>(GetWorld()->GetGameState()))
	{
		ULyraExperienceManagerComponent* ExperienceComponent = GameState->FindComponentByClass<ULyraExperienceManagerComponent>();
		check(ExperienceComponent);
		ExperienceComponent->CallOrRegister_OnExperienceLoaded_LowPriority(
			FOnLyraExperienceLoaded::FDelegate::CreateUObject(this, &ThisClass::OnExperienceLoaded));
	}
}

void ABattleField::OnExperienceLoaded(const ULyraExperienceDefinition* Experience)
{
	TArray<AActor*> Controllers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALyraPlayerBotController::StaticClass(), Controllers);

	for (auto Controller: Controllers)
	{
		if (Controller != nullptr)
		{
			EnemyControllers.Add(Cast<ALyraPlayerBotController>(Controller));
		}
	}
}

