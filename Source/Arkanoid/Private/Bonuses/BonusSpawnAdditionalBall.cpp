// Fill out your copyright notice in the Description page of Project Settings.


#include "Bonuses/BonusSpawnAdditionalBall.h"

#include "Framework/Paddle.h"


// Sets default values
ABonusSpawnAdditionalBall::ABonusSpawnAdditionalBall()
{
}

void ABonusSpawnAdditionalBall::BonusAction( APaddle* Paddle )
{
    Paddle->BonusSpawnAdditionalBall();
    Super::BonusAction( Paddle );
} // BonusAction
