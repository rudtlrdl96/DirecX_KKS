#pragma once
#include "BaseCommonData.h"
#include "AbilityCommonData.h"

class SkullData : public BaseCommonData
{
public:
	SkullData();
	~SkullData();

	SkullGrade Grade;
	AbilityCommonData SkullAbility;
};