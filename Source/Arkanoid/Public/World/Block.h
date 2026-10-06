// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Block.generated.h"

class ABonusAbstract;
class ULifeComponent;

UCLASS()
class ARKANOID_API ABlock : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category= Components, meta = (AllowPrivateAccess = true) )
	UStaticMeshComponent* StaticMesh = nullptr;
	
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category= Components, meta = (AllowPrivateAccess = true) )
	ULifeComponent* LifeComponent = nullptr;
	
	TSubclassOf<ABonusAbstract> BonusClass = nullptr;
public:	
	// Sets default values for this actor's properties
	ABlock();

protected:
	virtual	void BeginPlay() override;
	
	virtual void NotifyHit( class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, 
		bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit ) override;
	
public:	

	void Init( const FVector NewScale, const int32 LifeAmount, const TSubclassOf<ABonusAbstract> NewBonusClass = nullptr );
	
	UPROPERTY( EditAnywhere,BlueprintReadWrite, Category = "Settings" )
	TArray<UMaterialInterface*> LifeMaterials;
};
