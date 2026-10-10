// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ArkanoidGameMode.generated.h"


UCLASS()
class ARKANOID_API AArkanoidGameMode : public AGameModeBase
{
    GENERATED_BODY()
    
public:
    AArkanoidGameMode();
protected:
    virtual void BeginPlay() override;
    
public:
    UFUNCTION(BlueprintCallable, Category = "GameMode")
    void GameStarted();
    
    UFUNCTION(BlueprintCallable, Category = "GameMode")
    void GameEnded( const bool bWin );
};
