// Bohdan Pysko. Pingle Studio test


#include "Destructible/Destructible.h"
#include "Components/SphereComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "BohdanPysko_Test/BohdanPysko_TestCharacter.h"
#include "Sound/SoundCue.h"

#include "BohdanPysko_Test/BohdanPysko_TestProjectile.h"
#include "Kismet/GameplayStatics.h"

ADestructible::ADestructible()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
	
	VisibleSphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleSphere"));
	VisibleSphere->SetupAttachment(GetRootComponent());

	MinDistanceImplementation = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionMinDistanceImplementation"));
	MinDistanceImplementation->SetSphereRadius(40.f);	// 80/2. Can be edited in BP
	MinDistanceImplementation->SetupAttachment(GetRootComponent());

	/// Start exploding sequence when hit
	VisibleSphere->OnComponentHit.AddDynamic(this, &ADestructible::Explode);
}

void ADestructible::BeginPlay()
{
	Super::BeginPlay();
}

void ADestructible::Explode(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	/// Test if was hit by a projectile
	if (Cast<ABohdanPysko_TestProjectile>(OtherActor))
	{
		/// Play explosion VFX
		if (ensure(Effect))
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, Hit.ImpactPoint);

		/// Play explosion sound
		if (ensure(ExplosionCue))
			UGameplayStatics::PlaySoundAtLocation(this, ExplosionCue, GetActorLocation());

		/// Notify the spawner
		TArray<AActor*> Characters;
		ABohdanPysko_TestCharacter* Character = nullptr;
		
		UGameplayStatics::GetAllActorsOfClass(this, ABohdanPysko_TestCharacter::StaticClass(), Characters);
		if (ensure(Characters.Num()>0))
		{
			Character = Cast<ABohdanPysko_TestCharacter>(Characters[0]);
			Character->NotifySpawnerComp(Close);
		}
		
		/// Disappear
		Destroy();
	}
}


void ADestructible::SetVisualScale(const float Scale)
{
	VisibleSphere->SetRelativeScale3D(VisibleSphere->GetRelativeScale3D() * Scale);
}
