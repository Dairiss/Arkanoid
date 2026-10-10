// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/ArkanoidPlayerController.h"

#include "Framework/ArkanoidHUD.h"

void AArkanoidPlayerController::ExitButtonPressed()
{
    const auto CurrentHUD = Cast<AArkanoidHUD>(GetHUD() );
    if ( !CurrentHUD )
        return;
    
    if( IsPaused() )
    {
        SetPause( false );
        CurrentHUD->HidePauseWidget();
    }
    else
    {
        SetPause( true );
        CurrentHUD->ShowPauseWidget();
    }
}// ExitButtonPressed

void AArkanoidPlayerController::ShowGameEndMenu( const bool bWin )
{
    const auto CurrentHUD = Cast<AArkanoidHUD>(GetHUD() );
    if ( CurrentHUD )
        CurrentHUD->ShowGameEndWidget( bWin );
    
    SetPause( true );
}// ShowGameEndMenu
