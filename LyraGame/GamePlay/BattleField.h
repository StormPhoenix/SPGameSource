// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "GameFramework/Actor.h"
#include "BattleField.generated.h"

class ALyraPlayerBotController;
class ULyraExperienceDefinition;

UCLASS()
class LYRAGAME_API ABattleField : public ATriggerBox
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABattleField();

	void OnExperienceLoaded(const ULyraExperienceDefinition* Experience);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TArray<ALyraPlayerBotController*> EnemyControllers;
};
