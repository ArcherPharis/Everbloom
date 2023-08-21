// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseProjectile.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "EBAbilitySystemComponent.h"
// Sets default values
ABaseProjectile::ABaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereDetection = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Detection"));
	SetRootComponent(SphereDetection);
	ProjectileParticle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Particle Component"));
	ProjectileParticle->SetupAttachment(SphereDetection);
	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
    

}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
    SphereDetection->OnComponentBeginOverlap.AddDynamic(this, &ABaseProjectile::OnImpact);
	
}

// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseProjectile::SetHomingTarget(AActor* PotentialTarget, TSubclassOf<class UGameplayEffect> GPE)
{
    EffectToApply = GPE;
    if (PotentialTarget)
    {
        // Set the ProjectileMovementComponent to be a homing projectile
        MovementComp->HomingTargetComponent = PotentialTarget->GetRootComponent();
        MovementComp->bIsHomingProjectile = true;
    }
    else
    {
        FVector StartLocation = GetOwner()->GetActorLocation();
        FVector EndLocation = StartLocation + GetOwner()->GetActorForwardVector() * 5000;
        FCollisionShape CapsuleShape = FCollisionShape::MakeCapsule(3000, 3000);
        FHitResult HitResult;
        bool bHitSomething = GetWorld()->SweepSingleByChannel(HitResult, StartLocation, EndLocation, FQuat::Identity, ECC_GameTraceChannel3, CapsuleShape);



        if (bHitSomething)
        {
            AActor* HitActor = HitResult.GetActor();
            if (HitActor && HitActor->IsValidLowLevel() && HitActor != GetOwner())
            {
                MovementComp->HomingTargetComponent = HitActor->GetRootComponent();
                MovementComp->bIsHomingProjectile = true;
                return;
            }
        }

        MovementComp->HomingTargetComponent = nullptr;
        MovementComp->bIsHomingProjectile = false;
    }
}

void ABaseProjectile::SetProjectileVelocity(FVector CameraLocation, TSubclassOf<class UGameplayEffect> GPE)
{
    EffectToApply = GPE;
    MovementComp->Velocity = CameraLocation * MovementComp->InitialSpeed;

}
void ABaseProjectile::SetCaster(AActor* Caster)
{
    SetOwner(Caster);
}
//make the caster immune.

void ABaseProjectile::OnImpact(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor != GetOwner())
    {
        UE_LOG(LogTemp, Warning, TEXT("Contact made"));
        UEBAbilitySystemComponent* ASC = OtherActor->FindComponentByClass<UEBAbilitySystemComponent>();
        if (ASC && EffectToApply)
        {
            FGameplayEffectSpecHandle specHan = ASC->MakeOutgoingSpec(EffectToApply, -1, ASC->MakeEffectContext());
            ASC->ApplyGameplayEffectSpecToSelf(*specHan.Data.Get());
            if (!bIsPersistentProjectile)
            {
                Destroy();
            }


        }
    }
}


