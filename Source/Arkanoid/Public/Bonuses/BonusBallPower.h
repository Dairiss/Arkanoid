// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BonusAbstract.h"
#include "BonusBallPower.generated.h"

UCLASS()
class ARKANOID_API ABonusBallPower : public ABonusAbstract
{
    GENERATED_BODY()

public:
    ABonusBallPower();

protected:
    virtual void BonusAction( APaddle* Paddle ) override;
public:
    
};
