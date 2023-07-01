#include "PrecompileHeader.h"
#include "RigidProjectile.h"

RigidProjectile::RigidProjectile()
{
}

RigidProjectile::~RigidProjectile()
{
}

void RigidProjectile::InitRigd(float _MaxSpeed, float _FricCoeff, float _Mass /*= 1.0f*/)
{
	ProjectileRigidbody.SetMaxSpeed(_MaxSpeed);
	ProjectileRigidbody.SetFricCoeff(_FricCoeff);
	ProjectileRigidbody.SetMass(_Mass);
}

void RigidProjectile::Update(float _DeltaTime)
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

	HitParameter.ProjectilePos = GetTransform()->GetWorldPosition();
	HitParameter.Attack = Damage;

	GameEngineTransform* Trans = GetTransform();

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

	ProjectileRigidbody.AddForce(Dir * Speed);
	ProjectileRigidbody.UpdateForce(_DeltaTime);
	Trans->AddLocalPosition(ProjectileRigidbody.GetVelocity() * _DeltaTime);

	if (true == IsPlatformCol)
	{
		if (nullptr != ProjectileCol->Collision((int)CollisionOrder::Platform_Normal, ProjectileColType, ColType::AABBBOX2D))
		{
			if (nullptr != DeathEvent)
			{
				DeathEvent(GetTransform()->GetWorldPosition());
			}

			Death();
			return;
		}

		if (nullptr != ProjectileCol->Collision((int)CollisionOrder::Platform_Half, ProjectileColType, ColType::AABBBOX2D))
		{
			if (nullptr != DeathEvent)
			{
				DeathEvent(GetTransform()->GetWorldPosition());
			}

			Death();
			return;
		}
	}

	ColDatas.clear();
	if (true == ProjectileCol->CollisionAll(ColOrder, ColDatas, ProjectileColType, ColType::AABBBOX2D))
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
