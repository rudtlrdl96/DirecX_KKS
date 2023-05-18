#include "PrecompileHeader.h"
#include "BoneHead.h"
#include <GameEngineCore/GameEngineCollision.h>

BoneHead::BoneHead()
{
}

BoneHead::~BoneHead()
{
}

void BoneHead::ShotHead(ActorViewDir _Dir)
{
	Dir = _Dir;
	ShotProgress = 0.0f;
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

	float4 TextureScale = Render->GetTransform()->GetLocalScale() * 2.0f;
	Render->GetTransform()->SetLocalScale(TextureScale);

	Collision = CreateComponent<GameEngineCollision>();
	Collision->GetTransform()->SetLocalScale(TextureScale);
}

void BoneHead::Update(float _DeltaTime)
{
	ShotProgress += _DeltaTime;

	if (ShotProgress < ShotTime)
	{
		GameEngineTransform* Trans = GetTransform();

		switch (Dir)
		{
		case ActorViewDir::Left:
			Trans->AddLocalPosition(float4::Left * ShotSpeed * _DeltaTime);
			break;
		case ActorViewDir::Right:
			Trans->AddLocalPosition(float4::Right * ShotSpeed * _DeltaTime);
			break;
		default:
			break;
		}

		Trans->AddLocalRotation(float4(0, 0, -RotSpeed * _DeltaTime));
	}
}