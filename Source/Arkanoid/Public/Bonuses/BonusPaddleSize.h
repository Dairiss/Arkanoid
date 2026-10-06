// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BonusAbstract.h"
#include "BonusPaddleSize.generated.h"

UCLASS()
class ARKANOID_API ABonusPaddleSize : public ABonusAbstract
{
    GENERATED_BODY()

public:
    ABonusPaddleSize();

protected:
    virtual void BonusAction(APaddle* Paddle) override;

public:
};
