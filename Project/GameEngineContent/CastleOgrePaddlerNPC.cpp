#include "PrecompileHeader.h"
#include "CastleOgrePaddlerNPC.h"

CastleOgrePaddlerNPC::CastleOgrePaddlerNPC()
{
}

CastleOgrePaddlerNPC::~CastleOgrePaddlerNPC()
{
}

void CastleOgrePaddlerNPC::Start()
{
	BaseNPC::Start();

	MainRender->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "OgrePeddler_Idle.png", .ScaleToTexture = true });
	PlayAnimation("Idle", false);
}

void CastleOgrePaddlerNPC::SpriteLoad()
{
	if (nullptr == GameEngineSprite::Find("OgrePeddler_Idle.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("2_Castle");
		Path.Move("Npc");
		Path.Move("OgrePeddler");
		Path.Move("Sheet");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("OgrePeddler_Idle.png").GetFullPath(), 8, 1);
	}

}