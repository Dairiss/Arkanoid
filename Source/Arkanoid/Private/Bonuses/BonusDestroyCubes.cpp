// Fill out your copyright notice in the Description page of Project Settings.


#include "Bonuses/BonusDestroyCubes.h"

#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "World/PlayingBoard.h"


ABonusDestroyCubes::ABonusDestroyCubes()
{
    Value = 3.0f;
}// ABonusDestroyCubes

void ABonusDestroyCubes::BonusAction( APaddle* Paddle )
{
    for( TActorIterator<APlayingBoard> It( GetWorld() ); It; ++It )
    {
        if( const auto CurrentBoard = *It )        
            CurrentBoard->BonusDestroyCubes( Value );
    }
    
    Super::BonusAction( Paddle );
} // BonusAction
