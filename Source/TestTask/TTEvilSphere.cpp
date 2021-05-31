// Fill out your copyright notice in the Description page of Project Settings.


#include "TTEvilSphere.h"
#include "TestTaskProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

ATTEvilSphere::ATTEvilSphere()
{
	PrimaryActorTick.bCanEverTick = false;

	EvilSphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	EvilSphereCollision->SetupAttachment(GetRootComponent());
	EvilSphereCollision->InitSphereRadius(CurrentCollisionRadius);

	EvilSphereCheckSpace = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCheckSpace"));
	EvilSphereCollision->SetupAttachment(GetRootComponent());
	EvilSphereCollision->InitSphereRadius(1500.f);

	EvilSphereBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereBody"));
	EvilSphereBody->SetupAttachment(EvilSphereCollision);
	
}

void ATTEvilSphere::BeginPlay()
{
	Super::BeginPlay();

	if (EvilSphereCollision && EvilSphereCheckSpace)
	{
		EvilSphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ATTEvilSphere::OnSphereProjectileOverlap);
		EvilSphereCheckSpace->OnComponentBeginOverlap.AddDynamic(this, &ATTEvilSphere::OnEvilSphereOverlap);
	}	
}

void ATTEvilSphere::OnSphereProjectileOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		ATestTaskProjectile* Projectile = Cast<ATestTaskProjectile>(OtherActor);
		if (Projectile)
		{
			EvilSphereDefeated();
		}		
	}
}

void ATTEvilSphere::OnEvilSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		ATTEvilSphere* EvilBro = Cast<ATTEvilSphere>(OtherActor);
		if (EvilBro)
		{
			
			FVector EvilBroPosition = EvilBro->GetActorLocation();
			FVector CurrentSpherePosition = GetActorLocation();
			float Distance = (EvilBroPosition - CurrentSpherePosition).Size();

			if (Distance < 160.f)
			{
				CurrentSpherePosition.X += 160.f;
				SetActorLocation(CurrentSpherePosition);
			}
		}
	}
	else
	{
		ACharacter* Player = Cast<ACharacter>(OtherActor);
		if (Player)
		{
			FVector EvilBroPosition = Player->GetActorLocation();
			FVector CurrentSpherePosition = GetActorLocation();
			float Distance = (EvilBroPosition - CurrentSpherePosition).Size();

			if (Distance < 160.f)
			{
				CurrentSpherePosition.X += 160.f;
				SetActorLocation(CurrentSpherePosition);
			}
		}
	}
}

void ATTEvilSphere::EvilSphereDefeated()
{
	OnSphereDestroyed.Broadcast();
	
	if (DestroyParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestroyParticle, GetActorLocation());
	}
	
	Destroy();
}

