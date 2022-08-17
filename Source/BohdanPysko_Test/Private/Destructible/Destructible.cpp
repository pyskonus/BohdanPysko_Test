// Bohdan Pysko. Pingle Studio test


#include "Destructible/Destructible.h"
#include "Components/SphereComponent.h"
#include "NiagaraFunctionLibrary.h"

#include "BohdanPysko_Test/BohdanPysko_TestProjectile.h"

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
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Explode callback"));
	if (Cast<ABohdanPysko_TestProjectile>(OtherActor))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Entered If"));
		/// Play explosion VFX
		if (ensure(Effect))
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, Hit.ImpactPoint);
		/// Play explosion sound
		
		/// Disappear
		Destroy();
	}
}
