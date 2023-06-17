#include "PrecompileHeader.h"
#include "VeteranHeroMagicSword.h"

VeteranHeroMagicSword::VeteranHeroMagicSword()
{
}

VeteranHeroMagicSword::~VeteranHeroMagicSword()
{
}

void VeteranHeroMagicSword::FadeDeath()
{
	ProjectileEffectActor->GetTransform()->SetParent(nullptr);
	ProjectileEffectActor->IsFadeDeathOn(1.5f);
	ProjectileEffectActor = nullptr;
	Death();
}

void VeteranHeroMagicSword::Update(float _DeltaTime)
{
	TrackingTarget = nullptr;

	if (GetLiveTime() <= WaitTime)
	{
		return;
	}

	HitParameter.ProjectilePos = GetTransform()->GetWorldPosition();
	HitParameter.Attack = Damage;
	HitParameter.AttackDir = Dir;

	IsWaitEndValue = true;

	ColDatas.clear();

	if (true == IsPlatformCol)
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

