#pragma once

enum class MonsterArea
{
	None,			// ������ None
	Opning,			// ������ ��ȭ�� ��
	ForestOfHamory,	// ��ȭ�� ��
	GrandHall,		// �׷��� Ȧ
	SacredGrounds,	// ����
	MianBoss,		// ���κ���
	SubBoss,		// ���꺸�� (���谡)
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