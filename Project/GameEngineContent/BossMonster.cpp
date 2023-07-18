#include "PrecompileHeader.h"
#include "BossMonster.h"
#include "Player.h"

BossMonster::BossMonster() :
	CurAnimPause(PauseTimes["Idle"])
{
}

BossMonster::~BossMonster()
{
}

void BossMonster::Stun(float _Time)
{
	if (false == StateIsIdle && false == StateIsHit)
	{
		return;
	}

	BaseMonster::Stun(_Time);
}

void BossMonster::Start()
{
	BaseMonster::Start();

	CreateAnimation();

	BossFsm.Init(this);

	BossFsm.AddFSM("Idle", &BossMonster::Idle_Enter, &BossMonster::Idle_Update, &BossMonster::Idle_End);
	BossFsm.AddFSM("Dash", &BossMonster::Dash_Enter, &BossMonster::Dash_Update, &BossMonster::Dash_End);
	BossFsm.AddFSM("BackDash", &BossMonster::BackDash_Enter, &BossMonster::BackDash_Update, &BossMonster::BackDash_End);
	BossFsm.AddFSM("Pattern", &BossMonster::Pattern_Enter, &BossMonster::Pattern_Update, &BossMonster::Pattern_End);
	BossFsm.AddFSM("Hit", &BossMonster::Hit_Enter, &BossMonster::Hit_Update, &BossMonster::Hit_End);
	BossFsm.AddFSM("Behavior", &BossMonster::Behavior_Enter, &BossMonster::Behavior_Update, &BossMonster::Behavior_End);
	BossFsm.AddFSM("Groggy", &BossMonster::Groggy_Enter, &BossMonster::Groggy_Update, &BossMonster::Groggy_End);

	BossRigidbody.SetMaxSpeed(2000.0f);
	BossRigidbody.SetFricCoeff(2000.0f);

	BodyCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Monster);
	BodyCol->SetColType(ColType::AABBBOX2D);

	WalkCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Unknown);
	WalkCol->SetColType(ColType::AABBBOX2D);

	BackCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Unknown);
	BackCol->SetColType(ColType::AABBBOX2D);

	GroundCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Unknown);
	GroundCol->SetColType(ColType::AABBBOX2D);

	PlayerFindCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Unknown);
	PlayerFindCol->GetTransform()->SetLocalScale(float4(100000, 100000, 1));
	PlayerFindCol->SetColType(ColType::AABBBOX2D);

	BossFsm.ChangeState("Idle");

}

void BossMonster::Update(float _DeltaTime)
{
	CurWaitTime += _DeltaTime;
	CurFramePauseTime += _DeltaTime;

	if (CurFrameIndex != Render->GetCurrentFrame())
	{
		CurFrameIndex = static_cast<UINT>(Render->GetCurrentFrame());
		CurFramePauseTime = 0.0f;
	}

	if (CurFramePauseTime < CurAnimPause[CurFrameIndex])
	{
		Render->SetAnimPauseOn();
	}
	else
	{
		Render->SetAnimPauseOff();
	}

	if (false == IsDeathIntro)
	{
		BossFsm.Update(_DeltaTime);
	}

	BaseMonster::Update(_DeltaTime);

	if (true == IsGroundUpOff)
	{
		IsGroundUp = false;
		return;
	}

	std::shared_ptr<GameEngineCollision> PlatformCol = ContentFunc::PlatformColCheck(GroundCol);

	if (nullptr != PlatformCol)
	{
		float4 CurPos = GetTransform()->GetWorldPosition();

		GameEngineTransform* ColTrans = PlatformCol->GetTransform();
		CurPos.y = ColTrans->GetWorldPosition().y + ColTrans->GetWorldScale().hy();
		GroundY = CurPos.y;

		GetTransform()->SetWorldPosition(CurPos);
		GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());

		float4 CurVelocity = BossRigidbody.GetVelocity();
		CurVelocity.y = 0.0f;
		BossRigidbody.SetVelocity(CurVelocity);
		IsGroundUp = true;
	}
	else
	{
		IsGroundUp = false;
	}
}

bool BossMonster::HitCheck()
{
	if (true == IsHit && false == IsSuperArmor)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void BossMonster::LookPlayer()
{
	std::shared_ptr<Player> PlayerActor = FindPlayer.lock();

	if (nullptr != PlayerActor)
	{
		float4 Dir = PlayerActor->GetTransform()->GetWorldPosition() - GetTransform()->GetWorldPosition();

		if (0.0f > Dir.x)
		{
			SetViewDir(ActorViewDir::Left);
		}
		else
		{
			SetViewDir(ActorViewDir::Right);
		}
	}
}

void BossMonster::PlayAnimation(const std::string_view& _AnimationName, bool _IsForce /*= true*/, size_t Frame /*= 0*/)
{
	CurFrameIndex = static_cast<UINT>(-1);
	CurFramePauseTime = 0.0f;

	CurAnimPause = PauseTimes[_AnimationName.data()];
	Render->ChangeAnimation(_AnimationName, Frame, _IsForce);
}

void BossMonster::RigidbodyMovePlatformCheck(float4& _Dir)
{
	std::shared_ptr<GameEngineCollision> CheckCol = nullptr;

	switch (Dir)
	{
	case ActorViewDir::Left:
	{
		if (0.0f > _Dir.x)
		{
			CheckCol = WalkCol;
		}
		else
		{
			CheckCol = BackCol;
		}
	}
		break;
	case ActorViewDir::Right:
	{
		if (0.0f > _Dir.x)
		{
			CheckCol = BackCol;
		}
		else
		{
			CheckCol = WalkCol;
		}
	}
		break;
	}

	if (nullptr != CheckCol->Collision((int)CollisionOrder::Platform_Normal, ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		_Dir.x = 0.0f;
	}
}