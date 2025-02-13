// Copyright David-6


#include "AbilitySystem/Data/AttributeInfo.h"


FSkirmisherAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag &AttributeTag, bool bLogNotFound) const
{
    for (const FSkirmisherAttributeInfo& info : AttributeInformation)
    {
        if (info.AttributeTag == AttributeTag)
        {
            if (info.AttributeTag.MatchesTagExact(AttributeTag))
            {
                return info;
            }
        }
    }

    if (bLogNotFound)
    {
        UE_LOG(LogTemp, Error, TEXT("Can't find info for AttributeTag [%s] on AttributeInfo [%s]."), *AttributeTag.ToString(), *GetNameSafe(this));
    }

    return FSkirmisherAttributeInfo();
}