// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "TTEvilSphere.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnSphereDestroyed);

class UParticleSystemComponent;
class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class TESTTASK_API ATTEvilSphere : public AActor
{
	GENERATED_BODY()
	
public:
	ATTEvilSphere();

	// Sphere body
	UPROPERTY(VisibleAnywhere, Category = "Sphere Body")
	USphereComponent* EvilSphereCollision;

	UPROPERTY(VisibleAnywhere, Category = "Sphere Body")
	USphereComponent* EvilSphereCheckSpace;

	UPROPERTY(VisibleAnywhere, Category = "Sphere Body")
	UStaticMeshComponent* EvilSphereBody;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sphere Params")
	float CurrentCollisionRadius = 300.f;

	UPROPERTY(EditAnywhere, Category ="Particle")
	UParticleSystem* DestroyParticle;

	FOnSphereDestroyed OnSphereDestroyed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSphereProjectileOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
	void OnEvilSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	void EvilSphereDefeated();
};
