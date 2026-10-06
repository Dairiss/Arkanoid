// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BonusAbstract.h"
#include "BonusDestroyCubes.generated.h"

UCLASS()
class ARKANOID_API ABonusDestroyCubes : public ABonusAbstract
{
    GENERATED_BODY()

public:
    ABonusDestroyCubes();

protected:
    virtual void BonusAction(APaddle* Paddle) override;

public:
};
