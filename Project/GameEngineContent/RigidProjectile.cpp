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

	float RotZ = 0.0f;

	if (float4::Right != Dir)
	{
		RotZ = float4::GetAngleVectorToVectorDeg(Dir, float4::Right);
	}

	GameEngineTransform* Trans = GetTransform();
	Trans->SetLocalRotation(float4(0, 0, -RotZ));

	if (GetLiveTime() <= WaitTime)
	{
		return;
	}

	IsWaitEndValue = true;

	ProjectileRigidbody.AddForce(Dir * Speed);
	ProjectileRigidbody.UpdateForce(_DeltaTime);
	Trans->AddLocalPosition(ProjectileRigidbody.GetVelocity() * _DeltaTime);

	ColDatas.clear();
	if (true == ProjectileCol->CollisionAll(ColOrder, ColDatas, ColType::SPHERE2D, ColType::AABBBOX2D))
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
