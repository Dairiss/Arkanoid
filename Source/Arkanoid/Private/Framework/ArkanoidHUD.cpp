// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/ArkanoidHUD.h"

#include "Blueprint/UserWidget.h"
#include "Widgets/HUDWidget.h"
#include "Widgets/PauseWidget.h"

void AArkanoidHUD::ChangeInputMode( UWidget* Widget ) const
{
    if( Widget )
    {
        FInputModeGameAndUI InputMode;
        InputMode.SetWidgetToFocus( Widget->TakeWidget() );
        PlayerOwner->SetInputMode( InputMode );
        PlayerOwner->SetShowMouseCursor( true );
    }
    else
    {
        FInputModeGameOnly InputMode;
        PlayerOwner->SetInputMode( InputMode );
        PlayerOwner->SetShowMouseCursor( false );
        PlayerOwner->SetPause( false );
    }
}// ChangeInputMode

void AArkanoidHUD::BeginPlay()
{
    Super::BeginPlay();

    if( HUDWidgetClass )
    {
        HUDWidget = CreateWidget<UHUDWidget>( PlayerOwner, HUDWidgetClass );
        if( HUDWidget )
            HUDWidget->AddToViewport();
    }
    
    ChangeInputMode();
}// BeginPlay

void AArkanoidHUD::ShowPauseWidget()
{
    if( !PauseWidget )
    {
        PauseWidget = CreateWidget<UPauseWidget>( PlayerOwner, PauseWidgetClass );
        if( PauseWidget )
        {
            PauseWidget->AddToViewport(99 );
            ChangeInputMode( PauseWidget );
            PauseWidget->OnGameResume.AddDynamic( this, &AArkanoidHUD::HidePauseWidget );
        }
    }
    else
    {
        PauseWidget->SetVisibility( ESlateVisibility::SelfHitTestInvisible );
        ChangeInputMode( PauseWidget );
    }
}// ShowPauseWidget

void AArkanoidHUD::HidePauseWidget()
{
    if( PauseWidget )
    {
        PauseWidget->SetVisibility( ESlateVisibility::Collapsed );
        ChangeInputMode();
    }
}// HidePauseWidget

void AArkanoidHUD::ShowGameEndWidget( const bool bWin )
{
    ShowPauseWidget();
    if( PauseWidget )    
        PauseWidget->SetWinStatus( bWin );    
}// ShowGameEndWidget
