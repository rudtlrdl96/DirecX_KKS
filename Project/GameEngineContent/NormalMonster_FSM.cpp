#include "PrecompileHeader.h"
#include "NormalMonster.h"
#include <GameEngineCore/GameEngineCollision.h>

void NormalMonster::Idle_Enter() 
{
	Render->ChangeAnimation("Idle");
	IdleToWalkTime = 0.0f;

	RandIdleTime = GameEngineRandom::MainRandom.RandomFloat(0.5f, 1.0f);
	ChasingWaitTime = 0.0f;
	IsChasingWait = false;
}

void NormalMonster::Idle_Update(float _DeltaTime) 
{
	if (true == MonsterUnMove)
	{
		return;
	}

	if (true == Fall(_DeltaTime))
	{
		return;
	}

	if (true == HitCheck())
	{
		return;
	}

	if (AttackWaitTime < AttackWaitEndTime)
	{
		return;
	}

	if (true == IsChasingWait)
	{
		ChasingWaitTime += _DeltaTime;


		if (ChasingWaitTime >= 0.5f)
		{
			MonsterFsm.ChangeState("Chasing");
		}

		return;
	}

	if (false == IsUnWalkable)
	{
		IdleToWalkTime += _DeltaTime;

		if (IdleToWalkTime >= RandIdleTime)
		{
			if (0 == GameEngineRandom::MainRandom.RandomInt(0, 1))
			{
				Turn();
			}

			MonsterFsm.ChangeState("Walk");
			return;
		}
	}

	if (nullptr != PlayerActor)
	{
		MonsterFsm.ChangeState("Chasing");
		return;
	}

	std::shared_ptr<GameEngineCollision> ResultCol = nullptr;

	ResultCol = FindCol->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D);

	if (nullptr != ResultCol)
	{
		IsChasingWait = true;

		EffectManager::PlayEffect({
			.EffectName = "FindPlayer",
			.Position = GetTransform()->GetWorldPosition() + LoadFindEffectPos });

		PlayerActor = ResultCol->GetActor()->DynamicThis<GameEngineActor>();
		return;
	}
}

void NormalMonster::Idle_End() 
{

}

void NormalMonster::Walk_Enter() 
{
	Render->ChangeAnimation("Walk");
	WalkToIdleTime = 0.0f;
	WalkTurnTime = 0.0f;

	RandWalkTime = GameEngineRandom::MainRandom.RandomFloat(1.5f, 2.5f);
}

void NormalMonster::Walk_Update(float _DeltaTime) 
{
	if (true == MonsterUnMove)
	{
		MonsterFsm.ChangeState("Idle");
		return;
	}

	if (true == HitCheck())
	{
		return;
	}

	WalkToIdleTime += _DeltaTime;

	if (WalkToIdleTime >= RandWalkTime)
	{
		MonsterFsm.ChangeState("Idle");
		return;
	}

	if (nullptr == ContentFunc::PlatformColCheck(WalkFallCol, true))
	{
		Turn(true);
	}

	if (false == Walk(_DeltaTime))
	{
		Turn();
	}
	
	if (true == Fall(_DeltaTime))
	{
		return;
	}

	std::shared_ptr<GameEngineCollision> ResultCol = nullptr;

	ResultCol = FindCol->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D);

	if (nullptr != ResultCol)
	{
		EffectManager::PlayEffect({ 
			.EffectName = "FindPlayer",
			.Position = GetTransform()->GetWorldPosition() + LoadFindEffectPos });

		PlayerActor = ResultCol->GetActor()->DynamicThis<GameEngineActor>();
		MonsterFsm.ChangeState("Chasing");
		return;
	}
}

void NormalMonster::Walk_End() 
{

}

void NormalMonster::Chasing_Enter() 
{
	Render->ChangeAnimation("Walk");
	TurnCoolTime = 0.0f;
}

void NormalMonster::Chasing_Update(float _DeltaTime) 
{
	if (true == MonsterUnMove)
	{
		MonsterFsm.ChangeState("Idle");
		return;
	}

	if (true == HitCheck())
	{
		return;
	}

	Fall(_DeltaTime);

	if (nullptr == PlayerActor)
	{
		MonsterFsm.ChangeState("Idle");
		return;
	}

	GameEngineTransform* PlayerTrans = PlayerActor->GetTransform();
	GameEngineTransform* MonsterTrans = GetTransform();

	float4 ChasingDir = PlayerTrans->GetWorldPosition() - MonsterTrans->GetWorldPosition();
	ChasingDir.y = 0;
	ChasingDir.Normalize();
	
	if (ChasingDir.x < 0)
	{
		SetViewDir(ActorViewDir::Left);
	}
	else
	{
		SetViewDir(ActorViewDir::Right);
	}

	std::shared_ptr<GameEngineCollision> ResultCol = nullptr;

	ResultCol = ChasingCol->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D);

	if (nullptr != ResultCol)
	{
		PlayerActor = ResultCol->GetActor()->DynamicThis<GameEngineActor>();
		MonsterFsm.ChangeState("Attack");
		return;
	}

	if (nullptr == ContentFunc::PlatformColCheck(WalkFallCol, true))
	{
		Turn(true);
		return;
	}

	if (false == Walk(_DeltaTime))
	{
		PlayerActor = nullptr;
		Turn(true);
		MonsterFsm.ChangeState("Walk");
		return;
	}

}

void NormalMonster::Chasing_End() 
{

}

void NormalMonster::Attack_Enter() 
{
	if ("" == AnimColMeta_Attack.GetAnimationName())
	{
		MsgAssert_Rtti<NormalMonster>(" - 몬스터의 공격 정보가 존재하지 않습니다");
	}

	Render->ChangeAnimation(AnimColMeta_Attack.GetAnimationName());
	AttackRigidbody.SetVelocity(float4::Zero);

	AttackCheckFrame = 0;
	CurPauseTime = 0.0f;

	AttackCheck.Reset();
}

void NormalMonster::Attack_Update(float _DeltaTime)
{
	if (true == MonsterUnMove)
	{
		MonsterFsm.ChangeState("Idle");
		return;
	}

	AttackCheck.Update();

	if (true == HitCheck())
	{
		return;
	}

	Fall(_DeltaTime);
	AttackRigidbody.UpdateForce(_DeltaTime);

	size_t CurFrame = Render->GetCurrentFrame();

	if (AttackCheckFrame != CurFrame)
	{
		AttackCheckFrame = CurFrame;
		CurPauseTime = 0.0f;
	}
	
	CurPauseTime += _DeltaTime;

	if (AnimPauseTimes[AttackCheckFrame] > CurPauseTime)
	{
		Render->SetAnimPauseOn();
	}
	else
	{
		Render->SetAnimPauseOff();
	}

	if (nullptr == ContentFunc::PlatformColCheck(WalkCol))
	{
		float4 Velocity = AttackRigidbody.GetVelocity() * _DeltaTime;
		GetTransform()->AddLocalPosition(Velocity);
	}

	if (true == Render->IsAnimationEnd())
	{

		MonsterFsm.ChangeState("Idle");
		return;
	}
}

void NormalMonster::Attack_End() 
{
	AttackWaitTime = 0.0f;
}

void NormalMonster::Hit_Enter() 
{
	Render->ChangeAnimation("Hit1");
	HitAnimIndex = 0;
	HitWaitTime = 0.0f;
}

void NormalMonster::Hit_Update(float _DeltaTime) 
{
	HitWaitTime += _DeltaTime;

	Fall(_DeltaTime);

	if (false == IsSuperArmor && true == IsHit)
	{
		if (0 == HitAnimIndex)
		{
			HitEffect(HitEffectType::Normal);

			if (false == IsSuperArmor && true == IsStiffen)
			{
				Render->ChangeAnimation("Hit2");
				HitAnimIndex = 1;
				HitWaitTime = 0.0f;
			}

			HitPush();
		}
		else if(1 == HitAnimIndex)
		{
			HitEffect(HitEffectType::Normal);

			if (false == IsSuperArmor && true == IsStiffen)
			{
				Render->ChangeAnimation("Hit1");
				HitAnimIndex = 0;
				HitWaitTime = 0.0f;
			}

			HitPush();
		}

	}

	if (0.5f <= HitWaitTime)
	{
		MonsterFsm.ChangeState("Idle");
	}
}

void NormalMonster::Hit_End() 
{

}