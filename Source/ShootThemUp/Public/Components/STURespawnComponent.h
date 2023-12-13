// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STURespawnComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTURespawnComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    USTURespawnComponent();

    void Respawn(int32 RespawnTime);
    int32 GetRespawnConuntDown() const { return RespawnConuntDown; }
    bool IsRespawnInProgress() const;

private:
    FTimerHandle ReapawnTimerHandle;
    int32 RespawnConuntDown = 0;

    void RespawnTimerUpdate();
};
