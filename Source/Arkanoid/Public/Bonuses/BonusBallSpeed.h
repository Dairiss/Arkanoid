// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BonusAbstract.h"
#include "BonusBallSpeed.generated.h"

UCLASS()
class ARKANOID_API ABonusBallSpeed : public ABonusAbstract
{
    GENERATED_BODY()

public:
    ABonusBallSpeed();

protected:
    virtual void BonusAction( APaddle* Paddle ) override;
    
public:
    
};
