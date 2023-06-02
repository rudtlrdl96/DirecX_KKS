#include "PrecompileHeader.h"
#include "Vine.h"

Vine::Vine()
{
}

Vine::~Vine()
{
}

void Vine::Start()
{
	BehaviorObject::Start();

	if (nullptr == GameEngineSprite::Find("Vine_Idle.png"))
	{
		GameEngineDirectory Path;
		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("3_ForestOfHarmony");
		Path.Move("BehaviorObject");
		Path.Move("Vine");
		Path.Move("Sheet");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Vine_Idle.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Vine_BattleIdle.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Vine_AttackReady.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Vine_Attack.png").GetFullPath(), 9, 1);
	}

}

void Vine::ResetBehavior()
{
}

void Vine::PlayBehavior()
{
}
