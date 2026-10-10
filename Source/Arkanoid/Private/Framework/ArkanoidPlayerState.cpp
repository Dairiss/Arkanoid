// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/ArkanoidPlayerState.h"
#include "Framework/ArkanoidGameInstance.h"
#include "Kismet/GameplayStatics.h"

void AArkanoidPlayerState::ChangePlayerScore( const int32 Amount )
{
    PlayerScore = FMath::Max( PlayerScore + Amount,0 );

    if( const auto GameInstance = Cast<UArkanoidGameInstance>(GetGameInstance()) )
        GameInstance-> SetLevelRecord( UGameplayStatics::GetCurrentLevelName( this ), PlayerScore );
    
    OnPlayerScoreChanged.Broadcast( PlayerScore );
    
    //UE_LOG(LogTemp, Warning, TEXT("PlayerScore changed to: %d"), PlayerScore );
}// ChangePlayerScore
