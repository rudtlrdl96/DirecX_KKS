#pragma once

enum class CollisionOrder
{
	Player,
	PlayerAttack,
	Enemy,
	EnemyAttack,
	Platform_Normal,
	Platform_Half,
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