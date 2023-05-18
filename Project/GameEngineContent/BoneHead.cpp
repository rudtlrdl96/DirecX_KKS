#include "PrecompileHeader.h"
#include "BoneHead.h"

BoneHead::BoneHead()
{
}

BoneHead::~BoneHead()
{
}

void BoneHead::Start()
{
	if (nullptr == GameEngineTexture::Find("Skul_Head.png"))
	{
		GameEngineDirectory Path;
		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("Player");
		Path.Move("BoneSkull");
		Path.Move("Skill");

		GameEngineTexture::Load(Path.GetPlusFileName("Skul_Head.png").GetFullPath());
	}

	Render = CreateComponent<GameEngineSpriteRenderer>();
	Render->GetTransform()->SetLocalPosition(float4::Zero);
	Render->SetScaleToTexture("Skul_Head.png");

	float4 TextureScale = Render->GetTransform()->GetLocalScale();
	Render->GetTransform()->SetLocalScale(TextureScale * 2.0f);
}

void BoneHead::Update(float _DeltaTime)
{
}
