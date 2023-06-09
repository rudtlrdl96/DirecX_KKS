#include "PrecompileHeader.h"
#include "CastleWitchNPC.h"

CastleWitchNPC::CastleWitchNPC()
{
}

CastleWitchNPC::~CastleWitchNPC()
{
}

void CastleWitchNPC::Start()
{
	BaseNPC::Start();

	MainRender->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Witch_Castle_Idle.png", .ScaleToTexture = true });
	PlayAnimation("Idle", false);
}

void CastleWitchNPC::SpriteLoad()
{
	if (nullptr == GameEngineSprite::Find("Witch_Castle_Idle.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("2_Castle");
		Path.Move("Npc");
		Path.Move("Witch");
		Path.Move("Sheet");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Witch_Castle_Idle.png").GetFullPath(), 6, 1);
	}

}