// Shoot Them Up Game. All Rights Reserved.

#include "Components/STUAIPerceptionComponent.h"
#include "AIController.h"
#include "STUUtils.h"
#include "Components/STUHealthComponent.h"
#include "Perception/AISense_Sight.h"

AActor* USTUAIPerceptionComponent::GetClosestEnemy() const
{
    TArray<AActor*> PesciveActors;
    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PesciveActors);
    if (PesciveActors.Num() == 0) return nullptr;

    const auto Controller = Cast<AAIController>(GetOwner());
    if (!Controller) return nullptr;

    const auto Pawn = Controller->GetPawn();
    if (!Pawn) return nullptr;

    float BestDistance = MAX_FLT;
    AActor* BestPawn = nullptr;

    for (const auto PesciveActor : PesciveActors)
    {
        const auto HealthConponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(PesciveActor);

        const auto PercievePawn = Cast<APawn>(PesciveActor);
        const auto AreEnemies = PercievePawn && STUUtils::AreEnemies(Controller, PercievePawn->GetController());

        if (HealthConponent && !HealthConponent->IsDead() && AreEnemies)
        {
            const auto CurrentDistance = (PesciveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
            if (CurrentDistance < BestDistance)
            {
                BestDistance = CurrentDistance;
                BestPawn = PesciveActor;
            }
        }
    }

    return BestPawn;
}
