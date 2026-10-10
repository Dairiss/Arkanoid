// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/HUDWidget.h"

#include "Components/TextBlock.h"
#include "Framework/ArkanoidGameInstance.h"
#include "Framework/ArkanoidGameState.h"
#include "Framework/ArkanoidPlayerState.h"
#include "Kismet/GameplayStatics.h"

void UHUDWidget::NativeConstruct()
{
    Super::NativeConstruct();
    
    if( GetOwningPlayer() )
    {
        PlayerState = GetOwningPlayer()->GetPlayerState<AArkanoidPlayerState>();
        
        if( PlayerState )
            PlayerState->OnPlayerScoreChanged.AddDynamic( this, &UHUDWidget::UpdateScore );
    }

    if( GetWorld() )    
        GameState = Cast<AArkanoidGameState>(GetWorld()->GetGameState() ); 
    
    UpdateRecordOnScreen();
}// NativeConstruct

void UHUDWidget::NativeTick( const FGeometry& MyGeometry, float InDeltaTime )
{
    Super::NativeTick( MyGeometry, InDeltaTime );
    
    UpdateTime();
}// NativeTick

void UHUDWidget::UpdateScore( const int32 NewScore )
{
    if( CurrentScore )
    {
        const FString ScoreString = FString::Printf( TEXT("%03d"), NewScore );
        CurrentScore->SetText( FText::FromString( ScoreString ) );

        if( ShakeAnimation )        
            PlayAnimation( ShakeAnimation, 0.0f, 3, EUMGSequencePlayMode::Forward, 1.0f );        
    }
    UpdateRecordOnScreen();
}// UpdateScore

void UHUDWidget::UpdateTime()
{
    if( GameTime && GameState )
    {
        int32 Minutes {}, Seconds {}, Milliseconds {};
        GameState->GetGameTime( Minutes, Seconds, Milliseconds );
        
        const FString TimeString = FString::Printf( TEXT("%02d : %02d : %03d"), Minutes, Seconds, Milliseconds );
        GameTime->SetText( FText::FromString( TimeString ) );
    }
}// UpdateTime

void UHUDWidget::UpdateRecordOnScreen()
{
    if( LevelRecord )
    {
        if( const auto GameInstance = Cast<UArkanoidGameInstance>(GetGameInstance()) )
        {
            const int32 CurrentRecord = GameInstance->GetLevelRecord(UGameplayStatics::GetCurrentLevelName( this ) );
            const FString ScoreText = FString::Printf( TEXT("%03d"), CurrentRecord );
            LevelRecord->SetText( FText::FromString( *ScoreText ) );
        }
    }
}// UpdateRecordOnScreen
