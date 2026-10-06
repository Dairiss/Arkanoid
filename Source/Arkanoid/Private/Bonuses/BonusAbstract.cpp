// Fill out your copyright notice in the Description page of Project Settings.


#include "Bonuses/BonusAbstract.h"

#include "Framework/Paddle.h"


ABonusAbstract::ABonusAbstract()
{
    PrimaryActorTick.bCanEverTick = true;
    
    BonusMesh =CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "BonusMesh" ) );
    SetRootComponent( BonusMesh );
    
    BonusMesh->SetCollisionEnabled( ECollisionEnabled::QueryOnly );
    BonusMesh->SetCollisionObjectType( ECC_WorldDynamic);
    BonusMesh->SetCollisionResponseToAllChannels( ECR_Overlap );
    
    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset( TEXT( "/Engine/BasicShapes/Cube.Cube"));
    
    if (MeshAsset.Succeeded())
        BonusMesh->SetStaticMesh( MeshAsset.Object );
}// ABonusAbstract

void ABonusAbstract::BeginPlay()
{
    Super::BeginPlay();
    
    Direction = Direction.GetSafeNormal();        
}// BeginPlay

void ABonusAbstract::Move( const float DeltaTime )
{
    const FVector Offset = Direction * Speed * DeltaTime;
    AddActorWorldOffset( Offset );
}// Move

void ABonusAbstract::BonusAction( APaddle* Paddle )
{
    Destroy();
}// BonusAction

void ABonusAbstract::Tick( float DeltaTime )
{
    Super::Tick( DeltaTime );
    
    Move( DeltaTime );
}// Tick

void ABonusAbstract::NotifyActorBeginOverlap( AActor* OtherActor )
{
    Super::NotifyActorBeginOverlap( OtherActor );
    
    if( !IsValid( OtherActor ) )
        return;

    if( auto Paddle = Cast<APaddle>( OtherActor ) )
        BonusAction( Paddle );
} // NotifyActorBeginOverlap


void ABonusAbstract::InitScale( const FVector NewScale )
{
    SetActorScale3D( NewScale );
}// InitScale
