// Bohdan Pysko. Pingle Studio test


#include "Destructible/DestructibleSpawnerComp.h"

#include "BohdanPysko_Test/BohdanPysko_TestHUD.h"
#include "Kismet/GameplayStatics.h"

#include "Destructible/Destructible.h"


DEFINE_LOG_CATEGORY_STATIC(LogSpawner, All, All);

UDestructibleSpawnerComp::UDestructibleSpawnerComp()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UDestructibleSpawnerComp::BeginPlay()
{
	Super::BeginPlay();

	/// These 2 vars will not reflect blueprint changes during 1st wave if not reassigned here
	AmountToSpawn = InitialSpheresAmount;
	CurrentRadius = InitialRadius;
	
	/// Init first spawn point
	SpawnPoint = GetOwner()->GetActorLocation();

	InitWave();
}

void UDestructibleSpawnerComp::InitWave()
{
	// if wrong parameters given, log a warning
	if (AmountToPass > AmountToSpawn)
		UE_LOG(LogSpawner, Warning, TEXT("AmountToPass > AmountToSpawn"));
	
	for (int i = 0; i < AmountToSpawn; ++i)
	{
		SpawnOneSphere();

		/// Update scale
		const float NewScale = Scale * ScaleStep;
		if (NewScale >= MinScale)
			Scale = NewScale;
	}
}


void UDestructibleSpawnerComp::SpawnOneSphere()
{
	// find random location in polar coordinates, then switch to cartesian and apply offset
	float Radius = 0;
	float Angle = 0;
	float X = 0;
	float Y = 0;
	bool Close = false;		/// if this sphere spawns within PassRadius
	ADestructible* SpawnedSphere;
	
	if (AmountToPass - SpawnedWithinPassRadius == AmountToSpawn - SpawnedInThisWave)
	{	// must spawn within pass radius or there will be too few spheres in it
		Radius = FMath::RandRange(0, PassRadius);
	}
	else if (AmountToPass - SpawnedWithinPassRadius > AmountToSpawn - SpawnedInThisWave)
	{	// should never be here, something wrong happened
		UE_LOG(LogSpawner, Warning, TEXT("Cannot spawn sufficient spheres within pass radius"));
	}
	else
	{	// can still spawn anywhere within CurrentRadius
		Radius = FMath::RandRange(0, CurrentRadius);
	}
	
	if (Radius <= PassRadius)
	{
		SpawnedWithinPassRadius++;
		Close = true;
	}

	Angle = FMath::RandRange(0.f, 2*PI);
	
	FMath::PolarToCartesian(Radius, Angle, X, Y);

	/// SPAWN
	/// Utilize collision sphere to implement min distance
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	/// Offset accorrding to SpawnPoint
	FVector Location = SpawnPoint;
	Location += FVector(X, Y, 0);
	/// Set Z coordinate
	Location.Z = VerticalOffsetZ;
	/// Spawn
	UWorld* World = GetWorld();
	if (/*ensure(World) && */ensure(DestructibleBPClass))
	{
		SpawnedSphere = World->SpawnActor<ADestructible>(DestructibleBPClass, FTransform{FRotator::ZeroRotator, Location}, SpawnParameters);
		
		if (ensure(SpawnedSphere))
		{
			SpawnedSphere->Close = Close;	/// Mark this sphere as spawned within PassRadius
			SpawnedSphere->SetVisualScale(Scale);
			/// Not setting the scale during spawn because it would interfere with collision sphere
		}
	}

	SpawnedInThisWave++;
}


void UDestructibleSpawnerComp::EndWave()
{
	SpawnPoint = GetOwner()->GetActorLocation();

	/// Destroy remaining spheres
	TArray<AActor*> RemainingSpheres;
	UGameplayStatics::GetAllActorsOfClass(GetOwner(), DestructibleBPClass, RemainingSpheres);
	for (AActor* Sphere: RemainingSpheres)
		Sphere->Destroy();

	/// refresh variables
	WaveIndex++;
	AmountToSpawn = FMath::RoundToInt(AmountToSpawn * AmountMultiplier);
	CurrentRadius = FMath::RoundToInt(CurrentRadius * RadiusMultiplier);
	SpawnedInThisWave = 0;
	SpawnedWithinPassRadius = 0;
	DestroyedWithinPassRadius = 0;

	/// Notify the widget
	const APlayerController* PC = UGameplayStatics::GetPlayerController(this,0);
	if (ensure(PC))
	{
		ABohdanPysko_TestHUD* BohdanPysko_TestHUD = Cast<ABohdanPysko_TestHUD>(PC->GetHUD());
		if (ensure(BohdanPysko_TestHUD))
			BohdanPysko_TestHUD->UpdateWaveIndex(WaveIndex);
	}
	
	InitWave();		/// start the next wave
}

void UDestructibleSpawnerComp::SphereDestroyed(bool Close)
{
	Score++;

	/// Notify the widget
	const APlayerController* PC = UGameplayStatics::GetPlayerController(this,0);
	if (ensure(PC))
	{
		ABohdanPysko_TestHUD* BohdanPysko_TestHUD = Cast<ABohdanPysko_TestHUD>(PC->GetHUD());
		if (ensure(BohdanPysko_TestHUD))
			BohdanPysko_TestHUD->UpdateScore(Score);
	}
	
	if (Close)
		DestroyedWithinPassRadius++;
	if (DestroyedWithinPassRadius >= AmountToPass)	/// actually == would be more appropriate
		EndWave();
}

