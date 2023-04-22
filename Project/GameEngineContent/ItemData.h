#pragma once
#include "BaseCommonData.h"
#include "AbilityCommonData.h"

class ItemData : public BaseCommonData
{
public:
	ItemData();
	~ItemData();

	ItemGrade Grade;
	AbilityCommonData ItemAbility;
};