#pragma once

enum class MonsterArea
{
	None,			// 디버깅용 None
	Opning,			// 오프닝 조화의 숲
	ForestOfHamory,	// 조화의 숲
	GrandHall,		// 그랜드 홀
	SacredGrounds,	// 성역
	MianBoss,		// 메인보스
	SubBoss,		// 서브보스 (모험가)
};	

class MonsterData
{
public:
	std::string Name = "";
	std::string ImageName = "";
	size_t Index = 0;
	MonsterArea Grade = MonsterArea::None;

	float HP = 0;
	float DamageReduction = 0.0f;

	float Attack = 0.0f;
	float AttackSpeed = 1.0f;

	float MoveSpeed = 50.0f;
	float CastingSpeed = 1.0f;

	float SkillCoolDown = 0.0f;
	float CriticalPercent = 0.0f;
	float CriticalDamage = 2.0f;
};