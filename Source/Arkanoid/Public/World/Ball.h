// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnDeathEvent );

class UArrowComponent;

UENUM()
enum class EState : uint8
{
	Idle,
	Moving,
};

USTRUCT(BlueprintType)
struct FInitParams
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, meta = (ToolTip = "Start size"))
	float Scale;
	
	UPROPERTY(EditDefaultsOnly, meta = (ToolTip = "Start power"))
	int32 Power;
	
	UPROPERTY(EditDefaultsOnly, meta = (ToolTip = "Start speed"))
	float Speed;
	
	UPROPERTY(EditDefaultsOnly, meta = (ToolTip = "Max speed"))
	float MaxSpeed;
	
	FInitParams()
	{
		Scale = 0.5f;
		Power = 1;
		Speed = 500.0f;
		MaxSpeed = 2500.0f;
	}
};


UCLASS(Blueprintable)
class ARKANOID_API ABall : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= Components, meta = (AllowPrivateAccess = "true" ) )
	UStaticMeshComponent* StaticMesh = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= Components, meta = (AllowPrivateAccess = "true" ) )
	UArrowComponent* ForwardArrow = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= Components, meta = (AllowPrivateAccess = "true" ) )
	UAudioComponent* AudioComponent = nullptr;
	
	int32 Power = 1;
	float Speed = 0.0f;
	FVector Direction = FVector::ZeroVector;
	EState State = EState::Idle;
	
public:	
	ABall();
	
	FORCEINLINE int GetPower() const { return Power; }
	
	void SetBallState( const EState NewState );
	
	UPROPERTY(BlueprintAssignable)
	FOnDeathEvent OnDeathEvent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	UMaterialInterface* PowerMaterial = nullptr;

protected:

	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;	
	virtual void Destroyed() override;
	
	/*
	 * Передвижение актора
	 */
	UFUNCTION(BlueprintCallable, Category = Ball)
	void Move( const float DeltaTime );		
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	FInitParams InitParams;
	
	// Bonus data
	FTimerHandle TimerBallPower;
	
	UPROPERTY()
	UMaterialInterface* DefaultMaterial = nullptr;
	
	void ResetBallPower();
	void UpdateBallMaterial();

public:		
	void ChangeSpeed(const float Amount );
	void ChangePower( const int32 Amount, const float BonusTime );
};
