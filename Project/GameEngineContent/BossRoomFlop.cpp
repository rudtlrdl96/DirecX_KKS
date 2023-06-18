#include "PrecompileHeader.h"
#include "BossRoomFlop.h"

BossRoomFlop::BossRoomFlop()
{
}

BossRoomFlop::~BossRoomFlop()
{
}

void BossRoomFlop::Start()
{
	if (nullptr == GameEngineSprite::Find("BossRoom_Flop.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("3_ForestOfHarmony");
		Path.Move("AnimationObject");
		Path.Move("Flop");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BossRoom_Flop.png").GetFullPath(), 2, 3);
	}

	Render = CreateComponent<ContentSpriteRenderer>();
	Render->PipeSetting("2DTexture_Color");
	Render->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	Render->SetScaleRatio(2.0f);

	Render->CreateAnimation({
		.AnimationName = "Idle",
		.SpriteName = "BossRoom_Flop.png",
		.FrameInter = 0.1f,
		.Loop = true,
		.ScaleToTexture = true});

	Render->ChangeAnimation("Idle");
}
