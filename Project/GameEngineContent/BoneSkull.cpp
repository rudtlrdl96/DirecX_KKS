#include "PrecompileHeader.h"
#include "BoneSkull.h"

#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "BoneHead.h"
#include "EffectManager.h"

BoneSkull::BoneSkull()
{
}

BoneSkull::~BoneSkull()
{
}

void BoneSkull::SetBoneSkullState(BoneSkullState _State)
{
	State = _State;

	switch (State)
	{
	case BoneSkull::BoneSkullState::Normal:
		AnimNamePlusText = "";
		break;
	case BoneSkull::BoneSkullState::NoHead:
		AnimNamePlusText = "_NoHead";
		break;
	case BoneSkull::BoneSkullState::NoWeapon:
		AnimNamePlusText = "_NoWeapon";
		break;
	default:
		break;
	}
}

void BoneSkull::Start()
{
	PlayerBaseSkull::Start();

	HeadActor = GetLevel()->CreateActor<BoneHead>();
	HeadActor->SetParentSkull(this);
	HeadActor->Off();

	HeadPickupCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Unknown);
	HeadPickupCol->GetTransform()->SetLocalPosition(float4(0.0f, 30.0f, 1.0f));
	HeadPickupCol->GetTransform()->SetWorldScale(float4(30.0f, 60.0f, 1.0f));
	HeadPickupCol->GetTransform()->SetWorldRotation(float4::Zero);
}

void BoneSkull::Update(float _DeltaTime)
{
	PlayerBaseSkull::Update(_DeltaTime);

	if (true == HeadActor->IsUpdate())
	{
		if (1.0f <= HeadActor->ShotLiveTime)
		{

			if (nullptr != HeadPickupCol->Collision((int)CollisionOrder::BoneHead, ColType::AABBBOX2D, ColType::AABBBOX2D))
			{
				HeadReturn();
				return;
			}
		}		

		if (CurSkillATime >= GetSkillAEndTime())
		{
			HeadReturn();
		}

		IsLockSkillB = false;
	}
	else
	{
		IsLockSkillB = true;
	}

}

void BoneSkull::SwitchEnd()
{
	HeadReturn();
}

void BoneSkull::Skill_SlotA_Enter()
{
	PlayerBaseSkull::Skill_SlotA_Enter();
	SetBoneSkullState(BoneSkullState::NoHead);

	HeadActor->ShotLiveTime = 0.0f;
	HeadActor->Off();

	CurSkillATime = 0.0f;
}

void BoneSkull::Skill_SlotA_Update(float _DeltaTime)
{
	PlayerBaseSkull::Skill_SlotA_Update(_DeltaTime);

	if (false == HeadActor->IsUpdate() && 1 == Render->GetCurrentFrame())
	{
		HeadActor->ShotHead(GetViewDir());
		HeadActor->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition() + float4(8, 50));
		HeadActor->On();
	}
}

void BoneSkull::Skill_SlotB_Enter()
{
	HeadReturn();

	GameEngineTransform* HeadTrans = HeadActor->GetTransform();

	float4 PlayerPos = PlayerTrans->GetWorldPosition();
	float4 HeadPos = HeadTrans->GetWorldPosition();

	PlayerTrans->SetWorldPosition(HeadPos - float4(0, 15));

	EffectManager::PlayEffect({ "SkullAppearance", PlayerPos });
	EffectManager::PlayEffect({ "SkullAppearance", HeadPos - float4(0, 0) });
	EffectManager::PlayEffect({ "LandSmoke", HeadPos - float4(0, 50) });

	PlayerBaseSkull::Skill_SlotB_Enter();


}

void BoneSkull::Switch_Enter()
{
	PlayerBaseSkull::Switch_Enter();
	DashRigidbody.SetVelocity(float4::Zero);
	JumpDir.y = 0;
}

void BoneSkull::Switch_Update(float _DeltaTime)
{
	JumpDir.y += _DeltaTime * ContentConst::Gravity_f;
	PlayerTrans->AddLocalPosition(JumpDir * _DeltaTime);

	std::shared_ptr<GameEngineCollision> GroundColPtr = ContentFunc::PlatformColCheck(GroundCol, true);

	if (nullptr != GroundColPtr)
	{
		float4 CurPos = PlayerTrans->GetWorldPosition();

		GameEngineTransform* ColTrans = GroundColPtr->GetTransform();
		CurPos.y = ColTrans->GetWorldPosition().y + ColTrans->GetWorldScale().hy();

		PlayerTrans->SetWorldPosition(CurPos);
		PlayerTrans->SetLocalPosition(PlayerTrans->GetLocalPosition());

		JumpDir.y = 0.0f;
	}

	switch (GetViewDir())
	{
	case ActorViewDir::Left:
		DashRigidbody.SetVelocity(float4::Left * 175.0f);
		break;
	case ActorViewDir::Right:
		DashRigidbody.SetVelocity(float4::Right * 175.0f);
		break;
	default:
		break;
	}

	PlayerBaseSkull::Switch_Update(_DeltaTime);
}

void BoneSkull::Switch_End()
{
	DashRigidbody.SetVelocity(float4::Zero);
}

void BoneSkull::DataLoad()
{
	Data = ContentDatabase<SkullData, SkullGrade>::GetData(0); // 0 == ¸®Æ²º»
}

void BoneSkull::TextureLoad()
{
	if (nullptr == GameEngineTexture::Find("Skul_DeatParts01.png"))
	{
		GameEngineDirectory Path;
		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("Player");
		Path.Move("Skull");
		Path.Move("BoneSKull");
		Path.Move("DeadPart");

		GameEngineTexture::Load(Path.GetPlusFileName("Skul_DeatParts01.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("Skul_DeatParts02.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("Skul_DeatParts03.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("Skul_DeatParts04.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("Skul_DeatParts05.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("Skul_DeatParts06.png").GetFullPath());
	}

	DeadPartNames.reserve(6);
	DeadPartNames.push_back("Skul_DeatParts01.png");
	DeadPartNames.push_back("Skul_DeatParts02.png");
	DeadPartNames.push_back("Skul_DeatParts03.png");
	DeadPartNames.push_back("Skul_DeatParts04.png");
	DeadPartNames.push_back("Skul_DeatParts05.png");
	DeadPartNames.push_back("Skul_DeatParts06.png");

	TexName_MainSkullUI = "Skul_UI_MainSkull.png";
	TexName_SubSkullUI = "Skul_UI_SubSkull.png";
	TexName_InventoryUI = "Skul_UI_Inventory.png";

	TexName_SkillA = "SkullThrowing.png";
	TexName_SkillB = "Rebone.png";
}

void BoneSkull::CreateAnimation()
{
	//Idle Animation
	Render->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "BoneSkull_Idle.png", .FrameInter = 0.15f, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Idle_NoHead", .SpriteName = "BoneSkull_Idle_NoHead.png", .FrameInter = 0.15f, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Idle_NoWeapon", .SpriteName = "BoneSkull_Idle_NoWeapon.png", .FrameInter = 0.15f, .ScaleToTexture = true });

	//Walk Animation
	Render->CreateAnimation({ .AnimationName = "Walk", .SpriteName = "BoneSkull_Walk.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Walk_NoHead", .SpriteName = "BoneSkull_Walk_NoHead.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Walk_NoWeapon", .SpriteName = "BoneSkull_Walk_NoWeapon.png", .FrameInter = 0.08f, .ScaleToTexture = true });

	//Dash Animation
	Render->CreateAnimation({ .AnimationName = "Dash", .SpriteName = "BoneSkull_Dash.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Dash_NoHead", .SpriteName = "BoneSkull_Dash_NoHead.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Dash_NoWeapon", .SpriteName = "BoneSkull_Dash_NoWeapon.png", .FrameInter = 0.08f, .ScaleToTexture = true });

	// Fall
	Render->CreateAnimation({ .AnimationName = "Fall", .SpriteName = "BoneSkull_Fall.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Fall_NoHead", .SpriteName = "BoneSkull_Fall_NoHead.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Fall_NoWeapon", .SpriteName = "BoneSkull_Fall_NoWeapon.png", .FrameInter = 0.08f, .ScaleToTexture = true });

	// Fall Repeat
	Render->CreateAnimation({ .AnimationName = "FallRepeat", .SpriteName = "BoneSkull_FallRepeat.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "FallRepeat_NoHead", .SpriteName = "BoneSkull_FallRepeat_NoHead.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "FallRepeat_NoWeapon", .SpriteName = "BoneSkull_FallRepeat_NoWeapon.png", .FrameInter = 0.08f, .ScaleToTexture = true });

	// Jump
	Render->CreateAnimation({ .AnimationName = "Jump", .SpriteName = "BoneSkull_Jump.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Jump_NoHead", .SpriteName = "BoneSkull_Jump_NoHead.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Jump_NoWeapon", .SpriteName = "BoneSkull_Jump_NoWeapon.png", .FrameInter = 0.08f, .ScaleToTexture = true });
	
	// AttackA NoHead
	Render->CreateAnimation({ .AnimationName = "AttackA_NoHead", .SpriteName = "BoneSkull_AttackA_NoHead.png", .FrameInter = 0.1f, .ScaleToTexture = true });
	// AttackB NoHead
	Render->CreateAnimation({ .AnimationName = "AttackB_NoHead", .SpriteName = "BoneSkull_AttackB_NoHead.png", .FrameInter = 0.1f, .ScaleToTexture = true });	
	// JumpAttack NoHead
	Render->CreateAnimation({ .AnimationName = "JumpAttack_NoHead", .SpriteName = "BoneSkull_JumpAttack_NoHead.png", .FrameInter = 0.1f, .ScaleToTexture = true });
}

void BoneSkull::AnimationColLoad()
{
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Data");
		Path.Move("8_Player");
		Path.Move("BoneSkull"); 
		
		Pushback_Attack(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("BoneSukll_AttackA").GetFullPath()), 0.1f);
		Pushback_Attack(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("BoneSukll_AttackB").GetFullPath()), 0.1f);
		Pushback_JumpAttack(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("BoneSukll_JumpAttack").GetFullPath()), 0.1f);
		Pushback_SkillA(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("BoneSukll_SkillA").GetFullPath()), 0.1f);
		Pushback_SkillB(ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("BoneSukll_SkillB").GetFullPath()), 0.05f);

		AnimationAttackMetaData SwitchMeta = ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("BoneSukll_Switch").GetFullPath());

		Pushback_Switch(SwitchMeta, 0.06f);
		Pushback_Switch(SwitchMeta, 0.06f);
		Pushback_Switch(SwitchMeta, 0.06f);
	}
}

void BoneSkull::HeadReturn()
{
	HeadActor->Off();
	SetBoneSkullState(BoneSkullState::Normal);

	size_t Frame = Render->GetCurrentFrame();

	switch (FsmState)
	{
	case PlayerBaseSkull::PlayerFSM_State::Idle:
		Render->ChangeAnimation("Idle", Frame);
		break;
	case PlayerBaseSkull::PlayerFSM_State::Walk:
		Render->ChangeAnimation("Walk", Frame);
		break;
	case PlayerBaseSkull::PlayerFSM_State::Fall:
		Render->ChangeAnimation("Fall", Frame);
		break;
	case PlayerBaseSkull::PlayerFSM_State::Jump:
		Render->ChangeAnimation("Jump", Frame);
		break;
	case PlayerBaseSkull::PlayerFSM_State::JumpAttack:
		Render->ChangeAnimation(std::string(AnimColMeta_JumpAttack[JumpAttackCombo].GetAnimationName()), Frame);
		break;
	case PlayerBaseSkull::PlayerFSM_State::Attack:
		Render->ChangeAnimation(std::string(AnimColMeta_Attack[AttackComboCount].GetAnimationName()), Frame);
		break;
	case PlayerBaseSkull::PlayerFSM_State::Dash:
		Render->ChangeAnimation("Dash", Frame);
		break;
	default:
		break;
	}

	CurSkillATime = 1000.0f;
}