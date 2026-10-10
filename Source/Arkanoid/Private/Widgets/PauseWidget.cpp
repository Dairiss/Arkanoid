// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/PauseWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "DSP/BufferDiagnostics.h"
#include "HLSLTree/HLSLTreeTypes.h"
#include "Kismet/GameplayStatics.h"

void UPauseWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if( ResumeButton )
        ResumeButton->OnReleased.AddDynamic( this, &UPauseWidget::ResumeGame );
    
    if( RestartButton )
        RestartButton->OnReleased.AddDynamic( this, &UPauseWidget::RestartGame );
    
    if( MenuButton )
        MenuButton->OnReleased.AddDynamic( this, &UPauseWidget::BackToMainMenu );
}// NativeConstruct

void UPauseWidget::ResumeGame()
{ 
    OnGameResume.Broadcast();
}// ResumeGame

void UPauseWidget::RestartGame()
{
    const auto LevelName = UGameplayStatics::GetCurrentLevelName( GetWorld() );
    UGameplayStatics::OpenLevel( this, FName( *LevelName ) );
}// RestartGame

void UPauseWidget::BackToMainMenu()
{
    UGameplayStatics::OpenLevel( this, FName( "MainMenuLevel" ) );
}// BackToMainMenu

void UPauseWidget::SetWinStatus( const bool bWin )
{
    if( !StatusText )
        return;

    UGameplayStatics::PlaySound2D( this, bWin ? WinSound : LoseSound );
    
    if( ResumeButton )
    {
        ResumeButton->SetIsEnabled( false );
        ResumeButton->SetVisibility( ESlateVisibility::Hidden );
    }
    
    if( bWin )
    {
        StatusText->SetText( FText::FromString( TEXT( "Win" ) ) );
        StatusText->SetColorAndOpacity( FColor::Cyan );
    }
    else
    {
        StatusText->SetText( FText::FromString( TEXT( "You lose" ) ) );
        StatusText->SetColorAndOpacity( FColor::Red );
    }
}// SetWinStatus

