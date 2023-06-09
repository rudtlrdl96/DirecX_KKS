#include "PrecompileHeader.h"
#include "CastleFoxHunterNPC.h"

CastleFoxHunterNPC::CastleFoxHunterNPC()
{
}

CastleFoxHunterNPC::~CastleFoxHunterNPC()
{
}

void CastleFoxHunterNPC::Start()
{
	BaseNPC::Start();

	MainRender->CreateAnimation({.AnimationName = "Idle", .SpriteName = "FoxHunter_CastleIdle.png", .ScaleToTexture = true});
	PlayAnimation("Idle", false);
}

void CastleFoxHunterNPC::SpriteLoad()
{
	if (nullptr == GameEngineSprite::Find("FoxHunter_CastleIdle.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("2_Castle");
		Path.Move("Npc");
		Path.Move("FoxHunter");
		Path.Move("Sheet");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("FoxHunter_CastleIdle.png").GetFullPath(), 8, 1);
	}

}
