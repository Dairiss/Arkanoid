// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BonusAbstract.h"
#include "BonusSpawnBallAtCubeLocation.generated.h"

class ABall;

UCLASS()
class ARKANOID_API ABonusSpawnBallAtCubeLocation : public ABonusAbstract
{
    GENERATED_BODY()

private:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Components", meta=( AllowPrivateAccess = "true" ) )
    TSubclassOf<ABall> BallClass = nullptr;
    
public:
    ABonusSpawnBallAtCubeLocation();

protected:
    virtual void BeginPlay() override;

public:
};
