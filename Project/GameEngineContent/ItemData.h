#pragma once

enum class ItemGrade
{
	Normal,
	Rare,
	Unique,
	Legendary
};

enum class Synergy
{
	Courage,	// 용기
	Antique,	// 골동품
	Heritage,	// 고대의 힘
	Misfortune, // 불운
	Rapidity,	// 신속
	Soar,		// 비상
	Strike,		// 강타
	Wisdom,		// 지혜
	Chase,		// 추적
	ManaCycle,  // 마나 순환
	Count
};

class ItemData
{
public:
	std::string Name = "";
	std::string Note = "";
	std::string Story = "";

	size_t Index = 0;

	ItemGrade Grade = ItemGrade::Normal;

	Synergy Synergy1 = Synergy::Count;
	Synergy Synergy2 = Synergy::Count;

	std::string ItemTexName = "Empty.png";
	std::string InventoryTexName = "Empty.png";

	float HP = 0;
	float DamageReduction = 0.0f;

	float MeleeAttack = 0.0f;
	float MagicAttack = 0.0f;

	float AttackSpeed = 0.0f;
	float MoveSpeed = 0.0f;
	float CastingSpeed = 0.0f;

	float SkillCoolDown = 0.0f;
	float SwitchCoolDown = 0.0f;
	float QuintessenceCoolDown = 0.0f;

	float CriticalPercent = 0.0f;
	float CriticalDamage = 0.0f;

	float GoldPercent = 0.0f;

	static std::string GetSynergyIconTextureName(Synergy _Type, size_t SynergyCount = -1);
	static std::string GetSynergyName(Synergy _Type);
	static std::vector<int> GetSynergyGrade(Synergy _Type);

};