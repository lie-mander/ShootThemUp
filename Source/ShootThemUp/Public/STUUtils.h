#pragma once

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
};