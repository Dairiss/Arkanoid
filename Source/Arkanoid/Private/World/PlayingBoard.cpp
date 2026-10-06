// Fill out your copyright notice in the Description page of Project Settings.


#include "World/PlayingBoard.h"

#include "Bonuses/BonusAbstract.h"
#include "DSP/MidiNoteQuantizer.h"
#include "Kismet/KismetMathLibrary.h"
#include "World/Block.h"

void APlayingBoard::CreatePreviewComponents()
{
	if( GridSizeX <=0 || GridSizeY <= 0 )
	{
		UE_LOG( LogTemp, Error, TEXT( "CreatePreviewComponents: GridSize must be greater than 0" ) );	
		return;
	}
	
	const float BlockWidth = BlockScale.X * 100.0f;
	const float BlockHeight = BlockScale.Y * 100.0f;
	const float BlockDepth = BlockScale.Z * 100.0f;
	
	const float TotalWidth = GridSizeX * BlockWidth + ( GridSizeX -1 ) * SpacingX;
	const float TotalHeigh = GridSizeY * BlockHeight + ( GridSizeY -1 ) * SpacingY;
	
	const FVector CenterOffset = FVector(( TotalWidth - BlockWidth ) / 2, ( TotalHeigh - BlockHeight ) / 2, 0.0f );
	const FTransform ActorTransform = GetActorTransform();

	for( int32 x = 0; x < GridSizeX; ++x )
	{
		for( int y = 0; y < GridSizeY; ++y )
		{
			if( !PreviewMesh )
				continue;	
			
			const float XOffset = x * ( BlockWidth + SpacingX );
			const float YOffset = y * ( BlockHeight + SpacingY );
			const FVector PreviewLocation = FVector(XOffset, YOffset, 0.0f) - CenterOffset;
			const FVector WorldPreviewLocation = ActorTransform.TransformPosition( PreviewLocation );
			
			FCollisionQueryParams CollisionParams;
			CollisionParams.AddIgnoredActor( this );
			
			const FVector BoxExtents = FVector(BlockWidth * 0.5f, BlockHeight * 0.5f, BlockDepth * 0.5f);
			
			const bool bIsBlocked = GetWorld()->OverlapBlockingTestByChannel( WorldPreviewLocation, 
				ActorTransform.GetRotation(), ECC_Visibility, FCollisionShape::MakeBox( BoxExtents ),
				CollisionParams );
			
			if( bIsBlocked )
			{
				DrawDebugBox( GetWorld(), WorldPreviewLocation, BoxExtents, ActorTransform.GetRotation(), 
					FColor::White, false, 10.0f );
				continue;
			}
			UStaticMeshComponent* PreviewMeshComponent = NewObject<UStaticMeshComponent>(this );
			PreviewMeshComponent->SetStaticMesh( PreviewMesh );
			PreviewMeshComponent->AttachToComponent( GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform );
			PreviewMeshComponent->SetRelativeScale3D( BlockScale );
			PreviewMeshComponent->SetRelativeLocation( PreviewLocation );
			PreviewMeshComponent->RegisterComponent();
			PreviewComponents.Add( PreviewMeshComponent );
		}
	}
}// CreatePreviewComponents

void APlayingBoard::ClearPreviewComponents()
{
	for( UStaticMeshComponent* PreviewComponent : PreviewComponents )
	{
		if( PreviewComponent )
		{
			PreviewComponent->DestroyComponent();
		}
	}
	PreviewComponents.Empty();
}// ClearPreviewComponents

void APlayingBoard::SpawnBlockActors()
{
	for( UStaticMeshComponent* PreviewComponent : PreviewComponents )
	{
		if( PreviewComponent )
		{
			const FTransform SpawnTransform = PreviewComponent->GetComponentTransform();
			if( auto CurrentBlock = GetWorld()->SpawnActor<ABlock>( BlockClassForSpawn, SpawnTransform ) )
			{
				const int32 Life = UKismetMathLibrary::RandomBoolWithWeight( GameDifficulty ) ? 2 : 1;
				
				const auto BonusClass = UKismetMathLibrary::RandomBoolWithWeight( BonusChance ) ? GetBonusClass() : nullptr;
				
				CurrentBlock->Init( BlockScale, Life, BonusClass );
				CurrentBlock->AttachToComponent( SceneRoot, FAttachmentTransformRules::KeepWorldTransform );
				CurrentBlock->OnDestroyed.AddDynamic( this, &APlayingBoard::OnBlockDestroyed );
				
				BlockActors.Add( CurrentBlock );
			}
		}
	}
} // SpawnBlockActors

void APlayingBoard::OnBlockDestroyed( AActor* DestroyedBlock )
{
	BlockActors.Remove( Cast<ABlock>( DestroyedBlock ) );
}// OnBlockDestroyed

APlayingBoard::APlayingBoard()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SceneRoot = CreateDefaultSubobject<USceneComponent>( TEXT("SceneRoot") );
	SetRootComponent( SceneRoot );
}// APlayingBoard

void APlayingBoard::OnConstruction( const FTransform& Transform )
{
	Super::OnConstruction( Transform );
	
	ClearPreviewComponents();
	CreatePreviewComponents();
}// OnConstruction

void APlayingBoard::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnBlockActors();
	ClearPreviewComponents();
}// BeginPlay

TSubclassOf<ABonusAbstract> APlayingBoard::GetBonusClass()
{
	if( BonusTypeByChance.Num() == 0 || !BonusTypeByChance[0].BonusClass )
		return nullptr;
	
	int32 TotalWeight = 0;
	for( const auto& CurrentBonus : BonusTypeByChance )
		TotalWeight += CurrentBonus.DropChance * 100;
	
	int32 RandomWeight = FMath::RandHelper( TotalWeight );
	
	for( const auto& CurrentBonus : BonusTypeByChance )
	{
		if( RandomWeight > CurrentBonus.DropChance * 100 )
			RandomWeight -= CurrentBonus.DropChance * 100;		
		else
			return CurrentBonus.BonusClass;		
	}
	
	return nullptr;
}// GetBonusClass

void APlayingBoard::BonusDestroyCubes( const int32 Amount )
{
	if( Amount <=0 )	
		return;
	
	const int32 NumToDestroy = FMath::Min(Amount, BlockActors.Num() );

	for( int32 i = 0; i < NumToDestroy; ++i )
	{
		const int32 RandomIndex = FMath::RandHelper( BlockActors.Num() );
		if(BlockActors.IsValidIndex( RandomIndex ) )		
			BlockActors[ RandomIndex ]->Destroy();		
	}	
} // BonusDestroyCubes
