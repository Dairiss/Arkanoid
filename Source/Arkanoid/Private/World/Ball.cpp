// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Ball.h"
#include "Components/ArrowComponent.h"
#include "Components/AudioComponent.h"

ABall::ABall()
{
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "StaticMesh" ) );
	SetRootComponent( StaticMesh );
	
	ForwardArrow = CreateDefaultSubobject<UArrowComponent>( TEXT( "ForwardArrow" ) );
	ForwardArrow->SetupAttachment( StaticMesh );
	
	AudioComponent = CreateDefaultSubobject<UAudioComponent>( TEXT( "AudioComponent" ) );
	AudioComponent->SetupAttachment( StaticMesh );
	AudioComponent->SetAutoActivate( false );
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset( TEXT( "/Engine/BasicShapes/Sphere.Sphere" ) );
	if( SphereMeshAsset.Succeeded() )	
		StaticMesh->SetStaticMesh( SphereMeshAsset.Object );	
}// ABall

void ABall::OnConstruction( const FTransform& Transform )
{
	Super::OnConstruction( Transform );
	
	SetActorScale3D( FVector( InitParams.Scale ) );
	Power = InitParams.Power;
	Speed = InitParams.Speed;
}// OnConstruction

void ABall::BeginPlay()
{
	Super::BeginPlay();
	
	Direction = GetActorForwardVector().GetSafeNormal();
	SetBallState( EState::Moving );
	if( StaticMesh )
		DefaultMaterial = StaticMesh->GetMaterial( 0 );
	
	UpdateBallMaterial();
}// BeginPlay

void ABall::Tick( float DeltaTime )
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
}// Tick

void ABall::Destroyed()
{
	OnDeathEvent.Broadcast();
	
	Super::Destroyed();
}// Destroyed

void ABall::Move( const float DeltaTime )
{
	const FVector Offset = Direction * Speed * DeltaTime;
	FHitResult HitResult;
	AddActorWorldOffset( Offset,true, &HitResult );
	
	if( HitResult.bBlockingHit )
	{
		AudioComponent->Play();
		
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
}// Move

void ABall::ResetBallPower()
{
	Power = InitParams.Power;	
	UpdateBallMaterial();
}// ResetBallPower

void ABall::UpdateBallMaterial()
{
	if( !StaticMesh )
		return;

	if( Power > 1 )
	{
		if( PowerMaterial )
			StaticMesh->SetMaterial( 0, PowerMaterial );
	}
	else
		StaticMesh->SetMaterial( 0, DefaultMaterial );
}// UpdateBallMaterial

void ABall::ChangeSpeed( const float Amount )
{
	if( Amount < 0 )	
		Speed = FMath::Min( Speed - Speed * Amount, InitParams.Speed );	
	else	
		Speed = FMath::Max( Speed + Speed * Amount, InitParams.MaxSpeed );	
}// ChangeSpeed

void ABall::ChangePower( const int32 Amount, const float BonusTime )
{
	if( Amount == 0 || BonusTime <= 0 )
		return;

	if( !GetWorld()->GetTimerManager().IsTimerActive( TimerBallPower ) )
	{
		Power = FMath::Max( Power + Amount, 1 );
		UpdateBallMaterial();
	}
	
	GetWorld()->GetTimerManager().SetTimer( TimerBallPower, this, 
		&ABall::ResetBallPower, BonusTime, true );
	
	
}// ChangeBallPower

void ABall::SetBallState( const EState NewState )
{
	State = NewState;
}// SetBallState

