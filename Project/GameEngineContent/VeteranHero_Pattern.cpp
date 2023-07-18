#include "PrecompileHeader.h"
#include "VeteranHero.h"
#include "Player.h"
#include "Projectile.h"
#include "VeteranHeroEnergyBall.h"
#include "VeteranHeroMagicSword.h"

void VeteranHero::ComboAttack_Enter()
{
	ComboAttackIndex = 0;
	LookPlayer();

	AttackCheck.SetEvent([this](std::shared_ptr<BaseContentActor> _Ptr, const AttackColMetaData& _Data)
		{
			GameEngineSound::Play("Hit_Sword_Small.wav");

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
		PlaySpeechBubble("적에게 얕보이지 말 것!", 4.0f);
		SpeechCoolTime = -10.0f;
	}
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
				BossRigidbody.SetVelocity(float4::Left * 1100.0f);
				break;
			case ActorViewDir::Right:
				BossRigidbody.SetVelocity(float4::Right * 1100.0f);
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
				BossRigidbody.SetVelocity(float4::Left * 1100.0f);
				break;
			case ActorViewDir::Right:
				BossRigidbody.SetVelocity(float4::Right * 1100.0f);
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
			GameEngineSound::Play("Atk_Sword_Thin.wav");

			ComboDashCheck = true;

			switch (Dir)
			{
			case ActorViewDir::Left:
				BossRigidbody.SetVelocity(float4::Left * 1100.0f);
				break;
			case ActorViewDir::Right:
				BossRigidbody.SetVelocity(float4::Right * 1100.0f);
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
				GameEngineSound::Play("Hit_Sword_Large.wav");

				std::shared_ptr<Player> CastingPtr = _ColActor->DynamicThis<Player>();

				if (nullptr == CastingPtr)
				{
					MsgAssert_Rtti<VeteranHero>(" - 플레이어 클래스만 Player ColOrder를 가질 수 있습니다");
					return;
				}

				CastingPtr->HitPlayer(_Parameter.Attack, _Parameter.AttackDir * 400.0f);

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
				.IsRot = false,
				.IsFlipX = Dir == ActorViewDir::Left,
				.Damage = Data.Attack,
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

	GameEngineSound::Play("AdventurerHero_EnergyBall.wav");

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

	if (0.0f <= SpeechCoolTime)
	{
		PlaySpeechBubble("받아라!", 4.0f);
		SpeechCoolTime = -10.0f;
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
			GameEngineSound::Play("Atk_Explosion_Small.wav");

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
		CastingPtr->HitPlayer(_Parameter.Attack, _Parameter.AttackDir * 400.0f);

		EffectManager::PlayEffect({
			.EffectName = "RookieHero_EnergyBallExplosion_Large",
			.Position = _Parameter.ProjectilePos });

		SoundDoubleCheck::Play("Hit_Energy_Small.wav");
	};

	ContentLevel* Level = GetContentLevel();

	std::function<void(const float4& _Pos)> DeathCallback = [Level](const float4& _Pos)
	{
		Level->GetCamCtrl().CameraShake(4, 20, 3);
		EffectManager::PlayEffect({
			.EffectName = "RookieHero_EnergyBallExplosion_Large",
			.Position = _Pos });
	};

	ShotProjectile->ShotProjectile({
		.EffectName = "VeteranHero_EnergyBall",
		.TrackingTarget = FindPlayer,
		.Pos = GetTransform()->GetWorldPosition() + Pivot,
		.Dir = ShotDir.NormalizeReturn() * 300.0f,
		.ColScale = float4(50, 50, 1),
		.TrackingPivot = float4(0, 60, 0),
		.ColOrder = (int)CollisionOrder::Player,
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

	Buffer.Color = float4(0, 0, 0, 1);

	if (0.0f <= SpeechCoolTime)
	{
		PlaySpeechBubble("떨어져!", 4.0f);
		SpeechCoolTime = -10.0f;
	}
	IsExplosionSound = false;
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

		GameEngineSound::Play("AdventurerHero_EnergyBlast_Charging.wav");

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
		if (false == IsExplosionSound)
		{
			GameEngineSound::Play("Atk_Explosion_Large.wav");
			IsExplosionSound = true;
		}

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
				CastPtr->HitPlayer(Data.Attack, float4(-250, 400));
			}
			else
			{
				CastPtr->HitPlayer(Data.Attack, float4(250, 400));
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

void VeteranHero::Stinger_Enter()
{
	LookPlayer();
	PlayAnimation("StingerReady");
	IsStingerReadyEnd = false;
	IsStingerEnd = false;
	IsStingerAttackEffect = false;
	IsStingerAttackHit = false;
	IsStingerSwordHit = false;

	PrevRigdFricCoeff = BossRigidbody.GetFricCoeff();
	BossRigidbody.SetFricCoeff(3000.0f);
	BossRigidbody.SetActiveGravity(false);

	if (0.0f <= SpeechCoolTime)
	{
		PlaySpeechBubble("용사 검술, 제 2장!", 4.0f);
		SpeechCoolTime = -10.0f;
	}

	GameEngineSound::Play("AdventurerHero_EndAction_AttackReady.wav");
	GameEngineSound::Play("AdventurerHero_Voice_Short.wav");
}

void VeteranHero::Stinger_Update(float _DeltaTime)
{
	if (false == IsStingerReadyEnd && Render->IsAnimationEnd())
	{
		StingerAttackCol->On();

		GameEngineSound::Play("AdventurerHero_Stinger.wav");
		GameEngineSound::Play("AdventurerHero_Voice_SpecialMove.wav");

		StingerEffect = EffectManager::PlayEffect({
			.EffectName = "VeteranHero_Stinger",
			.Position = GetTransform()->GetWorldPosition() + float4(0, 40, 0),
			.Triger = EffectDeathTrigger::Time,
			.Time = 1.0f,
			.FlipX = Dir == ActorViewDir::Left,
			});

		StingerEffect->GetTransform()->SetParent(GetTransform());

		switch (Dir)
		{
		case ActorViewDir::Left:
			BossRigidbody.SetVelocity(float4::Left * 2000.0f);
			break;
		case ActorViewDir::Right:
			BossRigidbody.SetVelocity(float4::Right * 2000.0f);
			break;
		}

		PlayAnimation("Stinger");
		IsStingerReadyEnd = true;
	}

	if (true == IsStingerReadyEnd && false == IsStingerEnd)
	{
		BossRigidbody.UpdateForce(_DeltaTime);

		float4 Vel = BossRigidbody.GetVelocity();
		float4 CurDashVel = BossRigidbody.GetVelocity() * _DeltaTime;

		RigidbodyMovePlatformCheck(CurDashVel);
		GetTransform()->AddLocalPosition(CurDashVel);

		if (false == IsStingerAttackHit)
		{
			std::shared_ptr<GameEngineCollision> StingerCol = StingerAttackCol->Collision((int)CollisionOrder::Player, ColType::SPHERE2D, ColType::AABBBOX2D);

			if (nullptr != StingerCol)
			{
				std::shared_ptr<Player> CastPtr = StingerCol->GetActor()->DynamicThis<Player>();

				if (nullptr == CastPtr)
				{
					MsgAssert_Rtti<VeteranHero>(" - 플레이어만 Player Col Order를 가질 수 있습니다.");
					return;
				}

				float4 PlayerDir = CastPtr->GetTransform()->GetWorldPosition() - GetTransform()->GetWorldPosition();

				if (0.0f > PlayerDir.x)
				{
					CastPtr->HitPlayer(Data.Attack, float4(-250, 400));
				}
				else
				{
					CastPtr->HitPlayer(Data.Attack, float4(250, 400));
				}

				IsStingerAttackHit = true;
			}
		}

		if (nullptr != StingerEffect && 700.0f >= Vel.Size())
		{
			StingerEffect->IsFadeDeathOn(1.0f);
			StingerEffect = nullptr;
		}

		if (5.0f >= Vel.Size())
		{
			IsStingerEnd = true;
			LookPlayer();
			PlayAnimation("AttackB");
			StingerAttackCol->Off();
		}

		//VeteranHero_StingerSlash
	}

	if (false == IsStingerSwordHit &&
		true == IsStingerEnd &&  1 == Render->GetCurrentFrame())
	{
		StingerSwordAttackCol->On();
		std::shared_ptr<GameEngineCollision> SwrodCol = StingerSwordAttackCol->Collision((int)CollisionOrder::Player, ColType::SPHERE2D, ColType::AABBBOX2D);

		if (nullptr != SwrodCol)
		{
			GameEngineSound::Play("Hit_Sword_Large.wav");

			std::shared_ptr<Player> CastPtr = SwrodCol->GetActor()->DynamicThis<Player>();

			if (nullptr == CastPtr)
			{
				MsgAssert_Rtti<VeteranHero>(" - 플레이어만 Player Col Order를 가질 수 있습니다.");
				return;
			}

			float4 PlayerDir = CastPtr->GetTransform()->GetWorldPosition() - GetTransform()->GetWorldPosition();

			if (0.0f > PlayerDir.x)
			{
				CastPtr->HitPlayer(Data.Attack, float4(-250, 400));
			}
			else
			{
				CastPtr->HitPlayer(Data.Attack, float4(250, 400));
			}

			IsStingerSwordHit = true;
		}
	}
	else
	{
		StingerSwordAttackCol->Off();
	}

	if (false == IsStingerAttackEffect && 
		true == IsStingerEnd && 1 == Render->GetCurrentFrame())
	{
		IsStingerAttackEffect = true;

		float4 Pivot = float4::Zero;

		switch (Dir)
		{
		case ActorViewDir::Left:
			Pivot = float4(0, 60, 0);
			break;
		case ActorViewDir::Right:
			Pivot = float4(0, 60, 0);
			break;
		}

		GameEngineSound::Play("AdventurerHero_StingerSword.wav");

		StingerEffect = EffectManager::PlayEffect({
			.EffectName = "VeteranHero_StingerSlash",
			.Position = GetTransform()->GetWorldPosition() + Pivot,
			.FlipX = Dir == ActorViewDir::Left,});
	}

	if (true == IsStingerEnd && true == Render->IsAnimationEnd())
	{
		BossFsm.ChangeState("Idle");
	}
}

void VeteranHero::Stinger_End()
{
	BossRigidbody.SetFricCoeff(PrevRigdFricCoeff);
	BossRigidbody.SetActiveGravity(true);
	StingerSwordAttackCol->Off();
}

void VeteranHero::SwordWave_Enter()
{
	LookPlayer();
	PlayAnimation("AttackA_Ready");

	float4 Pivot = float4::Zero;

	switch (Dir)
	{
	case ActorViewDir::Left:
		Pivot = float4(50, 40, 0);
		break;
	case ActorViewDir::Right:
		Pivot = float4(-50, 40, 0);
		break;
	}

	StingerEffect = EffectManager::PlayEffect({
		.EffectName = "VeteranHero_WaveReady",
		.Position = GetTransform()->GetWorldPosition() + Pivot,
		.FlipX = Dir == ActorViewDir::Left, });

	SwordWaveCombo = 0;

	if (0.0f <= SpeechCoolTime)
	{
		PlaySpeechBubble("한발 한발에 진심 담기!", 4.0f);
		SpeechCoolTime = -10.0f;
	}

	GameEngineSound::Play("AdventurerHero_ComboD.wav");
}

void VeteranHero::SwordWave_Update(float _DeltaTime)
{
	if (0 == SwordWaveCombo && true == Render->IsAnimationEnd())
	{
		SworWaveShot();
		PlayAnimation("AttackA", true, 5);
		++SwordWaveCombo;
	}

	if (1 == SwordWaveCombo && true == Render->IsAnimationEnd())
	{
		SworWaveShot();
		PlayAnimation("AttackB");
		++SwordWaveCombo;
	}

	if (2 == SwordWaveCombo && true == Render->IsAnimationEnd())
	{
		BossFsm.ChangeState("Idle");
	}
}

void VeteranHero::SwordWave_End()
{

}

void VeteranHero::SworWaveShot()
{
	GameEngineSound::Play("Atk_Sword_Thin.wav");

	std::shared_ptr<Projectile> ShotProjectile = GetLevel()->CreateActor<Projectile>();

	float4 Pivot = float4::Zero;
	float4 ShotDir = float4::Zero;

	switch (Dir)
	{
	case ActorViewDir::Left:
		Pivot = float4(-50, 85, 0);
		ShotDir = float4::Left;
		break;
	case ActorViewDir::Right:
		Pivot = float4(50, 85, 0);
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

		GameEngineSound::Play("Hit_Sword_Large.wav");

		CastingPtr->HitPlayer(_Parameter.Attack, _Parameter.AttackDir * 300.0f);

		EffectManager::PlayEffect({
			.EffectName = "HitNormal",
			.Position = _Parameter.ProjectilePos });
	};

	ShotProjectile->ShotProjectile({
		.EffectName = "VeteranHero_Wave",
		.Pos = GetTransform()->GetWorldPosition() + Pivot,
		.Dir = ShotDir,
		.ColScale = float4(80, 150, 1),
		.ColOrder = (int)CollisionOrder::Player,
		.ProjectileColType = ColType::AABBBOX2D, 
		.IsRot = false,
		.IsFlipX = Dir == ActorViewDir::Left,
		.Damage = Data.Attack,
		.Speed = 1000.0f,
		.LiveTime = 1.5f,
		.EnterEvent = HitCallback });

	ShotProjectile->ColDebugOn();
}

void VeteranHero::JumpAttack_Enter()
{
	LookPlayer();
	PauseTimes["SwordEnergyReady"][2] = 0;
	PlayAnimation("SwordEnergyReady");
	IsJumpAttackStart = false;
	IsJumpAttackEnd = false;
	IsJumpAttackUp = false;
	IsJumpAttackLandSmoke = false;

	PrevRigdGravity = BossRigidbody.GetGravity();
	BossRigidbody.SetVelocity(float4::Zero);

	if (0.0f <= SpeechCoolTime)
	{
		PlaySpeechBubble("경험치를 내놔!", 4.0f);
		SpeechCoolTime = -10.0f;
	}
}

void VeteranHero::JumpAttack_Update(float _DeltaTime)
{
	BossRigidbody.UpdateForce(_DeltaTime);

	float4 BossVel = BossRigidbody.GetVelocity();
	float4 CurFreamVel = BossVel * _DeltaTime;

	RigidbodyMovePlatformCheck(CurFreamVel);
	GetTransform()->AddLocalPosition(CurFreamVel);

	if (false == IsJumpAttackStart && true == Render->IsAnimationEnd())
	{
		PlayAnimation("AttackD");
		IsJumpAttackStart = true;
	}

	if (false == IsJumpAttackUp &&
		true == IsJumpAttackStart && 1 == Render->GetCurrentFrame())
	{
		JumpAttackCol->GetTransform()->SetLocalPosition(float4(0, 60, 1));
		JumpAttackCol->GetTransform()->SetLocalScale(float4(245, 265, 1));
		JumpAttackCol->On();

		std::shared_ptr<GameEngineCollision> PlayerCol = JumpAttackCol->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D);

		if (nullptr != PlayerCol)
		{
			std::shared_ptr<Player> CastingPtr = PlayerCol->GetActor()->DynamicThis<Player>();

			if (nullptr == CastingPtr)
			{
				MsgAssert_Rtti<VeteranHero>(" - 플레이어 클래스만 Player ColOrder를 가질 수 있습니다");
				return;
			}

			switch (Dir)
			{
			case ActorViewDir::Left:
				CastingPtr->HitPlayer(Data.Attack, float4(-250, 400));
				break;
			case ActorViewDir::Right:
				CastingPtr->HitPlayer(Data.Attack, float4(250, 400));
				break;
			default:
				break;
			}

			EffectManager::PlayEffect({
			.EffectName = "HitNormal",
			.Position = CastingPtr->GetTransform()->GetWorldPosition()
			+ float4(GameEngineRandom::MainRandom.RandomFloat(-20, 20),
				50 + GameEngineRandom::MainRandom.RandomFloat(-20, 20)) });
		}		

		GameEngineSound::Play("Atk_Sword_Large (Slash Up).wav");

		GetTransform()->AddLocalPosition(float4(0, 5, 0));
		switch (Dir)
		{
		case ActorViewDir::Left:
			BossRigidbody.SetVelocity(float4(-1200, 1800));
			break;
		case ActorViewDir::Right:
			BossRigidbody.SetVelocity(float4(1200, 1800));
			break;
		}

		IsJumpAttackUp = true;
	}
	else
	{
		JumpAttackCol->Off();
	}

	if (false == IsJumpAttackEnd && 
		true == IsJumpAttackStart && true == Render->IsAnimationEnd())
	{
		BossRigidbody.SetMaxSpeed(6000);
		BossRigidbody.SetGravity(-100000.0f);
		BossRigidbody.SetVelocity(float4(0, -3000));
		PlayAnimation("AttackE");
		IsJumpAttackEnd = true;
	}

	if (false == IsJumpAttackLandSmoke && true == IsJumpAttackEnd &&
		true == IsGroundUp)
	{
		GameEngineSound::Play("Hit_Sword_Large.wav");
		GameEngineSound::Play("AdventurerHero_Voice_SpecialMove.wav");

		JumpAttackCol->GetTransform()->SetLocalPosition(float4(0, 40, 0));
		JumpAttackCol->GetTransform()->SetLocalScale(float4(300, 80, 1));
		JumpAttackCol->On();

		std::shared_ptr<GameEngineCollision> PlayerCol = JumpAttackCol->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D);

		if (nullptr != PlayerCol)
		{
			std::shared_ptr<Player> CastingPtr = PlayerCol->GetActor()->DynamicThis<Player>();

			if (nullptr == CastingPtr)
			{
				MsgAssert_Rtti<VeteranHero>(" - 플레이어 클래스만 Player ColOrder를 가질 수 있습니다");
				return;
			}

			float4 PlayerDir = CastingPtr->GetTransform()->GetWorldPosition() - GetTransform()->GetWorldPosition();

			if (0.0f > PlayerDir.x)
			{
				CastingPtr->HitPlayer(Data.Attack, float4(-250, 400));
			}
			else
			{
				CastingPtr->HitPlayer(Data.Attack, float4(250, 400));
			}

			GameEngineSound::Play("Hit_Sword_Large.wav");

			EffectManager::PlayEffect({
			.EffectName = "HitNormal",
			.Position = CastingPtr->GetTransform()->GetWorldPosition()
			+ float4(GameEngineRandom::MainRandom.RandomFloat(-20, 20),
				50 + GameEngineRandom::MainRandom.RandomFloat(-20, 20)) });
		}

		float4 SmokePos = GetTransform()->GetWorldPosition();
		SmokePos.y = GroundY;

		EffectManager::PlayEffect({
			.EffectName = "VeteranHero_LandingSmoke_Small",
			.Position = SmokePos + float4(-90, 50)});

		EffectManager::PlayEffect({
			.EffectName = "VeteranHero_LandingSmoke_Small",
			.Position = SmokePos + float4(90, 50),
			.FlipX = true});



		IsJumpAttackLandSmoke = true;
	}
	else
	{
		JumpAttackCol->Off();
	}

	if (true == IsJumpAttackEnd && true == Render->IsAnimationEnd())
	{
		BossFsm.ChangeState("Idle");
	}
}

void VeteranHero::JumpAttack_End()
{
	BossRigidbody.SetVelocity(float4::Zero);
	BossRigidbody.SetMaxSpeed(3000);
	BossRigidbody.SetGravity(PrevRigdGravity);
}

void VeteranHero::LandingAttack_Enter()
{
	LookPlayer();
	PlayAnimation("StingerReady");

	IsLandingUpReady = false;
	IsLandingUpEnd = false;
	IsLandingSignEffect = false;
	IsLandingMagicSwordAttack = false;

	LandingUpTime = 0.0f;
	LandingMagicSwordTime = -1.0f;

	MagicSwordCount = 0;
	MagicSwordInter = float4::Zero;

	if (0.0f <= SpeechCoolTime)
	{
		PlaySpeechBubble("제 2의 초대 용사! 뭔가 이상하지만.", 4.0f);
		SpeechCoolTime = -10.0f;
	}

	GameEngineSound::Play("AdventurerHero_Voice_Casting.wav");
}

void VeteranHero::LandingAttack_Update(float _DeltaTime)
{
	BossRigidbody.UpdateForce(_DeltaTime);

	if (false == IsLandingUpReady && Render->IsAnimationEnd())
	{
		IsLandingUpReady = true;
		PlayAnimation("Jump");

		GameEngineSound::Play("Default_Jump.wav");

		EffectManager::PlayEffect({
			.EffectName = "VeteranHero_JumpSmoke",
			.Position = GetTransform()->GetWorldPosition() + float4(0, 97)});
	}

	if (false == IsLandingUpEnd && true == IsLandingUpReady)
	{
		LandingUpTime += _DeltaTime;
		GetTransform()->AddLocalPosition(float4::Up * _DeltaTime * 2000.0f);
	}
	else
	{
		float4 BossVel = BossRigidbody.GetVelocity();
		float4 CurFreamVel = BossVel * _DeltaTime;

		RigidbodyMovePlatformCheck(CurFreamVel);
		GetTransform()->AddLocalPosition(CurFreamVel);
	}

	if (false == IsLandingSignEffect && 0.8f <= LandingUpTime)
	{
		IsLandingSignEffect = true;

		if (nullptr == FindPlayer)
		{
			LandingAttackPos = GetTransform()->GetWorldPosition();
		}
		else
		{
			LandingAttackPos = FindPlayer->GetTransform()->GetWorldPosition();
		}
			
		LandingAttackPos.y = 2000.0f;
		float HighY = -100000.0f;

		FindLandingCol->On();
		GameEngineTransform* FindColTrans = FindLandingCol->GetTransform();
		FindColTrans->SetWorldPosition(LandingAttackPos);

		std::vector<std::shared_ptr<GameEngineCollision>> PlatformCols;

		if (true == FindLandingCol->CollisionAll((int)CollisionOrder::Platform_Normal, PlatformCols, ColType::AABBBOX2D, ColType::AABBBOX2D))
		{
			for (size_t i = 0; i < PlatformCols.size(); i++)
			{
				GameEngineTransform* ColTrans = PlatformCols[i]->GetTransform();

				float ColY = ColTrans->GetWorldPosition().y + ColTrans->GetWorldScale().hy();

				if (HighY < ColY)
				{
					HighY = ColY;
					LandingAttackPos.y = HighY;
				}
			}
		}

		PlatformCols.clear();

		if (true == FindLandingCol->CollisionAll((int)CollisionOrder::Platform_Half, PlatformCols, ColType::AABBBOX2D, ColType::AABBBOX2D))
		{
			for (size_t i = 0; i < PlatformCols.size(); i++)
			{
				GameEngineTransform* ColTrans = PlatformCols[i]->GetTransform();

				float ColY = ColTrans->GetWorldPosition().y + ColTrans->GetWorldScale().hy();

				if (HighY < ColY)
				{
					HighY = ColY;
					LandingAttackPos.y = HighY;
				}
			}
		}

		FindColTrans->SetWorldPosition(LandingAttackPos);

		LandingSignEffect = EffectManager::PlayEffect({
			.EffectName = "VeteranHero_LandingAttackSign",
			.Position = LandingAttackPos});

		LandingSignEffect->GetTransform()->SetLocalScale(float4(0.8f, 1.0f, 1.0f));

		FindLandingCol->Off();
	}

	if (nullptr != LandingSignEffect && true == LandingSignEffect->IsAnimationEnd())
	{
		IsLandingUpEnd = true;
		LandingSignEffect = nullptr;

		PlayAnimation("AttackE");
		GetTransform()->SetWorldPosition(LandingAttackPos);

		EffectManager::PlayEffect({
			.EffectName = "VeteranHero_LandingSmoke",
			.Position = LandingAttackPos + float4(-100, 70) });

		EffectManager::PlayEffect({
			.EffectName = "VeteranHero_LandingSmoke",
			.Position = LandingAttackPos + float4(100, 70),
			.FlipX = true });

		LandingAttackCol->On();
		std::shared_ptr<GameEngineCollision> PlayerCol = LandingAttackCol->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D);

		GameEngineSound::Play("Hit_Sword_Large.wav");
		GameEngineSound::Play("AdventurerHero_Voice_SpecialMove.wav");

		if (nullptr != PlayerCol)
		{
			std::shared_ptr<Player> CastingPtr = PlayerCol->GetActor()->DynamicThis<Player>();

			if (nullptr == CastingPtr)
			{
				MsgAssert_Rtti<VeteranHero>(" - 플레이어 클래스만 Player ColOrder를 가질 수 있습니다.");
			}

			float4 PlayerDir = CastingPtr->GetTransform()->GetWorldPosition() - GetTransform()->GetWorldPosition();

			if (0.0f > PlayerDir.x)
			{
				CastingPtr->HitPlayer(Data.Attack, float4(-250, 400));
			}
			else
			{
				CastingPtr->HitPlayer(Data.Attack, float4(250, 400));
			}

			GameEngineSound::Play("Hit_Sword_Small.wav");

			EffectManager::PlayEffect({
			.EffectName = "HitNormal",
			.Position = CastingPtr->GetTransform()->GetWorldPosition()
			+ float4(GameEngineRandom::MainRandom.RandomFloat(-20, 20),
				50 + GameEngineRandom::MainRandom.RandomFloat(-20, 20)) });
		}

		LandingAttackCol->Off();

		IsLandingMagicSwordAttack = true;
	}
	//VeteranHero_LandingMagicSword

	if (true == IsLandingMagicSwordAttack)
	{
		LandingMagicSwordTime += _DeltaTime;

		if (0.0f <= LandingMagicSwordTime)
		{
			if (3 <= MagicSwordCount)
			{
				BossFsm.ChangeState("Idle");
				return;
			}

			GameEngineSound::Play("Hit_Sword_Large.wav");

			MagicSwordInter.x += 130.0f;
			++MagicSwordCount;
			LandingMagicSwordTime -= 0.2f;

			std::function<void(std::shared_ptr<BaseContentActor>, ProjectileHitParameter)> ColEnterEvent =
				[](std::shared_ptr<class BaseContentActor> _HitActor, ProjectileHitParameter _Data)
			{
				std::shared_ptr<Player> CastingPtr = _HitActor->DynamicThis<Player>();

				if (nullptr == CastingPtr)
				{
					MsgAssert_Rtti<VeteranHero>(" - 플레이어 클래스만 Player ColOrder를 가질 수 있습니다.");
				}

				CastingPtr->HitPlayer(_Data.Attack, float4(0, 500));

				EffectManager::PlayEffect({
					.EffectName = "HitNormal",
					.Position = CastingPtr->GetTransform()->GetWorldPosition()
					+ float4(GameEngineRandom::MainRandom.RandomFloat(-20, 20),
					50 + GameEngineRandom::MainRandom.RandomFloat(-20, 20)) });

				GameEngineSound::Play("Hit_Sword_Small.wav");
			};

			float4 LeftMagicSwordPos = LandingAttackPos + MagicSwordInter;

			std::shared_ptr<VeteranHeroMagicSword> MagicSwordProjectile = GetLevel()->CreateActor<VeteranHeroMagicSword>();

			MagicSwordProjectile->ShotProjectile({
				.EffectName = "VeteranHero_LandingMagicSword",
				.Pos = LeftMagicSwordPos + float4(0, 60, 0),
				.ColScale = float4(35, 100, 1),
				.ColOrder = (int)CollisionOrder::Player,
				.ProjectileColType = ColType::AABBBOX2D,
				.IsForceLoopOff = true,
				.Damage = Data.Attack,
				.LiveTime = 4.0f,
				.EnterEvent = ColEnterEvent,
				});

			MagicSwordProjectiles.push_back(MagicSwordProjectile);

			float4 RightMagicSwordPos = LandingAttackPos - MagicSwordInter;
			
			MagicSwordProjectile = GetLevel()->CreateActor<VeteranHeroMagicSword>();

			MagicSwordProjectile->ShotProjectile({
				.EffectName = "VeteranHero_LandingMagicSword",
				.Pos = RightMagicSwordPos + float4(0, 60, 0),
				.ColScale = float4(35, 100, 1),
				.ColOrder = (int)CollisionOrder::Player,
				.ProjectileColType = ColType::AABBBOX2D,
				.IsForceLoopOff = true,
				.Damage = Data.Attack,
				.LiveTime = 4.0f,
				.EnterEvent = ColEnterEvent,
				});

			MagicSwordProjectiles.push_back(MagicSwordProjectile);

			if (3 <= MagicSwordCount)
			{
				LandingMagicSwordTime = -0.7f;
			}
		}
	}
}

void VeteranHero::LandingAttack_End()
{
	for (size_t i = 0; i < MagicSwordProjectiles.size(); i++)
	{
		MagicSwordProjectiles[i]->FadeDeath();
	}

	MagicSwordProjectiles.clear();
}

void VeteranHero::Ultimate_Enter()
{
	PlayAnimation("Explosion");

	PauseTimes["SwordEnergyReady"][2] = 0.3f;
	IsUltimateCharge = false;
	IsSwordEnergyReadyStart = false;
	IsSwordEnergyReadyEnd = false;
	HitDamageCheck = 0.0f;
	SwordEnergyWaveTime = -0.5f;
	IsSwordWaveSmokeHit = false;

	SwordEnergyWaveEndTime = -2.0f;

	if (0.0f <= SpeechCoolTime)
	{
		PlaySpeechBubble("이걸로 끝을 내주지!", 4.0f);
		SpeechCoolTime = -10.0f;
	}
}

void VeteranHero::Ultimate_Update(float _DeltaTime)
{
	if (false == IsUltimateCharge && true == Render->IsAnimationEnd())
	{
		IsUltimateCharge = true;

		GameEngineSound::Play("Adventurer_Charge_End.wav");

		UltimateSmokeEffect = EffectManager::PlayEffect({
			.EffectName = "RookieHero_UltimateComplete",
			.Position = GetTransform()->GetWorldPosition() + float4(0, 70, 0),
			.AddSetZ = -20.0f });

		GetContentLevel()->GetCamCtrl().CameraShake(5, 20, 5);
		UltimateLightOn();
		return;
	}

	if (nullptr != UltimateSmokeEffect && true == UltimateSmokeEffect->IsAnimationEnd())
	{
		GetContentLevel()->GetCamCtrl().CameraShake(7, 20, 3);
		IsSwordEnergyReadyStart = true;

		ExplosionCol->On();
		std::shared_ptr<GameEngineCollision> ExploCol = ExplosionCol->Collision((int)CollisionOrder::Player, ColType::SPHERE2D, ColType::AABBBOX2D);

		if (nullptr != ExploCol)
		{
			std::shared_ptr<Player> CastPtr = ExploCol->GetActor()->DynamicThis<Player>();

			if (nullptr == CastPtr)
			{
				MsgAssert_Rtti<VeteranHero>(" - 플레이어만 Player Col Order를 가질 수 있습니다.");
				return;
			}

			float4 PlayerDir = CastPtr->GetTransform()->GetWorldPosition() - GetTransform()->GetWorldPosition();

			if (0.0f > PlayerDir.x)
			{
				CastPtr->AddPushPlayer(float4(-250, 400));
			}
			else
			{
				CastPtr->AddPushPlayer(float4(250, 400));
			}
		}

		ExplosionCol->Off();

		LookPlayer();
		PlayAnimation("SwordEnergyReady");

		GameEngineSound::Play("Atk_Explosion_Medium.wav");

		EffectManager::PlayEffect({
			.EffectName = "VeteranHero_EnergyBlast",
			.Position = GetTransform()->GetWorldPosition() + float4(0, 70, 0),
			.Scale = 2.0f });

		EffectManager::PlayEffect({
			.EffectName = "VeteranHero_EnergyBlast",
			.Position = GetTransform()->GetWorldPosition() + float4(0, 70, 0),
			.AddSetZ = -10.0f,
			.Scale = 1.0f,
			});

		return;
	}

	if (true == IsSwordEnergyReadyStart && false == IsSwordEnergyReadyEnd &&
		true == Render->IsAnimationEnd())
	{
		GameEngineSound::Play("AdventurerHero_Voice_SpecialMove.wav");
		GameEngineSound::Play("Atk_Smoke_Medium.wav");

		IsSwordEnergyReadyEnd = true;
		PlayAnimation("SwordEnergy");

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

			if (_Parameter.AttackDir.x < 0.0f)
			{
				CastingPtr->HitPlayer(_Parameter.Attack, float4(-250, 400));
			}
			else
			{
				CastingPtr->HitPlayer(_Parameter.Attack, float4(250, 400));
			}

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


		switch (Dir)
		{
		case ActorViewDir::Left:
			SwordSmokePos = GetTransform()->GetWorldPosition() + float4(-120, 125);
			break;
		case ActorViewDir::Right:
			SwordSmokePos = GetTransform()->GetWorldPosition() + float4(120, 125);
			break;
		}

		SmokeDir = Dir;

		return;
	}

	if (true == IsSwordEnergyReadyEnd)
	{
		SwordEnergyWaveTime += _DeltaTime;
		SwordEnergyWaveEndTime += _DeltaTime;

		if (0.0f <= SwordEnergyWaveTime)
		{
			GameEngineSound::Play("Atk_Smoke_Small.wav");
			SwordEnergyWaveTime -= 0.1f;

			switch (SmokeDir)
			{
			case ActorViewDir::Left:
				SwordSmokePos += float4(-60, 0);
				break;
			case ActorViewDir::Right:
				SwordSmokePos += float4(60, 0);
				break;
			}

			EffectManager::PlayEffect({
				.EffectName = "VeteranHero_WaveSmoke",
				.Position = SwordSmokePos,
				.FlipX = ActorViewDir::Left == SmokeDir});

			if (false == IsSwordWaveSmokeHit)
			{
				WaveSmokeCol->On();

				switch (SmokeDir)
				{
				case ActorViewDir::Left:
					WaveSmokeCol->GetTransform()->SetWorldPosition(SwordSmokePos + float4(70, -70));
					break;
				case ActorViewDir::Right:
					WaveSmokeCol->GetTransform()->SetWorldPosition(SwordSmokePos + float4(-70, -70));
					break;
				}

				std::shared_ptr<GameEngineCollision> SmokeCol = WaveSmokeCol->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D);

				if (nullptr != SmokeCol)
				{
					GameEngineSound::Play("Hit_Skull.wav");

					std::shared_ptr<Player> CastingPtr = SmokeCol->GetActor()->DynamicThis<Player>();

					if (nullptr == CastingPtr)
					{
						MsgAssert_Rtti<VeteranHero>(" - 플레이어 클래스만 Player ColOrder를 가질 수 있습니다");
						return;
					}

					switch (SmokeDir)
					{
					case ActorViewDir::Left:
						CastingPtr->HitPlayer(Data.Attack * 0.5f, float4(-250, 400));
						break;
					case ActorViewDir::Right:
						CastingPtr->HitPlayer(Data.Attack * 0.5f, float4(250, 400));
						break;
					default:
						break;
					}

					EffectManager::PlayEffect({
						.EffectName = "HitNormal",
						.Position = CastingPtr->GetTransform()->GetWorldPosition()
						+ float4(GameEngineRandom::MainRandom.RandomFloat(-20, 20),
							50 + GameEngineRandom::MainRandom.RandomFloat(-20, 20)) });

					IsSwordWaveSmokeHit = true;
				}
			}
		}
		else
		{
			WaveSmokeCol->Off();
		}
	}

	if (0.0f <= SwordEnergyWaveEndTime)
	{
		BossFsm.ChangeState("Idle");
	}

}

void VeteranHero::Ultimate_End()
{
	UltimateLightOff();

}

void VeteranHero::SecondUltimate_Enter()
{
	PlayAnimation("ExplosionReady");
	GetContentLevel()->GetCamCtrl().CameraShake(1, 40, 1000);

	if (false == GameEngineInput::IsKey("Debug_VeteranHeroIdle"))
	{
		GameEngineInput::CreateKey("Debug_VeteranHeroIdle", 'K');
	}

	SecondUltimateAuraEffect = EffectManager::PlayEffect({
		.EffectName = "VeteranHero_Aura",
		.Position = GetTransform()->GetWorldPosition() + float4(0, 60),
		.Scale = 1.2f});

	IsSecondUltimateReadyEnd = false;
	IsSecondUltimateJumpReady = false;
	IsSecondUltimateJump = false;
	IsSecondUltimateStingerStart = false;
	IsSecondUltimateLandingStart = false;
	IsSecondUltimateEnd = false;
	IsSecondUltimateCamShake = false;

	SecondUltimateStingerCount = 0;

	SecondUltimateUpTime = 0.0f;
	SecondUltimateStingerProgress = 0.0f;
	SecondUltimateLandingWaitTime = 0.0f;
	SecondUltimateLandingEndWaitTime = 0.0f;
	SecondUltimateLandingFinishTime = 0.0f;
	SecondUltimateHitWaitTime = 0.0f;
	SecondUltimateCamShakeTime = 0.0f;

	IsSecondUltimateStingerUpdate = false;
	UltimateLightOn();
}

void VeteranHero::SecondUltimate_Update(float _DeltaTime)
{
	if (false == IsSecondUltimateReadyEnd && true == Render->IsAnimationEnd())
	{
		GameEngineSound::Play("SuperUltraMove_Start.wav");
		PlayAnimation("Explosion");
		IsSecondUltimateReadyEnd = true;
	}

	if (nullptr != SecondUltimateAuraEffect && true == SecondUltimateAuraEffect->IsAnimationEnd())
	{
		GameEngineSound::Play("SuperUltraMove_End.wav");

		LookPlayer();
		PlayAnimation("StingerReady");
		SecondUltimateAuraEffect = nullptr;
		GetContentLevel()->GetCamCtrl().CameraShake(1, 1, 0);

		switch (Dir)
		{
		case ActorViewDir::Left:
			EffectManager::PlayEffect({
				.EffectName = "VeteranHero_SecondUlt_Electric",
				.Position = GetTransform()->GetWorldPosition() + float4(0, 50, 0),
				.Scale = 2.0f });
			break;
		case ActorViewDir::Right:
			EffectManager::PlayEffect({
				.EffectName = "VeteranHero_SecondUlt_Electric",
				.Position = GetTransform()->GetWorldPosition() + float4(0, 50, 0),
				.Scale = 2.0f });
			break;
		}
				
		EffectManager::PlayEffect({
			.EffectName = "VeteranHero_EnergyBlast",
			.Position = GetTransform()->GetWorldPosition() + float4(0, 70, 0),
			.AddSetZ = -10.0f,
			.Scale = 1.0f,
			});

		IsSecondUltimateJumpReady = true;
	}

	if (true == IsSecondUltimateJumpReady && true == Render->IsAnimationEnd())
	{
		GameEngineSound::Play("Default_Jump.wav");

		PlayAnimation("Jump");

		EffectManager::PlayEffect({
			.EffectName = "VeteranHero_JumpSmoke",
			.Position = GetTransform()->GetWorldPosition() + float4(0, 97) });

		IsSecondUltimateJump = true;
		IsSecondUltimateJumpReady = false;
	}

	if (true == IsSecondUltimateJump)
	{
		SecondUltimateUpTime += _DeltaTime;
		GetTransform()->AddLocalPosition(float4::Up * _DeltaTime * 2000.0f);
	
		if (1.5f <= SecondUltimateUpTime)
		{
			IsSecondUltimateJump = false;
			IsSecondUltimateStingerStart = true;
		}
	}

	if (true == IsSecondUltimateStingerStart && false == IsSecondUltimateStingerUpdate)
	{
		float StartX = 0.0f;
		float EndX = 0.0f;

		float RandStartY = GameEngineRandom::MainRandom.RandomFloat(150.0f, 400.0f);
		float RandEndY = GameEngineRandom::MainRandom.RandomFloat(250.0f, 400.0f);

		float CurZ = GetTransform()->GetWorldPosition().z;

		PlayAnimation("Stinger", false);

		if (nullptr != SecondUltimateStingerEffect)
		{
			SecondUltimateStingerEffect->Death();
			SecondUltimateStingerEffect = nullptr;
		}

		SetViewDir(ActorViewDir::Right);

		if (0 == SecondUltimateStingerCount % 2)
		{
			StartX = Battle_Platform_Left->GetTransform()->GetWorldPosition().x - 200.0f;
			EndX = Battle_Platform_Right->GetTransform()->GetWorldPosition().x + 200.0f;	
		}
		else
		{
			StartX = Battle_Platform_Right->GetTransform()->GetWorldPosition().x + 200.0f;
			EndX = Battle_Platform_Left->GetTransform()->GetWorldPosition().x - 200.0f;
		}
		
		SecondUltimateStingerStart = float4(StartX, RandStartY, CurZ);
		SecondUltimateStingerEnd = float4(EndX, RandEndY, CurZ);

		GetTransform()->SetLocalRotation(float4::Zero);

		SecondStingerForwardDir = SecondUltimateStingerEnd - SecondUltimateStingerStart;
		SecondStingerForwardDir.Normalize();

		float ZRot = 0.0f;

		if (0 == SecondUltimateStingerCount % 2)
		{
			ZRot = float4::DotProduct3D(SecondStingerForwardDir, float4::Right);
		}
		else
		{
			ZRot = float4::DotProduct3D(SecondStingerForwardDir, float4::Left);
		}

		ZRot = std::acos(ZRot);


		SecondUltimateStingerEffect = EffectManager::PlayEffect({
			.EffectName = "VeteranHero_Stinger",
			.Position = GetTransform()->GetWorldPosition() + float4(0, 40, 0),
			.Triger = EffectDeathTrigger::Time,
			.Time = 2.0f});

		if (0 == SecondUltimateStingerCount % 2)
		{
			if (0.0f > SecondStingerForwardDir.y)
			{
				ZRot = -ZRot;
			}

			GetTransform()->SetLocalRotation(float4(0, 0, ZRot * GameEngineMath::RadToDeg));
			SecondUltimateStingerEffect->GetTransform()->SetLocalRotation(float4(0, 0, ZRot* GameEngineMath::RadToDeg));
			SetViewDir(ActorViewDir::Right);
		}
		else
		{
			if (0.0f < SecondStingerForwardDir.y)
			{
				ZRot = -ZRot;
			}

			GetTransform()->SetLocalRotation(float4(0, 0, ZRot * GameEngineMath::RadToDeg));
			SecondUltimateStingerEffect->GetTransform()->SetLocalRotation(float4(0, 0, ZRot * GameEngineMath::RadToDeg));
			SetViewDir(ActorViewDir::Left);
			SecondUltimateStingerEffect->GetTransform()->SetLocalNegativeScaleX();
		}
				
		SecondUltimateStingerEffect->GetTransform()->SetParent(GetTransform());

		++SecondUltimateStingerCount;	
		IsSecondUltimateStingerUpdate = true;
		IsSecondUltimateStingerSound = false;

		IsGroundUpOff = true;
		IsSecondUltimatePlayerHit = false;

		UltimateStingerAttackCol->On();
	}

	if (true == IsSecondUltimateStingerUpdate)
	{
		SecondUltimateStingerProgress += _DeltaTime * 1.2f;

		float4 StingerLerpPos = float4::LerpClamp(SecondUltimateStingerStart, SecondUltimateStingerEnd, SecondUltimateStingerProgress);
		GetTransform()->SetWorldPosition(StingerLerpPos);

		if (false == IsSecondUltimatePlayerHit)
		{
			std::shared_ptr<GameEngineCollision> PlayerCol = 
				UltimateStingerAttackCol->Collision((int)CollisionOrder::Player, ColType::OBBBOX2D, ColType::AABBBOX2D);

			if (nullptr != PlayerCol)
			{
				GameEngineSound::Play("Hit_Sword_Large.wav");

				std::shared_ptr<Player> CastingPtr = PlayerCol->GetActor()->DynamicThis<Player>();

				if (0.0f > SecondStingerForwardDir.x)
				{
					CastingPtr->HitPlayer(Data.Attack, float4(-250, 400));
				}
				else
				{
					CastingPtr->HitPlayer(Data.Attack, float4(250, 400));
				}

				IsSecondUltimatePlayerHit = true;
			}
		}

		if (false == IsSecondUltimateStingerSound && 0.25f <= SecondUltimateStingerProgress)
		{
			GameEngineSound::Play("AdventurerHero_Slash_withAura.wav");
			IsSecondUltimateStingerSound = true;
		}

		if (1.0f <= SecondUltimateStingerProgress)
		{
			SecondUltimateStingerProgress -= 1.2f;
			IsSecondUltimateStingerUpdate = false;

			if (6 <= SecondUltimateStingerCount)
			{
				GetTransform()->SetLocalRotation(float4::Zero);
				IsSecondUltimateStingerStart = false;

				if (nullptr != SecondUltimateStingerEffect)
				{
					SecondUltimateStingerEffect->Death();
					SecondUltimateStingerEffect = nullptr;
				}

				IsSecondUltimateLandingStart = true;
				UltimateStingerAttackCol->Off();
			}
		}
	}

	if (true == IsSecondUltimateLandingStart)
	{
		SecondUltimateLandingWaitTime += _DeltaTime;

		if (1.0f <= SecondUltimateLandingWaitTime)
		{
			IsSecondUltimateLandingStart = false;

			if (nullptr == FindPlayer)
			{
				LandingAttackPos = GetTransform()->GetWorldPosition();
			}
			else
			{
				LandingAttackPos = FindPlayer->GetTransform()->GetWorldPosition();
			}

			LandingAttackPos.y = 2000.0f;
			float HighY = -100000.0f;

			FindLandingCol->On();
			GameEngineTransform* FindColTrans = FindLandingCol->GetTransform();
			FindColTrans->SetWorldPosition(LandingAttackPos);

			std::vector<std::shared_ptr<GameEngineCollision>> PlatformCols;

			if (true == FindLandingCol->CollisionAll((int)CollisionOrder::Platform_Normal, PlatformCols, ColType::AABBBOX2D, ColType::AABBBOX2D))
			{
				for (size_t i = 0; i < PlatformCols.size(); i++)
				{
					GameEngineTransform* ColTrans = PlatformCols[i]->GetTransform();

					float ColY = ColTrans->GetWorldPosition().y + ColTrans->GetWorldScale().hy();

					if (HighY < ColY)
					{
						HighY = ColY;
						LandingAttackPos.y = HighY;
					}
				}
			}

			PlatformCols.clear();

			if (true == FindLandingCol->CollisionAll((int)CollisionOrder::Platform_Half, PlatformCols, ColType::AABBBOX2D, ColType::AABBBOX2D))
			{
				for (size_t i = 0; i < PlatformCols.size(); i++)
				{
					GameEngineTransform* ColTrans = PlatformCols[i]->GetTransform();

					float ColY = ColTrans->GetWorldPosition().y + ColTrans->GetWorldScale().hy();

					if (HighY < ColY)
					{
						HighY = ColY;
						LandingAttackPos.y = HighY;
					}
				}
			}

			FindColTrans->SetWorldPosition(LandingAttackPos);

			LandingSignEffect = EffectManager::PlayEffect({
				.EffectName = "VeteranHero_LandingAttackSign",
				.Position = LandingAttackPos});

			LandingSignEffect->GetTransform()->SetLocalScale(float4(0.8f, 1.0f, 1.0f));

			FindLandingCol->Off();
		}
	}

	if (nullptr != LandingSignEffect && true == LandingSignEffect->IsAnimationEnd())
	{
		GameEngineSound::Play("AdventurerHero_Voice_SpecialMove.wav");
		GameEngineSound::Play("AdventurerHero_UltraLanding.wav");
		GameEngineSound::Play("Hit_Sword_Large.wav");

		SetViewDir(ActorViewDir::Right);
		PlayAnimation("AttackE");
		GetTransform()->SetWorldPosition(LandingAttackPos);

		EffectManager::PlayEffect({
			.EffectName = "VeteranHero_LandingSmoke",
			.Position = LandingAttackPos + float4(-100, 70) });

		EffectManager::PlayEffect({
			.EffectName = "VeteranHero_LandingSmoke",
			.Position = LandingAttackPos + float4(100, 70),
			.FlipX = true });

		PlaySpeechBubble("널 위해 준비한 최강의 공격!", 4.0f);
		SpeechCoolTime = -10.0f;

		LandingAttackCol->On();
		std::shared_ptr<GameEngineCollision> PlayerCol = LandingAttackCol->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D);

		if (nullptr != PlayerCol)
		{
			std::shared_ptr<Player> CastingPtr = PlayerCol->GetActor()->DynamicThis<Player>();

			if (nullptr == CastingPtr)
			{
				MsgAssert_Rtti<VeteranHero>(" - 플레이어 클래스만 Player ColOrder를 가질 수 있습니다.");
			}

			float4 PlayerDir = CastingPtr->GetTransform()->GetWorldPosition() - GetTransform()->GetWorldPosition();

			if (0.0f > PlayerDir.x)
			{
				CastingPtr->HitPlayer(Data.Attack, float4(-250, 400));
			}
			else
			{
				CastingPtr->HitPlayer(Data.Attack, float4(250, 400));
			}

			EffectManager::PlayEffect({
				.EffectName = "HitNormal",
				.Position = CastingPtr->GetTransform()->GetWorldPosition()
				+ float4(GameEngineRandom::MainRandom.RandomFloat(-20, 20),
					50 + GameEngineRandom::MainRandom.RandomFloat(-20, 20)) });
		}

		LandingAttackCol->Off();

		IsSecondUltimateCamShake = true;
		GetContentLevel()->GetCamCtrl().CameraShake(10, 40, 1000);


		SecondUltimateFinishEffect = EffectManager::PlayEffect({
			.EffectName = "VeteranHero_StingerFinish",
			.Position = LandingAttackPos + float4(0, 280)});

		SecondUltimateFinishEffect->GetTransform()->SetLocalScale(float4(1.0f, 2.0f, 1.0f));

		UltimateFinishAttackCol->On();
		LandingSignEffect = nullptr;
	}

	if (true == IsSecondUltimateCamShake)
	{
		SecondUltimateCamShakeTime += _DeltaTime;

		if (0.5f <= SecondUltimateCamShakeTime)
		{
			GetContentLevel()->GetCamCtrl().CameraShake(3, 40, 1000);
			IsSecondUltimateCamShake = false;
		}
	}

	if (nullptr != SecondUltimateFinishEffect)
	{
		SecondUltimateLandingFinishTime += _DeltaTime;
		SecondUltimateHitWaitTime += _DeltaTime;

		float4 FinishColScale = float4::LerpClamp(SecondFinishScaleStart, SecondFinishScaleEnd, SecondUltimateLandingFinishTime / 1.5f);
		UltimateFinishAttackCol->GetTransform()->SetLocalScale(FinishColScale);

		if (0.0f <= SecondUltimateHitWaitTime)
		{
			std::shared_ptr<GameEngineCollision> PlayerCol =
				UltimateFinishAttackCol->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D);

			if (nullptr != PlayerCol)
			{
				std::shared_ptr<Player> CastingCol = PlayerCol->GetActor()->DynamicThis<Player>();

				if (nullptr == CastingCol)
				{
					MsgAssert_Rtti<VeteranHero>(" - 플레이어 클래스만 Player ColOrder를 가질 수 있습니다.");
					return;
				}

				CastingCol->HitPlayer(Data.Attack * 0.2f, float4::Zero);

				EffectManager::PlayEffect({
					.EffectName = "HitNormal",
					.Position = CastingCol->GetTransform()->GetWorldPosition() + float4(GameEngineRandom::MainRandom.RandomFloat(-20, 20),
					50 + GameEngineRandom::MainRandom.RandomFloat(-20, 20)) });

				SecondUltimateHitWaitTime = -0.15f;
			}
		}

		if (1.5f <= SecondUltimateLandingFinishTime)
		{
			UltimateFinishAttackCol->Off();
			GetContentLevel()->GetCamCtrl().CameraShake(1, 1, 0);
			SecondUltimateFinishEffect->IsFadeDeathOn(0.7f);
			SecondUltimateFinishEffect = nullptr;
			IsSecondUltimateEnd = true;
		}
	}

	if (true == IsSecondUltimateEnd)
	{
		SecondUltimateLandingEndWaitTime += _DeltaTime;

		if (1.3f <= SecondUltimateLandingEndWaitTime)
		{
			BossFsm.ChangeState("Idle");
		}
	}

	if (true == GameEngineInput::IsDown("Debug_VeteranHeroIdle"))
	{
		BossFsm.ChangeState("Idle");
	}
}

void VeteranHero::SecondUltimate_End()
{
	LandingSignEffect = nullptr;
	SecondUltimateAuraEffect = nullptr;
	SecondUltimateFinishEffect = nullptr;

	UltimateLightOff();
	GetTransform()->SetLocalRotation(float4::Zero);

	if (nullptr != SecondUltimateStingerEffect)
	{
		SecondUltimateStingerEffect->Death();
		SecondUltimateStingerEffect = nullptr;
	}

	UltimateStingerAttackCol->Off();
	IsGroundUpOff = false;
}