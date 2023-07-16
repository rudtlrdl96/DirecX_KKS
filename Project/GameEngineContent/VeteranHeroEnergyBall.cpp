#include "PrecompileHeader.h"
#include "VeteranHeroEnergyBall.h"

VeteranHeroEnergyBall::VeteranHeroEnergyBall()
{
}

VeteranHeroEnergyBall::~VeteranHeroEnergyBall()
{
}

void VeteranHeroEnergyBall::ShotProjectile(const ProjectileParameter& _Parameter)
{
	Projectile::ShotProjectile(_Parameter);

	Dir = _Parameter.Dir;
}

void VeteranHeroEnergyBall::Update(float _DeltaTime)
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

	TrackingWaitTime += _DeltaTime;

	if (0.5f <= TrackingWaitTime)
	{
		TrackingStart = true;
	}

	if (true == TrackingStart && nullptr != TrackingTarget)
	{
		float4 TrackingDir = (TrackingTarget->GetTransform()->GetWorldPosition() + TrackingPivot) - Trans->GetWorldPosition();
		TrackingDir.Normalize();

		Dir += TrackingDir * _DeltaTime * TrackingSpeed;
	}

	float4 DirNormal = Dir.NormalizeReturn();
	float DirSize = Dir.Size();

	if (false == TrackingStart)
	{
		DirSize -= 1000.0f * _DeltaTime;
	}
	else
	{
		DirSize -= 800.0f * _DeltaTime;
	}

	if (Speed < DirSize)
	{
		DirSize = Speed;
	}

	if (0.0f > DirSize)
	{
		DirSize = 0.0f;	
	}

	Dir = DirNormal * DirSize;

	HitParameter.ProjectilePos = GetTransform()->GetWorldPosition();
	HitParameter.Attack = Damage;
	HitParameter.AttackDir = Dir.NormalizeReturn();

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
	Trans->AddLocalPosition(Dir * _DeltaTime);

	ColDatas.clear();

	if (true == IsNormalPlatformCol)
	{
		if (nullptr != ProjectileCol->Collision((int)CollisionOrder::Platform_Normal, ColType::SPHERE2D, ColType::AABBBOX2D))
		{
			if (nullptr != DeathEvent)
			{
				DeathEvent(GetTransform()->GetWorldPosition());
			}

			Death();
			return;
		}
	}

	if (true == IsHalfPlatformCol)
	{
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
