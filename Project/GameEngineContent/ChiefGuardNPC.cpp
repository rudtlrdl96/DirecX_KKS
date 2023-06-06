#include "PrecompileHeader.h"
#include "ChiefGuardNPC.h"

ChiefGuardNPC::ChiefGuardNPC()
{
}

ChiefGuardNPC::~ChiefGuardNPC()
{
}

void ChiefGuardNPC::Start()
{
	BaseNPC::Start();


	MainRender->CreateAnimation({
	.AnimationName = "Idle", .SpriteName = "ChiefGuardNPC_Idle.png", .ScaleToTexture = true, });

	MainRender->ChangeAnimation("Idle");

	HeadRender = CreateComponent<ContentSpriteRenderer>();
	HeadRender->PipeSetting("2DTexture_ColorLight");
	HeadRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	HeadRender->SetScaleRatio(2.0f);
	
	HeadRender->CreateAnimation({
		.AnimationName = "HeadIdle", .SpriteName = "ChiefGuardNPC_Head.png", .ScaleToTexture = true, });

	HeadRender->ChangeAnimation("HeadIdle");
	HeadRender->GetTransform()->SetLocalPosition(float4(-13, 20, 0));
}

void ChiefGuardNPC::SpriteLoad()
{
	if (nullptr == GameEngineSprite::Find("ChiefGuardNPC_Head.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("1_Opening");
		Path.Move("Npc");
		Path.Move("ChiefGuard");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ChiefGuardNPC_Head.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ChiefGuardNPC_Idle.png").GetFullPath(), 1, 1);
	}
}
