// Bohdan Pysko. Pingle Studio test

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Destructible.generated.h"

class USphereComponent;
class UNiagaraSystem;

UCLASS()
class BOHDANPYSKO_TEST_API ADestructible : public AActor
{
	GENERATED_BODY()
	
public:
	ADestructible();

protected:
	virtual void BeginPlay() override;

private:
	// This component will ensure that distance between destructible spheres is at least 80 units
	// It uses a separate collision channel
	UPROPERTY(EditDefaultsOnly)
	USphereComponent* MinDistanceImplementation;

	// Actual destructible sphere
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* VisibleSphere;

	// SceneComponent is unnecessary, but I think it is better for the mesh and
	// the collision sphere to have unrelated scaling
	// Does not really need "EditDefaultsOnly"
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* SceneComponent;

	// Reference to the explosion effect
	UPROPERTY(EditDefaultsOnly, Category = "Custom Properties")
	UNiagaraSystem* Effect;

	UFUNCTION()
	void Explode(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
