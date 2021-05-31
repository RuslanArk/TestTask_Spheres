// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/TTSphereManagerComponent.h"

#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"


UTTSphereManagerComponent::UTTSphereManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	SpawningVolume = CreateDefaultSubobject<UBoxComponent>("Spawning Volume");
}

void UTTSphereManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	
	check(EvilSphereClass);
	check(SpawningVolume);

	SpawningVolume->SetBoxExtent(FVector(SpawnDistance, SpawnDistance, 300.f));
	
}

void UTTSphereManagerComponent::SpawnSpheres()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!GetWorld() || !Character) return;

	// Multiplies spawn params every wave
	WaveCount++;
	if (WaveCount > 1)
	{
		InitialSphereNumber += InitialSphereNumber / 10;
		SpawnDistance += SpawnDistance / 20;
		SpawningVolume->SetBoxExtent(FVector(SpawnDistance, SpawnDistance, 300.f));
	}
	
	SpawningVolume->SetWorldLocation(Character->GetActorLocation());
	
	for (int32 i = 0; i < InitialSphereNumber; i++)
	{
		const FTransform SpawnTransform = FTransform(FRotator::ZeroRotator, CalculateSphereRandomLocation());
		auto EvilSphere = GetWorld()->SpawnActor<ATTEvilSphere>(EvilSphereClass, SpawnTransform);
		EvilSphere->OnSphereDestroyed.AddUObject(this, &UTTSphereManagerComponent::SphereDefeated);
		CurrentEvilSpheresOnLevel++;
	}
}

// Randomize spawn position
FVector UTTSphereManagerComponent::CalculateSphereRandomLocation()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!GetWorld() || !Character) return FVector::ZeroVector;

	FVector Extent = SpawningVolume->GetScaledBoxExtent();
	FVector Origin = Character->GetActorLocation();

	FVector NewLocation = UKismetMathLibrary::RandomPointInBoundingBox(Origin, Extent);
	NewLocation.Z = FMath::RandRange(300.f, 700.f);
	
	return NewLocation;
}

void UTTSphereManagerComponent::SphereDefeated()
{
	CurrentEvilSpheresOnLevel--;
	if (CurrentEvilSpheresOnLevel < 5)
	{
		SpawnSpheres();
	}
}

