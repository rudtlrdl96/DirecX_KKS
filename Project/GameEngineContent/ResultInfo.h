#pragma once
#include "QuintessenceData.h"


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

protected:
	
private:
	ResultInfo();
	~ResultInfo();

	ResultInfo(const ResultInfo& _Other) = delete;
	ResultInfo(ResultInfo&& _Other) noexcept = delete;
	ResultInfo& operator=(const ResultInfo& _Other) = delete;
	ResultInfo& operator=(ResultInfo&& _Other) noexcept = delete;

};

