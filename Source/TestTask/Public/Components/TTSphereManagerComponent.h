// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TestTask/TTEvilSphere.h"

#include "TTSphereManagerComponent.generated.h"

class ATTEvilSphere;
class UBoxComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTTASK_API UTTSphereManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTTSphereManagerComponent();

	UPROPERTY(EditAnywhere, Category = "Spawn Params")
	int32 InitialSphereNumber = 15;

	UPROPERTY(EditAnywhere, Category = "Spawn Params")
	float SpawnDistance = 2000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn Params")
	TSubclassOf<ATTEvilSphere> EvilSphereClass;

	UPROPERTY(VisibleAnywhere, Category = "Spawning Box")
	UBoxComponent* SpawningVolume;

private:
	int32 WaveCount = 0;

	int32 CurrentEvilSpheresOnLevel = 0;	

protected:
	virtual void BeginPlay() override;
	
	FVector CalculateSphereRandomLocation();

	void SphereDefeated();

public:
	void SpawnSpheres();

};
