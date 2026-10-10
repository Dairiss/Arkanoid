// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/ArkanoidGameState.h"



AArkanoidGameState::AArkanoidGameState()
{
    PrimaryActorTick.bCanEverTick = true;
}// AArkanoidGameState

void AArkanoidGameState::Tick( float DeltaSeconds )
{
    Super::Tick( DeltaSeconds );
    
    if( bGameStarted )
        GameTime+= DeltaSeconds;
}// Tick

void AArkanoidGameState::StartGame()
{
    bGameStarted = true;
}// StartGame

void AArkanoidGameState::StopGame()
{
    bGameStarted = false;
}// StopGame

void AArkanoidGameState::GetGameTime( int32& Minutes, int32& Seconds, int32& Milliseconds ) const
{
    Minutes = static_cast<int32>( GameTime ) / 60;
    Seconds = static_cast<int32>( GameTime ) % 60;
    Milliseconds = static_cast<int32>( ( GameTime - FMath::Floor( GameTime ) ) * 1000 );
}// GetGameTime
