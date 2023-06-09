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

enum class CameraOrder
{
	Main = 0,
	UI = 100,
	Fade = 101
};