// Fill out your copyright notice in the Description page of Project Settings.


#include "WIMPProjectile.h"
#include "WIMPCharacter.h"

// Sets default values
AWIMPProjectile::AWIMPProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSceneComponent"));

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->InitSphereRadius(20.0f);
	RootComponent = CollisionComponent;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 1000.0f;
	ProjectileMovementComponent->MaxSpeed = 1000.0f;
	ProjectileMovementComponent->Bounciness = 0.0f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

	PS_Shoot = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PS_Shoot"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem>particleShoot(TEXT("'/Game/StylizedProjectiles/Particles/Projectile_01/P_Projectile_01.P_Projectile_01'"));
	if (particleShoot.Succeeded())
	{
		PS_Shoot->SetTemplate(particleShoot.Object);
	}
	PS_Shoot->SetupAttachment(RootComponent);
	PS_Shoot->SetWorldScale3D(FVector(2.f, 2.f, 2.f));

	PS_Explosion = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PS_Explosion"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem>particle(TEXT("'/Game/StylizedProjectiles/Particles/Projectile_01/P_Projectile_01_Hit.P_Projectile_01_Hit'"));
	if (particle.Succeeded())
	{
		PS_Explosion->SetTemplate(particle.Object);
	}
	PS_Explosion->bAutoActivate = false;
	PS_Explosion->SetupAttachment(RootComponent);
	PS_Explosion->SetWorldScale3D(FVector(2.f, 2.f, 2.f));

	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void AWIMPProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AWIMPProjectile::OnBeginOverlap);
}

void AWIMPProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AWIMPCharacter* character = Cast<AWIMPCharacter>(OtherActor);
	if (character->IsValidLowLevel())
	{
		PS_Explosion->Activate();
		ProjectileMovementComponent->Velocity = FVector(0.f, 0.f, 0.f);
		GetWorldTimerManager().SetTimer(ExplosionHandle, this, &AWIMPProjectile::ExplosionProjectile, 1.f, false);
		character->DestroyTimelineComponent->Play();
	}
}

void AWIMPProjectile::ExplosionProjectile()
{
	Destroy();
}



// Called every frame
void AWIMPProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

