#pragma once

class UAnimMontage;

class AnimUtils
{
public:
    template <class T>
    static T* FindNotifyByClass(UAnimMontage* AnimMontage)
    {
        if (!AnimMontage) return nullptr;

        const auto NotifyEvents = AnimMontage->Notifies;
        for (auto NotifyEvent : NotifyEvents)
        {
            auto ResultNotify = Cast<T>(NotifyEvent.Notify);
            if (ResultNotify)
            {
                return ResultNotify;
            }
        }
        return nullptr;
    }
};