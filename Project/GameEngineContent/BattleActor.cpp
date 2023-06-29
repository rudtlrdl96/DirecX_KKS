#include "PrecompileHeader.h"
#include "BattleActor.h"
#include <GameEngineCore/GameEngineLevel.h>

#include "HitParticle.h"
#include "BattleLevel.h"

BattleActor::BattleActor()
{
}

BattleActor::~BattleActor()
{
}

void BattleActor::Start()
{
	Render = CreateComponent<ContentSpriteRenderer>();
	Render->PipeSetting("2DTexture_Outline");
	Render->GetShaderResHelper().SetConstantBufferLink("OutlineColorBuffer", Buffer);
	Render->GetTransform()->SetLocalPosition(float4::Zero);
	Render->SetScaleRatio(2.0f);
	
	Buffer.Color = float4::Zero;
	Buffer.OutlineColor = float4::Null;
}

void BattleActor::Update(float _DeltaTime)
{
	ThornWaitTime -= _DeltaTime;
	HitParticleCoolTime += _DeltaTime;	
	IsHit = false;

	if (true == IsHitEffectOn)
	{
		HitEffectProgress += _DeltaTime * HitEffectSpeed;

		if (false == IsHitEffectOff)
		{
			if (0.5f >= HitEffectProgress)
			{
				Buffer.Color = float4::LerpClamp(float4(0, 0, 0, 1), float4(1, 1, 1, 1), HitEffectProgress * 2.0f);
			}
			else
			{
				Buffer.Color = float4::LerpClamp(float4(1, 1, 1, 1), float4(0, 0, 0, 1), (HitEffectProgress * 2.0f) - 1.0f);
			}
		}

		if (1.0f <= HitEffectProgress)
		{
			IsHitEffectOn = false;
			HitEffectProgress = 0.0f;
		}
	}
}

void BattleActor::HitEffect(HitEffectType _Type)
{
	GameEngineRandom& Rand = GameEngineRandom::MainRandom;

	if (0.2f <= HitParticleCoolTime)
	{
		HitParticleCoolTime = 0.0f;

		for (size_t i = 0; i < 8; i++)
		{
			std::shared_ptr<HitParticle> NewParticle = GetLevel()->CreateActor<HitParticle>();

			float4 RandPos = float4(Rand.RandomFloat(-30, 30), Rand.RandomFloat(-30, 30), -1);

			NewParticle->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition() + RandPos);

			float4 RandDir = float4(1.0f, 0.0f, 0.0f);

			switch (HitDir)
			{
			case ActorViewDir::Left:
				RandDir.RotaitonZDeg(Rand.RandomFloat(110, 140));
				NewParticle->Init(RandDir, Rand.RandomFloat(750, 1000), 1.0f);
				break;
			case ActorViewDir::Right:
				RandDir.RotaitonZDeg(Rand.RandomFloat(40, 70));
				NewParticle->Init(RandDir, Rand.RandomFloat(750, 1000), 1.0f);
				break;
			default:
				break;
			}
		}
	}

	switch (_Type)
	{
	case HitEffectType::Normal:
		switch (HitDir)
		{
		case ActorViewDir::Left:
			EffectManager::PlayEffect({ .EffectName = "HitNormal",
				.Position = GetTransform()->GetLocalPosition() + float4(Rand.RandomFloat(-30, -20), Rand.RandomFloat(25, 70), 0),
				.FlipX = true });
			break;
		case ActorViewDir::Right:
			EffectManager::PlayEffect({ .EffectName = "HitNormal",
					.Position = GetTransform()->GetLocalPosition() + float4(Rand.RandomFloat(20, 30), Rand.RandomFloat(25, 70), 0),
					.FlipX = false });
			break;
		default:
			break;
		}
		break;
	case HitEffectType::Skull:
		switch (HitDir)
		{
		case ActorViewDir::Left:
			EffectManager::PlayEffect({ .EffectName = "HitSkul",
				.Position = GetTransform()->GetLocalPosition() + float4(Rand.RandomFloat(-30, -20), Rand.RandomFloat(25, 70), 0),
				.Scale = 0.6f,
				.FlipX = true });
			break;
		case ActorViewDir::Right:
			EffectManager::PlayEffect({ .EffectName = "HitSkul",
				.Position = GetTransform()->GetLocalPosition() + float4(Rand.RandomFloat(20, 30), Rand.RandomFloat(25, 70), 0),
				.Scale = 0.6f,
				.FlipX = false });
			break;
		default:
			break;
		}
		break;
	case HitEffectType::Sword:
	{
		std::shared_ptr<EffectActor> Effect = nullptr;

		switch (HitDir)
		{
		case ActorViewDir::Left:

			Effect = EffectManager::PlayEffect({ .EffectName = "HitSkeletonSword",
				.Position = GetTransform()->GetLocalPosition() + float4(Rand.RandomFloat(-55, -35), Rand.RandomFloat(25, 70), 0),
				.Scale = Rand.RandomFloat(0.8f, 1.2f),
				.FlipX = true });

			break;
		case ActorViewDir::Right:
			Effect = EffectManager::PlayEffect({ .EffectName = "HitSkeletonSword",
				.Position = GetTransform()->GetLocalPosition() + float4(Rand.RandomFloat(35, 55), Rand.RandomFloat(25, 70), 0),
				.Scale = Rand.RandomFloat(0.8f, 1.2f),
				.FlipX = true });
			break;
		default:
			break;
		}

		Effect->GetTransform()->SetLocalRotation(float4(0, 0, Rand.RandomFloat(0.0f, 360.0f)));
	}
	break;
	case HitEffectType::MinoTaurus:
	{
		switch (HitDir)
		{
		case ActorViewDir::Left:
			EffectManager::PlayEffect({ .EffectName = "HitMinotaurus",
				.Position = GetTransform()->GetLocalPosition() + float4(Rand.RandomFloat(-30, -20), Rand.RandomFloat(25, 70), 0),
				.FlipX = true });
			break;
		case ActorViewDir::Right:
			EffectManager::PlayEffect({ .EffectName = "HitMinotaurus",
					.Position = GetTransform()->GetLocalPosition() + float4(Rand.RandomFloat(20, 30), Rand.RandomFloat(25, 70), 0),
					.FlipX = false });
			break;
		default:
			break;
		}
	}
		break;
	default:
		break;
	}

	
}

void BattleActor::HitPush()
{
	if (true == IsUnPushArmor)
	{
		return;
	}

	if (false == IsPush)
	{
		return;
	}

	switch (HitDir)
	{
	case ActorViewDir::Left:
		BattleActorRigidbody.SetVelocity(float4::Left * 200.0f);
		break;
	case ActorViewDir::Right:
		BattleActorRigidbody.SetVelocity(float4::Right * 200.0f);
		break;
	default:
		break;
	}

}