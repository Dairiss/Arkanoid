// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/ArkanoidGameMode.h"

#include "Framework/ArkanoidGameState.h"
#include "Framework/ArkanoidPlayerController.h"
#include "Framework/ArkanoidPlayerState.h"

AArkanoidGameMode::AArkanoidGameMode()
{
    GameStateClass = AArkanoidGameState::StaticClass();
    PlayerStateClass = AArkanoidPlayerState::StaticClass();
}// AArkanoidGameMode

void AArkanoidGameMode::BeginPlay()
{
    Super::BeginPlay();
    
    GameStarted();
}// BeginPlay

void AArkanoidGameMode::GameStarted()
{
    if(  auto ArkanoidGameState = Cast<AArkanoidGameState>( GameState ) )    
        ArkanoidGameState->StartGame();    
}// GameStarted

void AArkanoidGameMode::GameEnded( const bool bWin )
{    
    if( auto ArkanoidGameState = Cast<AArkanoidGameState>( GameState ) )    
        ArkanoidGameState->StopGame();    
    
    //UE_LOG( LogTemp, Warning, TEXT( "Game Ended" ) );

    for( APlayerState* PlayerState : GameState->PlayerArray )
    {
        if( PlayerState )
        {
            if( const auto Player = Cast<AArkanoidPlayerController>(PlayerState->GetPlayerController() ) )            
                Player->ShowGameEndMenu( bWin );            
        }
    }    
}// GameEnded
