#include "PrecompileHeader.h"
#include "MinotaurusSkull_Rare.h"
#include "BaseMonster.h"

MinotaurusSkull_Rare::MinotaurusSkull_Rare()
{
}

MinotaurusSkull_Rare::~MinotaurusSkull_Rare()
{
	AttackDoubleCheck.clear();
	PassiveDoubleCheck.clear();
}

void MinotaurusSkull_Rare::Start()
{
	Type = SkullType::Power;

	PlayerBaseSkull::Start();

	IsActiveSkillA_Value = true;
	IsActiveSkillB_Value = false;
	IsLockSkillB = true;

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

	PassiveCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::PlayerAttack);
	PassiveCol->GetTransform()->SetLocalPosition(float4(0, 15, 0));
	PassiveCol->GetTransform()->SetLocalScale(float4(110, 30, 1));
	PassiveCol->SetColType(ColType::AABBBOX2D);
	PassiveCol->Off();

	SkillARigidbody.SetMaxSpeed(3000.0f);
	SkillARigidbody.SetGravity(-3500.0f);
	SkillARigidbody.SetActiveGravity(true);
	SkillARigidbody.SetFricCoeff(1000.0f);

	SkillA_DamageRatio = 2.0f;
}

void MinotaurusSkull_Rare::Update(float _DeltaTime)
{
	PlayerBaseSkull::Update(_DeltaTime);

	if (true == IsPassive)
	{
		PassiveTime += _DeltaTime;

		for (std::pair<const UINT, float>& Pair : PassiveDoubleCheck)
		{
			Pair.second += _DeltaTime;
		}

		std::vector<std::shared_ptr<GameEngineCollision>> AllCol;
		AllCol.reserve(8);

		if (true == PassiveCol->CollisionAll((int)CollisionOrder::Monster, AllCol, ColType::AABBBOX2D, ColType::AABBBOX2D))
		{
			for (size_t i = 0; i < AllCol.size(); i++)
			{
				std::shared_ptr<BaseMonster> CastingCol = AllCol[i]->GetActor()->DynamicThis<BaseMonster>();

				if (nullptr == CastingCol)
				{
					MsgAssert_Rtti<MinotaurusSkull_Rare>(" - BaseMonster를 상속 받은 클래스만 Monster ColOrder를 가질 수 있습니다.");
					return;
				}

				if (0.0f > PassiveDoubleCheck[CastingCol->GetActorCode()])
				{
					continue;
				}

				CastingCol->HitMonster(GetMeleeAttackDamage() * 0.5f, GetViewDir(), true, false, false, HitEffectType::Normal);
				PassiveDoubleCheck[CastingCol->GetActorCode()] = -0.5f;
			}
		}

		if (3.0f <= PassiveTime)
		{
			if (nullptr != PassiveEffect)
			{
				PassiveEffect->Death();
			}

			PassiveEffect = nullptr;			
			IsPassive = false;
			PassiveTime = 0.0f;
			PassiveCol->Off();
			PassiveDoubleCheck.clear();
		}
	}
}

void MinotaurusSkull_Rare::Attack_Enter()
{
	PlayerBaseSkull::Attack_Enter();

	HitEvent = [this]()
	{
		GetContentLevel()->GetCamCtrl().CameraShake(5, 30, 5);
	};
}

void MinotaurusSkull_Rare::Attack_End()
{
	PlayerBaseSkull::Attack_End();

	HitEvent = nullptr;
}

void MinotaurusSkull_Rare::JumpAttack_Enter()
{
	Render->ChangeAnimation("JumpAttack");

	AttackRigidbody.SetActiveGravity(true);
	AttackRigidbody.SetGravity(-13000.0f);
	AttackRigidbody.SetMaxSpeed(5000.0f);
	AttackRigidbody.SetVelocity(float4(0, 1300));

	JumpAttackTime = 0.0f;
	JumpAttackLandTime = 0.0f;

	BattleActorRigidbody.SetVelocity(float4::Zero);
	DashRigidbody.SetVelocity(float4::Zero);
	IsJumpAttackLand = false;
	IsDownPlatformCheckOff = true;

	AttackDoubleCheck.clear();
}

void MinotaurusSkull_Rare::JumpAttack_Update(float _DeltaTime)
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
					MsgAssert_Rtti<MinotaurusSkull_Rare>(" - BaseMonster를 상속 받은 클래스만 Monster ColOrder를 가질 수 있습니다.");
					return;
				}

				CastingCol->HitMonster(GetMeleeAttackDamage(), GetViewDir(), true, true, false, HitEffectType::MinoTaurus);
				AttackDoubleCheck[CastingCol->GetActorCode()] = CastingCol;
			}
		}
	}

	if (false == IsDownPlatformCheckOff && false == IsJumpAttackLand && nullptr != ContentFunc::PlatformColCheck(GroundCol, true))
	{
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

void MinotaurusSkull_Rare::JumpAttack_End()
{
	AttackRigidbody.SetActiveGravity(false);
	AttackRigidbody.SetMaxSpeed(1000.0f);

	AttackDoubleCheck.clear();
	IsDownPlatformCheckOff = false;
}

void MinotaurusSkull_Rare::Switch_Enter()
{
	PlayerBaseSkull::Switch_Enter();
	IsSwitchMove = false;
}

void MinotaurusSkull_Rare::Switch_Update(float _DeltaTime)
{
	PlayerBaseSkull::Switch_Update(_DeltaTime);

	if (false == IsSwitchMove && 3 == Render->GetCurrentFrame())
	{
		IsSwitchMove = true;

		switch (GetViewDir())
		{
		case ActorViewDir::Left:
			AttackRigidbody.SetVelocity(float4::Left * 800.0f);
			break;

		case ActorViewDir::Right:
			AttackRigidbody.SetVelocity(float4::Right * 800.0f);
			break;
		default:
			break;
		}
	}

	AttackRigidbody.UpdateForce(_DeltaTime);

	if (nullptr == ContentFunc::PlatformColCheck(WalkCol))
	{
		float4 AttackVelocity = AttackRigidbody.GetVelocity() * _DeltaTime;
		PlayerTrans->AddLocalPosition(AttackVelocity);
	}

}

void MinotaurusSkull_Rare::Dash_Enter()
{
	PlayerBaseSkull::Dash_Enter();

	std::shared_ptr<EffectActor> DashEffect = EffectManager::PlayEffect({
		.EffectName = "DashTackleEffect",
		.FlipX = ActorViewDir::Left == GetViewDir()});

	DashEffect->GetTransform()->SetParent(GetTransform());
	DashEffect->GetTransform()->SetLocalPosition(float4(30, 45, -35));

	AttackDoubleCheck.clear();
	DashAttackCol->On();
}

void MinotaurusSkull_Rare::Dash_Update(float _DeltaTime)
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
				MsgAssert_Rtti<MinotaurusSkull_Rare>(" - BaseMonster를 상속 받은 클래스만 Monster ColOrder를 가질 수 있습니다.");
				return;
			}

			CastingCol->HitMonster(GetMeleeAttackDamage(), GetViewDir(), true, true, false, HitEffectType::Normal);
			AttackDoubleCheck[CastingCol->GetActorCode()] = CastingCol;
		}
	}
}

void MinotaurusSkull_Rare::Dash_End()
{
	PlayerBaseSkull::Dash_End();
	AttackDoubleCheck.clear();
	DashAttackCol->Off();
}

void MinotaurusSkull_Rare::Skill_SlotA_Enter()
{
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
	SkillALandTime = 0.0f;
	SkillACol->Off();

	PassiveCheck();
	IsDownPlatformCheckOff = true;
}

void MinotaurusSkull_Rare::Skill_SlotA_Update(float _DeltaTime)
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
		IsSkillALand = true;
		Render->ChangeAnimation("JumpAttack_Land");
		GetContentLevel()->GetCamCtrl().CameraShake(15, 120, 20);

		std::shared_ptr<EffectActor> StampEffect = EffectManager::PlayEffect({
			.EffectName = "StampEffect",
			.Position = GetTransform()->GetWorldPosition(),
			.Scale = 0.65f});

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
					MsgAssert_Rtti<MinotaurusSkull_Rare>(" - BaseMonster를 상속 받은 클래스만 Monster ColOrder를 가질 수 있습니다.");
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

		if (0.3f <= SkillALandTime)
		{
			PlayerFSM.ChangeState("Idle");
		}
	}
}

void MinotaurusSkull_Rare::Skill_SlotA_End()
{
	PlayerBaseSkull::Skill_SlotA_End();
	AttackDoubleCheck.clear();
	AttackRigidbody.SetActiveGravity(false);
	AttackRigidbody.SetMaxSpeed(1000.0f);
	SkillACol->Off();
	IsDownPlatformCheckOff = false;
}


void MinotaurusSkull_Rare::DataLoad()
{
	Data = ContentDatabase<SkullData, SkullGrade>::GetData(101); // 101 == 미노타우로스
}

void MinotaurusSkull_Rare::TextureLoad()
{
	DeadPartNames.reserve(6);
	DeadPartNames.push_back("Minotaurus_Head1.png");
	DeadPartNames.push_back("Skul_DeatParts01.png");
	DeadPartNames.push_back("Skul_DeatParts02.png");
	DeadPartNames.push_back("Skul_DeatParts03.png");
	DeadPartNames.push_back("Skul_DeatParts04.png");
	DeadPartNames.push_back("Skul_DeatParts05.png");

	TexName_MainSkullUI = "Rare_Minotaurus_UI_MainSkull.png";
	TexName_SubSkullUI = "Rare_Minotaurus_UI_SubSkull.png";
	TexName_InventoryUI = "Rare_Minotaurus_UI_Inventory.png";

	TexName_SkillA = "Minotaurus_Stamp1.png";
	TexName_SkillB = "Empty.png";
}

void MinotaurusSkull_Rare::CreateAnimation()
{
	//Idle Animation
	Render->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Minotaurus_Rare_Idle.png", .FrameInter = 0.1f, .ScaleToTexture = true });
	//Walk Animation
	Render->CreateAnimation({ .AnimationName = "Walk", .SpriteName = "Minotaurus_Rare_Walk.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	//Dash Animation
	Render->CreateAnimation({ .AnimationName = "Dash", .SpriteName = "Minotaurus_Rare_Dash.png", .FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });
	// Fall
	Render->CreateAnimation({ .AnimationName = "Fall", .SpriteName = "Minotaurus_Rare_Fall.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	// Fall Repeat
	Render->CreateAnimation({ .AnimationName = "FallRepeat", .SpriteName = "Minotaurus_Rare_FallRepeat.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	// Jump
	Render->CreateAnimation({ .AnimationName = "Jump", .SpriteName = "Minotaurus_Rare_Jump.png", .FrameInter = 0.08f, .ScaleToTexture = true });

	Render->CreateAnimation({ .AnimationName = "JumpAttack_Land", .SpriteName = "Minotaurus_Rare_JumpAttackLand.png", .FrameInter = 0.1f, .ScaleToTexture = true });
}

void MinotaurusSkull_Rare::AnimationColLoad()
{
	GameEngineDirectory Path;

	Path.MoveParentToDirectory("Resources");
	Path.Move("Resources");
	Path.Move("Data");
	Path.Move("8_Player");
	Path.Move("Minotaurus");
	Path.Move("Rare");

	Pushback_Attack(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("Minotaurus_Rare_AttackA").GetFullPath()), 0.1f);
	Pushback_Attack(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("Minotaurus_Rare_AttackB").GetFullPath()), 0.1f);
	Pushback_JumpAttack(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("Minotaurus_Rare_JumpAttack").GetFullPath()), 0.08f);
	Pushback_SkillA(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("Minotaurus_Rare_SkillA").GetFullPath()), 0.08f);
	Pushback_Switch(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("Minotaurus_Rare_Switch").GetFullPath()), 0.1f);
}

void MinotaurusSkull_Rare::PassiveCheck()
{
	if (false == IsPassive)
	{
		PassiveEffect = EffectManager::PlayEffect({
			.EffectName = "Minotaurus_Rare_Passive",
			.Position = GetTransform()->GetWorldPosition() + float4(0, 10),
			.Scale = 0.6f,
			.Triger = EffectDeathTrigger::Time
			,.Time = 100.0f,
			});

		PassiveEffect->GetTransform()->SetParent(GetTransform());
		IsPassive = true;
		PassiveTime = 0.0f;
		PassiveDoubleCheck.clear();
		PassiveCol->On();
	}
}
