#include "PrecompileHeader.h"
#include "RookieHero.h"
#include "Player.h"
#include "Projectile.h"
#include "BattleActorHealFont.h"

void RookieHero::ComboAttack_Enter()
{
	ComboAttackIndex = 0;
	LookPlayer();

	AttackCheck.SetEvent([this](std::shared_ptr<BaseContentActor> _Ptr, const AttackColMetaData& _Data)
		{
			std::shared_ptr <Player> CastPtr = std::static_pointer_cast<Player>(_Ptr);

			if (nullptr == CastPtr)
			{
				MsgAssert_Rtti<RookieHero>(" - 플레이어만 Player Col Order를 가질 수 있습니다.");
				return;
			}

			GameEngineSound::Play("Hit_Sword_Large.wav");

			EffectManager::PlayEffect({
				.EffectName = "HitSlashEffect",
				.Position = CastPtr->GetTransform()->GetWorldPosition() + float4(0, 40, 0),
				.AddSetZ = -10.0f});

			switch (Dir)
			{
			case ActorViewDir::Left:
				CastPtr->HitPlayer(Data.Attack, float4(-250, 400));
				break;
			case ActorViewDir::Right:
				CastPtr->HitPlayer(Data.Attack, float4(250, 400));
				break;
			default:
				break;
			}
		});

	BossRigidbody.SetVelocity(float4::Zero);
	ComboDashCheck = false;

	if (0.0f <= SpeechCoolTime)
	{
		PlaySpeechBubble("더러운 마족 놈들!", 4.0f);
		SpeechCoolTime = -10.0f;
	}
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

		GameEngineSound::Play("AdventurerHero_Voice_Short.wav");
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
				BossRigidbody.SetVelocity(float4::Left * 800.0f);
				break;
			case ActorViewDir::Right:
				BossRigidbody.SetVelocity(float4::Right * 800.0f);
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
				BossRigidbody.SetVelocity(float4::Left * 800.0f);
				break;
			case ActorViewDir::Right:
				BossRigidbody.SetVelocity(float4::Right * 800.0f);
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
				BossRigidbody.SetVelocity(float4::Left * 800.0f);
				break;
			case ActorViewDir::Right:
				BossRigidbody.SetVelocity(float4::Right * 800.0f);
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

	float4 Pivot = float4::Zero;

	switch (Dir)
	{
	case ActorViewDir::Left:
		Pivot = float4(-50, 75, 0);
		break;
	case ActorViewDir::Right:
		Pivot = float4(50, 75, 0);
		break;
	}

	EffectManager::PlayEffect({
	.EffectName = "RookieHero_EnergyBallShot",
	.Position = GetTransform()->GetWorldPosition() + Pivot,
	.AddSetZ = 10.0f,
	.FlipX = Dir == ActorViewDir::Left});

	if (0.0f <= SpeechCoolTime)
	{
		PlaySpeechBubble("받아라!", 4.0f);
		SpeechCoolTime = -10.0f;
	}
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
			GameEngineSound::Play("Atk_Explosion_Small.wav");

			PlayAnimation("EnergyBall");
			IsEnergyBallShot = true;

			std::shared_ptr<Projectile> ShotProjectile = GetLevel()->CreateActor<Projectile>();
			
			float4 Pivot = float4::Zero;
			float4 ShotDir = float4::Zero;

			switch (Dir)
			{
			case ActorViewDir::Left:
				Pivot = float4(-50, 75, 0);
				ShotDir = float4::Left;
				break;
			case ActorViewDir::Right:
				Pivot = float4(50, 75, 0);
				ShotDir = float4::Right;
				break;
			}

			std::function<void(std::shared_ptr<class BaseContentActor>, ProjectileHitParameter _Parameter)> HitCallback =
				[](std::shared_ptr<class BaseContentActor> _ColActor, ProjectileHitParameter _Parameter)
			{
				std::shared_ptr<Player> CastingPtr = _ColActor->DynamicThis<Player>();
				
				if (nullptr == CastingPtr)
				{
					MsgAssert_Rtti<RookieHero>(" - 플레이어 클래스만 Player ColOrder를 가질 수 있습니다");
					return;
				}

				CastingPtr->HitPlayer(_Parameter.Attack, _Parameter.AttackDir * 400.0f);

				EffectManager::PlayEffect({
					.EffectName = "RookieHero_EnergyBallExplosion",
					.Position = _Parameter.ProjectilePos});

				GameEngineSound::Play("Hit_Energy_Small.wav");
			};

			std::function<void(const float4& _Pos)> DeathCallback = [](const float4& _Pos)
			{
				EffectManager::PlayEffect({
					.EffectName = "RookieHero_EnergyBallExplosion",
					.Position = _Pos });

				GameEngineSound::Play("Hit_Energy_Small.wav");
			};

			ShotProjectile->ShotProjectile({
				.EffectName = "RookieHero_EnergyBall",
				.TrackingTarget = FindPlayer.lock(),
				.Pos = GetTransform()->GetWorldPosition() + Pivot,
				.Dir = ShotDir,
				.ColScale = float4(50, 50, 1),
				.TrackingPivot = float4(0, 60, 0),
				.ColOrder = (int)CollisionOrder::Player,
				.IsColDeath = true,
				.IsRot = false,
				.Damage = Data.Attack,
				.Speed = 600.0f,
				.LiveTime = 1.2f,
				.TrackingSpeed = 6.0f,
				.EnterEvent = HitCallback,
				.DeathEvent = DeathCallback, });
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
		GameEngineSound::Play("Adventurer_Drink.wav");

		EffectManager::PlayEffect({
			.EffectName = "MonsterHeal",
			.Position = GetTransform()->GetWorldPosition() + float4(0, 78, 0),
			.AddSetZ = -10.0f});

		PotionHealTime = -0.72f;

		float HealHp = 5.0f;
		HP += HealHp;

		if (HP > Data.HP)
		{
			HP = Data.HP;
		}

		std::shared_ptr<BattleActorHealFont> NewDamageFont = GetLevel()->CreateActor<BattleActorHealFont>();

		float4 FontDir = float4(0, 10, 0);
		float4 FontColor = float4(0.3607f, 0.9215f, 0.0784f, 1);

		NewDamageFont->InitFont({
			.Damage = HealHp,
			.FontSize = 30,
			.FontColor = FontColor,
			.Pos = GetTransform()->GetWorldPosition() + float4(0, 50, -100) + DamageFontPivot,
			.Dir = FontDir,
			.MoveSpeed = 300,
			.RandX = 30.0f,
			.LiveTime = 0.55f,
			});
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

	if (0.0f <= SpeechCoolTime)
	{
		PlaySpeechBubble("칼레온을 위하여!", 4.0f);
		SpeechCoolTime = -10.0f;
	}

	GameEngineSound::Play("AdventurerHero_Voice_Short.wav");
}

void RookieHero::Explosion_Update(float _DeltaTime)
{
	if (false == IsExplosionEffect && true == Render->IsAnimationEnd())
	{
		IsExplosionEffect = true;
		PlayAnimation("Explosion", false);

		GameEngineSound::Play("AdventurerHero_EndAction_AttackReady.wav");
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

		GameEngineSound::Play("Atk_Explosion_Large.wav");
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

			GameEngineSound::Play("Hit_Energy_Medium.wav");

			EffectManager::PlayEffect({
				.EffectName = "HitNormal",
				.Position = CastPtr->GetTransform()->GetWorldPosition() + float4(0, 40, 0),
				.AddSetZ = -10.0f });

			float4 PlayerDir = CastPtr->GetTransform()->GetWorldPosition() - GetTransform()->GetWorldPosition();

			if (0.0f > PlayerDir.x)
			{
				CastPtr->HitPlayer(Data.Attack, float4(-250, 400));
			}
			else
			{
				CastPtr->HitPlayer(Data.Attack, float4(250, 400));
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

	IsUltimateComplete = false;

	UltimateLightOn();
	GameEngineSound::Play("AdventurerHero_Voice_Casting.wav");
	ChargeSound = GameEngineSound::Play("Adventurer_Charge_Start.wav");
}

void RookieHero::Ultimate_Update(float _DeltaTime)
{
	UltimateLiveTime += _DeltaTime;

	if (false == IsUltimateShot && (nullptr == UltimateAuraEffect || true == UltimateAuraEffect->IsAnimationEnd()))
	{
		UltimateAuraEffect = EffectManager::PlayEffect({
			.EffectName = "RookieHero_UltimateAura",
			.Position = GetTransform()->GetWorldPosition() + float4(0, 80, 0),
			.AddSetZ = 0.0f });
	}

	if (false == IsUltimateShot && (nullptr == UltimateSmokeEffect || true == UltimateSmokeEffect->IsAnimationEnd()))
	{
		UltimateSmokeEffect = EffectManager::PlayEffect({
			.EffectName = "RookieHero_UltimateSmoke",
			.Position = GetTransform()->GetWorldPosition() + float4(0, 30, 0),
			.AddSetZ = -10.0f });
	}

	if (false == IsUltimateShotReady && 
		false == IsUltimateShot && 
		true == Render->IsAnimationEnd())
	{
		PlayAnimation("Explosion", false);
	}

	if (false == IsUltimateShotReady && 100.0f <= HitDamageCheck)
	{
		if (true == ChargeSound.IsValid())
		{
			ChargeSound.Stop();
			ChargeSound.Clear();
		}

		EffectManager::PlayEffect({
			.EffectName = "RookieHero_UltimateFail",
			.Position = GetTransform()->GetWorldPosition() + float4(0, 80, 0),
			.AddSetZ = -20.0f });

		BossFsm.ChangeState("Groggy");
		UltimateLightOff();
		return;
	}

	if (false == IsUltimateComplete && 3.5f <= UltimateLiveTime)
	{
		IsUltimateComplete = true;

		EffectManager::PlayEffect({
			.EffectName = "RookieHero_UltimateComplete",
			.Position = GetTransform()->GetWorldPosition() + float4(0, 80, 0),
			.AddSetZ = -20.0f });

		GameEngineSound::Play("Adventurer_Charge_End.wav");
		ChargeSound.Clear();
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

		PlaySpeechBubble("이제 끝이다! 더 이상 용서하지 않겠어!", 4.0f);
		SpeechCoolTime = -10.0f;

		PlayAnimation("SwordEnergyReady");
		IsUltimateShotReady = true;
		UltimateLightOff();
		return;
	}

	if (false == IsUltimateShot && 
		true == IsUltimateShotReady && 
		true == Render->IsAnimationEnd())
	{
		GameEngineSound::Play("AdventurerHero_Voice_SpecialMove.wav");
		GameEngineSound::Play("AdventurerHero_EndAction_AttackReady.wav");
		GameEngineSound::Play("Atk_Smoke_Medium.wav");

		UltimateFadeOn();

		IsUltimateShotReady = true;
		IsUltimateShot = true;
		PlayAnimation("SwordEnergy", false);
			
		std::shared_ptr<Projectile> ShotProjectile = GetLevel()->CreateActor<Projectile>();

		float4 Pivot = float4::Zero;
		float4 ShotDir = float4::Zero;

		switch (Dir)
		{
		case ActorViewDir::Left:
			Pivot = float4(-50, 90, 0);
			ShotDir = float4::Left;
			break;
		case ActorViewDir::Right:
			Pivot = float4(50, 90, 0);
			ShotDir = float4::Right;
			break;
		}

		std::function<void(std::shared_ptr<class BaseContentActor>, ProjectileHitParameter _Parameter)> HitCallback =
			[](std::shared_ptr<class BaseContentActor> _ColActor, ProjectileHitParameter _Parameter)
		{
			std::shared_ptr<Player> CastingPtr = _ColActor->DynamicThis<Player>();

			if (nullptr == CastingPtr)
			{
				MsgAssert_Rtti<RookieHero>(" - 플레이어 클래스만 Player ColOrder를 가질 수 있습니다");
				return;
			}

			CastingPtr->HitPlayer(_Parameter.Attack, _Parameter.AttackDir * 400.0f);

			EffectManager::PlayEffect({
				.EffectName = "RookieHero_EnergyBallExplosion",
				.Position = _Parameter.ProjectilePos });

			GameEngineSound::Play("Hit_Sword_Large.wav");
		};

		std::function<void(const float4& _Pos)> DeathCallback = [](const float4& _Pos)
		{
			EffectManager::PlayEffect({
				.EffectName = "RookieHero_EnergyBallExplosion",
				.Position = _Pos });
		};


		ShotProjectile->ShotProjectile({
			.EffectName = "RookieHero_Ultimate_Projectile",
			.Pos = GetTransform()->GetWorldPosition() + Pivot,
			.Dir = ShotDir,
			.ColScale = float4(100, 100, 1),
			.ColOrder = (int)CollisionOrder::Player,
			.ProjectileColType = ColType::AABBBOX2D,
			.IsRot = false,
			.IsFlipX = Dir == ActorViewDir::Left, 
			.Damage = Data.Attack * 2.0f,
			.Speed = 1200.0f,
			.LiveTime = 3.0f,
			.EnterEvent = HitCallback,
			.DeathEvent = DeathCallback, });
	}

	if (true == IsUltimateShot && true == Render->IsAnimationEnd())
	{
		BossFsm.ChangeState("Idle");
	}
}

void RookieHero::Ultimate_End()
{

}

