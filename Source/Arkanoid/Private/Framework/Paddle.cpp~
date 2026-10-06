// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/Paddle.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MaterialHLSLTree.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "World/Ball.h"


void APaddle::SpawnBallLives()
{
    UStaticMesh* Mesh = LoadObject<UStaticMesh>( nullptr, TEXT( "/Engine/BasicShapes/Sphere.Sphere" ) );
    UMaterialInterface* Material = LoadObject<UMaterialInterface>( nullptr, TEXT( "/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial" ) );
    
    if( !Mesh || !Material )
        return;

    
     for( auto BallLive : BallLives )
        BallLive->DestroyComponent();
    
    BallLives.Empty();    
        
    for( int8 i = 0; i < Lives - 1; ++i )
    {
        auto NewMeshComponent = NewObject<UStaticMeshComponent>( this, *FString::Printf( TEXT( "Lives %d"), i + 1 )  );
        
        if( !NewMeshComponent )
            continue;
        
        NewMeshComponent->SetStaticMesh( Mesh );
        NewMeshComponent->SetMaterial( 0, Material );
        NewMeshComponent->SetAbsolute( false,false, true );
        NewMeshComponent->SetWorldScale3D( FVector( 0.5f ) );
        NewMeshComponent->SetupAttachment( StaticMesh );
        NewMeshComponent->RegisterComponent();
        
        BallLives.Add( NewMeshComponent );
    }
    
    UpdateBallLivesLocation();
} // SpawnBallLives

void APaddle::UpdateBallLivesLocation()
{
    constexpr float BallSpacing = 30.0f;
    const int8 NumBalls = BallLives.Num();
    const float TotalWidth = ( NumBalls - 1 ) * BallSpacing;
    const float StartOffset = -TotalWidth / 2.0f;

    for( int8 i = 0; i < NumBalls; ++i )
    {
        const float Offset = StartOffset + i * BallSpacing;
        if( IsValid( BallLives[i] ) )
            BallLives[i]->SetRelativeLocation( FVector( -100, Offset, 0.0f ) );
    }
} // UpdateBallLivesLocation

APaddle::APaddle()
{
    PrimaryActorTick.bCanEverTick = false;
    
    BoxCollider = CreateDefaultSubobject<UBoxComponent>( TEXT( " BoxCollider" ) );
    BoxCollider->SetBoxExtent( FVector( 25.0f, 50.0f, 25.0f ) );
    BoxCollider->SetCollisionResponseToAllChannels( ECR_Block );
    SetRootComponent( BoxCollider );
    
    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "StaticMesh" ) );
    StaticMesh->SetupAttachment( BoxCollider );
    
    LeftStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "LeftStaticMesh" ) );
    LeftStaticMesh->SetupAttachment( BoxCollider );
    LeftStaticMesh->AddRelativeLocation( FVector( 0.0f, -50.0f, 0.0f ) );
    LeftStaticMesh->SetAbsolute( false,false, true );
    
    
    RightStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "RightStaticMesh" ) );
    RightStaticMesh->SetupAttachment( BoxCollider );
    RightStaticMesh->AddRelativeLocation( FVector( 0.0f, 50.0f, 0.0f ) );
    RightStaticMesh->SetAbsolute( false,false, true );
    
    Arrow = CreateDefaultSubobject<UArrowComponent>( TEXT( "Arrow" ) );
    Arrow->SetupAttachment( StaticMesh );
    Arrow->AddRelativeLocation( FVector( 150.0f, 0.0f, 0.0f ) );
    Arrow->SetAbsolute( false,false, true );
} // APaddle

void APaddle::OnConstruction( const FTransform& Transform )
{
    Super::OnConstruction( Transform );
    
    SetActorScale3D( DefaultScale );
    BoxCollider->SetBoxExtent( FVector( 25.0f, 50.0f + 20.0f / DefaultScale.Y, 25.0f ) );
    const FVector TmpScale = FVector(GetActorScale().X, GetActorScale().X, GetActorScale().Z);
    LeftStaticMesh->SetWorldScale3D( TmpScale );
    RightStaticMesh->SetWorldScale3D( TmpScale );
} // OnConstruction

void APaddle::BeginPlay()
{
    Super::BeginPlay();
    
    if(APlayerController* PlayerController = Cast<APlayerController>(Controller) )
    {
        if( const auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>( PlayerController->GetLocalPlayer() ) )
            Subsystem->AddMappingContext( DefaultMappingContext, 0);
    }
    
    SpawnBall();
    SpawnBallLives();
} // BeginPlay

void APaddle::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent )
{
    Super::SetupPlayerInputComponent( PlayerInputComponent );

    if( const auto EnhancedInputComponent = Cast<UEnhancedInputComponent>( PlayerInputComponent ) )
    {
        EnhancedInputComponent->BindAction( EscapeAction, ETriggerEvent::Started, this, &APaddle::ExitGame );
        EnhancedInputComponent->BindAction( SpawnBallAction, ETriggerEvent::Started, this, &APaddle::PushBall );
        EnhancedInputComponent->BindAction( MoveAction, ETriggerEvent::Triggered, this, &APaddle::Move );
    }
} // SetupPlayerInputComponent

void APaddle::SetDefaultSize()
{
    SetActorScale3D( DefaultScale );
    BoxCollider->SetBoxExtent( FVector( 25.0f, 50.0f + 20.0f / DefaultScale.Y, 25.0f ) );
} // SetDefaultSize

void APaddle::BonusChangeSize( const float AdditionalSize, const float BonusTime )
{
    if( !AdditionalSize|| !BonusTime  ) 
        return;

    if( GetWorld()->GetTimerManager().IsTimerActive( TimerForBonuses ) )
        return;
    
    FVector TmpScale = GetActorScale3D();
    TmpScale.Y += TmpScale.Y * AdditionalSize;
    SetActorScale3D( TmpScale );
    BoxCollider->SetBoxExtent( FVector( 25.0f, 50.0f + 20.0f / TmpScale.Y, 25.0f ) );
    
    GetWorld()->GetTimerManager().SetTimer( TimerForBonuses, this, &APaddle::SetDefaultSize,BonusTime, false );
} // BonusChangeSize

void APaddle::BonusChangeLife( const int32 Amount )
{
    Lives += Amount;
    SpawnBallLives();
} // BonusChangeLife

void APaddle::BonusChangeBallSpeed( const float Amount )
{
    if( !IsValid( CurrentBall ) )
        return;
    CurrentBall->ChangeSpeed( Amount );
} // BonusChangeBallSpeed

void APaddle::BonusChangeBallPower( const float Amount, const float BonusTime )
{
    if( !IsValid( CurrentBall ) )
        return;
    CurrentBall->ChangePower( Amount, BonusTime );
} // BonusChangeBallPower

void APaddle::BonusSpawnAdditionalBall()
{
    const FVector SpawnLocation = Arrow->GetComponentLocation();
    const FRotator SpawnRotation = Arrow->GetComponentRotation();
    
    GetWorld()->SpawnActor<ABall>( BallClass, SpawnLocation, SpawnRotation );    
} // BonusSpawnAdditionalBall

void APaddle::ExitGame()
{
    UGameplayStatics::OpenLevel( GetWorld(), "Menu", true );    
} // ExitGame

void APaddle::PushBall()
{
    if( !CurrentBall )
        return;
    
    CurrentBall->DetachFromActor( FDetachmentTransformRules::KeepWorldTransform );
    CurrentBall->SetBallState( EState::Moving );
} // PushBall

void APaddle::Move( const FInputActionValue& Value )
{
    const FVector2D AxisVector = Value.Get<FVector2D>();

    if( !Controller )
        return;
    
    const float CurrentSpeed = AxisVector.X * Speed * UGameplayStatics::GetWorldDeltaSeconds( GetWorld() );
    AddActorWorldOffset( FVector(0.0f, CurrentSpeed, 0.0f), true );
} // Move

void APaddle::SpawnBall()
{    
    if( !BallClass || CurrentBall )
        return;
    
    const FVector SpawnLocation = Arrow->GetComponentLocation();
    const FRotator SpawnRotation = Arrow->GetComponentRotation();    
    CurrentBall = GetWorld()->SpawnActor<ABall>( BallClass, SpawnLocation, SpawnRotation );
    
    if( CurrentBall )
    {
        CurrentBall->SetOwner( this );
        CurrentBall->SetBallState( EState::Idle );
        CurrentBall->OnDeathEvent.AddDynamic( this, &APaddle::BallIsDead );
        CurrentBall->AttachToComponent( Arrow, FAttachmentTransformRules::SnapToTargetNotIncludingScale );
    }
} // SpawnBall

void APaddle::BallIsDead()
{
    CurrentBall = nullptr;
    Lives = FMath::Max( Lives - 1,0 );

    if( !Lives )
        return;
    
    SpawnBall();    
    BallLives[Lives - 1]->DestroyComponent();
    BallLives.RemoveAt( Lives - 1 );
    UpdateBallLivesLocation();
} // BallIsDead
