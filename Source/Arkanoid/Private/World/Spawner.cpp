// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Spawner.h"
#include "Components/ArrowComponent.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot =CreateDefaultSubobject<USceneComponent>( TEXT("SceneRoot") );
	SetRootComponent( SceneRoot );
	
	ForwardArrow = CreateDefaultSubobject<UArrowComponent>( TEXT("ForwardArrow") );
	ForwardArrow->SetupAttachment( SceneRoot );
	ForwardArrow->SetAbsolute(false,false,true);
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnActor();
}

void ASpawner::SpawnActor()
{
	if (SpawnedActor)
	{
		if(auto world = GetWorld())
		{
			world->SpawnActor<AActor>( SpawnedActor, ForwardArrow->GetComponentLocation(), ForwardArrow->GetComponentRotation() );
		}
	}
}
