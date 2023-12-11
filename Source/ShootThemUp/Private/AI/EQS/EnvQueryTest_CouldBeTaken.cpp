// Shoot Them Up Game. All Rights Reserved.

#include "AI/EQS/EnvQueryTest_CouldBeTaken.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"
#include "Pickups/STUBasePickup.h"

UEnvQueryTest_CouldBeTaken::UEnvQueryTest_CouldBeTaken(const FObjectInitializer& ObjectInitializer) //
    : Super(ObjectInitializer)
{
    Cost = EEnvTestCost::Low;
    ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
    SetWorkOnFloatValues(false);
}

void UEnvQueryTest_CouldBeTaken::RunTest(FEnvQueryInstance& QueryInstance) const
{
    const auto DataOwner = QueryInstance.Owner.Get();
    BoolValue.BindData(DataOwner, QueryInstance.QueryID);

    const bool bWantsBeTakable = BoolValue.GetValue();

    for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
    {
        const auto ItemActor = GetItemActor(QueryInstance, It.GetIndex());
        const auto PickupActor = Cast<ASTUBasePickup>(ItemActor);
        if (!PickupActor) continue;

        const auto bCouldBeTaken = PickupActor->CouldBeTaken();
        It.SetScore(TestPurpose, FilterType, bCouldBeTaken, bWantsBeTakable);
    }
}
