// Copyright (c) 2025 Guardbrawl Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSpawnDelegate);

UCLASS(Blueprintable)
class GGAMEUTILS_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

	// Helper functions
	UFUNCTION(BlueprintCallable)
	void SpawnActor();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Getters

protected:
	// Helper functions
	UFUNCTION(BlueprintCallable)
	void HandleSpawnedActorDestroyed(AActor* DestroyedActor);

	// Blueprint Editable Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SpawnBehaviour")
	TSubclassOf<AActor> mActorClassToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnBehaviour")
	float mInitialSpawnWaitTime = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnBehaviour")
	float mSpawnInterval = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnBehaviour")
	bool mStartWithSpawningOn = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnBehaviour")
	FVector mSpawnOffset = FVector();


	// Public for event binding
	UPROPERTY(BlueprintAssignable, BlueprintReadWrite)
	FOnSpawnDelegate OnSpawn;

private:


	// Private Variables

	AActor* currentlySpawnedActor;

	FTimerHandle mSpawnerUpdateTimerHandle;
};
