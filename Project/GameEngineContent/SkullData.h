#pragma once

enum class SkullGrade
{
	Normal,
	Rare,
	Unique,
	Legendary
};

enum class SkullType
{
	Power,
	Speed,
	Balance
};

class SkullData
{
public:
	std::string Name = "";
	std::string HeadTexName = "";

	std::string StoryNote = "";
	std::string SkullNote = "";

	std::string IconName_MainSkull = "";
	std::string IconName_SubSkull = "";
	std::string IconName_Inventory = "";

	std::string IconName_SkillA = "Empty.png";
	std::string IconName_SkillB = "Empty.png";

	std::string Name_SkillA = "";
	std::string Name_SkillB = "";
	std::string Name_Switch = "";

	size_t Index = static_cast<size_t>(-1);
	size_t UpgradeIndex = static_cast<size_t>(-1);

	SkullGrade Grade = SkullGrade::Normal;
	SkullType SkullType = SkullType::Balance;

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