#pragma once

enum class SkullGrade
{
	Normal,
	Rare,
	Unique,
	Legendary
};

class SkullData
{
public:
	std::string Name = "";
	size_t Index = static_cast<size_t>(-1);

	SkullGrade Grade;

	float HP = 0;
	float DamageReduction = 0.0f;

	float MeleeAttack = 1.0f;
	float MagicAttack = 1.0f;

	float AttackSpeed = 1.0f;
	float MoveSpeed = 400.0f;
	float CastingSpeed = 1.0f;

	float SkillCoolDown = 1.0f;
	float SwitchCoolDown = 1.0f;
	float QuintessenceCoolDown = 1.0f;

	float CriticalPercent = 0.0f;
	float CriticalDamage = 2.0f;
};