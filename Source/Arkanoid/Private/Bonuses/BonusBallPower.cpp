// Fill out your copyright notice in the Description page of Project Settings.


#include "Bonuses/BonusBallPower.h"

#include "Framework/Paddle.h"


ABonusBallPower::ABonusBallPower()
{
    Value = 1.0f;
    Duration = 10.0f;
}// ABonusBallPower

void ABonusBallPower::BonusAction( APaddle* Paddle )
{
    Paddle->BonusChangeBallPower( Value, Duration );    
    Super::BonusAction( Paddle );
}// BonusAction
