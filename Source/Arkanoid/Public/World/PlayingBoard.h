// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayingBoard.generated.h"

class ABonusAbstract;
class ABlock;

USTRUCT(BlueprintType)
struct FBonusTypeChance
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ABonusAbstract> BonusClass = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta =( ClampMin = "0", ClampMax = "1" ) )
	float DropChance = 0.2f;
};

UCLASS()
class ARKANOID_API APlayingBoard : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess = true), Category = "Components")
	USceneComponent* SceneRoot = nullptr;
	
	UPROPERTY()
	TArray<UStaticMeshComponent*> PreviewComponents;
	
	UPROPERTY()
	TArray<ABlock*> BlockActors;
	
	void CreatePreviewComponents();
	void ClearPreviewComponents();
	void SpawnBlockActors();
	
	UFUNCTION()
	void OnBlockDestroyed( AActor* DestroyedBlock );
	
	
public:	
	APlayingBoard();

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Settings | Base", meta=(ToolTip = "Cubes blueprint") )
	TSubclassOf<ABlock> BlockClassForSpawn;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Settings | Base", meta=(ToolTip = "Preview mesh") )
	UStaticMesh* PreviewMesh = nullptr;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Settings | Base" )
	FVector BlockScale = FVector(0.5f, 0.5f, 0.5f);
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Settings | Base" )
	int32 GridSizeX = 5;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Settings | Base" )
	int32 GridSizeY = 5;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Settings | Base" )
	int32 SpacingX = 60;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Settings | Base" )
	int32 SpacingY = 60;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Settings | Game", meta =( ClampMin = "0", ClampMax = "1" ) )
	float GameDifficulty = 0.2f;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Settings | Game", meta =( ClampMin = "0", ClampMax = "1" ) )
	float BonusChance = 0.2f;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Settings | Game", meta =( ClampMin = "0", ClampMax = "1" ) )
	TArray<FBonusTypeChance> BonusTypeByChance;
	
	
protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	
	TSubclassOf<ABonusAbstract> GetBonusClass();
	
public:	

	void BonusDestroyCubes( const int32 Amount );
};
