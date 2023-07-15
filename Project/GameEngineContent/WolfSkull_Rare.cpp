#include "PrecompileHeader.h"
#include "WolfSkull_Rare.h"
#include "Player.h"
#include "BaseMonster.h"

WolfSkull_Rare::WolfSkull_Rare()
{
}

WolfSkull_Rare::~WolfSkull_Rare()
{
}

void WolfSkull_Rare::Start()
{
	PlayerBaseSkull::Start();

	GroundCol->GetTransform()->SetWorldScale(float4(14.0f, 5.0f, 1.0f));

	DashRigidbody.SetMaxSpeed(1400.0f);
	DashRigidbody.SetGravity(-4000.0f);

	IsActiveSkillA_Value = true;
	IsActiveSkillB_Value = false;
	IsLockSkillB = true;


	SwitchCol = CreateComponent<GameEngineCollision>();
	SwitchCol->SetColType(ColType::AABBBOX2D);
	SwitchCol->Off();

	SkillA_DamageRatio = 2.0f;
	//SkillB_DamageRatio = 2.7f;
	Switch_DamageRatio = 2.0f;

	AttackEffectType = HitEffectType::Sword;
}

void WolfSkull_Rare::Attack_Enter()
{
	PlayerBaseSkull::Attack_Enter();
	AttackTypeValue = AttackType::MeleeAttack;
}

void WolfSkull_Rare::JumpAttack_Enter()
{
	PlayerBaseSkull::JumpAttack_Enter();
	AttackTypeValue = AttackType::MeleeAttack;
}

void WolfSkull_Rare::Skill_SlotA_Enter()
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

void WolfSkull_Rare::Skill_SlotA_Update(float _DeltaTime)
{
	PlayerBaseSkull::Skill_SlotA_Update(_DeltaTime);

	if (false == IsSkillMove && 4 == Render->GetCurrentFrame())
	{
		switch (GetViewDir())
		{
		case ActorViewDir::Left:
			DashRigidbody.SetVelocity(float4::Left * 2500.0f);
			break;
		case ActorViewDir::Right:
			DashRigidbody.SetVelocity(float4::Right * 2500.0f);
			break;
		}

		IsSkillMove = true;
	}

	if (5 == Render->GetCurrentFrame())
	{
		DashRigidbody.SetVelocity(float4::Zero);
	}
}

void WolfSkull_Rare::Skill_SlotA_End()
{
	DashRigidbody.SetMaxSpeed(1400.0f);
	DashRigidbody.SetVelocity(float4::Zero);
	PlayerBaseSkull::Skill_SlotA_End();
	KillEvent = nullptr;
}

void WolfSkull_Rare::Dash_Enter()
{
	PlayerBaseSkull::Dash_Enter();
	WalkCol->GetTransform()->SetLocalPosition(float4(40, 35, 0));
}

void WolfSkull_Rare::Dash_Update(float _DeltaTime)
{
	PlayerBaseSkull::Dash_Update(_DeltaTime);
	BattleActorRigidbody.AddVelocity(float4(0, -3200.0f * _DeltaTime));
}

void WolfSkull_Rare::Dash_End()
{
	PlayerBaseSkull::Dash_End();
	WalkCol->GetTransform()->SetLocalPosition(float4(20, 35, 0));
}

void WolfSkull_Rare::Switch_Enter()
{
	PlayerBaseSkull::Switch_Enter();
	AttackTypeValue = AttackType::MeleeAttack;
	IsSwitchMove = false;
	SwitchMoveProgress = 0.0f;
	DashAvoidance = true;
}

void WolfSkull_Rare::Switch_Update(float _DeltaTime)
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
		}
		break;
		case ActorViewDir::Right:
		{
			float4 Pos = DashPos + float4(225, 0);
			float4 Scale = float4(450, WalkCol->GetTransform()->GetWorldScale().y, 1);

			ColTrans->SetWorldPosition(Pos);
			ColTrans->SetWorldScale(Scale);
			SwitchMoveEnd.x = SearchPositionX(Pos, Scale, Inter, SearchColMode::Left);
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
					MsgAssert_Rtti<WolfSkull_Rare>(" - BaseMonster 클래스를 상속받은 클래스만 Monster ColOrder를 가질 수 있습니다");
					return;
				}

				CastingPtr->HitMonster(GetMeleeAttackDamage() * Switch_DamageRatio, GetViewDir(), true, true, false, HitEffectType::Sword);
			}
		}

		SwitchCol->Off();
	}
}

void WolfSkull_Rare::Switch_End()
{
	PlayerBaseSkull::Switch_End();
	DashAvoidance = false;
}

void WolfSkull_Rare::DataLoad()
{
	Data = ContentDatabase<SkullData, SkullGrade>::GetData(100); // 100 == 나이 든 웨어울프
}

void WolfSkull_Rare::TextureLoad()
{
	DeadPartNames.reserve(6);
	DeadPartNames.push_back("Werewolf_Head2.png");
	DeadPartNames.push_back("Skul_DeatParts01.png");
	DeadPartNames.push_back("Skul_DeatParts02.png");
	DeadPartNames.push_back("Skul_DeatParts03.png");
	DeadPartNames.push_back("Skul_DeatParts04.png");
	DeadPartNames.push_back("Skul_DeatParts05.png");
}

void WolfSkull_Rare::CreateAnimation()
{
	//Idle Animation
	Render->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Wolf_Rare_Idle.png", .FrameInter = 0.1f, .ScaleToTexture = true });
	//Walk Animation
	Render->CreateAnimation({ .AnimationName = "Walk", .SpriteName = "Wolf_Rare_Walk.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	//Dash Animation
	Render->CreateAnimation({ .AnimationName = "Dash", .SpriteName = "Wolf_Rare_Dash.png", .FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });
	// Fall
	Render->CreateAnimation({ .AnimationName = "Fall", .SpriteName = "Wolf_Rare_Fall.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	// Fall Repeat
	Render->CreateAnimation({ .AnimationName = "FallRepeat", .SpriteName = "Wolf_Rare_FallRepeat.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	// Jump
	Render->CreateAnimation({ .AnimationName = "Jump", .SpriteName = "Wolf_Rare_Jump.png", .FrameInter = 0.08f, .ScaleToTexture = true });
}

void WolfSkull_Rare::AnimationColLoad()
{
	GameEngineDirectory Path;

	Path.MoveParentToDirectory("Resources");
	Path.Move("Resources");
	Path.Move("Data");
	Path.Move("8_Player");
	Path.Move("Wolf");
	Path.Move("Rare");

	Pushback_Attack(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("Wolf_Rare_AttackA").GetFullPath()), 0.07f);
	Pushback_Attack(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("Wolf_Rare_AttackB").GetFullPath()), 0.06f);
	Pushback_JumpAttack(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("Wolf_Rare_JumpAttack").GetFullPath()), 0.05f);
	Pushback_SkillA(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("Wolf_Rare_SkillA").GetFullPath()), 0.08f);
	Pushback_Switch(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("Wolf_Rare_Switch").GetFullPath()), 0.1f);
}

void WolfSkull_Rare::Dash()
{
	GameEngineSound::Play("Default_Dash.wav");

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
