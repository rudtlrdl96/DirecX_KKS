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
	None,		// ����׿� None
	Courage,	// ���
	Antique,	// ��ǰ
	Heritage,	// ����� ��
	Misfortune, // �ҿ�
	Rapidity,	// �ż�
	Soar,		// ���
	Strike,		// ��Ÿ
	Wisdom,		// ����
	Chase,		// ����
	ManaCycle,  // ���� ��ȯ
};

class ItemData
{
public:
	std::string Name = "";
	std::string Note = "";
	size_t Index = 0;

	ItemGrade Grade = ItemGrade::Normal;

	Synergy Synergy1 = Synergy::None;
	Synergy Synergy2 = Synergy::None;

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
};