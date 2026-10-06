// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BonusAbstract.h"
#include "BonusLive.generated.h"

UCLASS()
class ARKANOID_API ABonusLive : public ABonusAbstract
{
    GENERATED_BODY()

public:
    ABonusLive();

protected:
    virtual void BonusAction( APaddle* Paddle ) override;
    
};
