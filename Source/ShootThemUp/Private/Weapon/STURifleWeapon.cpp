// Shoot Them Up Game. All Rights Reserved.

#include "Weapon/STURifleWeapon.h"
#include "Weapon/Components/STUWeaponFXComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

ASTURifleWeapon::ASTURifleWeapon()
{
    WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponFXComponent");
}

void ASTURifleWeapon::BeginPlay()
{
    Super::BeginPlay();

    check(WeaponFXComponent);
}

void ASTURifleWeapon::StartFire()
{
    InitFX();
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASTURifleWeapon::MakeShot, TimeBetwenShots, true);
    MakeShot();
}
void ASTURifleWeapon::StopFire()
{
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
    SetFXActive(false);
}

void ASTURifleWeapon::MakeShot()
{
    if (!GetWorld() || IsAmmoEmpty())
    {
        StopFire();
        return;
    }

    FVector TraceStart, TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd))
    {
        StopFire();
        return;
    }

    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    const FVector WeaponVector = WeaponMesh->GetSocketTransform(MuzzleSocketName).GetRotation().GetForwardVector();
    const FVector ShootingVector = (HitResult.ImpactPoint - GetMuzzleWorldLocation());
    const float Angle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(WeaponVector, ShootingVector.GetSafeNormal())));

    FVector TraceFXEnd = TraceEnd;
    if (HitResult.bBlockingHit && Angle < MaxAngle)
    {
        TraceFXEnd = HitResult.ImpactPoint;
        WeaponFXComponent->PlayImpactFX(HitResult);

        MakeDamage(HitResult);
    }
    SpawnTraceFX(GetMuzzleWorldLocation(), TraceFXEnd);

    DecreaseAmmo();
}

bool ASTURifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

    TraceStart = ViewLocation;
    const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
    const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
    TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
    return true;
}

void ASTURifleWeapon::MakeDamage(const FHitResult& HitResult)
{
    const auto DamagedActor = HitResult.GetActor();
    if (!DamagedActor) return;

    DamagedActor->TakeDamage(DamageAmount, FDamageEvent{}, GetController(), this);
}

void ASTURifleWeapon::InitFX()
{
    if (!MuzzleFXComponent)
    {
        MuzzleFXComponent = SpawnMuzzleFX();
    }

    if (!FireAudioComponent)
    {
        FireAudioComponent = UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);
    }

    SetFXActive(true);
}

void ASTURifleWeapon::SetFXActive(bool IsActive)
{
    if (MuzzleFXComponent)
    {
        MuzzleFXComponent->SetPaused(!IsActive);
        MuzzleFXComponent->SetVisibility(IsActive, true);
    }

    if (FireAudioComponent)
    {
        FireAudioComponent->SetPaused(!IsActive);
    }
}

void ASTURifleWeapon::SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd)
{
    const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX, TraceStart);
    if (TraceFXComponent)
    {
        TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
    }
}

AController* ASTURifleWeapon::GetController() const
{
    const auto Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}

void ASTURifleWeapon::Zoom(bool Enabled)
{
    const auto Controller = Cast<APlayerController>(GetController());
    if (!Controller || !Controller->PlayerCameraManager) return;

    if (Enabled)
    {
        DefaultCameraFOV = Controller->PlayerCameraManager->GetFOVAngle();
    }

    Controller->PlayerCameraManager->SetFOV(Enabled ? FOVZoomAngle : DefaultCameraFOV);
}