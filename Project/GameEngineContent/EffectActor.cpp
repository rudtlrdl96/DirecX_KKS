#include "PrecompileHeader.h"
#include "EffectActor.h"

EffectActor::EffectActor()
{
}

EffectActor::~EffectActor()
{
}

void EffectActor::PauseOn()
{
	EffectRender->SetAnimPauseOn();
}

void EffectActor::PauseOff()
{
	EffectRender->SetAnimPauseOff();
}

void EffectActor::Start()
{
	EffectRender = CreateComponent<ContentSpriteRenderer>();
	EffectRender->PipeSetting("2DTexture_Color");
	EffectRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	EffectRender->SetTexture("Empty.png");
	EffectRender->Off();
}

void EffectActor::Update(float _DeltaTime)
{
	if (true == IsFadeDeathValue)
	{
		DeathProgress += _DeltaTime * DeathFadeSpeed;

		if (1.0f <= DeathProgress)
		{
			DeathProgress = 1.0f;
			Death();
		}

		Buffer.Color.a = 1.0f - DeathProgress;
		return;
	}

	if (GetLiveTime() < WaitTime)
	{
		EffectRender->Off();
		return;
	}
	else
	{
		EffectRender->On();
	}

	switch (DeathTrigger)
	{
	case EffectDeathTrigger::Time:
	{
		if (GetLiveTime() >= DeathTime)
		{
			if (true == IsFadeDeath)
			{
				IsFadeDeathValue = true;
			}
			else
			{
				Death();
			}

			return;
		}
	}
		break;
	case EffectDeathTrigger::AnimEnd:
	{
		if (true == EffectRender->IsAnimationEnd())
		{
			if (true == IsFadeDeath)
			{
				IsFadeDeathValue = true;
			}
			else
			{
				Death();
			}

			return;
		}
	}
		break;
	default:
		MsgAssert_Rtti<EffectActor>(" - 알 수 없는 이펙트 DeathTrigger 입니다");
		break;
	}

}

void EffectActor::Init(const EffectMetaData& _MetaData, EffectDeathTrigger _DeathTrigger, float _DeathTime, float _WaitTime, bool _IsForceLoopOff, bool _IsFadeDeath, float _FadeSpeed)
{
	DeathTime = _DeathTime;
	DeathTrigger = _DeathTrigger;
	
	bool Loop = _DeathTrigger != EffectDeathTrigger::AnimEnd;

	if (true == _IsForceLoopOff)
	{
		Loop = false;
	}

	EffectRender->CreateAnimation({
	_MetaData.SpriteName,
	_MetaData.SpriteName,
	_MetaData.AnimStart,
	_MetaData.AnimEnd,
	_MetaData.AnimIter,
	Loop,
	true });

	GameEngineTransform* RenderTrans = EffectRender->GetTransform();
	RenderTrans->SetLocalPosition(_MetaData.RenderPivot);
	EffectRender->SetScaleRatio(_MetaData.ScaleRatio);
	EffectRender->ChangeAnimation(_MetaData.SpriteName);
	EffectRender->On();

	WaitTime = _WaitTime;

	Buffer.Color = _MetaData.Color;
	IsFadeDeath = _IsFadeDeath;
	DeathFadeSpeed = _FadeSpeed;
}
