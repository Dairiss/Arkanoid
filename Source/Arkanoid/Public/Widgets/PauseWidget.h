// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseWidget.generated.h"


class UButton;
class UTextBlock;

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnGameResume );

UCLASS()
class ARKANOID_API UPauseWidget : public UUserWidget
{
    GENERATED_BODY()
    
private:
    UPROPERTY( meta = ( BindWidget, AllowPrivateAccess = true ) )
    UTextBlock* StatusText = nullptr;
    
    UPROPERTY( meta = ( BindWidget, AllowPrivateAccess = true ) )
    UButton* ResumeButton = nullptr;
    
    UPROPERTY( meta = ( BindWidget, AllowPrivateAccess = true ) )
    UButton* RestartButton = nullptr;
    
    UPROPERTY( meta = ( BindWidget, AllowPrivateAccess = true ) )
    UButton* MenuButton = nullptr;
    
protected:
    virtual void NativeConstruct() override;
    
    UFUNCTION()
    void ResumeGame();
    
    UFUNCTION()
    void RestartGame();
    
    UFUNCTION()
    void BackToMainMenu();
    
public:
    UPROPERTY( BlueprintAssignable, Category = "PauseWidget" )
    FOnGameResume OnGameResume;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings")
    USoundBase* WinSound = nullptr;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings")
    USoundBase* LoseSound = nullptr;
    
    void SetWinStatus( const bool bWin );
};
