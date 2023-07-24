#pragma once
#include "QuintessenceData.h"
#include "ItemData.h"
#include "SkullData.h"

class GearKey
{
public: 
	union
	{
		size_t GearIndex;

		struct
		{
			int Left;
			int Right;
		};
	};

	bool operator==(GearKey _Ohter)
	{
		return GearIndex == _Ohter.GearIndex;
	}

	bool operator!=(GearKey _Ohter)
	{
		return GearIndex != _Ohter.GearIndex;
	}
};

class ResultInfo
{
public:
	static float PlayTime;
	static int DeathCount;
	static int KillCount;

	static int GetManaStone;
	static int GetGold;
	static int GetBone;

	static float TotalDamage;
	static float MaxDamage;
	static float HitDamage;
	static float HealValue;

	static int GetSkullCount;
	static int GetItemCount;
	static int GetQuintessenceCount;

	static std::string StageName;

	static void ResultReset();

	static void AddSkullCount(size_t _SkullIndex);
	static void AddItemCount(size_t _ItemIndex);

	static std::vector<GearKey> GetGetGearDatas()
	{
		return GetGearDatas;
	}

protected:
	
private:
	ResultInfo();
	~ResultInfo();

	ResultInfo(const ResultInfo& _Other) = delete;
	ResultInfo(ResultInfo&& _Other) noexcept = delete;
	ResultInfo& operator=(const ResultInfo& _Other) = delete;
	ResultInfo& operator=(ResultInfo&& _Other) noexcept = delete;

	static std::vector<GearKey> GetGearDatas;
};

