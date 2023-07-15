#include "PrecompileHeader.h"
#include "PlayerBaseSkull.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "CollisionDebugRender.h"
#include "CaptureTrail.h"
#include "Player.h"
#include "BaseMonster.h"
#include "TexturePartParticle.h"
#include "CaptureRenderer.h"
#include "CaptureAnimation.h"

PlayerBaseSkull::PlayerBaseSkull()
{
}

PlayerBaseSkull::~PlayerBaseSkull()
{
}

float PlayerBaseSkull::GetMeleeAttackDamage() const
{
	return ParentPlayer->GetMeleeAttack() * Data.MeleeAttack;
}

float PlayerBaseSkull::GetMagicAttackDamage() const
{
	return ParentPlayer->GetMagicAttack() * Data.MagicAttack;
}

void PlayerBaseSkull::SetPlayer(std::shared_ptr<class Player> _ParentPlayer)
{

	if (nullptr == _ParentPlayer)
	{
		MsgAssert_Rtti<PlayerBaseSkull>(" - nullptr 플레이어 포인터가 들어왔습니다");
		return;
	}

	ParentPlayer = _ParentPlayer.get();
	PlayerTrans = _ParentPlayer->GetTransform();
}

std::shared_ptr<GameEngineActor> PlayerBaseSkull::SkullDeath()
{
	GameEngineRandom& Rand = GameEngineRandom::MainRandom;

	std::shared_ptr<GameEngineActor> ReturnActor = nullptr;

	for (size_t i = 0; i < DeadPartNames.size(); i++)
	{
		std::shared_ptr<TexturePartParticle> NewDeadPart = GetLevel()->CreateActor<TexturePartParticle>();

		if (nullptr == ReturnActor)
		{
			ReturnActor = NewDeadPart;
		}

		NewDeadPart->GetTransform()->SetWorldPosition(PlayerTrans->GetWorldPosition() + float4(0, 40, -0.1f));

		float4 RandDir = float4(Rand.RandomFloat(-0.8f, 0.8f), 1.0f);
		RandDir.Normalize();
		NewDeadPart->Init(DeadPartNames[i], RandDir, 500.0f, 1.5f);

		float4 Scale = NewDeadPart->GetTransform()->GetWorldScale();
		NewDeadPart->GetTransform()->SetWorldScale(Scale * 2.0f);
	}

	return ReturnActor;
}

void PlayerBaseSkull::PlayStoryMove(const float4& _MovePos, std::function<void()> _EndCallback /*= nullptr*/)
{
	StoryMovePos = _MovePos;
	StoryMoveEndCallback = _EndCallback;
	PlayerFSM.ChangeState("StoryMove");
}

void PlayerBaseSkull::Start()
{
	BattleActor::Start();

	DataLoad();
	TextureLoad();

	CreateAnimation();
	AnimationColLoad();

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
		GameEngineInput::CreateKey("PlayerMove_Switch", VK_SPACE);

		GameEngineInput::CreateKey("PlayerCollisionDebugSwitch", VK_F2);
	}

	Type = Data.SkullType;

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
	PlayerFSM.AddFSM("Behavior", &PlayerBaseSkull::Behavior_Enter, &PlayerBaseSkull::Behavior_Update, &PlayerBaseSkull::Behavior_End);
	PlayerFSM.AddFSM("StoryMove", &PlayerBaseSkull::StoryMove_Enter, &PlayerBaseSkull::StoryMove_Update, &PlayerBaseSkull::StoryMove_End);

	PlayerFSM.ChangeState("Idle");

	BattleActorRigidbody.SetMaxSpeed(1800.0f);
	BattleActorRigidbody.SetFricCoeff(900.0f);

	DashRigidbody.SetActiveGravity(false);
	DashRigidbody.SetMaxSpeed(1050);
	DashRigidbody.SetFricCoeff(3500);


	switch (Type)
	{
	case SkullType::Speed:
		DashRigidbody.SetMaxSpeed(1300);
		break;
	default:
		break;
	}

	
	AttackRigidbody.SetActiveGravity(false);
	AttackRigidbody.SetMaxSpeed(1000);
	AttackRigidbody.SetFricCoeff(5000);

	GroundCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Unknown);
	GroundCol->GetTransform()->SetLocalPosition(float4(0.0f, 2.5f, 1.0f));
	GroundCol->GetTransform()->SetWorldScale(float4(22.0f, 5.0f, 1.0f));	
	GroundCol->GetTransform()->SetWorldRotation(float4::Zero);	
	GroundCol->SetColType(ColType::AABBBOX2D);
	
	JumpCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Unknown);
	JumpCol->GetTransform()->SetLocalPosition(float4(0.0f, 74.0f, 1.0f));
	JumpCol->GetTransform()->SetWorldScale(float4(22.0f, 5.0f, 1.0f));
	JumpCol->GetTransform()->SetWorldRotation(float4::Zero);
	JumpCol->SetColType(ColType::AABBBOX2D);

	WalkCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Unknown);
	WalkCol->GetTransform()->SetLocalPosition(float4(25, 35, 0));
	WalkCol->GetTransform()->SetWorldScale(float4(10, 56, 1));
	WalkCol->GetTransform()->SetWorldRotation(float4::Zero);
	WalkCol->SetColType(ColType::AABBBOX2D);

	BackCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Unknown);
	BackCol->GetTransform()->SetLocalPosition(float4(-25, 35, 0));
	BackCol->GetTransform()->SetWorldScale(float4(10, 56, 1));
	BackCol->GetTransform()->SetWorldRotation(float4::Zero);
	BackCol->SetColType(ColType::AABBBOX2D);

	AttackCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::PlayerAttack);
	AttackCol->GetTransform()->SetWorldRotation(float4::Zero);
	AttackCol->SetColType(ColType::AABBBOX2D);
	AttackCol->Off();

	RayCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Unknown);
	RayCol->SetColType(ColType::AABBBOX2D);
	RayCol->Off();

	DashTrail = GetLevel()->CreateActor<CaptureTrail>();
	DashTrail->GetTransform()->SetParent(GetTransform());
	DashTrail->SetTime(0.4f);
	DashTrail->SetColor(float4(0.0f, 0.0f, 0.0f, 1.0f), float4::Null);

	EffectCaptureTrail = GetLevel()->CreateActor<CaptureTrail>();
	EffectCaptureTrail->GetTransform()->SetParent(GetTransform());
	EffectCaptureTrail->SetTime(0.4f);
	EffectCaptureTrail->SetColor(float4(0.0f, 0.0f, 0.0f, 1.0f), float4::Null);

	AttackEnterCheck.SetCol(AttackCol, (UINT)CollisionOrder::Monster);
	AttackEnterCheck.SetRender(Render);

	AttackEnterCheck.SetEvent([this](std::shared_ptr<BaseContentActor> _Ptr, const AttackColMetaData& _Data)
		{			
			std::shared_ptr<BaseMonster> CastPtr = std::static_pointer_cast<BaseMonster>(_Ptr);

			if (nullptr != CastPtr)
			{
				switch (AttackTypeValue)
				{
				case PlayerBaseSkull::AttackType::MeleeAttack:
					CastPtr->HitMonster(GetMeleeAttackDamage() * CurDamageRatio * _Data.AttackRatio, GetViewDir(), _Data.IsStiffen, _Data.IsPush, false, AttackEffectType, KillEvent);
					break;
				case PlayerBaseSkull::AttackType::MagicAttack:
					CastPtr->HitMonster(GetMagicAttackDamage() * CurDamageRatio * _Data.AttackRatio, GetViewDir(), _Data.IsStiffen, _Data.IsPush, true, AttackEffectType, KillEvent);
					break;
				default:
					break;
				}
			}

			if (nullptr != HitEvent)
			{
				HitEvent();
			}
		});
}

void PlayerBaseSkull::Update(float _DeltaTime)
{
	BattleActorRigidbody.UpdateForce(_DeltaTime);
	float4 HitVelocity = BattleActorRigidbody.GetVelocity();
	float4 DashVelocity = DashRigidbody.GetVelocity();

	if (0 < HitVelocity.x + DashVelocity.x)
	{
		if (ViewDir == ActorViewDir::Left && nullptr != ContentFunc::PlatformColCheck(BackCol))
		{
			HitVelocity.x = 0.0f;
			DashVelocity.x = 0.0f;
		}
		else if(nullptr != ContentFunc::PlatformColCheck(WalkCol))
		{
			HitVelocity.x = 0.0f;
			DashVelocity.x = 0.0f;
		}
	}
	else 
	{
		if (ViewDir == ActorViewDir::Left && nullptr != ContentFunc::PlatformColCheck(WalkCol))
		{
			HitVelocity.x = 0.0f;
			DashVelocity.x = 0.0f;
		}
		else if (nullptr != ContentFunc::PlatformColCheck(BackCol))
		{
			HitVelocity.x = 0.0f;
			DashVelocity.x = 0.0f;
		}
	}

	if (true == IsFallEnd)
	{
		BattleActorRigidbody.SetVelocity(float4::Zero);
	}

	if (0 < HitVelocity.y + DashVelocity.y)
	{
		if (nullptr != ContentFunc::PlatformColCheck(JumpCol))
		{
			HitVelocity.y = 0.0f;
			DashVelocity.y = 0.0f;
			BattleActorRigidbody.SetVelocity(HitVelocity);
			DashRigidbody.SetVelocity(DashVelocity);
		}
	}
	else if(false == IsDownPlatformCheckOff)
	{
		bool IsHalfCheck = 0.0f >= FallCooldown;

		std::shared_ptr<GameEngineCollision> GroundColPtr = ContentFunc::PlatformColCheck(GroundCol, IsHalfCheck);

		if (nullptr != GroundColPtr)
		{
			HitVelocity.y = 0.0f;
			DashVelocity.y = 0.0f;
			HitVelocity.x = HitVelocity.x * (1.0f - _DeltaTime);
			BattleActorRigidbody.SetVelocity(HitVelocity);
			DashRigidbody.SetVelocity(DashVelocity);

			float4 CurPos = PlayerTrans->GetWorldPosition();

			GameEngineTransform* ColTrans = GroundColPtr->GetTransform();
			CurPos.y = ColTrans->GetWorldPosition().y + ColTrans->GetWorldScale().hy();

			PlayerTrans->SetWorldPosition(CurPos);
			PlayerTrans->SetLocalPosition(PlayerTrans->GetLocalPosition());
		}
	}

	PlayerTrans->AddLocalPosition(HitVelocity * _DeltaTime);

	if (1.0f > RenderEffectProgress)
	{
		Buffer.Color = float4::LerpClamp(RenderEffectStartColor, RenderEffectEndColor, RenderEffectProgress);
	}
	else
	{
		Buffer.Color = float4::Zero;
	}

	BattleActor::Update(_DeltaTime);

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

	IsFallEnd = false;

	PlayerFSM.Update(_DeltaTime);
	DashRigidbody.UpdateForce(_DeltaTime);
}

void PlayerBaseSkull::Pushback_Attack(const AnimationAttackMetaData& _AnimData, float _InterTime)
{
	if (nullptr == Render->FindAnimation(_AnimData.GetAnimationName()))
	{
		CreateAttackAnim(_AnimData, _InterTime);
	}

	AnimColMeta_Attack.push_back(_AnimData);
}

void PlayerBaseSkull::Pushback_JumpAttack(const AnimationAttackMetaData& _AnimData, float _InterTime)
{
	if (nullptr == Render->FindAnimation(_AnimData.GetAnimationName()))
	{
		CreateAttackAnim(_AnimData, _InterTime);
	}

	AnimColMeta_JumpAttack.push_back(_AnimData);
}

void PlayerBaseSkull::Pushback_SkillA(const AnimationAttackMetaData& _AnimData, float _InterTime)
{
	if (nullptr == Render->FindAnimation(_AnimData.GetAnimationName()))
	{
		CreateAttackAnim(_AnimData, _InterTime);
	}

	AnimColMeta_SkillA.push_back(_AnimData);
}

void PlayerBaseSkull::Pushback_SkillB(const AnimationAttackMetaData& _AnimData, float _InterTime)
{
	if (nullptr == Render->FindAnimation(_AnimData.GetAnimationName()))
	{
		CreateAttackAnim(_AnimData, _InterTime);
	}

	AnimColMeta_SkillB.push_back(_AnimData);
}

void PlayerBaseSkull::Pushback_Switch(const AnimationAttackMetaData& _AnimData, float _InterTime)
{
	if (nullptr == Render->FindAnimation(_AnimData.GetAnimationName()))
	{
		CreateAttackAnim(_AnimData, _InterTime);	
	}

	AnimColMeta_Switch.push_back(_AnimData);
}

void PlayerBaseSkull::SetViewDir(ActorViewDir _ViewDir)
{
	ViewDir = _ViewDir;

	switch (ViewDir)
	{
	case ActorViewDir::Left:
	{
		GetTransform()->SetLocalNegativeScaleX();
	}
		break;
	case ActorViewDir::Right:
	{
		GetTransform()->SetLocalPositiveScaleX();
	}
		break;
	default:
		break;
	}
}

void PlayerBaseSkull::CoolTimeCheck(float _DeltaTime)
{

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

	CurSkillATime += _DeltaTime;
	CurSkillBTime += _DeltaTime;

	RenderEffectProgress += _DeltaTime * RenderEffectSpeed;

}

void PlayerBaseSkull::Jump()
{
	float4 JumpVel = BattleActorRigidbody.GetVelocity();

	if (JumpVel.y < JumpPower)
	{
		JumpVel.y = JumpPower;
	}

	BattleActorRigidbody.SetVelocity(JumpVel);
}

void PlayerBaseSkull::Dash()
{
	GameEngineSound::Play(DashSound);

	switch (ViewDir)
	{
	case ActorViewDir::Left:
		DashRigidbody.SetVelocity(float4::Left * DashVelocity);
		break;
	case ActorViewDir::Right:
		DashRigidbody.SetVelocity(float4::Right * DashVelocity);
		break;
	default:
		break;
	}
}

float PlayerBaseSkull::SearchPositionX(const float4& _Pos, const float4& _ColScale, float _Inter, SearchColMode _Mode)
{
	float ResultX = 0.0f;

	switch (_Mode)
	{
	case SearchColMode::Left:
		ResultX = _Pos.x + _ColScale.hx();
		break;
	case SearchColMode::Right:
		ResultX = _Pos.x - _ColScale.hx();
		break;
	default:
		break;
	}

	RayCol->On();

	GameEngineTransform* ColTrans = RayCol->GetTransform();

	ColTrans->SetWorldPosition(_Pos);
	ColTrans->SetWorldScale(_ColScale);

	std::vector<std::shared_ptr<GameEngineCollision>> PlatformDatas;

	if (true == RayCol->CollisionAll(CollisionOrder::Platform_Normal, PlatformDatas, ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		float NearDis = D3D10_FLOAT32_MAX;

		for (size_t i = 0; i < PlatformDatas.size(); i++)
		{
			GameEngineTransform* PlatformTrans = PlatformDatas[i]->GetTransform();

			float4 PlatformColPos = PlatformTrans->GetWorldPosition();
			float4 PlatformSize = PlatformTrans->GetWorldScale();

			float PlatformX = 0.0f;

			switch (_Mode)
			{
			case SearchColMode::Left:
				PlatformX = PlatformColPos.x - (PlatformSize.hx() + _Inter);

				if (PlatformX < ResultX)
				{
					ResultX = PlatformX;
				}

				break;
			case SearchColMode::Right:
				PlatformX = PlatformColPos.x + PlatformSize.hx() + _Inter;

				if (PlatformX > ResultX)
				{
					ResultX = PlatformX;
				}
				break;
			default:
				break;
			}
		}
	}

	RayCol->Off();
	return ResultX;
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
	Render->CreateAnimation({
		.AnimationName = _AnimData.GetAnimationName().data(),
		.SpriteName = _AnimData.GetSpriteName().data(),
		.Start = _AnimData.GetStartFrame() ,
		.End = _AnimData.GetEndFrame(),
		.FrameInter = _InterTime,
		.Loop = false,
		.ScaleToTexture = true});
}


void PlayerBaseSkull::RendererEffect(const float4& _StartColor, const float4& _EndColor, float _Speed)
{
	RenderEffectProgress = 0.0f;
	RenderEffectSpeed = _Speed;
	RenderEffectStartColor = _StartColor;
	RenderEffectEndColor = _EndColor;
}

void PlayerBaseSkull::CaptureRenderTex(const float4& _StartColor, const float4& _EndColor, float _Speed)
{
	EffectCaptureTrail->SetColor(_StartColor, _EndColor);
	EffectCaptureTrail->SetTime(1.0f / _Speed);

	std::shared_ptr<CaptureRenderer> WaitRender = EffectCaptureTrail->PlayTrail(Render->GetTexName(),
		Render->GetAtlasData(),
		(ActorViewDir::Left == ViewDir),
		Render->GetScaleRatio());
}

void PlayerBaseSkull::EffectCaptureAnimation(const CaptureAnimParameter& _Parameter)
{
	std::shared_ptr<CaptureAnimation> Capture = GetLevel()->CreateActor<CaptureAnimation>();
	Capture->PlayCapture(_Parameter);
}