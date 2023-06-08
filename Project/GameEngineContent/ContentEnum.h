#pragma once

enum class CollisionOrder
{
	Unknown,
	Player,
	PlayerAttack,
	Monster,
	MonsterAttack,
	BrokenObject,
	Platform_Normal,
	Platform_Half,
	BoneHead
};

enum class LevelArea
{
	None,			// ������ None
	Opening,		// ������
	Castle,			// ĳ��
	ForestOfHamory,	// ��ȭ�� ��
	GrandHall,		// �׷��� Ȧ
	HolyCourtyard,	// ����
	Shop,		    // ����
};

enum class ActorViewDir
{
	Left,
	Right
};