#include "PrecompileHeader.h"
#include "MinotaurusSkull_Unique.h"
#include "BaseMonster.h"
#include "RigidProjectile.h"

MinotaurusSkull_Unique::MinotaurusSkull_Unique()
{
}

MinotaurusSkull_Unique::~MinotaurusSkull_Unique()
{
	AttackDoubleCheck.clear();

	if (nullptr != SkillBPlowUpEffect)
	{
		SkillBPlowUpEffect->IsFadeDeathOn(2.0f);
		SkillBPlowUpEffect = nullptr;
	}
}

void MinotaurusSkull_Unique::Start()
{
	PlayerBaseSkull::Start();

	IsActiveSkillA_Value = true;
	IsActiveSkillB_Value = true;

	AttackEffectType = HitEffectType::MinoTaurus;

	JumpAttackCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::PlayerAttack);
	JumpAttackCol->GetTransform()->SetLocalPosition(float4(10, 45, 0));
	JumpAttackCol->GetTransform()->SetLocalScale(float4(80, 90, 1));
	JumpAttackCol->SetColType(ColType::AABBBOX2D);
	JumpAttackCol->Off();

	DashAttackCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::PlayerAttack);
	DashAttackCol->GetTransform()->SetLocalPosition(float4(5, 43, 0));
	DashAttackCol->GetTransform()->SetLocalScale(float4(116, 85, 1));
	DashAttackCol->SetColType(ColType::AABBBOX2D);
	DashAttackCol->Off();

	SkillACol = CreateComponent<GameEngineCollision>((int)CollisionOrder::PlayerAttack);
	SkillACol->GetTransform()->SetLocalPosition(float4(0, 40, 0));
	SkillACol->GetTransform()->SetLocalScale(float4(350, 80, 1));
	SkillACol->SetColType(ColType::AABBBOX2D);
	SkillACol->Off();

	SkillBCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::PlayerAttack);
	SkillBCol->GetTransform()->SetLocalPosition(float4(110, 50, 0));
	SkillBCol->GetTransform()->SetLocalScale(float4(80, 150, 1));
	SkillBCol->GetTransform()->SetLocalRotation(float4(0, 0, -30));
	SkillBCol->SetColType(ColType::AABBBOX2D);
	SkillBCol->Off();

	PassiveCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::PlayerAttack);
	PassiveCol->GetTransform()->SetLocalPosition(float4(0, 15, 0));
	PassiveCol->GetTransform()->SetLocalScale(float4(220, 30, 1));
	PassiveCol->SetColType(ColType::AABBBOX2D);
	PassiveCol->Off();

	SkillBDoubleAttackCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::PlayerAttack);
	SkillBDoubleAttackCol->GetTransform()->SetLocalPosition(float4(70, 90, 0));
	SkillBDoubleAttackCol->GetTransform()->SetLocalScale(float4(150, 180, 1));
	SkillBDoubleAttackCol->SetColType(ColType::AABBBOX2D);
	SkillBDoubleAttackCol->Off();

	SkillARigidbody.SetMaxSpeed(3000.0f);
	SkillARigidbody.SetGravity(-3500.0f);
	SkillARigidbody.SetActiveGravity(true);
	SkillARigidbody.SetFricCoeff(1000.0f);

	SkillA_DamageRatio = 2.0f;

	ProjectileEffectNames.resize(4);

	ProjectileEffectNames[0] = "Minotaurus_Rare_PlowUp_Projectile1";
	ProjectileEffectNames[1] = "Minotaurus_Rare_PlowUp_Projectile2";
	ProjectileEffectNames[2] = "Minotaurus_Rare_PlowUp_Projectile3";
	ProjectileEffectNames[3] = "Minotaurus_Rare_PlowUp_Projectile4";

	DashSound = "Default_Dash_Tackle.wav";
}

void MinotaurusSkull_Unique::Update(float _DeltaTime)
{
	PlayerBaseSkull::Update(_DeltaTime);

	if (true == IsPassive)
	{
		PassiveTime += _DeltaTime;

		if (0.0f < PassiveTime)
		{
			PassiveTime -= 1.0f;

			GameEngineSound::Play("Atk_Stomp_Medium.wav");

			EffectManager::PlayEffect({
			.EffectName = "Minitaurus_Unique_Passive",
			.Position = GetTransform()->GetWorldPosition() + float4(0, -5),
			.Scale = 0.6f,});

			std::vector<std::shared_ptr<GameEngineCollision>> AllCol;
			AllCol.reserve(8);

			if (true == PassiveCol->CollisionAll((int)CollisionOrder::Monster, AllCol, ColType::AABBBOX2D, ColType::AABBBOX2D))
			{
				for (size_t i = 0; i < AllCol.size(); i++)
				{
					std::shared_ptr<BaseMonster> CastingCol = AllCol[i]->GetActor()->DynamicThis<BaseMonster>();

					if (nullptr == CastingCol)
					{
						MsgAssert_Rtti<MinotaurusSkull_Unique>(" - BaseMonster를 상속 받은 클래스만 Monster ColOrder를 가질 수 있습니다.");
						return;
					}

					CastingCol->HitMonster(GetMeleeAttackDamage(), GetViewDir(), true, false, false, HitEffectType::MinoTaurus);

					if (10.0f >= GameEngineRandom::MainRandom.RandomFloat(0.0f, 100.0f))
					{
						CastingCol->Stun(3.0f);
					}
				}
			}

			++PassiveCount;
			GetContentLevel()->GetCamCtrl().CameraShake(5, 30, 5);
		}
		

		if (4 <= PassiveCount)
		{
			PassiveCount = 0;
			IsPassive = false;
			PassiveTime = 0.0f;
			PassiveCol->Off();
		}
	}
}

void MinotaurusSkull_Unique::Attack_Enter()
{
	PlayerBaseSkull::Attack_Enter();

	HitEvent = [this]()
	{
		GetContentLevel()->GetCamCtrl().CameraShake(5, 30, 5);
	};
}

void MinotaurusSkull_Unique::Attack_End()
{
	PlayerBaseSkull::Attack_End();

	HitEvent = nullptr;
}

void MinotaurusSkull_Unique::JumpAttack_Enter()
{
	Render->ChangeAnimation("JumpAttack");

	GameEngineSound::Play("MinoTaurus_JumpAttack.wav");

	AttackRigidbody.SetActiveGravity(true);
	AttackRigidbody.SetGravity(-13000.0f);
	AttackRigidbody.SetMaxSpeed(5000.0f);
	AttackRigidbody.SetVelocity(float4(0, 1300));

	JumpAttackTime = 0.0f;
	JumpAttackLandTime = 0.0f;

	BattleActorRigidbody.SetVelocity(float4::Zero);
	DashRigidbody.SetVelocity(float4::Zero);
	IsJumpAttackLand = false;

	AttackDoubleCheck.clear();
	IsDownPlatformCheckOff = true;
}

void MinotaurusSkull_Unique::JumpAttack_Update(float _DeltaTime)
{
	if (false == IsJumpAttackLand)
	{
		if (0.25f >= JumpAttackTime)
		{
			JumpAttackTime += _DeltaTime;
			AttackRigidbody.AddForce(float4(0, 7000));
		}

		AttackRigidbody.UpdateForce(_DeltaTime);

		float4 AttackVel = AttackRigidbody.GetVelocity();
		PlayerTrans->AddLocalPosition(AttackVel * _DeltaTime);

		if (-200.0f > AttackVel.y)
		{
			JumpAttackCol->On();
			IsDownPlatformCheckOff = false;
		}

		std::vector<std::shared_ptr<GameEngineCollision>> AllCol;
		AllCol.reserve(8);

		if (true == JumpAttackCol->CollisionAll((int)CollisionOrder::Monster, AllCol, ColType::AABBBOX2D, ColType::AABBBOX2D))
		{
			for (size_t i = 0; i < AllCol.size(); i++)
			{
				std::shared_ptr<BaseMonster> CastingCol = AllCol[i]->GetActor()->DynamicThis<BaseMonster>();

				if (nullptr != AttackDoubleCheck[CastingCol->GetActorCode()])
				{
					continue;
				}

				if (nullptr == CastingCol)
				{
					MsgAssert_Rtti<MinotaurusSkull_Unique>(" - BaseMonster를 상속 받은 클래스만 Monster ColOrder를 가질 수 있습니다.");
					return;
				}

				CastingCol->HitMonster(GetMeleeAttackDamage(), GetViewDir(), true, true, false, HitEffectType::MinoTaurus);
				AttackDoubleCheck[CastingCol->GetActorCode()] = CastingCol;
			}
		}
	}

	if (false == IsDownPlatformCheckOff && false == IsJumpAttackLand && nullptr != ContentFunc::PlatformColCheck(GroundCol, true))
	{
		GameEngineSound::Play("Atk_Stomp_Large.wav");
		Render->ChangeAnimation("JumpAttack_Land");
		IsJumpAttackLand = true;

		float4 AttackVel = AttackRigidbody.GetVelocity();
		AttackRigidbody.SetVelocity(float4::Zero);
		JumpAttackCol->Off();

		if (-200.0f > AttackVel.y)
		{
			GetContentLevel()->GetCamCtrl().CameraShake(6, 60, 15);
		}
		else
		{
			PlayerFSM.ChangeState("Idle");
			return;
		}
	}

	if (true == IsJumpAttackLand)
	{
		JumpAttackLandTime += _DeltaTime;

		if (0.3f <= JumpAttackLandTime)
		{
			PlayerFSM.ChangeState("Idle");
		}
	}
}

void MinotaurusSkull_Unique::JumpAttack_End()
{
	AttackRigidbody.SetActiveGravity(false);
	AttackRigidbody.SetMaxSpeed(1000.0f);

	AttackDoubleCheck.clear();
	IsDownPlatformCheckOff = false;
}

void MinotaurusSkull_Unique::Switch_Enter()
{
	PlayerBaseSkull::Switch_Enter();

	IsSwitchMove = false;
	IsSwitchProjectileShot = false;
	SwitchProjectileTime = 0.0f;
	SwitchShotCount = 0;
}

void MinotaurusSkull_Unique::Switch_Update(float _DeltaTime)
{
	PlayerBaseSkull::Switch_Update(_DeltaTime);

	BattleActorRigidbody.AddVelocity(float4(0, _DeltaTime * ContentConst::Gravity_f, 0));
	PlayerTrans->AddLocalPosition(BattleActorRigidbody.GetVelocity() * _DeltaTime);

	std::shared_ptr<GameEngineCollision> GroundColPtr = ContentFunc::PlatformColCheck(GroundCol, true);

	if (nullptr != GroundColPtr)
	{
		float4 CurPos = PlayerTrans->GetWorldPosition();

		GameEngineTransform* ColTrans = GroundColPtr->GetTransform();
		CurPos.y = ColTrans->GetWorldPosition().y + ColTrans->GetWorldScale().hy();

		PlayerTrans->SetWorldPosition(CurPos);
		PlayerTrans->SetLocalPosition(PlayerTrans->GetLocalPosition());

		float4 Vel = BattleActorRigidbody.GetVelocity();
		Vel.y = 0;
		BattleActorRigidbody.SetVelocity(Vel);
	}

	if (false == IsSwitchMove && 3 == Render->GetCurrentFrame())
	{
		IsSwitchMove = true;

		switch (GetViewDir())
		{
		case ActorViewDir::Left:
			AttackRigidbody.SetVelocity(float4::Left * 800.0f);

			EffectManager::PlayEffect({
				.EffectName = "Minotaurus_PlowUp_Smoke",
				.Position = GetTransform()->GetWorldPosition() + float4(-130, 50),
				.AddSetZ = -20,
				.FlipX = true,
				});
			break;
		case ActorViewDir::Right:
			AttackRigidbody.SetVelocity(float4::Right * 800.0f);

			EffectManager::PlayEffect({
				.EffectName = "Minotaurus_PlowUp_Smoke",
				.Position = GetTransform()->GetWorldPosition() + float4(130, 50),
				.AddSetZ = -20 });
			break;
		default:
			break;
		}

		IsSwitchProjectileShot = true;
	}

	if (true == IsSwitchProjectileShot)
	{
		SwitchProjectileTime += _DeltaTime * 20.0f;

		if (1.0f <= SwitchProjectileTime)
		{
			SwitchProjectileTime -= 1.0f;
			ShotProjectile(SwitchShotCount);
			++SwitchShotCount;
		}

		if (4 <= SwitchShotCount)
		{
			IsSwitchProjectileShot = false;
		}
	}

	AttackRigidbody.UpdateForce(_DeltaTime);

	if (nullptr == ContentFunc::PlatformColCheck(WalkCol))
	{
		float4 AttackVelocity = AttackRigidbody.GetVelocity() * _DeltaTime;
		PlayerTrans->AddLocalPosition(AttackVelocity);
	}

}

void MinotaurusSkull_Unique::Dash_Enter()
{
	PlayerBaseSkull::Dash_Enter();

	std::shared_ptr<EffectActor> DashEffect = EffectManager::PlayEffect({
		.EffectName = "DashTackleEffect",
		.FlipX = ActorViewDir::Left == GetViewDir() });

	DashEffect->GetTransform()->SetParent(GetTransform());
	DashEffect->GetTransform()->SetLocalPosition(float4(30, 45, -35));

	AttackDoubleCheck.clear();
	DashAttackCol->On();
}

void MinotaurusSkull_Unique::Dash_Update(float _DeltaTime)
{
	PlayerBaseSkull::Dash_Update(_DeltaTime);

	std::vector<std::shared_ptr<GameEngineCollision>> AllCol;
	AllCol.reserve(8);

	if (true == DashAttackCol->CollisionAll((int)CollisionOrder::Monster, AllCol, ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		for (size_t i = 0; i < AllCol.size(); i++)
		{
			std::shared_ptr<BaseMonster> CastingCol = AllCol[i]->GetActor()->DynamicThis<BaseMonster>();

			if (nullptr != AttackDoubleCheck[CastingCol->GetActorCode()])
			{
				continue;
			}

			if (nullptr == CastingCol)
			{
				MsgAssert_Rtti<MinotaurusSkull_Unique>(" - BaseMonster를 상속 받은 클래스만 Monster ColOrder를 가질 수 있습니다.");
				return;
			}

			CastingCol->HitMonster(GetMeleeAttackDamage(), GetViewDir(), true, true, false, HitEffectType::MinoTaurus);
			AttackDoubleCheck[CastingCol->GetActorCode()] = CastingCol;
		}
	}
}

void MinotaurusSkull_Unique::Dash_End()
{
	PlayerBaseSkull::Dash_End();
	AttackDoubleCheck.clear();
	DashAttackCol->Off();
}

void MinotaurusSkull_Unique::Skill_SlotA_Enter()
{
	GameEngineSound::Play("MinoTaurus_JumpAttack.wav");

	PlayerBaseSkull::Skill_SlotA_Enter();
	AttackDoubleCheck.clear();

	switch (GetViewDir())
	{
	case ActorViewDir::Left:
		SkillARigidbody.SetVelocity(float4(-900, 1000));
		break;
	case ActorViewDir::Right:
		SkillARigidbody.SetVelocity(float4(900, 1000));
		break;
	}

	DashRigidbody.SetVelocity(float4::Zero);
	BattleActorRigidbody.SetVelocity(float4::Zero);

	IsSkillALand = false;
	IsSkillADoubleAttack = false;

	SkillALandTime = 0.0f;
	SkillACol->Off();

	IsDownPlatformCheckOff = true;
}

void MinotaurusSkull_Unique::Skill_SlotA_Update(float _DeltaTime)
{
	if (false == IsSkillALand)
	{
		SkillARigidbody.UpdateForce(_DeltaTime);
		float4 SkillVel = SkillARigidbody.GetVelocity();

		if (0.0f < SkillVel.y)
		{
			if (nullptr != ContentFunc::PlatformColCheck(JumpCol))
			{
				SkillVel.y = 0.0f;
				SkillARigidbody.SetVelocity(SkillVel);
			}
		}

		if (nullptr != ContentFunc::PlatformColCheck(WalkCol))
		{
			SkillVel.x = 0.0f;
			SkillARigidbody.SetVelocity(SkillVel);
		}

		if (-200.0f > SkillVel.y)
		{
			IsDownPlatformCheckOff = false;
		}

		PlayerTrans->AddLocalPosition(SkillVel * _DeltaTime);
	}

	if (false == IsDownPlatformCheckOff && false == IsSkillALand && nullptr != ContentFunc::PlatformColCheck(GroundCol, true))
	{
		GameEngineSound::Play("MinoTaurus_PowerStompLand.wav");

		SkillALandTime = 0.0f;
		IsSkillALand = true;
		Render->ChangeAnimation("JumpAttack_Land");
		GetContentLevel()->GetCamCtrl().CameraShake(15, 120, 20);

		PassiveCheck();

		std::shared_ptr<EffectActor> StampEffect = EffectManager::PlayEffect({
			.EffectName = "StampEffect",
			.Position = GetTransform()->GetWorldPosition(),
			.Scale = 0.65f });

		if (true == IsSkillADoubleAttack)
		{
			EffectManager::PlayEffect({
			.EffectName = "MinoSkillA_Smoke",
			.Position = GetTransform()->GetWorldPosition() + float4(20, 40),
			.Scale = 0.5f });
		}

		SkillACol->On();

		std::vector<std::shared_ptr<GameEngineCollision>> AllCol;
		AllCol.reserve(8);

		if (true == SkillACol->CollisionAll((int)CollisionOrder::Monster, AllCol, ColType::AABBBOX2D, ColType::AABBBOX2D))
		{
			for (size_t i = 0; i < AllCol.size(); i++)
			{
				std::shared_ptr<BaseMonster> CastingCol = AllCol[i]->GetActor()->DynamicThis<BaseMonster>();

				if (nullptr == CastingCol)
				{
					MsgAssert_Rtti<MinotaurusSkull_Unique>(" - BaseMonster를 상속 받은 클래스만 Monster ColOrder를 가질 수 있습니다.");
					return;
				}

				CastingCol->HitMonster(GetMeleeAttackDamage() * SkillA_DamageRatio, GetViewDir(), true, true, false, HitEffectType::MinoTaurus);
			}
		}

		SkillACol->Off();
	}

	if (true == IsSkillALand)
	{
		SkillALandTime += _DeltaTime;

		if (false == IsSkillADoubleAttack && true == GameEngineInput::IsDown("PlayerMove_Skill_A"))
		{
			IsSkillALand = false;
			IsSkillADoubleAttack = true;

			Render->ChangeAnimation("JumpAttack");
			SkillARigidbody.SetVelocity(float4(0, 700));
		}
		else if (0.3f <= SkillALandTime)
		{
			PlayerFSM.ChangeState("Idle");
		}
	}
}

void MinotaurusSkull_Unique::Skill_SlotA_End()
{
	PlayerBaseSkull::Skill_SlotA_End();
	AttackDoubleCheck.clear();
	AttackRigidbody.SetActiveGravity(false);
	AttackRigidbody.SetMaxSpeed(1000.0f);
	SkillACol->Off();
	IsDownPlatformCheckOff = false;
}

void MinotaurusSkull_Unique::Skill_SlotB_Enter()
{
	PlayerBaseSkull::Skill_SlotB_Enter();

	IsSkillBWait = false;
	IsSkillBEffect = false;
	IsSKillBProjectileShot = false;
	IsSKillBDoubleAttack = false;

	SkillBWaitTime = 0.0f;
	SkillBShotCount = 0;
	SkillBProjectileTime = 0.0f;
}

void MinotaurusSkull_Unique::Skill_SlotB_Update(float _DeltaTime)
{
	BattleActorRigidbody.AddVelocity(float4(0, _DeltaTime * ContentConst::Gravity_f, 0));
	PlayerTrans->AddLocalPosition(BattleActorRigidbody.GetVelocity() * _DeltaTime);

	std::shared_ptr<GameEngineCollision> GroundColPtr = ContentFunc::PlatformColCheck(GroundCol, true);

	if (nullptr != GroundColPtr)
	{
		float4 CurPos = PlayerTrans->GetWorldPosition();

		GameEngineTransform* ColTrans = GroundColPtr->GetTransform();
		CurPos.y = ColTrans->GetWorldPosition().y + ColTrans->GetWorldScale().hy();

		PlayerTrans->SetWorldPosition(CurPos);
		PlayerTrans->SetLocalPosition(PlayerTrans->GetLocalPosition());

		float4 Vel = BattleActorRigidbody.GetVelocity();
		Vel.y = 0;
		BattleActorRigidbody.SetVelocity(Vel);
	}

	if (false == IsSkillBEffect && 3 == Render->GetCurrentFrame())
	{
		GameEngineSound::Play("Minotaurus_PlowUp_Stonecrash.wav");

		IsSkillBEffect = true;
		IsSKillBProjectileShot = true;

		PassiveCheck();

		switch (GetViewDir())
		{
		case ActorViewDir::Left:
		{
			EffectManager::PlayEffect({
			.EffectName = "Minotaurus_PlowUp_Smoke",
			.Position = GetTransform()->GetWorldPosition() + float4(-130, 50),
			.AddSetZ = -20,
			.FlipX = true,
				});

			SkillBPlowUpEffect = EffectManager::PlayEffect({
			.EffectName = "Minotaurus_Rare_PlowUp",
			.Position = GetTransform()->GetWorldPosition() + float4(-110, 100),
			.Triger = EffectDeathTrigger::Time,
			.Time = 5.0f,
			.FlipX = true,
			.IsForceLoopOff = true, });
		}
		break;
		case ActorViewDir::Right:
		{
			EffectManager::PlayEffect({
			.EffectName = "Minotaurus_PlowUp_Smoke",
			.Position = GetTransform()->GetWorldPosition() + float4(130, 50),
			.AddSetZ = -20});

			SkillBPlowUpEffect = EffectManager::PlayEffect({
			.EffectName = "Minotaurus_Rare_PlowUp",
			.Position = GetTransform()->GetWorldPosition() + float4(110, 100),
			.Triger = EffectDeathTrigger::Time,
			.Time = 5.0f,
			.IsForceLoopOff = true, });
		}
		break;
		}

		SkillBCol->On();

		std::vector<std::shared_ptr<GameEngineCollision>> AllCol;
		AllCol.reserve(8);

		GetContentLevel()->GetCamCtrl().CameraShake(5, 30, 5);

		if (true == SkillBCol->CollisionAll((int)CollisionOrder::Monster, AllCol, ColType::OBBBOX2D, ColType::AABBBOX2D))
		{
			for (size_t i = 0; i < AllCol.size(); i++)
			{

				std::shared_ptr<BaseMonster> CastingCol = AllCol[i]->GetActor()->DynamicThis<BaseMonster>();

				if (nullptr == CastingCol)
				{
					MsgAssert_Rtti<MinotaurusSkull_Unique>(" - BaseMonster를 상속 받은 클래스만 Monster ColOrder를 가질 수 있습니다.");
					return;
				}

				CastingCol->HitMonster(GetMeleeAttackDamage() * SkillB_DamageRatio * 2.0f, GetViewDir(), true, true, false, HitEffectType::MinoTaurus);
			}
		}

		SkillBCol->Off();
	}

	if (true == IsSKillBProjectileShot)
	{
		SkillBProjectileTime += _DeltaTime * 20.0f;

		if (1.0f <= SkillBProjectileTime)
		{
			SkillBProjectileTime -= 1.0f;
			ShotProjectile(SkillBShotCount);
			++SkillBShotCount;
		}

		if (4 <= SkillBShotCount)
		{
			IsSKillBProjectileShot = false;
		}
	}

	if (false == IsSkillBWait && true == Render->IsAnimationEnd())
	{
		IsSkillBWait = true;		
	}

	if (3 <= Render->GetCurrentFrame() && true == GameEngineInput::IsDown("PlayerMove_Skill_B"))
	{
		GameEngineSound::Play("Atk_Explosion_Large.wav");
		GetContentLevel()->GetCamCtrl().CameraShake(15, 120, 20);
		IsSKillBDoubleAttack = true;
	
		Render->ChangeAnimation("Dash");

		SkillBDoubleAttackCol->On();

		switch (GetViewDir())
		{
		case ActorViewDir::Left:
			AttackRigidbody.AddVelocity(float4::Left * 1500.0f);

			EffectManager::PlayEffect({
				.EffectName = "Minotaurus_Rare_PlowUp_Explosion",
				.Position = GetTransform()->GetWorldPosition() + float4(-210, 130),
				.AddSetZ = 5,
				.FlipX = true,});
			break;

		case ActorViewDir::Right:
			AttackRigidbody.AddVelocity(float4::Right * 1500.0f);

			EffectManager::PlayEffect({
				.EffectName = "Minotaurus_Rare_PlowUp_Explosion",
				.Position = GetTransform()->GetWorldPosition() + float4(220, 130),
				.AddSetZ = 5});
			break;
		}

		std::vector<std::shared_ptr<GameEngineCollision>> AllCol;
		AllCol.reserve(8);

		if (true == SkillBDoubleAttackCol->CollisionAll((int)CollisionOrder::Monster, AllCol, ColType::AABBBOX2D, ColType::AABBBOX2D))
		{
			for (size_t i = 0; i < AllCol.size(); i++)
			{
				std::shared_ptr<BaseMonster> CastingCol = AllCol[i]->GetActor()->DynamicThis<BaseMonster>();

				if (nullptr == CastingCol)
				{
					MsgAssert_Rtti<MinotaurusSkull_Unique>(" - BaseMonster를 상속 받은 클래스만 Monster ColOrder를 가질 수 있습니다.");
					return;
				}

				CastingCol->HitMonster(GetMeleeAttackDamage() * SkillB_DamageRatio, GetViewDir(), true, true, false, HitEffectType::MinoTaurus);
				GetContentLevel()->GetCamCtrl().CameraShake(5, 30, 5);
			}
		}

		SkillBDoubleAttackCol->Off();
	}

	if (false == IsSKillBDoubleAttack && true == IsSkillBWait)
	{
		SkillBWaitTime += _DeltaTime;

		if (0.2f <= SkillBWaitTime)
		{
			PlayerFSM.ChangeState("Idle");
		}
	}

	if (true == IsSKillBDoubleAttack && true == IsSkillBWait)
	{
		AttackRigidbody.UpdateForce(_DeltaTime);
		float4 AttackVelocity = AttackRigidbody.GetVelocity();

		if (nullptr == ContentFunc::PlatformColCheck(WalkCol))
		{
			PlayerTrans->AddLocalPosition(AttackVelocity * _DeltaTime);
		}

		if (50.0f > AttackVelocity.Size())
		{
			PlayerFSM.ChangeState("Idle");
		}
	}
}

void MinotaurusSkull_Unique::Skill_SlotB_End()
{
	if (nullptr != SkillBPlowUpEffect)
	{
		SkillBPlowUpEffect->IsFadeDeathOn(2.0f);
		SkillBPlowUpEffect = nullptr;
	}
}


void MinotaurusSkull_Unique::DataLoad()
{
	Data = ContentDatabase<SkullData, SkullGrade>::GetData(201); // 201 == 미노타우로스 2세
}

void MinotaurusSkull_Unique::TextureLoad()
{
	DeadPartNames.reserve(6);
	DeadPartNames.push_back("Minotaurus_Head2.png");
	DeadPartNames.push_back("Skul_DeatParts01.png");
	DeadPartNames.push_back("Skul_DeatParts02.png");
	DeadPartNames.push_back("Skul_DeatParts03.png");
	DeadPartNames.push_back("Skul_DeatParts04.png");
	DeadPartNames.push_back("Skul_DeatParts05.png");
}

void MinotaurusSkull_Unique::CreateAnimation()
{
	//Idle Animation
	Render->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Minotaurus_Unique_Idle.png", .FrameInter = 0.1f, .ScaleToTexture = true });
	//Walk Animation
	Render->CreateAnimation({ .AnimationName = "Walk", .SpriteName = "Minotaurus_Unique_Walk.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	//Dash Animation
	Render->CreateAnimation({ .AnimationName = "Dash", .SpriteName = "Minotaurus_Unique_Dash.png", .FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });
	// Fall
	Render->CreateAnimation({ .AnimationName = "Fall", .SpriteName = "Minotaurus_Unique_Fall.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	// Fall Repeat
	Render->CreateAnimation({ .AnimationName = "FallRepeat", .SpriteName = "Minotaurus_Unique_FallRepeat.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	// Jump
	Render->CreateAnimation({ .AnimationName = "Jump", .SpriteName = "Minotaurus_Unique_Jump.png", .FrameInter = 0.08f, .ScaleToTexture = true });

	Render->CreateAnimation({ .AnimationName = "JumpAttack_Land", .SpriteName = "Minotaurus_Unique_JumpAttackLand.png", .FrameInter = 0.1f, .ScaleToTexture = true });
}

void MinotaurusSkull_Unique::AnimationColLoad()
{
	GameEngineDirectory Path;

	Path.MoveParentToDirectory("Resources");
	Path.Move("Resources");
	Path.Move("Data");
	Path.Move("8_Player");
	Path.Move("Minotaurus");
	Path.Move("Unique");

	Pushback_Attack(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("Minotaurus_Unique_AttackA").GetFullPath()), 0.08f);
	Pushback_Attack(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("Minotaurus_Unique_AttackB").GetFullPath()), 0.08f);
	Pushback_JumpAttack(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("Minotaurus_Unique_JumpAttack").GetFullPath()), 0.08f);
	Pushback_SkillA(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("Minotaurus_Unique_SkillA").GetFullPath()), 0.08f);
	Pushback_SkillB(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("Minotaurus_Unique_SkillB").GetFullPath()), 0.1f);
	Pushback_Switch(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("Minotaurus_Unique_Switch").GetFullPath()), 0.1f);

	Render->SetAnimationStartEvent("AttackA", 3, []()
		{
			GameEngineSound::Play("MinoTaurus_ATKA.wav");
		});

	Render->SetAnimationStartEvent("AttackB", 2, []()
		{
			GameEngineSound::Play("MinoTaurus_JumpAttack.wav");
		});

	Render->SetAnimationStartEvent("Switch", 3, []()
		{
			GameEngineSound::Play("MinoTaurus_Swap.wav");
		});
}

void MinotaurusSkull_Unique::PassiveCheck()
{
	if (false == IsPassive)
	{
		IsPassive = true;
		PassiveTime = -1.0f;
		PassiveCol->On();
		PassiveCount = 0;
	}
}

void MinotaurusSkull_Unique::ShotProjectile(size_t _TextureIndex)
{
	_TextureIndex %= 4;

	std::shared_ptr<RigidProjectile> Projectile = GetLevel()->CreateActor<RigidProjectile>();

	GameEngineRandom& Rand = GameEngineRandom::MainRandom;

	float4 ProjectilePos = GetTransform()->GetWorldPosition() + float4(Rand.RandomFloat(-25, 25), Rand.RandomFloat(-25, 25));
	ActorViewDir LookDir = GetViewDir();

	switch (LookDir)
	{
	case ActorViewDir::Left:
		ProjectilePos += float4(-100, 100);
		break;
	case ActorViewDir::Right:
		ProjectilePos += float4(100, 100);
		break;
	}

	Projectile->InitRigd(2000.0f, 0.0f, 1.0f);

	Rigidbody2D& ProjectileRigid = Projectile->GetRigid();

	ContentLevel* Level = GetContentLevel();

	Projectile->ShotProjectile({
		.EffectName = ProjectileEffectNames[_TextureIndex],
		.Pos = ProjectilePos,
		.Dir = float4::Up,
		.ColScale = float4(30, 30, 1),
		.ColOrder = (int)CollisionOrder::Monster,
		.IsPlatformCol = true,
		.IsColDeath = true,
		.IsFlipX = ActorViewDir::Left == GetViewDir(),
		.Damage = GetMeleeAttackDamage() * 0.7f,
		.Speed = 0.0f,
		.LiveTime = 10.0f,
		.EnterEvent = [LookDir, Level](std::shared_ptr<BaseContentActor> _HitActor, ProjectileHitParameter _HitData)
		{
			std::shared_ptr<BaseMonster> CastingActor = _HitActor->DynamicThis<BaseMonster>();

			if (nullptr == CastingActor)
			{
				MsgAssert_Rtti<MinotaurusSkull_Unique>(" - BaseMonster를 상속 받은 클래스만 Monster ColOrder를 가질 수 있습니다.");
				return;
			}

			CastingActor->HitMonster(_HitData.Attack, LookDir, true, true, false, HitEffectType::None);

			EffectManager::PlayEffect({
				.EffectName = "Minotaurus_Projectile_Hit",
				.Position = _HitData.ProjectilePos});
		
			Level->GetCamCtrl().CameraShake(5, 30, 5);

			SoundDoubleCheck::Play("MinoTaurus_Debris_despawn.wav");
		},
		.DeathEvent = [Level](const float4& _DeathPos)
		{
			EffectManager::PlayEffect({
				.EffectName = "Minotaurus_Projectile_Hit",
				.Position = _DeathPos});

			Level->GetCamCtrl().CameraShake(5, 30, 5);

			SoundDoubleCheck::Play("MinoTaurus_Debris_despawn.wav");
		}
		});


	ProjectileRigid.SetActiveGravity(true);
	ProjectileRigid.SetGravity(-1300.0f);

	float4 ShotDir = float4(0, 1);

	switch (LookDir)
	{
	case ActorViewDir::Left:
		ShotDir.RotaitonZDeg(Rand.RandomFloat(20.0f, 45.0f));
		ProjectileRigid.SetVelocity(ShotDir * Rand.RandomFloat(850.0f, 1050.0f));
		break;
	case ActorViewDir::Right:
		ShotDir.RotaitonZDeg(Rand.RandomFloat(-45.0f, -20.0f));
		ProjectileRigid.SetVelocity(ShotDir * Rand.RandomFloat(850.0f, 1050.0f));
		break;
	}
}
