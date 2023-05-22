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
		std::shared_ptr<EffectActor> NewEffect = EffectManager::PlayEffect({
			.EffectName = _Parameter.EffectName,
			.Postion = _Parameter.Pos,
			.Triger = EffectDeathTrigger::Time,
			.Time = _Parameter.LiveTime,
			.FlipX = false,
			});

		NewEffect->GetTransform()->SetParent(GetTransform());
		NewEffect->GetTransform()->SetLocalPosition(float4::Zero);
	}

	Dir = _Parameter.Dir.NormalizeReturn();
	LiveTime = _Parameter.LiveTime;
	Speed = _Parameter.Speed;
	ColOrder = _Parameter.ColOrder;

	EnterEvent = _Parameter.EnterEvent;
	UpdateEvent = _Parameter.UpdateEvent;


	On();
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
		Death();
		return;
	}

	float RotZ = 0.0f;

	if (float4::Right != Dir)
	{
		RotZ = float4::GetAngleVectorToVectorDeg(Dir, float4::Right);
	}

	GameEngineTransform* Trans = GetTransform();
	Trans->AddLocalPosition(Dir * _DeltaTime * Speed);
	Trans->SetLocalRotation(float4(0, 0, RotZ));

	ColDatas.clear();

	if (nullptr == UpdateEvent && nullptr == EnterEvent)
	{
		return;
	}

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
					EnterEvent(ActorPtr);
					ColBuffers[ActorPtr->GetActorCode()] = ActorPtr;
				}
			}

			if (nullptr != UpdateEvent)
			{
				UpdateEvent(ActorPtr);
			}
		}
	}
}
