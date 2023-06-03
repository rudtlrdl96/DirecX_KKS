#include "PrecompileHeader.h"
#include "GiantEnt.h"
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentLevel.h"

void GiantEnt::Idle_Update(float _DeltaTime)
{
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
			.Postion = GetTransform()->GetWorldPosition() + LoadFindEffectPos });

		PlayerActor = ResultCol->GetActor()->DynamicThis<GameEngineActor>();
		return;
	}
}

void GiantEnt::Walk_Enter()
{
	MsgAssert_Rtti<GiantEnt>(" - 숲지기(자이언트 엔트)는 Walk 스테이트에 들어올 수 없습니다");
	return;
}

void GiantEnt::Chasing_Enter()
{

}

void GiantEnt::Chasing_Update(float _DeltaTime)
{
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

	std::shared_ptr<GameEngineCollision> ResultCol = nullptr;

	ResultCol = ChasingCol->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D);

	if (nullptr != ResultCol)
	{
		PlayerActor = ResultCol->GetActor()->DynamicThis<GameEngineActor>();
		MonsterFsm.ChangeState("Attack");
		return;
	}
}

void GiantEnt::Attack_Enter() 
{
	IsAttackStempEffect = false;
	IsRangeAttack = false;
	IsRnageProjectile = false;
	CurPauseTime = 0.0f;

	GameEngineTransform* PlayerTrans = PlayerActor->GetTransform();
	GameEngineTransform* MonsterTrans = GetTransform();

	float4 TargetDir = PlayerTrans->GetWorldPosition() - MonsterTrans->GetWorldPosition();
	float Distance = TargetDir.Size();

	if (Distance <= 200.0f)
	{
		NormalMonster::Attack_Enter();
	}
	else
	{
		IsRangeAttack = true;
		Render->ChangeAnimation("RangeAttack");
	}
}

void GiantEnt::Attack_Update(float _DeltaTime)
{
	if (false == IsRangeAttack)
	{
		NormalMonster::Attack_Update(_DeltaTime);

		if (false == IsAttackStempEffect && 4 == Render->GetCurrentFrame())
		{
			IsAttackStempEffect = true;

			EffectManager::PlayEffect({
				.EffectName = "GaintEntStampEffect",
				.Postion = GetTransform()->GetWorldPosition(),
				});

			std::shared_ptr<ContentLevel> ContentLevelPtr = GetLevel()->DynamicThis<ContentLevel>();

			if (nullptr != ContentLevelPtr)
			{
				ContentLevelPtr->GetCamCtrl().CameraShake(5, 50, 3);
			}
		}

	}
	else
	{
		size_t CurFrame = Render->GetCurrentFrame();

		if (false == IsRnageProjectile && 2 == CurFrame)
		{
			IsRnageProjectile = true;

			ShotProjectile(35.0f);
			ShotProjectile(90.0f);
			ShotProjectile(145.0f);

			ShotProjectile(215.0f);
			ShotProjectile(270.0f);
			ShotProjectile(325.0f);
		}

		if (AttackCheckFrame != CurFrame)
		{
			AttackCheckFrame = CurFrame;
			CurPauseTime = 0.0f;
		}

		CurPauseTime += _DeltaTime;

		if (RangeAttackPauseTimes[static_cast<UINT>(AttackCheckFrame)] > CurPauseTime)
		{
			Render->SetAnimPauseOn();
		}
		else
		{
			Render->SetAnimPauseOff();
		}

		if (true == Render->IsAnimationEnd())
		{
			MonsterFsm.ChangeState("Idle");
			return;
		}
	}
}

