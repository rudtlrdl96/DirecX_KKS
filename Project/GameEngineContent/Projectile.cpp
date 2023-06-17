#include "PrecompileHeader.h"
#include "Projectile.h"
#include <GameEngineCore/GameEngineCollision.h>

#include "EffectManager.h"

Projectile::Projectile()
{
	ColDatas.reserve(8);
}

Projectile::~Projectile()
{
}

void Projectile::ShotProjectile(const ProjectileParameter& _Parameter)
{
	GameEngineTransform* Trans = GetTransform();

	Trans->SetLocalPosition(_Parameter.Pos);

	ProjectileCol->GetTransform()->SetLocalScale(_Parameter.ColScale);

	if ("" != _Parameter.EffectName)
	{
		ProjectileEffectActor = EffectManager::PlayEffect({
			.EffectName = _Parameter.EffectName,
			.Position = _Parameter.Pos,
			.Triger = EffectDeathTrigger::Time,
			.Time = _Parameter.LiveTime,
			.FlipX = _Parameter.IsFlipX,
			.IsForceLoopOff = _Parameter.IsForceLoopOff});

		ProjectileEffectActor->GetTransform()->SetParent(GetTransform());
		ProjectileEffectActor->GetTransform()->SetLocalPosition(float4::Zero);
	}



	TrackingTarget = _Parameter.TrackingTarget;

	ProjectileColType = _Parameter.ProjectileColType;
	ProjectileCol->SetColType(ProjectileColType);

	Damage = _Parameter.Damage;

	Dir = _Parameter.Dir.NormalizeReturn();

	WaitTime = _Parameter.WaitTime;
	LiveTime = _Parameter.LiveTime;
	Speed = _Parameter.Speed;
	TrackingSpeed = _Parameter.TrackingSpeed;
	TrackingPivot = _Parameter.TrackingPivot;
	ColOrder = _Parameter.ColOrder;

	IsPlatformCol = _Parameter.IsPlatformCol;
	IsColDeath = _Parameter.IsColDeath;
	IsRot = _Parameter.IsRot;

	EnterEvent = _Parameter.EnterEvent;
	UpdateEvent = _Parameter.UpdateEvent;
	DeathEvent = _Parameter.DeathEvent;

	On();
}

void Projectile::ColDebugOn()
{
	ProjectileCol->DebugOn();
}

void Projectile::Start()
{
	ProjectileCol = CreateComponent<GameEngineCollision>();

	Off();
}

void Projectile::Update(float _DeltaTime)
{
	if (GetLiveTime() >= LiveTime)
	{
		if (nullptr != DeathEvent)
		{
			DeathEvent(GetTransform()->GetWorldPosition());
		}

		Death();
		return;
	}

	if (nullptr != TrackingTarget && true == TrackingTarget->IsDeath())
	{
		TrackingTarget = nullptr;
	}

	GameEngineTransform* Trans = GetTransform();

	if (nullptr != TrackingTarget)
	{
		float4 TrackingDir = (TrackingTarget->GetTransform()->GetWorldPosition() + TrackingPivot) - Trans->GetWorldPosition();
		TrackingDir.Normalize();

		Dir += TrackingDir * _DeltaTime * TrackingSpeed;
		Dir.Normalize();
	}

	HitParameter.ProjectilePos = GetTransform()->GetWorldPosition();
	HitParameter.Attack = Damage;
	HitParameter.AttackDir = Dir;


	if (true == IsRot)
	{
		float RotZ = 0.0f;

		if (float4::Right != Dir)
		{
			RotZ = float4::GetAngleVectorToVectorDeg(Dir, float4::Right);
		}

		Trans->SetLocalRotation(float4(0, 0, -RotZ));
	}

	if (GetLiveTime() <= WaitTime)
	{
		return;
	}

	IsWaitEndValue = true;
	Trans->AddLocalPosition(Dir * _DeltaTime * Speed);

	ColDatas.clear();

	if (true == IsPlatformCol)
	{
		if(nullptr != ProjectileCol->Collision((int)CollisionOrder::Platform_Normal, ColType::SPHERE2D, ColType::AABBBOX2D))
		{
			if (nullptr != DeathEvent)
			{
				DeathEvent(GetTransform()->GetWorldPosition());
			}

			Death();
			return;
		}

		if (nullptr != ProjectileCol->Collision((int)CollisionOrder::Platform_Half, ColType::SPHERE2D, ColType::AABBBOX2D))
		{
			if (nullptr != DeathEvent)
			{
				DeathEvent(GetTransform()->GetWorldPosition());
			}

			Death();
			return;
		}
	}

	if (true == ProjectileCol->CollisionAll(ColOrder, ColDatas, ColType::MAX, ColType::AABBBOX2D))
	{

		for (size_t i = 0; i < ColDatas.size(); i++)
		{
			std::shared_ptr<BaseContentActor> ActorPtr = ColDatas[i]->GetActor()->DynamicThis<BaseContentActor>();

			if (nullptr == ActorPtr)
			{
				MsgAssert_Rtti<Projectile>(" - 충돌할 모든 액터는 BaseContentActor를 상속받아야 합니다");
				continue;
			}

			if (nullptr != EnterEvent)
			{
				if (nullptr == ColBuffers[ActorPtr->GetActorCode()])
				{
					EnterEvent(ActorPtr, HitParameter);
					ColBuffers[ActorPtr->GetActorCode()] = ActorPtr;
				}
			}

			if (nullptr != UpdateEvent)
			{
				UpdateEvent(ActorPtr, HitParameter);
			}
		}
	}


	if (true == IsColDeath)
	{
		if (0 != ColDatas.size())
		{
			Death();
			return;
		}
	}
}
