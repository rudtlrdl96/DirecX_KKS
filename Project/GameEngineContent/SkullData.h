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

	SkullGrade Grade = SkullGrade::Normal;

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

	void Reset()
	{
		Name = "";
		Index = static_cast<size_t>(-1);

		Grade = SkullGrade::Normal;

		HP = 0;
		DamageReduction = 0.0f;

		MeleeAttack = 1.0f;
		MagicAttack = 1.0f;

		AttackSpeed = 1.0f;
		MoveSpeed = 400.0f;
		CastingSpeed = 1.0f;

		SkillCoolDown = 1.0f;
		SwitchCoolDown = 1.0f;
		QuintessenceCoolDown = 1.0f;

		CriticalPercent = 0.0f;
		CriticalDamage = 2.0f;
	}
};