// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BonusAbstract.generated.h"

class APaddle;

UCLASS(Blueprintable, Abstract)
class ARKANOID_API ABonusAbstract : public AActor
{
    GENERATED_BODY()

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components", meta=( AllowPrivateAccess = "true" ))
    UStaticMeshComponent* BonusMesh = nullptr;    
    
public:
    ABonusAbstract();

protected:
    virtual void BeginPlay() override;
    
    void Move( const float DeltaTime );
    virtual void BonusAction(APaddle* Paddle);

public:
    virtual void Tick( float DeltaTime ) override;
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Settings", meta=(ToolTip = "Movement direction") )
    FVector Direction = FVector(-1.0f, 0.0f, 0.0f);
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Settings", meta=(ToolTip = "Duration") )
    float Duration = 0.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Settings", meta=(ToolTip = "Movement speed") )
    float Speed = 500.0f;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Settings", meta=(ToolTip = "Value") )
    float Value = 0.5f;
    
    void InitScale( const FVector NewScale );
};
