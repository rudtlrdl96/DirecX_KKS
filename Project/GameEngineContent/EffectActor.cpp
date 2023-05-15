#include "PrecompileHeader.h"
#include "EffectActor.h"

EffectActor::EffectActor()
{
}

EffectActor::~EffectActor()
{
}

void EffectActor::Start()
{
	EffectRender = CreateComponent<GameEngineSpriteRenderer>();
	EffectRender->SetTexture("Empty.png");
	EffectRender->Off();
}

void EffectActor::Update(float _DeltaTime)
{
	switch (DeathTrigger)
	{
	case EffectDeathTrigger::Time:
	{

		DeathTime += _DeltaTime;

		if (GetLiveTime() >= DeathTime)
		{
			Death();
			return;
		}
	}
		break;
	case EffectDeathTrigger::AnimEnd:
	{
		if (true == EffectRender->IsAnimationEnd())
		{
			Death();
			return;
		}
	}
		break;
	default:
		MsgAssert_Rtti<EffectActor>(" - 알 수 없는 이펙트 DeathTrigger 입니다");
		break;
	}

}

void EffectActor::Init(const EffectMetaData& _MetaData, EffectDeathTrigger _DeathTrigger, float _DeathTime)
{
	DeathTime = _DeathTime;
	DeathTrigger = _DeathTrigger;

	EffectRender->CreateAnimation({ 
		_MetaData.AnimationName,
		_MetaData.SpriteName,
		_MetaData.AnimStart,
		_MetaData.AnimEnd,
		_MetaData.AnimIter,
		true,
		true});

	GameEngineTransform* RenderTrans = EffectRender->GetTransform();
	RenderTrans->SetLocalPosition(_MetaData.RenderPivot);
	EffectRender->SetScaleRatio(_MetaData.ScaleRatio);
	EffectRender->ChangeAnimation(_MetaData.AnimationName);
	EffectRender->On();
}
