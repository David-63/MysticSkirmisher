// Copyright David-6


#include "AbilitySystem/Data/CharacterClassInfo.h"


FCharacterClassDefaultInfo UCharacterClassInfo::GetClassDefaultInfo(ECharacterClass CharacterClass)
{
    
    return CharacterClassInformation.FindChecked(CharacterClass);

}