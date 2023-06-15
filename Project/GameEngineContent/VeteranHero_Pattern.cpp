#include "PrecompileHeader.h"
#include "VeteranHero.h"
#include "Player.h"
#include "Projectile.h"
#include "VeteranHeroEnergyBall.h"

void VeteranHero::ComboAttack_Enter()
{
	ComboAttackIndex = 0;
	LookPlayer();

	AttackCheck.SetEvent([this](std::shared_ptr<BaseContentActor> _Ptr, const AttackColMetaData& _Data)
		{
			std::shared_ptr <Player> CastPtr = std::static_pointer_cast<Player>(_Ptr);

			if (nullptr == CastPtr)
			{
				MsgAssert_Rtti<VeteranHero>(" - 플레이어만 Player Col Order를 가질 수 있습니다.");
				return;
			}

			EffectManager::PlayEffect({
				.EffectName = "HitSlashEffect",
				.Position = CastPtr->GetTransform()->GetWorldPosition() + float4(0, 40, 0),
				.AddSetZ = -10.0f });

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

void VeteranHero::ComboAttack_Update(float _DeltaTime)
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

			std::shared_ptr<Projectile> ShotProjectile = GetLevel()->CreateActor<Projectile>();

			float4 Pivot = float4::Zero;
			float4 ShotDir = float4::Zero;

			switch (Dir)
			{
			case ActorViewDir::Left:
				Pivot = float4(-50, 47, 0);
				ShotDir = float4::Left;
				break;
			case ActorViewDir::Right:
				Pivot = float4(50, 47, 0);
				ShotDir = float4::Right;
				break;
			}

			std::function<void(std::shared_ptr<class BaseContentActor>, ProjectileHitParameter _Parameter)> HitCallback =
				[](std::shared_ptr<class BaseContentActor> _ColActor, ProjectileHitParameter _Parameter)
			{
				std::shared_ptr<Player> CastingPtr = _ColActor->DynamicThis<Player>();

				if (nullptr == CastingPtr)
				{
					MsgAssert_Rtti<VeteranHero>(" - 플레이어 클래스만 Player ColOrder를 가질 수 있습니다");
					return;
				}

				CastingPtr->HitPlayer(_Parameter.Attack, _Parameter.AttackDir * 500.0f);

				EffectManager::PlayEffect({
					.EffectName = "HitNormal",
					.Position = _Parameter.ProjectilePos });
			};

			ShotProjectile->ShotProjectile({
				.EffectName = "VeteranHero_ComboWave",
				.Pos = GetTransform()->GetWorldPosition() + Pivot,
				.Dir = ShotDir,
				.ColScale = float4(50, 60, 1),
				.ColOrder = (int)CollisionOrder::Player,
				.ProjectileColType = ColType::AABBBOX2D,
				.IsPlatformCol = false,
				.IsRot = false,
				.IsFlipX = Dir == ActorViewDir::Left,
				.Damage = Data.Attack * 2.0f,
				.Speed = 1000.0f,
				.LiveTime = 0.64f,
				.EnterEvent = HitCallback});
		}
	}
}

void VeteranHero::ComboAttack_End()
{
}

void VeteranHero::EnergyBall_Enter()
{
	LookPlayer();
	PlayAnimation("EnergyBallReady");
	IsEnergyBallShot = false;

	switch (Dir)
	{
	case ActorViewDir::Left:
		EnergyBallReady(130);
		EnergyBallReady(180);
		EnergyBallReady(230);
		break;
	case ActorViewDir::Right:
		EnergyBallReady(-50);
		EnergyBallReady(0);
		EnergyBallReady(50);
		break;
	}
}

void VeteranHero::EnergyBall_Update(float _DeltaTime)
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

			switch (Dir)
			{
			case ActorViewDir::Left:
				EnergyBallShot(130, 2.6f);
				EnergyBallShot(180, 3.0f);
				EnergyBallShot(230, 3.4f);
				break;
			case ActorViewDir::Right:
				EnergyBallShot(-50, 2.6f);
				EnergyBallShot(0, 3.0f);
				EnergyBallShot(50, 3.4f);
				break;
			}
		}
	}
}

void VeteranHero::EnergyBall_End()
{

}

void VeteranHero::EnergyBallReady(float _Rot)
{
	float4 Pivot = float4::Zero;
	Pivot = float4(0, 75, 0);

	float4 Dir = float4::Right * 50.0f;
	Dir.RotaitonZDeg(_Rot);

	Pivot += Dir;

	std::shared_ptr<EffectActor> Effect = EffectManager::PlayEffect({
	.EffectName = "RookieHero_EnergyBallShot",
	.Position = GetTransform()->GetWorldPosition() + Pivot,
	.AddSetZ = 10.0f,
	.FlipX = Pivot.x < 0});

	if (Pivot.x < 0)
	{
		Effect->GetTransform()->SetLocalRotation(float4(0, 0, _Rot - 180));
	}
	else
	{
		Effect->GetTransform()->SetLocalRotation(float4(0, 0, _Rot));
	}
}

void VeteranHero::EnergyBallShot(float _Rot, float _LiveTime)
{
	std::shared_ptr<VeteranHeroEnergyBall> ShotProjectile = GetLevel()->CreateActor<VeteranHeroEnergyBall>();

	float4 Pivot = float4(0, 75, 0);

	float4 ShotDir = float4::Right * 50.0f;
	ShotDir.RotaitonZDeg(_Rot);

	Pivot += ShotDir;

	std::function<void(std::shared_ptr<class BaseContentActor>, ProjectileHitParameter _Parameter)> HitCallback =
		[](std::shared_ptr<class BaseContentActor> _ColActor, ProjectileHitParameter _Parameter)
	{
		std::shared_ptr<Player> CastingPtr = _ColActor->DynamicThis<Player>();

		if (nullptr == CastingPtr)
		{
			MsgAssert_Rtti<VeteranHero>(" - 플레이어 클래스만 Player ColOrder를 가질 수 있습니다");
			return;
		}
		CastingPtr->GetContentLevel()->GetCamCtrl().CameraShake(4, 20, 3);
		CastingPtr->HitPlayer(_Parameter.Attack, _Parameter.AttackDir * 800.0f);

		EffectManager::PlayEffect({
			.EffectName = "RookieHero_EnergyBallExplosion_Large",
			.Position = _Parameter.ProjectilePos });
	};

	std::function<void(const float4& _Pos)> DeathCallback = [](const float4& _Pos)
	{
		EffectManager::PlayEffect({
			.EffectName = "RookieHero_EnergyBallExplosion_Large",
			.Position = _Pos });
	};

	ShotProjectile->ShotProjectile({
		.EffectName = "VeteranHero_EnergyBall",
		.TrackingTarget = FindPlayer.lock(),
		.Pos = GetTransform()->GetWorldPosition() + Pivot,
		.Dir = ShotDir.NormalizeReturn() * 300.0f,
		.ColScale = float4(50, 50, 1),
		.TrackingPivot = float4(0, 60, 0),
		.ColOrder = (int)CollisionOrder::Player,
		.IsPlatformCol = false,
		.IsColDeath = true,
		.IsRot = false,
		.Damage = Data.Attack,
		.Speed = 600.0f,
		.LiveTime = _LiveTime,
		.TrackingSpeed = 1350.0f,
		.EnterEvent = HitCallback,
		.DeathEvent = DeathCallback, });
}

void VeteranHero::Explosion_Enter()
{
	PlayAnimation("ExplosionReady");

	IsExplosion = false;
	IsExplosionEffect = false;
	IsExplosionChargeEffect = false;

	ExplosionTime = 0.0f;
	IsHitEffectOff = true;
	IsExplosionAttackEnd = false;

	PlayerChargeHitTime = 0.0f;

	ExplosionChargeCol->On();
	ExplosionChargeProgress = 0.0f;
}

void VeteranHero::Explosion_Update(float _DeltaTime)
{
	PlayerChargeHitTime += _DeltaTime;

	if (true == Render->IsAnimationEnd())
	{
		IsExplosionEffect = true;
		PlayAnimation("Explosion", false);
	}

	if (false == IsExplosionChargeEffect && 2 == Render->GetCurrentFrame())
	{
		IsExplosionChargeEffect = true;

		EffectManager::PlayEffect({
			.EffectName = "VeteranHero_EnergyCharging",
			.Position = GetTransform()->GetWorldPosition() + float4(0, 170, 0) });
	}

	if (true == IsExplosionChargeEffect && 1.0f > ExplosionChargeProgress)
	{
		ExplosionChargeProgress += _DeltaTime * 0.5f;
		ExplosionChargeDamageCoolTime += _DeltaTime;

		ExplosionCol->On();
		ExplosionCol->GetTransform()->SetLocalScale(
			float4::LerpClamp(ExplosionChargeScaleStart, ExplosionChargeScaleEnd, ExplosionChargeProgress));

		if (0.0f < ExplosionChargeDamageCoolTime)
		{	
			std::shared_ptr<GameEngineCollision> ExploCol = ExplosionCol->Collision((int)CollisionOrder::Player, ColType::SPHERE2D, ColType::AABBBOX2D);

			if (nullptr != ExploCol)
			{
				ExplosionChargeDamageCoolTime = -0.2f;
				std::shared_ptr<Player> CastingPtr = ExploCol->GetActor()->DynamicThis<Player>();

				if (nullptr == CastingPtr)
				{
					MsgAssert_Rtti<VeteranHero>(" - 플레이어 클래스만 Player ColOrder를 가질 수 있습니다");
					return;
				}

				float4 HitDir = CastingPtr->GetTransform()->GetWorldPosition() - GetTransform()->GetWorldPosition();

				CastingPtr->HitPlayer(Data.Attack * 0.1f, float4::Zero);

				EffectManager::PlayEffect({
					.EffectName = "HitNormal",
					.Position = CastingPtr->GetTransform()->GetWorldPosition() 
					+ float4(GameEngineRandom::MainRandom.RandomFloat(-20, 20),
						50 + GameEngineRandom::MainRandom.RandomFloat(-20, 20))});

			}
		}
	}
	else
	{
		ExplosionCol->Off();
	}

	if (true == IsExplosionEffect)
	{
		ExplosionTime += _DeltaTime;
	}

	if (false == IsExplosion && 1.7f <= ExplosionTime)
	{
		IsHitEffectOff = false;
		IsExplosion = true;

		GetContentLevel()->GetCamCtrl().CameraShake(10, 30, 9);

		ExplosionEffect = EffectManager::PlayEffect({
			.EffectName = "VeteranHero_Explosion",
			.Position = GetTransform()->GetWorldPosition() + float4(0, 200, 0),
			.AddSetZ = -10.0f });
	}

	if (false == IsExplosionAttackEnd &&
		nullptr != ExplosionEffect && 4 == ExplosionEffect->GetCurrentFrame())
	{
		ExplosionCol->On();
		std::shared_ptr<GameEngineCollision> ExploCol = ExplosionCol->Collision((int)CollisionOrder::Player, ColType::SPHERE2D, ColType::AABBBOX2D);

		if (nullptr != ExploCol)
		{
			IsExplosionAttackEnd = true;

			std::shared_ptr<Player> CastPtr = ExploCol->GetActor()->DynamicThis<Player>();

			if (nullptr == CastPtr)
			{
				MsgAssert_Rtti<VeteranHero>(" - 플레이어만 Player Col Order를 가질 수 있습니다.");
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

	if (2.4f <= ExplosionTime)
	{
		BossFsm.ChangeState("Idle");
	}
}

void VeteranHero::Explosion_End()
{
	ExplosionChargeCol->Off();
	ExplosionCol->Off();
	IsHitEffectOff = false;
}

void VeteranHero::Ultimate_Enter()
{
	PlayAnimation("ExplosionReady");
	UltimateLiveTime = 0.0f;
	HitDamageCheck = 0.0f;
	IsUltimateShotReady = false;
	IsUltimateShot = false;

	IsUltimateComplete = false;

	UltimateLightOn();
}

void VeteranHero::Ultimate_Update(float _DeltaTime)
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
		return;
	}

	if (false == IsUltimateShot &&
		true == IsUltimateShotReady &&
		true == Render->IsAnimationEnd())
	{
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
				MsgAssert_Rtti<VeteranHero>(" - 플레이어 클래스만 Player ColOrder를 가질 수 있습니다");
				return;
			}

			CastingPtr->HitPlayer(_Parameter.Attack, _Parameter.AttackDir * 500.0f);

			EffectManager::PlayEffect({
				.EffectName = "RookieHero_EnergyBallExplosion",
				.Position = _Parameter.ProjectilePos });
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
			.IsPlatformCol = false,
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

void VeteranHero::Ultimate_End()
{

}