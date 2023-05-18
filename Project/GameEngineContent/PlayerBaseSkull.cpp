#include "PrecompileHeader.h"
#include "PlayerBaseSkull.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "CollisionDebugRender.h"
#include "CaptureTrail.h"

PlayerBaseSkull::PlayerBaseSkull()
{
}

PlayerBaseSkull::~PlayerBaseSkull()
{
}

void PlayerBaseSkull::Start()
{
	SkullRenderer = CreateComponent<ContentSpriteRenderer>();
	SkullRenderer->GetTransform()->SetLocalPosition(float4::Zero);
	SkullRenderer->SetScaleRatio(2.0f);

	TextureLoad();
	CreateAnimation();
	AnimationColLoad();

	if (nullptr == GameEngineSprite::Find("Player_DashSmokeEffect.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("Player");
		Path.Move("Effect");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Player_DashSmokeEffect.png").GetFullPath(), 6, 2);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Player_DoubleJumpEffect.png").GetFullPath(), 5, 2);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("HitSkul.png").GetFullPath(), 5, 2);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("HitNormal.png").GetFullPath(), 6, 2);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("SkullAppearance.png").GetFullPath(), 7, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("LandSmoke.png").GetFullPath(), 7, 3);
	}

	if (false == GameEngineInput::IsKey("PlayerMove_Left"))
	{
		GameEngineInput::CreateKey("PlayerMove_Up", VK_UP);
		GameEngineInput::CreateKey("PlayerMove_Down", VK_DOWN);
		GameEngineInput::CreateKey("PlayerMove_Left", VK_LEFT);
		GameEngineInput::CreateKey("PlayerMove_Right", VK_RIGHT);
		GameEngineInput::CreateKey("PlayerMove_Dash", 'Z');
		GameEngineInput::CreateKey("PlayerMove_Attack", 'X');
		GameEngineInput::CreateKey("PlayerMove_Jump", 'C');
		GameEngineInput::CreateKey("PlayerMove_Skill_A", 'A');
		GameEngineInput::CreateKey("PlayerMove_Skill_B", 'S');

		GameEngineInput::CreateKey("PlayerCollisionDebugSwitch", VK_F2);
	}

	PlayerFSM.Init(this);

	PlayerFSM.AddFSM("Idle", &PlayerBaseSkull::Idle_Enter, &PlayerBaseSkull::Idle_Update, &PlayerBaseSkull::Idle_End);
	PlayerFSM.AddFSM("Walk", &PlayerBaseSkull::Walk_Enter, &PlayerBaseSkull::Walk_Update, &PlayerBaseSkull::Walk_End);
	PlayerFSM.AddFSM("Attack", &PlayerBaseSkull::Attack_Enter, &PlayerBaseSkull::Attack_Update, &PlayerBaseSkull::Attack_End);
	PlayerFSM.AddFSM("Jump", &PlayerBaseSkull::Jump_Enter, &PlayerBaseSkull::Jump_Update, &PlayerBaseSkull::Jump_End);
	PlayerFSM.AddFSM("JumpAttack", &PlayerBaseSkull::JumpAttack_Enter, &PlayerBaseSkull::JumpAttack_Update, &PlayerBaseSkull::JumpAttack_End);
	PlayerFSM.AddFSM("Fall", &PlayerBaseSkull::Fall_Enter, &PlayerBaseSkull::Fall_Update, &PlayerBaseSkull::Fall_End);
	PlayerFSM.AddFSM("Dash", &PlayerBaseSkull::Dash_Enter, &PlayerBaseSkull::Dash_Update, &PlayerBaseSkull::Dash_End);
	PlayerFSM.AddFSM("Switch", &PlayerBaseSkull::Switch_Enter, &PlayerBaseSkull::Switch_Update, &PlayerBaseSkull::Switch_End);
	PlayerFSM.AddFSM("Skill_A", &PlayerBaseSkull::Skill_SlotA_Enter, &PlayerBaseSkull::Skill_SlotA_Update, &PlayerBaseSkull::Skill_SlotA_End);
	PlayerFSM.AddFSM("Skill_B", &PlayerBaseSkull::Skill_SlotB_Enter, &PlayerBaseSkull::Skill_SlotB_Update, &PlayerBaseSkull::Skill_SlotB_End);

	PlayerFSM.ChangeState("Idle");

	if (false == EffectManager::IsCreate("PlayerDashEffect"))
	{
		EffectManager::CreateMetaData("PlayerDashEffect", { 
			"Player_DashSmokeEffect.png" ,
			float4::Zero,
			0, 11,
			0.04f,
			2.0f});

		EffectManager::CreateMetaData("PlayerJumpEffect", {
			"Player_DoubleJumpEffect.png" ,
			float4::Zero,
			0, 9,
			0.05f,
			2.0f});

		EffectManager::CreateMetaData("SkullAppearance", {
			"SkullAppearance.png" ,
			float4::Zero,
			0, 6,
			0.05f,
			2.0f });

		EffectManager::CreateMetaData("HitSkul", {
			"HitSkul.png" ,
			float4::Zero,
			0, 9,
			0.05f,
			2.0f });

		EffectManager::CreateMetaData("HitNormal", {
			"HitNormal.png" ,
			float4::Zero,
			0, 11,
			0.05f,
			2.0f });

		EffectManager::CreateMetaData("LandSmoke", {
			"LandSmoke.png" ,
			float4::Zero,
			0, 20,
			0.03f,
			2.0f });
	}

	DashRigidbody.SetActiveGravity(false);
	DashRigidbody.SetMaxSpeed(1050);
	DashRigidbody.SetFricCoeff(3500);
	
	AttackRigidbody.SetActiveGravity(false);
	AttackRigidbody.SetMaxSpeed(300);
	AttackRigidbody.SetFricCoeff(600);

	GroundCol = CreateComponent<GameEngineCollision>();
	GroundCol->GetTransform()->SetLocalPosition(float4(0.0f, -2.0f, 1.0f));
	GroundCol->GetTransform()->SetLocalScale(float4(30.0f, 5.0f, 1.0f));	
	
	JumpCol = CreateComponent<GameEngineCollision>();
	JumpCol->GetTransform()->SetLocalPosition(float4(0.0f, 66.0f, 1.0f));
	JumpCol->GetTransform()->SetLocalScale(float4(30.0f, 5.0f, 1.0f));

	WalkCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Player);
	WalkCol->GetTransform()->SetLocalPosition(float4(20, 30, 0));
	WalkCol->GetTransform()->SetLocalScale(float4(10, 58, 1));

	DashTrail = GetLevel()->CreateActor<CaptureTrail>();
	DashTrail->GetTransform()->SetParent(GetTransform());
	DashTrail->SetTime(0.4f);
	DashTrail->SetColor(float4(0.0f, 0.0f, 0.0f, 1.0f), float4::Null);

	//DashTrail->GetTransform()->SetLocalPosition(float4(0, 0, 1));
}

void PlayerBaseSkull::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("PlayerCollisionDebugSwitch"))
	{
		if (true == IsDebug())
		{
			DebugOff();
		}
		else
		{
			DebugOn();
			CreateColDebugRender();
		}
	}

	PlayerFSM.Update(_DeltaTime);
	DashRigidbody.UpdateForce(_DeltaTime);

	FallCooldown -= _DeltaTime;

	if (false == CanDash)
	{
		DashCoolTime += _DeltaTime;
	}

	if (DashCoolTime >= 0.9f)
	{
		CanDash = true;
		DashCoolTime = 0.0f;
	}
}

std::shared_ptr< GameEngineCollision> PlayerBaseSkull::PlatformColCheck(const std::shared_ptr<class GameEngineCollision>& _Col, bool _IsHalf /*= false*/)
{
	std::shared_ptr<GameEngineCollision> ReslutCol = nullptr;

	ReslutCol = _Col->Collision(CollisionOrder::Platform_Normal, ColType::AABBBOX2D, ColType::AABBBOX2D);

	if (nullptr != ReslutCol)
	{
		return ReslutCol;
	}

	if (false == _IsHalf)
	{
		return ReslutCol;
	}

	ReslutCol = _Col->Collision(CollisionOrder::Platform_Half, ColType::AABBBOX2D, ColType::AABBBOX2D);

	if (nullptr != ReslutCol)
	{
		return ReslutCol;
	}

	return ReslutCol;
}

void PlayerBaseSkull::Pushback_Attack(const AnimationAttackMetaData& _AnimData, float _InterTime)
{
	CreateAttackAnim(_AnimData, _InterTime);
	AnimColMeta_Attack.push_back(_AnimData);
}

void PlayerBaseSkull::Pushback_JumpAttack(const AnimationAttackMetaData& _AnimData, float _InterTime)
{
	CreateAttackAnim(_AnimData, _InterTime);
	AnimColMeta_JumpAttack.push_back(_AnimData);
}

void PlayerBaseSkull::Pushback_SkillA(const AnimationAttackMetaData& _AnimData, float _InterTime)
{
	CreateAttackAnim(_AnimData, _InterTime);
	AnimColMeta_SkillA.push_back(_AnimData);
}

void PlayerBaseSkull::Pushback_SkillB(const AnimationAttackMetaData& _AnimData, float _InterTime)
{
	CreateAttackAnim(_AnimData, _InterTime);
	AnimColMeta_SkillB.push_back(_AnimData);
}

void PlayerBaseSkull::SetViewDir(ActorViewDir _ViewDir)
{
	ViewDir = _ViewDir;

	GameEngineTransform* WalkColTrans = WalkCol->GetTransform();
	GameEngineTransform* GroundColTrans = GroundCol->GetTransform();
	GameEngineTransform* JumpColTrans = JumpCol->GetTransform();

	switch (ViewDir)
	{
	case ActorViewDir::Left:
	{
		GetTransform()->SetLocalNegativeScaleX();

		float4 GroundColScale = GroundColTrans->GetLocalScale();
		GroundColScale.x = fabsf(GroundColScale.x);
		GroundColScale.y = -fabsf(GroundColScale.y);
		GroundColTrans->SetLocalScale(GroundColScale);

		float4 JumpColScale = JumpColTrans->GetLocalScale();
		JumpColScale.x = fabsf(JumpColScale.x);
		JumpColScale.y = -fabsf(JumpColScale.y);
		JumpColTrans->SetLocalScale(JumpColScale);

		float4 WalkColScale = WalkColTrans->GetLocalScale();
		WalkColScale.x = fabsf(WalkColScale.x);
		WalkColScale.y = -fabsf(WalkColScale.y);
		WalkColTrans->SetLocalScale(WalkColScale);

	}
		break;
	case ActorViewDir::Right:
	{
		GetTransform()->SetLocalPositiveScaleX();


		float4 GroundColScale = GroundColTrans->GetLocalScale();
		GroundColScale.x = fabsf(GroundColScale.x);
		GroundColScale.y = fabsf(GroundColScale.y);
		GroundColTrans->SetLocalScale(GroundColScale);

		float4 JumpColScale = JumpColTrans->GetLocalScale();
		JumpColScale.x = fabsf(JumpColScale.x);
		JumpColScale.y = fabsf(JumpColScale.y);
		JumpColTrans->SetLocalScale(JumpColScale);

		float4 WalkColScale = WalkColTrans->GetLocalScale();
		WalkColScale.x = fabsf(WalkColScale.x);
		WalkColScale.y = fabsf(WalkColScale.y);
		WalkColTrans->SetLocalScale(WalkColScale);


	}
		break;
	default:
		break;
	}
}

void PlayerBaseSkull::CreateColDebugRender()
{
	{
		std::shared_ptr<CollisionDebugRender> GroundDebugRender = GetLevel()->CreateActor<CollisionDebugRender>();

		GroundDebugRender->SetColor(CollisionDebugRender::DebugColor::Red);
		GroundDebugRender->SetTargetCollision(GroundCol);
		GroundDebugRender->GetTransform()->SetParent(GroundCol->GetTransform(), false);	
		GroundDebugRender->GetTransform()->AddLocalPosition(float4(0, 0, -10));
	}

	{
		std::shared_ptr<CollisionDebugRender> JumpColDebugRender = GetLevel()->CreateActor<CollisionDebugRender>();

		JumpColDebugRender->SetColor(CollisionDebugRender::DebugColor::Red);
		JumpColDebugRender->SetTargetCollision(JumpCol);
		JumpColDebugRender->GetTransform()->SetParent(JumpCol->GetTransform(), false);
		JumpColDebugRender->GetTransform()->AddLocalPosition(float4(0, 0, -10));
	}

	{
		std::shared_ptr<CollisionDebugRender> WalkDebugRender = GetLevel()->CreateActor<CollisionDebugRender>();

		WalkDebugRender->SetColor(CollisionDebugRender::DebugColor::Green);
		WalkDebugRender->SetTargetCollision(WalkCol);
		WalkDebugRender->GetTransform()->SetParent(WalkCol->GetTransform(), false);
		WalkDebugRender->GetTransform()->AddLocalPosition(float4(0, 0, -10));
	}

}

void PlayerBaseSkull::CreateAttackAnim(const AnimationAttackMetaData& _AnimData, float _InterTime)
{
	SkullRenderer->CreateAnimation({ 
		.AnimationName = _AnimData.GetAnimationName().data(),
		.SpriteName = _AnimData.GetSpriteName().data(),
		.Start = _AnimData.GetStartFrame() ,
		.End = _AnimData.GetEndFrame(),
		.FrameInter = _InterTime,
		.ScaleToTexture = true});

}
