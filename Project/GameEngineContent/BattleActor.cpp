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

	if (true == IsColorEffect)
	{
		ColorEffectProgress += _DeltaTime * ColorEffectSpeed;
		Buffer.Color = float4::LerpClamp(ColorEffectStart, ColorEffectEnd, ColorEffectProgress - ColorEffectWaitTime);

		if (1.0f <= ColorEffectProgress)
		{
			IsColorEffect = false;
		}
	}
	else if (true == IsHitEffectOn)
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

void BattleActor::HitEffect(HitEffectType _Type, bool _IsCritical)
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

	std::string EffectName = "";

	switch (_Type)
	{
	case HitEffectType::Normal:

		if (true == _IsCritical)
		{
			EffectName = "HitNormalCritical";
		}
		else
		{
			EffectName = "HitNormal";
		}

		switch (HitDir)
		{
		case ActorViewDir::Left:
			EffectManager::PlayEffect({ .EffectName = EffectName,
				.Position = GetTransform()->GetLocalPosition() + float4(Rand.RandomFloat(-30, -20), Rand.RandomFloat(25, 70), 0),
				.FlipX = true });
			break;
		case ActorViewDir::Right:
			EffectManager::PlayEffect({ .EffectName = EffectName,
					.Position = GetTransform()->GetLocalPosition() + float4(Rand.RandomFloat(20, 30), Rand.RandomFloat(25, 70), 0),
					.FlipX = false });
			break;
		default:
			break;
		}
		break;
	case HitEffectType::Skull:
		SoundDoubleCheck::Play("Hit_Skull.wav");

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
		SoundDoubleCheck::Play("Hit_Sword_Small.wav");

		std::shared_ptr<EffectActor> Effect = nullptr;

		if (true == _IsCritical)
		{
			EffectName = "HitSlashCritical";
		}
		else
		{
			EffectName = "HitSkeletonSword";
		}

		switch (HitDir)
		{
		case ActorViewDir::Left:

			Effect = EffectManager::PlayEffect({ .EffectName = EffectName,
				.Position = GetTransform()->GetLocalPosition() + float4(Rand.RandomFloat(-55, -35), Rand.RandomFloat(25, 70), 0),
				.Scale = Rand.RandomFloat(0.8f, 1.2f),
				.FlipX = true });

			break;
		case ActorViewDir::Right:
			Effect = EffectManager::PlayEffect({ .EffectName = EffectName,
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
		SoundDoubleCheck::Play("MinoTaurus_ATK_Hit.wav");

		std::shared_ptr<EffectActor> Effect = nullptr;

		if (true == _IsCritical)
		{
			EffectName = "HitSpecialCritical";
		}
		else
		{
			EffectName = "HitMinotaurus";
		}

		switch (HitDir)
		{
		case ActorViewDir::Left:

			Effect = EffectManager::PlayEffect({ .EffectName = EffectName,
				.Position = GetTransform()->GetLocalPosition() + float4(Rand.RandomFloat(-55, -35), Rand.RandomFloat(25, 70), 0),
				.Scale = Rand.RandomFloat(0.7f, 0.9f),
				.FlipX = true });

			break;
		case ActorViewDir::Right:
			Effect = EffectManager::PlayEffect({ .EffectName = EffectName,
				.Position = GetTransform()->GetLocalPosition() + float4(Rand.RandomFloat(35, 55), Rand.RandomFloat(25, 70), 0),
				.Scale = Rand.RandomFloat(0.7f, 0.9f),
				.FlipX = true });
			break;
		default:
			break;
		}

		Effect->GetTransform()->SetLocalRotation(float4(0, 0, Rand.RandomFloat(0.0f, 360.0f)));
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

void BattleActor::ColorEffectOn(float _Speed, float _WaitTime, const float4& _StartColor, const float4& _EndColor)
{
	ColorEffectProgress = 0.0f;
	ColorEffectWaitTime = _WaitTime;
	ColorEffectSpeed = _Speed;
	ColorEffectStart = _StartColor;
	ColorEffectEnd = _EndColor;
	IsColorEffect = true;
}