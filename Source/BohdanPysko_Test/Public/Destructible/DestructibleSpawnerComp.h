// Bohdan Pysko. Pingle Studio test

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DestructibleSpawnerComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOHDANPYSKO_TEST_API UDestructibleSpawnerComp : public UActorComponent
{
	GENERATED_BODY()

public:
	UDestructibleSpawnerComp();

protected:
	virtual void BeginPlay() override;
};
