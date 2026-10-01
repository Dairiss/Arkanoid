// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Ball.h"
#include "Components/ArrowComponent.h"

// Sets default values
ABall::ABall()
{
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "StaticMesh" ) );
	SetRootComponent( StaticMesh );
	ForwardArrow = CreateDefaultSubobject<UArrowComponent>( TEXT( "ForwardArrow" ) );
	ForwardArrow->SetupAttachment( StaticMesh );
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset( TEXT( "/Engine/BasicShapes/Sphere.Sphere" ) );
	if( SphereMeshAsset.Succeeded() )
	{
		StaticMesh->SetStaticMesh( SphereMeshAsset.Object );
	}
}

void ABall::OnConstruction( const FTransform& Transform )
{
	Super::OnConstruction( Transform );
	
	SetActorScale3D( FVector( InitParams.Scale ) );
	Power = InitParams.Power;
	Speed = InitParams.Speed;
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	
	Direction = GetActorForwardVector().GetSafeNormal();
	SetBallState( EState::Moving );
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	switch( State )
	{
		case EState::Idle:
			break;
		case EState::Moving:
			{
				Move(DeltaTime);
				break;
			}
		default:
			{
				UE_LOG(LogTemp,Warning,TEXT("Wrong EState"));
				break;
			}
	}	
}

void ABall::Move( const float DeltaTime )
{
	const FVector Offset = Direction * Speed * DeltaTime;
	FHitResult HitResult;
	AddActorWorldOffset( Offset,true, &HitResult );
	
	if( HitResult.bBlockingHit )
	{
		Direction = Direction - 2 * ( FVector::DotProduct( Direction, HitResult.Normal ) ) * HitResult.Normal;
		Direction.Z = 0.0f;
		Direction = Direction.GetSafeNormal();
		if( Speed < InitParams.MaxSpeed )
		{
			Speed += InitParams.Speed * 0.1f;
			Speed = FMath::Min( Speed, InitParams.MaxSpeed );
		}
		UE_LOG( LogTemp, Warning, TEXT("Ball name %s, speed = %f"), *GetName(), Speed );
	}
}

void ABall::SetBallState( const EState NewState )
{
	State = NewState;
}

