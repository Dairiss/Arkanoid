// Fill out your copyright notice in the Description page of Project Settings.


#include "Bonuses/BonusBallSpeed.h"

#include "Framework/Paddle.h"


ABonusBallSpeed::ABonusBallSpeed()
{
    Value = -0.5f;
}// ABonusBallSpeed

void ABonusBallSpeed::BonusAction( APaddle* Paddle )
{
    Paddle->BonusChangeBallSpeed( Value );
    Super::BonusAction( Paddle );
}// BonusAction
