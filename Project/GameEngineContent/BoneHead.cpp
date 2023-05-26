#include "PrecompileHeader.h"
#include "BoneHead.h"
#include <GameEngineCore/GameEngineCollision.h>

#include "PlayerBaseSkull.h"

#include "BoneSkull.h"
#include "BaseMonster.h"

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
	ShotLiveTime = 0.0f;

	HeadRigid.SetVelocity(float4::Zero);
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
		Path.Move("Skull");
		Path.Move("BoneSkull");
		Path.Move("Skill");

		GameEngineTexture::Load(Path.GetPlusFileName("Skul_Head.png").GetFullPath());
	}

	Render = CreateComponent<GameEngineSpriteRenderer>();
	Render->GetTransform()->SetLocalPosition(float4::Zero);
	Render->SetScaleToTexture("Skul_Head.png");


	float4 TextureScale = Render->GetTransform()->GetLocalScale() * 2.0f;
	Render->GetTransform()->SetLocalScale(TextureScale);

	Collision = CreateComponent<GameEngineCollision>((int)CollisionOrder::BoneHead);
	Collision->GetTransform()->SetLocalScale(TextureScale);

	HeadRigid.SetMaxSpeed(600.0f);
	HeadRigid.SetFricCoeff(50.0f);
	HeadRigid.SetActiveGravity(true);
}

void BoneHead::Update(float _DeltaTime)
{
	if (nullptr == ParentSkull)
	{
		MsgAssert_Rtti<BoneHead>(" - 부모를 설정하지 않았습니다");
	}

	ShotProgress += _DeltaTime;
	ShotLiveTime += _DeltaTime;

	if (false == IsMoveEnd)
	{
		if (nullptr != Collision->Collision(CollisionOrder::Platform_Normal, ColType::AABBBOX2D, ColType::AABBBOX2D))
		{
			ShotProgress += 1000.0f;
		}

		std::shared_ptr<GameEngineCollision> MonsterCol = Collision->Collision(CollisionOrder::Monster, ColType::AABBBOX2D, ColType::AABBBOX2D);

		if (nullptr != MonsterCol)
		{
			ShotProgress += 1000.0f;

			std::shared_ptr<BaseMonster> MonsterPtr = MonsterCol->GetActor()->DynamicThis<BaseMonster>();

			if (nullptr == MonsterPtr)
			{
				MsgAssert_Rtti<BoneHead>(" - BaseMonster를 상속받은 클래스만 MonsterCol Order로 설정할 수 있습니다");
				return;
			}

			MonsterPtr->HitMonster(ParentSkull->GetMagicAttackDamage(), Dir, true, true);
		}
	}

	if (ShotProgress < ShotTime)
	{
		IsMoveEnd = false;
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
	else
	{
		HeadRigid.UpdateForce(_DeltaTime);

		GameEngineTransform* Trans = GetTransform();
		float4 HeadVelocity = HeadRigid.GetVelocity();

		Trans->AddLocalPosition(HeadVelocity * _DeltaTime);

		if (false == IsMoveEnd)
		{
			PlayEndEffect();
			IsMoveEnd = true;

			switch (Dir)
			{
			case ActorViewDir::Left:
				HeadRigid.SetVelocity(float4(400, 800));
				break;
			case ActorViewDir::Right:
				HeadRigid.SetVelocity(float4(-400, 800));
				break;
			default:
				break;
			}
		}
	}
}

void BoneHead::PlayEndEffect()
{
	std::shared_ptr<EffectActor> EffectPtr = nullptr;

	switch (Dir)
	{
	case ActorViewDir::Left:
		EffectPtr = EffectManager::PlayEffect({ .EffectName = "HitSkul",
			.Postion = GetTransform()->GetLocalPosition(),
			.FlipX = false });
		break;
	case ActorViewDir::Right:
		EffectPtr = EffectManager::PlayEffect({ .EffectName = "HitSkul",
			.Postion = GetTransform()->GetLocalPosition(),
			.FlipX = true });
		break;
	default:
		break;
	}

	EffectPtr->GetTransform()->SetLocalRotation(float4(0, 0, GameEngineRandom::MainRandom.RandomFloat(-70.0f, 70.0f)));
}
