// Fill out your copyright notice in the Description page of Project Settings.


#include "Bonuses/BonusLive.h"
#include "Framework/Paddle.h"


ABonusLive::ABonusLive()
{
    Value = 1.0f;
}

void ABonusLive::BonusAction( APaddle* Paddle )
{
    Paddle->BonusChangeLife( Value );
    
    Super::BonusAction( Paddle );
}


