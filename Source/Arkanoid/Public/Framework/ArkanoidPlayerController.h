// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ArkanoidPlayerController.generated.h"


UCLASS()
class ARKANOID_API AArkanoidPlayerController : public APlayerController
{
    GENERATED_BODY()
    
public:
    void ExitButtonPressed();
    void ShowGameEndMenu( const bool bWin );
};
