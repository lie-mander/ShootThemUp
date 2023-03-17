#pragma once
#include "Player/STUPlayerState.h"

class UActorComponent;

class STUUtils
{
public:
    template <typename T>
    static T* GetSTUPlayerComponent(AActor* Pawn)
    {
        if (!Pawn) return nullptr;

        const auto Component = Pawn->GetComponentByClass(T::StaticClass());
        return Cast<T>(Component);
    }

    static bool AreEnemies(const AController* Controller1, const AController* Controller2)
    {
        if (!Controller1 || !Controller2 || Controller1 == Controller2) return false;

        const auto PlayerState1 = Cast<ASTUPlayerState>(Controller1->PlayerState);
        const auto PlayerState2 = Cast<ASTUPlayerState>(Controller2->PlayerState);

        return PlayerState1 && PlayerState2 && PlayerState1->GetTeamID() != PlayerState2->GetTeamID();
    }

    static FText TextFromInt(int32 Number) { return FText::FromString(FString::FromInt(Number)); }
};