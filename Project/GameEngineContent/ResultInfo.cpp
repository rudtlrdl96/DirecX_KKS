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
}

ResultInfo::ResultInfo()
{
}

ResultInfo::~ResultInfo()
{
}
