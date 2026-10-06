// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BonusAbstract.h"
#include "BonusSpawnAdditionalBall.generated.h"

UCLASS()
class ARKANOID_API ABonusSpawnAdditionalBall : public ABonusAbstract
{
    GENERATED_BODY()

public:
    ABonusSpawnAdditionalBall();

protected:
    virtual void BonusAction( APaddle* Paddle ) override;

public:
    
};
