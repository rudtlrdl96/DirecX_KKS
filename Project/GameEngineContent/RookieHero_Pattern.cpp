#include "PrecompileHeader.h"
#include "RookieHero.h"
#include "Player.h"

void RookieHero::ComboAttack_Enter()
{
	ComboAttackIndex = 0;
	LookPlayer();
	//PlayAnimation("AttackA_Ready");

	AttackCheck.SetEvent([this](std::shared_ptr<BaseContentActor> _Ptr, const AttackColMetaData& _Data)
		{
			std::shared_ptr <Player> CastPtr = std::static_pointer_cast<Player>(_Ptr);

			if (nullptr == CastPtr)
			{
				MsgAssert_Rtti<RookieHero>(" - 플레이어만 Player Col Order를 가질 수 있습니다.");
				return;
			}

			EffectManager::PlayEffect({
				.EffectName = "HitSlashEffect",
				.Position = CastPtr->GetTransform()->GetWorldPosition() + float4(0, 40, 0),
				.AddSetZ = -10.0f});

			switch (Dir)
			{
			case ActorViewDir::Left:
				CastPtr->HitPlayer(Data.Attack, float4(-300, 500));
				break;
			case ActorViewDir::Right:
				CastPtr->HitPlayer(Data.Attack, float4(300, 500));
				break;
			default:
				break;
			}
		});

	BossRigidbody.SetVelocity(float4::Zero);
	ComboDashCheck = false;
}

void RookieHero::ComboAttack_Update(float _DeltaTime)
{
	BossRigidbody.UpdateForce(_DeltaTime);

	float4 AttackVel = BossRigidbody.GetVelocity() * _DeltaTime;

	RigidbodyMovePlatformCheck(AttackVel);
	GetTransform()->AddLocalPosition(AttackVel);

	if (0 == ComboAttackIndex)
	{
		AttackCheck.SetColData(AttackA_Data);
		PlayAnimation(AttackA_Data.GetAnimationName());
		++ComboAttackIndex;
		ComboDashCheck = false;
	}
	
	if (1 == ComboAttackIndex)
	{
		if (false == AttackCheck.Update())
		{
			AttackCheck.SetColData(AttackD_Data);
			PlayAnimation(AttackD_Data.GetAnimationName());
			++ComboAttackIndex;
			ComboDashCheck = false;
		}
		else if (false == ComboDashCheck && 5 == Render->GetCurrentFrame())
		{
			ComboDashCheck = true;

			switch (Dir)
			{
			case ActorViewDir::Left:
				BossRigidbody.SetVelocity(float4::Left * 700.0f);
				break;
			case ActorViewDir::Right:
				BossRigidbody.SetVelocity(float4::Right * 700.0f);
				break;
			default:
				break;
			}
		}		
	}

	if (2 == ComboAttackIndex)
	{
		if (false == AttackCheck.Update())
		{
			LookPlayer();
			AttackCheck.SetColData(AttackB_Data);
			PlayAnimation(AttackB_Data.GetAnimationName());
			++ComboAttackIndex;
			ComboDashCheck = false;
		}
		else if (false == ComboDashCheck && 1 == Render->GetCurrentFrame())
		{
			ComboDashCheck = true;

			switch (Dir)
			{
			case ActorViewDir::Left:
				BossRigidbody.SetVelocity(float4::Left * 700.0f);
				break;
			case ActorViewDir::Right:
				BossRigidbody.SetVelocity(float4::Right * 700.0f);
				break;
			default:
				break;
			}
		}
	}

	if (3 == ComboAttackIndex)
	{
		if (false == AttackCheck.Update())
		{
			BossFsm.ChangeState("Idle");
		}
		else if (false == ComboDashCheck && 1 == Render->GetCurrentFrame())
		{
			ComboDashCheck = true;

			switch (Dir)
			{
			case ActorViewDir::Left:
				BossRigidbody.SetVelocity(float4::Left * 700.0f);
				break;
			case ActorViewDir::Right:
				BossRigidbody.SetVelocity(float4::Right * 700.0f);
				break;
			default:
				break;
			}
		}
	}
}

void RookieHero::ComboAttack_End()
{
}

void RookieHero::EnergyBall_Enter()
{
	LookPlayer();
	PlayAnimation("EnergyBallReady");
	IsEnergyBallShot = false;
}

void RookieHero::EnergyBall_Update(float _DeltaTime)
{
	if (true == IsEnergyBallShot)
	{
		if (true == Render->IsAnimationEnd())
		{
			BossFsm.ChangeState("Idle");
		}
	}
	else
	{
		if (true == Render->IsAnimationEnd())
		{
			PlayAnimation("EnergyBall");
			IsEnergyBallShot = true;
		}
	}
}

void RookieHero::EnergyBall_End()
{

}

void RookieHero::Potion_Enter()
{
	PlayAnimation("Potion");
	PotionTime = -3.5f;
	PotionHealTime = 0.0f;
}

void RookieHero::Potion_Update(float _DeltaTime)
{
	PotionTime += _DeltaTime;
	PotionHealTime += _DeltaTime;

	if (0.0f <= PotionHealTime)
	{
		EffectManager::PlayEffect({
			.EffectName = "MonsterHeal",
			.Position = GetTransform()->GetWorldPosition() + float4(0, 80, 0),
			.AddSetZ = -10.0f});

		PotionHealTime = -0.72f;

		HP += 5.0f;

		if (HP > Data.HP)
		{
			HP = Data.HP;
		}
	}

	if (0.0f <= PotionTime)
	{
		BossFsm.ChangeState("Idle");
	}
}

void RookieHero::Potion_End()
{

}

void RookieHero::Explosion_Enter()
{
	PlayAnimation("ExplosionReady");

	IsExplosion = false;
	IsExplosionEffect = false;
	ExplosionTime = 0.0f;

	IsHitEffectOff = true;
	IsExplosionAttackEnd = false;
}

void RookieHero::Explosion_Update(float _DeltaTime)
{

	if (true == Render->IsAnimationEnd())
	{
		IsExplosionEffect = true;
		PlayAnimation("Explosion", false);
	}

	if (true == IsExplosionEffect)
	{
		ExplosionTime += _DeltaTime;

		float Progress = ExplosionTime - 0.2f;

		if (1.0f < Progress)
		{
			Progress = 1.0f;
		}

		Buffer.Color = float4::LerpClamp(float4(1, 1, 1, 1), float4(0, 0, 0, 1), Progress);
	}

	if (false == IsExplosion && 1.2f <= ExplosionTime)
	{
		IsHitEffectOff = false;
		IsExplosion = true;

		GetContentLevel()->GetCamCtrl().CameraShake(10, 30, 9);

		ExplosionEffect = EffectManager::PlayEffect({
			.EffectName = "RookieHero_Explosion",
			.Position = GetTransform()->GetWorldPosition() + float4(0, 130, 0),
			.AddSetZ = -10.0f });
	}

	if (false == IsExplosionAttackEnd && 
		nullptr != ExplosionEffect && 4 == ExplosionEffect->GetCurrentFrame())
	{
		std::shared_ptr<GameEngineCollision> ExploCol = ExplosionCol->Collision((int)CollisionOrder::Player, ColType::SPHERE2D, ColType::AABBBOX2D);

		if (nullptr != ExploCol)
		{
			IsExplosionAttackEnd = true;

			std::shared_ptr<Player> CastPtr = ExploCol->GetActor()->DynamicThis<Player>();

			if (nullptr == CastPtr)
			{
				MsgAssert_Rtti<RookieHero>(" - 플레이어만 Player Col Order를 가질 수 있습니다.");
				return;
			}

			EffectManager::PlayEffect({
				.EffectName = "HitNormal",
				.Position = CastPtr->GetTransform()->GetWorldPosition() + float4(0, 40, 0),
				.AddSetZ = -10.0f });

			float4 PlayerDir = CastPtr->GetTransform()->GetWorldPosition() - GetTransform()->GetWorldPosition();

			if (0.0f > PlayerDir.x)
			{
				CastPtr->HitPlayer(Data.Attack, float4(-300, 500));
			}
			else
			{
				CastPtr->HitPlayer(Data.Attack, float4(300, 500));
			}
		}		

		ExplosionEffect = nullptr;
	}

	if (2.0f <= ExplosionTime)
	{
		BossFsm.ChangeState("Idle");
	}
}

void RookieHero::Explosion_End()
{
	IsHitEffectOff = false;
}

void RookieHero::Ultimate_Enter()
{
	PlayAnimation("ExplosionReady");
	UltimateLiveTime = 0.0f;
	HitDamageCheck = 0.0f;
	IsUltimateShotReady = false;
	IsUltimateShot = false;

	UltimateLightOn();
}

void RookieHero::Ultimate_Update(float _DeltaTime)
{
	UltimateLiveTime += _DeltaTime;

	if (false == IsUltimateShotReady && 
		false == IsUltimateShot && 
		true == Render->IsAnimationEnd())
	{
		PlayAnimation("Explosion", false);
	}

	if (false == IsUltimateShotReady && 100.0f <= HitDamageCheck)
	{
		BossFsm.ChangeState("Groggy");
		UltimateLightOff();
	}

	if (false == IsUltimateShotReady && 4.0f <= UltimateLiveTime)
	{
		std::shared_ptr<Player> PlayerActor = FindPlayer.lock();

		if (nullptr != PlayerActor)
		{
			float4 Dir = PlayerActor->GetTransform()->GetWorldPosition() - GetTransform()->GetWorldPosition();

			if (0.0f > Dir.x)
			{
				SetViewDir(ActorViewDir::Left);
			}
			else
			{
				SetViewDir(ActorViewDir::Right);
			}
		}

		PlayAnimation("SwordEnergyReady");
		IsUltimateShotReady = true;
		UltimateLightOff();
	}

	if (false == IsUltimateShot && 
		true == IsUltimateShotReady && 
		true == Render->IsAnimationEnd())
	{
		UltimateFadeOn();

		IsUltimateShotReady = true;
		IsUltimateShot = true;
		PlayAnimation("SwordEnergy", false);
	}

	if (true == IsUltimateShot && true == Render->IsAnimationEnd())
	{
		BossFsm.ChangeState("Idle");
	}
}

void RookieHero::Ultimate_End()
{

}

