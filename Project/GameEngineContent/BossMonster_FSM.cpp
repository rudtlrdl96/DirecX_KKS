#include "PrecompileHeader.h"
#include "BossMonster.h"
#include "Player.h"


void BossMonster::Idle_Enter() 
{
	PlayAnimation("Idle");
}

void BossMonster::Idle_Update(float _DeltaTime) 
{
	if (true == HitCheck())
	{
		BossFsm.ChangeState("Hit");
	}

	std::shared_ptr<Player> PlayerPtr = FindPlayer.lock();

	if (nullptr == PlayerPtr)
	{
		std::shared_ptr<GameEngineCollision> Col = PlayerFindCol->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D);

		if (nullptr == Col)
		{
			return;
		}

		std::shared_ptr<Player> CastingPtr = Col->GetActor()->DynamicThis<Player>();

		if (nullptr == CastingPtr)
		{
			MsgAssert_Rtti<BossMonster>(" - Player 클래스만 Player ColOrder를 가질 수 있습니다");
			return;
		}

		FindPlayer = CastingPtr;
		PlayerPtr = FindPlayer.lock();
	}
	
	if (false == IsIntro && 0.0f < CurWaitTime)
	{
		if (nullptr == Cur_Pattern_Update)
		{
			SelectPattern();
		}

		GameEngineTransform* PlayerTrans = PlayerPtr->GetTransform();

		float4 BossPos = GetTransform()->GetWorldPosition();
		float4 PlayerPos = PlayerTrans->GetWorldPosition();
		float4 Dir = PlayerPos - BossPos;

		float DistanceX = fabsf(Dir.x);

		if (AttackDistance <= DistanceX)
		{
			if (0.0f > Dir.x)
			{
				SetViewDir(ActorViewDir::Left);
			}
			else
			{
				SetViewDir(ActorViewDir::Right);
			}

			BossFsm.ChangeState("Dash");
			return;
		}
		else
		{
			BossFsm.ChangeState("Pattern");	
		}
	}
}

void BossMonster::Idle_End() 
{

}


void BossMonster::Dash_Enter() 
{
	PlayAnimation("Dash");

	switch (Dir)
	{
	case ActorViewDir::Left:
		BossRigidbody.SetVelocity(float4::Left * DashPower);
		break;
	case ActorViewDir::Right:
		BossRigidbody.SetVelocity(float4::Right * DashPower);
		break;
	}
}

void BossMonster::Dash_Update(float _DeltaTime) 
{
	BossRigidbody.UpdateForce(_DeltaTime);

	float4 DashVel = BossRigidbody.GetVelocity();
	float4 CurDashVel = BossRigidbody.GetVelocity() * _DeltaTime;

	RigidbodyMovePlatformCheck(CurDashVel);
	GetTransform()->AddLocalPosition(CurDashVel);

	if (1.0f >= DashVel.Size())
	{
		BossFsm.ChangeState("Idle");
	}
}

void BossMonster::Dash_End() 
{

}

void BossMonster::BackDash_Enter()
{
	PlayAnimation("BackDash");
	HitWaitTime = 0.0f;

	switch (Dir)
	{
	case ActorViewDir::Left:
		BossRigidbody.SetVelocity(float4::Right * BackDashPower);
		break;
	case ActorViewDir::Right:
		BossRigidbody.SetVelocity(float4::Left * BackDashPower);
		break;
	default:
		break;
	}
}

void BossMonster::BackDash_Update(float _DeltaTime)
{
	BossRigidbody.UpdateForce(_DeltaTime);

	float4 BackDashVel = BossRigidbody.GetVelocity();
	float4 CurFrameVel = BossRigidbody.GetVelocity() * _DeltaTime;

	RigidbodyMovePlatformCheck(CurFrameVel);
	GetTransform()->AddLocalPosition(CurFrameVel);

	if (1.0f <= BackDashVel.Size())
	{
		return;
	}

	if (false == IsIntro && 0.0f < CurWaitTime)
	{
		if (nullptr == Cur_Pattern_Update)
		{
			SelectPattern();
		}

		std::shared_ptr<Player> PlayerPtr = FindPlayer.lock();
		GameEngineTransform* PlayerTrans = PlayerPtr->GetTransform();

		float4 BossPos = GetTransform()->GetWorldPosition();
		float4 PlayerPos = PlayerTrans->GetWorldPosition();
		float4 Dir = PlayerPos - BossPos;

		float DistanceX = fabsf(Dir.x);

		if (AttackDistance <= DistanceX)
		{
			if (0.0f > Dir.x)
			{
				SetViewDir(ActorViewDir::Left);
			}
			else
			{
				SetViewDir(ActorViewDir::Right);
			}

			BossFsm.ChangeState("Dash");
			return;
		}
		else
		{
			BossFsm.ChangeState("Pattern");
			return;
		}
	}
	else
	{
		BossFsm.ChangeState("Idle");
	}
}

void BossMonster::BackDash_End()
{

}

void BossMonster::Hit_Enter()
{
	PlayAnimation("Hit");
	HitWaitTime = 0.0f;
	CurWaitTime -= 2.0f;

	switch (HitDir)
	{
	case ActorViewDir::Left:
		SetViewDir(ActorViewDir::Right);
		BossRigidbody.SetVelocity(float4::Left * HitPower);
		break;
	case ActorViewDir::Right:
		SetViewDir(ActorViewDir::Left);
		BossRigidbody.SetVelocity(float4::Right * HitPower);
		break;
	default:
		break;
	}
}

void BossMonster::Hit_Update(float _DeltaTime)
{
	HitWaitTime += _DeltaTime;
	BossRigidbody.UpdateForce(_DeltaTime);

	float4 DashVel = BossRigidbody.GetVelocity() * _DeltaTime;

	RigidbodyMovePlatformCheck(DashVel);
	GetTransform()->AddLocalPosition(DashVel);

	if (false == IsSuperArmor && true == IsHit)
	{
		switch (HitDir)
		{
		case ActorViewDir::Left:
			SetViewDir(ActorViewDir::Right);
			BossRigidbody.SetVelocity(float4::Left * HitPower);
			break;
		case ActorViewDir::Right:
			SetViewDir(ActorViewDir::Left);
			BossRigidbody.SetVelocity(float4::Right * HitPower);
			break;
		default:
			break;
		}

		if (false == IsSuperArmor && true == IsStiffen)
		{
			PlayAnimation("Hit");
			HitWaitTime = 0.0f;
		}

		HitPush();
	}

	if (0.5f <= HitWaitTime)
	{
		BossFsm.ChangeState("Idle");
	}

	if (false == IsIntro && 0.0f < CurWaitTime)
	{
		BossFsm.ChangeState("BackDash");
	}
}

void BossMonster::Hit_End()
{
	CurWaitTime += 2.0f;
}

void BossMonster::Groggy_Enter()
{
	PlayAnimation("Groggy");

	CurGroggyTime = -GroggyTime;
}

void BossMonster::Groggy_Update(float _DeltaTime)
{
	CurGroggyTime += _DeltaTime;

	if (0.0f <= CurGroggyTime)
	{
		BossFsm.ChangeState("Idle");
	}
}

void BossMonster::Groggy_End()
{

}

void BossMonster::Pattern_Enter() 
{
	CurWaitTime = -PatternWaitTime;

	if (nullptr != Cur_Pattern_Enter)
	{
		Cur_Pattern_Enter();
	}
}

void BossMonster::Pattern_Update(float _DeltaTime) 
{
	if (nullptr != Cur_Pattern_Update)
	{
		Cur_Pattern_Update(_DeltaTime);
	}
}

void BossMonster::Pattern_End() 
{
	CurWaitTime = -PatternWaitTime;

	if (nullptr != Cur_Pattern_End)
	{
		Cur_Pattern_End();
	}

	Cur_Pattern_Enter = nullptr;
	Cur_Pattern_Update = nullptr;
	Cur_Pattern_End = nullptr;
}

void BossMonster::Behavior_Enter() 
{
	PlayAnimation(PlayBehaviorAnim);
}

void BossMonster::Behavior_Update(float _DeltaTime) 
{
	if (false == IsBehaviorLoop && true == Render->IsAnimationEnd())
	{
		BossFsm.ChangeState("Idle");
	}
}

void BossMonster::Behavior_End() 
{
	if (nullptr != BehaviorEndCallback)
	{
		std::function<void()> TempCallback = BehaviorEndCallback;
		BehaviorEndCallback = nullptr;
		TempCallback();
	}
}