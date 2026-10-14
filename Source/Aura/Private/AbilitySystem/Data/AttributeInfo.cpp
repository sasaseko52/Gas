// Copyright Mostafa Ibrahem


#include "AbilitySystem/Data/AttributeInfo.h"

FFrozenAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	for (const FFrozenAttributeInfo& AttributeInfo : AttributeInformation)
	{
		if (AttributeInfo.AttributeTag == AttributeTag)
		{
			return AttributeInfo;
		}
		
	}
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Attribute tag not found: %s  on %s"), *AttributeTag.ToString(),*GetNameSafe(this));
	}
	
	return FFrozenAttributeInfo();
	
}
