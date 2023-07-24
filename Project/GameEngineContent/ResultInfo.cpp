#include "PrecompileHeader.h"
#include "ResultInfo.h"

float ResultInfo::PlayTime = 0.0f;
int ResultInfo::DeathCount = 0;
int ResultInfo::KillCount = 0;

int ResultInfo::GetManaStone = 0;
int ResultInfo::GetGold = 0;
int ResultInfo::GetBone = 0;

float ResultInfo::TotalDamage = 0.0f;
float ResultInfo::MaxDamage = 0.0f;
float ResultInfo::HitDamage = 0.0f;
float ResultInfo::HealValue = 0.0f;

int ResultInfo::GetSkullCount = 0;
int ResultInfo::GetItemCount = 0;
int ResultInfo::GetQuintessenceCount = 0;

std::string ResultInfo::StageName = "알 수 없음";

std::vector<GearKey> ResultInfo::GetGearDatas;

void ResultInfo::ResultReset()
{
	PlayTime = 0.0f;
	DeathCount = 0;
	KillCount = 0;

	GetManaStone = 0;
	GetGold = 0;
	GetBone = 0;

	TotalDamage = 0.0f;
	MaxDamage = 0.0f;
	HitDamage = 0.0f;
	HealValue = 0.0f;

	GetSkullCount = 0;
	GetItemCount = 0;
	GetQuintessenceCount = 0;

	StageName = "알 수 없음";

	GetGearDatas.clear();
}

void ResultInfo::AddSkullCount(size_t _SkullIndex)
{
	GearKey GearData;

	GearData.Left = 0;
	GearData.Right = (int)_SkullIndex;

	std::vector<GearKey>::iterator FindIter = std::find(GetGearDatas.begin(), GetGearDatas.end(), GearData);

	if (FindIter != GetGearDatas.end())
	{
		return;
	}

	GetGearDatas.push_back(GearData);
	++GetSkullCount;
}

void ResultInfo::AddItemCount(size_t _ItemIndex)
{
	GearKey GearData;

	GearData.Left = 1;
	GearData.Right = (int)_ItemIndex;

	size_t GearIndex = GearData.GearIndex;

	std::vector<GearKey>::iterator FindIter = std::find(GetGearDatas.begin(), GetGearDatas.end(), GearData);

	if (FindIter != GetGearDatas.end())
	{
		return;
	}

	GetGearDatas.push_back(GearData);
	++GetItemCount;
}

ResultInfo::ResultInfo()
{
}

ResultInfo::~ResultInfo()
{
}
