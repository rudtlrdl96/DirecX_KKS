#include "PrecompileHeader.h"
#include "MinotaurusSkull_Rare.h"

MinotaurusSkull_Rare::MinotaurusSkull_Rare()
{
}

MinotaurusSkull_Rare::~MinotaurusSkull_Rare()
{
}

void MinotaurusSkull_Rare::Start()
{
	Type = SkullType::Power;

	PlayerBaseSkull::Start();

	IsActiveSkillA_Value = true;
	IsActiveSkillB_Value = false;
	IsLockSkillB = true;

	AttackEffectType = HitEffectType::MinoTaurus;
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

	TexName_SkillA = "Minotaurus_PlowUp1.png";
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

	Pushback_Attack(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("Minotaurus_Rare_AttackA").GetFullPath()), 0.07f);
	Pushback_Attack(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("Minotaurus_Rare_AttackB").GetFullPath()), 0.06f);
	Pushback_JumpAttack(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("Minotaurus_Rare_JumpAttack").GetFullPath()), 0.05f);
	Pushback_SkillA(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("Minotaurus_Rare_SkillA").GetFullPath()), 0.08f);
	Pushback_Switch(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("Minotaurus_Rare_Switch").GetFullPath()), 0.1f);
}
