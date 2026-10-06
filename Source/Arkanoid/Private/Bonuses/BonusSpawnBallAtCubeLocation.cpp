// Fill out your copyright notice in the Description page of Project Settings.


#include "Bonuses/BonusSpawnBallAtCubeLocation.h"
#include "World/Ball.h"


ABonusSpawnBallAtCubeLocation::ABonusSpawnBallAtCubeLocation()
{
}

void ABonusSpawnBallAtCubeLocation::BeginPlay()
{
    Super::BeginPlay();
    
    GetWorld()->SpawnActor<ABall>( BallClass, GetActorLocation(), GetActorRotation() );
    Destroy();
} //BeginPlay