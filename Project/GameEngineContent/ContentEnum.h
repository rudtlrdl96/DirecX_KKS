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
	None,			// 디버깅용 None
	Opening,		// 오프닝
	Castle,			// 캐슬
	ForestOfHamory,	// 조화의 숲
	GrandHall,		// 그랜드 홀
	HolyCourtyard,	// 성역
	Shop,		    // 상점
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