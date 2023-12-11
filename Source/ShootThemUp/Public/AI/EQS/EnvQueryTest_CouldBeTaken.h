// Shoot Them Up Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_CouldBeTaken.generated.h"

UCLASS()
class SHOOTTHEMUP_API UEnvQueryTest_CouldBeTaken : public UEnvQueryTest
{
    GENERATED_BODY()

public:
    UEnvQueryTest_CouldBeTaken(const FObjectInitializer& ObjectInitializer);

    virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
};
