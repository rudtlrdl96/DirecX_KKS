#include "PrecompileHeader.h"
#include "WolfSkull_Unique.h"
#include "Player.h"
#include "BaseMonster.h"
#include "Projectile.h"

WolfSkull_Unique::WolfSkull_Unique()
{
}

WolfSkull_Unique::~WolfSkull_Unique()
{
}

void WolfSkull_Unique::Start()
{
	PlayerBaseSkull::Start();

	GroundCol->GetTransform()->SetWorldScale(float4(14.0f, 5.0f, 1.0f));

	DashRigidbody.SetMaxSpeed(1400.0f);
	DashRigidbody.SetGravity(-4000.0f);

	IsActiveSkillA_Value = true;
	IsActiveSkillB_Value = true;

	SwitchCol = CreateComponent<GameEngineCollision>();
	SwitchCol->SetColType(ColType::AABBBOX2D);
	SwitchCol->Off();

	SkillA_DamageRatio = 2.0f;
	//SkillB_DamageRatio = 2.7f;
	Switch_DamageRatio = 2.0f;

	AttackEffectType = HitEffectType::Sword;
}

void WolfSkull_Unique::Update(float _DeltaTime)
{
	PlayerBaseSkull::Update(_DeltaTime);

	if (true == IsSwitchTrailAttack)
	{
		TrailAttackProgress += _DeltaTime * 7.5f;

		if (1.0f <= TrailAttackProgress)
		{
			std::shared_ptr<Projectile> TrailProjectile = GetLevel()->CreateActor<Projectile>();
			ActorViewDir Dir = GetViewDir();

			float4 AttackPos = float4::LerpClamp(SwitchMoveStart, SwitchMoveEnd, static_cast<float>(TrailAttackCount) / 7.0f);

			TrailProjectile->ShotProjectile({
				.EffectName = "WereWolf_Unique_SwitchAttack",
				.Pos = AttackPos + float4(0, 50),
				.Dir = float4::Zero,
				.ColScale = float4(80, 150),
				.ColOrder = (int)CollisionOrder::Monster,
				.ProjectileColType = ColType::OBBBOX2D,
				.IsRot = false,
				.IsEffectEndDeath = true,
				.Damage = GetMeleeAttackDamage(),
				.Speed = 0.0f,
				.EnterEvent = [Dir](std::shared_ptr<BaseContentActor> _ColActor, const ProjectileHitParameter& _Hit)
				{
					std::shared_ptr<BaseMonster> CastingPtr = _ColActor->DynamicThis<BaseMonster>();

					if (nullptr == CastingPtr)
					{
						MsgAssert_Rtti<WolfSkull_Unique>(" - BaseMonster를 상속받은 클래스만 Monster ColOrder를 가질 수 있습니다.");
						return;
					}

					CastingPtr->HitMonster(_Hit.Attack, Dir, true, false, false, HitEffectType::Sword);
				}
				});

			TrailProjectile->GetTransform()->SetLocalRotation(float4(0, 0, GameEngineRandom::MainRandom.RandomFloat(0, 360.0f)));

			++TrailAttackCount;
			TrailAttackProgress = 0.0f;
		}

		if (7 <= TrailAttackCount)
		{
			TrailAttackProgress = 0.0f;
			IsSwitchTrailAttack = false;
			TrailAttackCount = 0;
		}
	}
}

void WolfSkull_Unique::Attack_Enter()
{
	PlayerBaseSkull::Attack_Enter();
	AttackTypeValue = AttackType::MeleeAttack;
}

void WolfSkull_Unique::JumpAttack_Enter()
{
	PlayerBaseSkull::JumpAttack_Enter();
	AttackTypeValue = AttackType::MeleeAttack;
}

void WolfSkull_Unique::Skill_SlotA_Enter()
{
	PlayerBaseSkull::Skill_SlotA_Enter();
	IsSkillMove = false;

	AttackTypeValue = AttackType::MagicAttack;

	KillEvent = [this]()
	{
		ParentPlayer->HealPlayer(1, float4::Up);
	};

	DashRigidbody.SetMaxSpeed(3000.0f);
}

void WolfSkull_Unique::Skill_SlotA_Update(float _DeltaTime)
{
	PlayerBaseSkull::Skill_SlotA_Update(_DeltaTime);

	if (false == IsSkillMove && 4 == Render->GetCurrentFrame())
	{
		switch (GetViewDir())
		{
		case ActorViewDir::Left:
		{
			DashRigidbody.SetVelocity(float4::Left * 2500.0f);

			std::shared_ptr<EffectActor> Effect = EffectManager::PlayEffect({
				.EffectName = "WereWolf_Unique_Predation",
				.Position = GetTransform()->GetWorldPosition() + float4(-50, 70),
				.FlipX = true });

			Effect->GetTransform()->SetParent(GetTransform());
		}
			break;
		case ActorViewDir::Right:
		{
			DashRigidbody.SetVelocity(float4::Right * 2500.0f);

			std::shared_ptr<EffectActor> Effect = EffectManager::PlayEffect({
				.EffectName = "WereWolf_Unique_Predation",
				.Position = GetTransform()->GetWorldPosition() + float4(50, 70),
				.FlipX = false });

			Effect->GetTransform()->SetParent(GetTransform());
		}	
			break;
		}

		IsSkillMove = true;
	}

	if (5 == Render->GetCurrentFrame())
	{
		DashRigidbody.SetVelocity(float4::Zero);
	}
}

void WolfSkull_Unique::Skill_SlotA_End()
{
	DashRigidbody.SetMaxSpeed(1400.0f);
	DashRigidbody.SetVelocity(float4::Zero);
	PlayerBaseSkull::Skill_SlotA_End();
	KillEvent = nullptr;
}

void WolfSkull_Unique::Skill_SlotB_Enter()
{
	PlayerBaseSkull::Skill_SlotB_Enter();
	AttackTypeValue = AttackType::MeleeAttack;
	IsSwitchMove = false;
	SwitchMoveProgress = 0.0f;
}

void WolfSkull_Unique::Skill_SlotB_Update(float _DeltaTime)
{
	PlayerBaseSkull::Skill_SlotB_Update(_DeltaTime);

	if (true == IsSwitchMove)
	{
		SwitchMoveProgress += _DeltaTime * 15.0f;

		PlayerTrans->SetWorldPosition(float4::LerpClamp(SwitchMoveStart, SwitchMoveEnd, SwitchMoveProgress));
	}

	if (false == IsSwitchMove && 1 == Render->GetCurrentFrame())
	{
		IsSwitchMove = true;
		SwitchMoveProgress = 0.0f;
		float4 DashPos = GetTransform()->GetWorldPosition();
		DashPos.y += WalkCol->GetTransform()->GetWorldScale().hy() + 6;

		float Inter = GroundCol->GetTransform()->GetWorldScale().x;

		SwitchMoveStart = GetTransform()->GetWorldPosition();
		SwitchMoveEnd = GetTransform()->GetWorldPosition();

		GameEngineTransform* ColTrans = SwitchCol->GetTransform();

		switch (GetViewDir())
		{
		case ActorViewDir::Left:
		{
			float4 Pos = DashPos - float4(225, 0);
			float4 Scale = float4(450, WalkCol->GetTransform()->GetWorldScale().y, 1);

			ColTrans->SetWorldPosition(Pos);
			ColTrans->SetWorldScale(Scale);
			SwitchMoveEnd.x = SearchPositionX(Pos, Scale, Inter, SearchColMode::Right);


			EffectManager::PlayEffect({
				.EffectName = "WereWolf_Unique_SwitchFlash",
				.Position = Pos + float4(0, 40),
				.Scale = 0.75f,
				.FlipX = true });

			EffectManager::PlayEffect({
				.EffectName = "WereWolf_Unique_SwitchFlash",
				.Position = Pos + float4(0, 15),
				.Scale = 0.5f,
				.FlipX = true });


			EffectManager::PlayEffect({
				.EffectName = "WereWolf_Unique_DashSmoke",
				.Position = GetTransform()->GetWorldPosition() + float4(230, 85),
				.FlipX = true });
		}
		break;
		case ActorViewDir::Right:
		{
			float4 Pos = DashPos + float4(225, 0);
			float4 Scale = float4(450, WalkCol->GetTransform()->GetWorldScale().y, 1);

			ColTrans->SetWorldPosition(Pos);
			ColTrans->SetWorldScale(Scale);
			SwitchMoveEnd.x = SearchPositionX(Pos, Scale, Inter, SearchColMode::Left);

			EffectManager::PlayEffect({
				.EffectName = "WereWolf_Unique_SwitchFlash",
				.Position = Pos + float4(0, 40),
				.Scale = 0.75f,
				.FlipX = false ,
				});

			EffectManager::PlayEffect({
				.EffectName = "WereWolf_Unique_SwitchFlash",
				.Position = Pos + float4(0, 15),
				.Scale = 0.5f,
				.FlipX = false });

			EffectManager::PlayEffect({
				.EffectName = "WereWolf_Unique_DashSmoke",
				.Position = GetTransform()->GetWorldPosition() + float4(-230, 85),
				.FlipX = false });
		}
		break;
		}

		SwitchCol->On();

		std::vector<std::shared_ptr<GameEngineCollision>> Cols;
		Cols.reserve(8);

		if (true == SwitchCol->CollisionAll((int)CollisionOrder::Monster, Cols, ColType::AABBBOX2D, ColType::AABBBOX2D))
		{
			for (size_t i = 0; i < Cols.size(); i++)
			{
				std::shared_ptr<BaseMonster> CastingPtr = Cols[i]->GetActor()->DynamicThis<BaseMonster>();

				if (nullptr == CastingPtr)
				{
					MsgAssert_Rtti<WolfSkull_Unique>(" - BaseMonster 클래스를 상속받은 클래스만 Monster ColOrder를 가질 수 있습니다");
					return;
				}

				CastingPtr->HitMonster(GetMeleeAttackDamage() * Switch_DamageRatio, GetViewDir(), true, true, false, HitEffectType::Sword, [this]()
					{
						CurSkillBTime = GetSkillBEndTime();
					});
			}
		}

		SwitchCol->Off();
	}
}

void WolfSkull_Unique::Skill_SlotB_End()
{
	PlayerBaseSkull::Skill_SlotB_End();
}

void WolfSkull_Unique::Dash_Enter()
{
	PlayerBaseSkull::Dash_Enter();
	WalkCol->GetTransform()->SetLocalPosition(float4(40, 35, 0));
}

void WolfSkull_Unique::Dash_Update(float _DeltaTime)
{
	PlayerBaseSkull::Dash_Update(_DeltaTime);
	BattleActorRigidbody.AddVelocity(float4(0, -3200.0f * _DeltaTime));
}

void WolfSkull_Unique::Dash_End()
{
	PlayerBaseSkull::Dash_End();
	WalkCol->GetTransform()->SetLocalPosition(float4(20, 35, 0));
}

void WolfSkull_Unique::Switch_Enter()
{
	PlayerBaseSkull::Switch_Enter();
	AttackTypeValue = AttackType::MeleeAttack;
	IsSwitchMove = false;
	SwitchMoveProgress = 0.0f;
}

void WolfSkull_Unique::Switch_Update(float _DeltaTime)
{
	PlayerBaseSkull::Switch_Update(_DeltaTime);

	if (true == IsSwitchMove)
	{
		SwitchMoveProgress += _DeltaTime * 15.0f;

		PlayerTrans->SetWorldPosition(float4::LerpClamp(SwitchMoveStart, SwitchMoveEnd, SwitchMoveProgress));
	}

	if (false == IsSwitchMove && 1 == Render->GetCurrentFrame())
	{
		IsSwitchMove = true;
		SwitchMoveProgress = 0.0f;
		IsSwitchTrailAttack = true;
		TrailAttackProgress = 0.0f;
		TrailAttackCount = 0;

		float4 DashPos = GetTransform()->GetWorldPosition();
		DashPos.y += WalkCol->GetTransform()->GetWorldScale().hy() + 6;

		float Inter = GroundCol->GetTransform()->GetWorldScale().x;

		SwitchMoveStart = GetTransform()->GetWorldPosition();
		SwitchMoveEnd = GetTransform()->GetWorldPosition();

		GameEngineTransform* ColTrans = SwitchCol->GetTransform();

		switch (GetViewDir())
		{
		case ActorViewDir::Left:
		{
			float4 Pos = DashPos - float4(225, 0);
			float4 Scale = float4(450, WalkCol->GetTransform()->GetWorldScale().y, 1);

			ColTrans->SetWorldPosition(Pos);
			ColTrans->SetWorldScale(Scale);
			SwitchMoveEnd.x = SearchPositionX(Pos, Scale, Inter, SearchColMode::Right);

			EffectManager::PlayEffect({
				.EffectName = "WereWolf_Unique_DashSmoke",
				.Position = GetTransform()->GetWorldPosition() + float4(230, 85),
				.FlipX = true});
		}
		break;
		case ActorViewDir::Right:
		{
			float4 Pos = DashPos + float4(225, 0);
			float4 Scale = float4(450, WalkCol->GetTransform()->GetWorldScale().y, 1);

			ColTrans->SetWorldPosition(Pos);
			ColTrans->SetWorldScale(Scale);
			SwitchMoveEnd.x = SearchPositionX(Pos, Scale, Inter, SearchColMode::Left);

			EffectManager::PlayEffect({
				.EffectName = "WereWolf_Unique_DashSmoke",
				.Position = GetTransform()->GetWorldPosition() + float4(-230, 85),
				.FlipX = false });
		}
		break;
		}

		SwitchCol->On();

		std::vector<std::shared_ptr<GameEngineCollision>> Cols;
		Cols.reserve(8);

		if (true == SwitchCol->CollisionAll((int)CollisionOrder::Monster, Cols, ColType::AABBBOX2D, ColType::AABBBOX2D))
		{
			for (size_t i = 0; i < Cols.size(); i++)
			{
				std::shared_ptr<BaseMonster> CastingPtr = Cols[i]->GetActor()->DynamicThis<BaseMonster>();

				if (nullptr == CastingPtr)
				{
					MsgAssert_Rtti<WolfSkull_Unique>(" - BaseMonster 클래스를 상속받은 클래스만 Monster ColOrder를 가질 수 있습니다");
					return;
				}

				CastingPtr->HitMonster(GetMeleeAttackDamage() * Switch_DamageRatio, GetViewDir(), true, true, false, HitEffectType::Sword);
			}
		}

		SwitchCol->Off();
	}
}

void WolfSkull_Unique::DataLoad()
{
	Data = ContentDatabase<SkullData, SkullGrade>::GetData(200); // 200 == 우두머리 웨어울프
}

void WolfSkull_Unique::TextureLoad()
{
	DeadPartNames.reserve(6);
	DeadPartNames.push_back("Werewolf_Head3.png");
	DeadPartNames.push_back("Skul_DeatParts01.png");
	DeadPartNames.push_back("Skul_DeatParts02.png");
	DeadPartNames.push_back("Skul_DeatParts03.png");
	DeadPartNames.push_back("Skul_DeatParts04.png");
	DeadPartNames.push_back("Skul_DeatParts05.png");
}

void WolfSkull_Unique::CreateAnimation()
{
	//Idle Animation
	Render->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Wolf_Unique_Idle.png", .FrameInter = 0.1f, .ScaleToTexture = true });
	//Walk Animation
	Render->CreateAnimation({ .AnimationName = "Walk", .SpriteName = "Wolf_Unique_Walk.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	//Dash Animation
	Render->CreateAnimation({ .AnimationName = "Dash", .SpriteName = "Wolf_Unique_Dash.png", .FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });
	// Fall
	Render->CreateAnimation({ .AnimationName = "Fall", .SpriteName = "Wolf_Unique_Fall.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	// Fall Repeat
	Render->CreateAnimation({ .AnimationName = "FallRepeat", .SpriteName = "Wolf_Unique_FallRepeat.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	// Jump
	Render->CreateAnimation({ .AnimationName = "Jump", .SpriteName = "Wolf_Unique_Jump.png", .FrameInter = 0.08f, .ScaleToTexture = true });
}

void WolfSkull_Unique::AnimationColLoad()
{
	GameEngineDirectory Path;

	Path.MoveParentToDirectory("Resources");
	Path.Move("Resources");
	Path.Move("Data");
	Path.Move("8_Player");
	Path.Move("Wolf");
	Path.Move("Unique");

	Pushback_Attack(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("Wolf_Unique_AttackA").GetFullPath()), 0.07f);
	Pushback_Attack(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("Wolf_Unique_AttackB").GetFullPath()), 0.06f);
	Pushback_JumpAttack(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("Wolf_Unique_JumpAttack").GetFullPath()), 0.05f);
	Pushback_SkillA(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("Wolf_Unique_SkillA").GetFullPath()), 0.08f);
	Pushback_SkillB(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("Wolf_Unique_SkillB").GetFullPath()), 0.05f);
	Pushback_Switch(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("Wolf_Unique_Switch").GetFullPath()), 0.05f);
}

void WolfSkull_Unique::Dash()
{
	switch (GetViewDir())
	{
	case ActorViewDir::Left:
		DashRigidbody.SetVelocity(float4(-1, 0.35f, 0) * DashVelocity);
		break;
	case ActorViewDir::Right:
		DashRigidbody.SetVelocity(float4(1, 0.35f, 0) * DashVelocity);
		break;
	default:
		break;
	}

	float4 CurVel = BattleActorRigidbody.GetVelocity();
	CurVel.y = 0.0f;
	BattleActorRigidbody.SetVelocity(CurVel);
}
