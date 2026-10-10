// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Paddle.generated.h"

class UInputAction;
class UInputMappingContext;
class ABall;
class UBoxComponent;
class UArrowComponent;

UCLASS()
class ARKANOID_API APaddle : public APawn
{
    GENERATED_BODY()

private:
    UPROPERTY( VisibleAnywhere, BlueprintReadOnly, meta = ( AllowPrivateAccess = true ), Category = "Components" )
    UBoxComponent* BoxCollider = nullptr;
    
    UPROPERTY( VisibleAnywhere, BlueprintReadOnly, meta = ( AllowPrivateAccess = true ), Category = "Components" )
    UStaticMeshComponent* StaticMesh = nullptr;
    
    UPROPERTY( VisibleAnywhere, BlueprintReadOnly, meta = ( AllowPrivateAccess = true ), Category = "Components" )
    UStaticMeshComponent* LeftStaticMesh = nullptr;
    
    UPROPERTY( VisibleAnywhere, BlueprintReadOnly, meta = ( AllowPrivateAccess = true ), Category = "Components" )
    UStaticMeshComponent* RightStaticMesh = nullptr;
    
    UPROPERTY( VisibleAnywhere, BlueprintReadOnly, meta = ( AllowPrivateAccess = true ), Category = "Components" )
    UArrowComponent* Arrow = nullptr;
    
    UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, meta = ( AllowPrivateAccess = true), Category= "Components")
    UMaterialInterface* AdditionalBallMaterial = nullptr;
    
    UPROPERTY()
    ABall* CurrentBall = nullptr;
    
    UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, meta = ( AllowPrivateAccess = true ), Category= "Settings | Input" )
    UInputMappingContext* DefaultMappingContext = nullptr;
    
    UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, meta = ( AllowPrivateAccess = true ), Category= "Settings | Input" )
    UInputAction* EscapeAction = nullptr;
    
    UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, meta = ( AllowPrivateAccess = true ), Category= "Settings | Input" )
    UInputAction* SpawnBallAction= nullptr;
    
    UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, meta = ( AllowPrivateAccess = true ), Category= "Settings | Input" )
    UInputAction* MoveAction = nullptr;
    
    UPROPERTY()
    TArray<UStaticMeshComponent*> BallLives;
    
    void SpawnBallLives();
    void UpdateBallLivesLocation();
    
public:
    APaddle();

protected:
    virtual void OnConstruction(const FTransform& Transform) override;
    virtual void BeginPlay() override;
    
    UFUNCTION()
    void ExitGame();
    
    UFUNCTION()
    void PushBall();
    
    UFUNCTION()
    void Move(const FInputActionValue& Value);
    
    UFUNCTION()
    void SpawnBall();
    
    UFUNCTION()
    void BallIsDead();    

public:
    virtual void SetupPlayerInputComponent( class UInputComponent* PlayerInputComponent ) override;
    
    UPROPERTY(EditDefaultsOnly, Category = "Settings | Game ", meta = ( ToolTip = "Ball class for spawn" ) )
    TSubclassOf<ABall> BallClass = nullptr;
    
    UPROPERTY(EditDefaultsOnly, Category = "Settings | Game ", meta = ( ToolTip = "Paddle speed" ) )
    float Speed = 2000.0f;
    
    UPROPERTY(EditDefaultsOnly, Category = "Settings | Game ", meta = ( ToolTip = "Default scale" ) )
    FVector DefaultScale = FVector( 0.4f, 2.4f, 0.5f );
    
    UPROPERTY(EditDefaultsOnly, Category = "Settings | Game ", meta = ( ToolTip = "Ball count" ) )
    int32 Lives = 3;
    
    // Функции и данные для бонусов
protected:
    FTimerHandle TimerForBonuses;
    
    UFUNCTION()
    void SetDefaultSize();
    
public:
    void BonusChangeSize( const float AdditionalSize, const float BonusTime );
    void BonusChangeLife( const int32 Amount );
    void BonusChangeBallSpeed( const float Amount );
    void BonusChangeBallPower( const float Amount, const float BonusTime );
    void BonusSpawnAdditionalBall();
};
