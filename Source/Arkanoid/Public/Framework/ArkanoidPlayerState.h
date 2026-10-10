// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ArkanoidPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnPlayerScoreChanged, const int32, PlayerScore );

/**
 * 
 */
UCLASS()
class ARKANOID_API AArkanoidPlayerState : public APlayerState
{
    GENERATED_BODY()
    
private:
    int32 PlayerScore = 0;
    
public:
    UPROPERTY( BlueprintAssignable, Category = "PlayerState")
    FOnPlayerScoreChanged OnPlayerScoreChanged;
    
    UFUNCTION(BlueprintPure, Category = "PlayerState")
    FORCEINLINE int32 GetPlayerScore() const { return PlayerScore; }
    
    UFUNCTION(BlueprintCallable, Category = "PlayerState")
    void ChangePlayerScore( const int32 Amount );
};
