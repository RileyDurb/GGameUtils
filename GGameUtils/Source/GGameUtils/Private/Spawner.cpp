// Copyright (c) 2025 Guardbrawl Games

#include "Spawner.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
	if (mStartWithSpawningOn)
	{
		// Set first spawn to happen after the initial wait time
		FTimerDelegate updateDelegate;
		updateDelegate.BindUFunction(this, "SpawnActor");
		GetWorld()->GetTimerManager().SetTimer(mSpawnerUpdateTimerHandle, updateDelegate, mInitialSpawnWaitTime, false);
	}


}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawner::HandleSpawnedActorDestroyed(AActor* destroyedActor)
{
	// Set the next spawn to happen after waiting for the spawn interval
	FTimerDelegate updateDelegate;
	updateDelegate.BindUFunction(this, "SpawnActor");
	GetWorld()->GetTimerManager().SetTimer(mSpawnerUpdateTimerHandle, updateDelegate, mSpawnInterval, false);
}

void ASpawner::SpawnActor()
{
	FTransform spawnTransform = GetTransform();
	spawnTransform.AddToTranslation(mSpawnOffset);
	FActorSpawnParameters spawnParameters;
	spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	spawnParameters.Owner = this;
	spawnParameters.Instigator = GetInstigator();

	AActor* spawnedActor = GetWorld()->SpawnActor(mActorClassToSpawn, &spawnTransform, spawnParameters);

	currentlySpawnedActor = spawnedActor;
	
	// Subscrite to the destruction of the spawned object, to spawn another
	//FScriptDelegate onSpawnedActorDestroyed;
	//onSpawnedActorDestroyed.BindUFunction(this, "HandleSpawnedActorDestroyed");

	currentlySpawnedActor->OnDestroyed.AddDynamic(this, &ASpawner::HandleSpawnedActorDestroyed);

	OnSpawn.Broadcast();
}

