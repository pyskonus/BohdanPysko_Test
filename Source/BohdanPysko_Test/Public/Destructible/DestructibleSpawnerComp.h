// Bohdan Pysko. Pingle Studio test

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DestructibleSpawnerComp.generated.h"

class ADestructible;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOHDANPYSKO_TEST_API UDestructibleSpawnerComp : public UActorComponent
{
	GENERATED_BODY()

public:
	UDestructibleSpawnerComp();

protected:
	virtual void BeginPlay() override;

private:
	void InitWave();

	void SpawnOneSphere();

	void EndWave();


	UPROPERTY(EditDefaultsOnly, Category = "Custom Properties", meta=(ClampMin="1"))
	TSubclassOf<ADestructible> DestructibleBPClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Custom Properties", meta=(ClampMin="1"))
	int AmountToPass = 10;

	UPROPERTY(EditDefaultsOnly, Category = "Custom Properties", meta=(ClampMin="100"))
	int PassRadius = 1500;
	
	UPROPERTY(EditDefaultsOnly, Category = "Custom Properties", meta=(ClampMin="1"))
	int InitialSpheresAmount = 15;

	UPROPERTY(EditDefaultsOnly, Category = "Custom Properties", meta=(ClampMin="100"))
	int InitialRadius = 2000;

	UPROPERTY(EditDefaultsOnly, Category = "Custom Properties", meta=(ClampMin="1"))
	float AmountMultiplier = 1.1f;

	UPROPERTY(EditDefaultsOnly, Category = "Custom Properties", meta=(ClampMin="1"))
	float RadiusMultiplier = 1.05f;

	UPROPERTY(EditDefaultsOnly, Category = "Custom Properties")
	float VerticalOffsetZ = 500.f;

	UPROPERTY(EditDefaultsOnly, Category = "Custom Properties")
	float ScaleStep = 0.95f;

	UPROPERTY(EditDefaultsOnly, Category = "Custom Properties")
	float MinScale = 0.5f;
	

	int WaveIndex = 0;
	
	int AmountToSpawn = InitialSpheresAmount;	/// InitialSpheresAmount * pow(AmountMultiplier, WaveIndex); WaveIndex starts from 0
	
	int CurrentRadius = InitialRadius;	/// InitialRadius * pow(RadiusMultiplier, WaveIndex)

	int SpawnedInThisWave = 0;

	int SpawnedWithinPassRadius = 0;	/// Must reach AmountToPass during spawning stage

	int DestroyedWithinPassRadius = 0;	/// Must reach AmountToPass during playing stage

	int Score = 0;						/// Total spheres destroyed

	FVector SpawnPoint;
	
	float Scale = 1;				/// Related to additional task 3
	

public:
	void SphereDestroyed(bool Close);
};
