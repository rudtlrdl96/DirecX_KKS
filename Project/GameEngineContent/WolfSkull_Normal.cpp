#include "PrecompileHeader.h"
#include "WolfSkull_Normal.h"
#include "BaseMonster.h"

WolfSkull_Normal::WolfSkull_Normal()
{
}

WolfSkull_Normal::~WolfSkull_Normal()
{
}

void WolfSkull_Normal::Start()
{
	Type = SkullType::Speed;

	PlayerBaseSkull::Start();

	GroundCol->GetTransform()->SetWorldScale(float4(14.0f, 5.0f, 1.0f));

	DashRigidbody.SetMaxSpeed(1500.0f);
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
}

void WolfSkull_Normal::Skill_SlotA_Enter()
{
	PlayerBaseSkull::Skill_SlotA_Enter();
	IsSkillMove = false;

	AttackTypeValue = AttackType::MagicAttack;
}

void WolfSkull_Normal::Skill_SlotA_Update(float _DeltaTime)
{
	PlayerBaseSkull::Skill_SlotA_Update(_DeltaTime);

	if (false == IsSkillMove && 4 == Render->GetCurrentFrame())
	{
		switch (GetViewDir())
		{
		case ActorViewDir::Left:
			DashRigidbody.SetVelocity(float4::Left * 750.0f);
			break;
		case ActorViewDir::Right:
			DashRigidbody.SetVelocity(float4::Right * 750.0f);
			break;
		}

		IsSkillMove = true;
	}
}

void WolfSkull_Normal::Dash_Update(float _DeltaTime)
{
	PlayerBaseSkull::Dash_Update(_DeltaTime);
	BattleActorRigidbody.AddVelocity(float4(0, -2800.0f * _DeltaTime));
}

void WolfSkull_Normal::Switch_Enter()
{
	PlayerBaseSkull::Switch_Enter();
	IsSwitchMove = false;
	SwitchMoveProgress = 0.0f;
}

void WolfSkull_Normal::Switch_Update(float _DeltaTime)
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
			float4 Pos = DashPos - float4(150, 0);
			float4 Scale = float4(300, WalkCol->GetTransform()->GetWorldScale().y, 1);

			ColTrans->SetWorldPosition(Pos);
			ColTrans->SetWorldScale(Scale);
			SwitchMoveEnd.x = SearchPositionX(Pos, Scale, Inter, SearchColMode::Right);
		}
			break;
		case ActorViewDir::Right:
		{		
			float4 Pos = DashPos + float4(150, 0);
			float4 Scale = float4(300, WalkCol->GetTransform()->GetWorldScale().y, 1);

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
					MsgAssert_Rtti<WolfSkull_Normal>(" - BaseMonster 클래스를 상속받은 클래스만 Monster ColOrder를 가질 수 있습니다");
					return;
				}

				CastingPtr->HitMonster(GetMeleeAttackDamage() * Switch_DamageRatio, GetViewDir(), true, true, false);
			}
		}

		SwitchCol->Off();
	}
}

void WolfSkull_Normal::DataLoad()
{
	Data = ContentDatabase<SkullData, SkullGrade>::GetData(1); // 1 == 웨어울프
}

void WolfSkull_Normal::TextureLoad()
{
	DeadPartNames.reserve(6);
	DeadPartNames.push_back("Werewolf_Head1.png");
	DeadPartNames.push_back("Skul_DeatParts01.png");
	DeadPartNames.push_back("Skul_DeatParts02.png");
	DeadPartNames.push_back("Skul_DeatParts03.png");
	DeadPartNames.push_back("Skul_DeatParts04.png");
	DeadPartNames.push_back("Skul_DeatParts05.png");

	TexName_MainSkullUI = "Normal_WereWolf_UI_MainSkull.png";
	TexName_SubSkullUI = "Normal_WereWolf_UI_SubSkull.png";
	TexName_InventoryUI = "Normal_WereWolf_UI_Inventory.png";

	TexName_SkillA = "Normal_WereWolf_Skill1.png";
	TexName_SkillB = "Normal_WereWolf_Skill1.png";
}

void WolfSkull_Normal::CreateAnimation()
{
	//Idle Animation
	Render->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Wolf_Normal_Idle.png", .FrameInter = 0.1f, .ScaleToTexture = true });
	//Walk Animation
	Render->CreateAnimation({ .AnimationName = "Walk", .SpriteName = "Wolf_Normal_Walk.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	//Dash Animation
	Render->CreateAnimation({ .AnimationName = "Dash", .SpriteName = "Wolf_Normal_Dash.png", .FrameInter = 0.15f, .Loop = false, .ScaleToTexture = true });
	// Fall
	Render->CreateAnimation({ .AnimationName = "Fall", .SpriteName = "Wolf_Normal_Fall.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	// Fall Repeat
	Render->CreateAnimation({ .AnimationName = "FallRepeat", .SpriteName = "Wolf_Normal_FallRepeat.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	// Jump
	Render->CreateAnimation({ .AnimationName = "Jump", .SpriteName = "Wolf_Normal_Jump.png", .FrameInter = 0.08f, .ScaleToTexture = true });
}

void WolfSkull_Normal::AnimationColLoad()
{
	GameEngineDirectory Path;

	Path.MoveParentToDirectory("Resources");
	Path.Move("Resources");
	Path.Move("Data");
	Path.Move("8_Player");
	Path.Move("Wolf");
	Path.Move("Normal");

	Pushback_Attack(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("Wolf_Normal_AttackA").GetFullPath()), 0.07f);
	Pushback_Attack(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("Wolf_Normal_AttackB").GetFullPath()), 0.07f);
	Pushback_JumpAttack(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("Wolf_Normal_JumpAttack").GetFullPath()), 0.08f);
	Pushback_SkillA(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("Wolf_Normal_SkillA").GetFullPath()), 0.08f);
	Pushback_Switch(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("Wolf_Normal_Switch").GetFullPath()), 0.1f);
}

void WolfSkull_Normal::Dash()
{
	switch (GetViewDir())
	{
	case ActorViewDir::Left:
		DashRigidbody.SetVelocity(float4(-1, 0.3f, 0) * DashVelocity);
		break;
	case ActorViewDir::Right:
		DashRigidbody.SetVelocity(float4(1, 0.3f, 0) * DashVelocity);
		break;
	default:
		break;
	}

	float4 CurVel = BattleActorRigidbody.GetVelocity();
	CurVel.y = 0.0f;
	BattleActorRigidbody.SetVelocity(CurVel);
}
