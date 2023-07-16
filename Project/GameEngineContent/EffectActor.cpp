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
	if (true == IsFadeIntroValue)
	{
		IntroProgress += _DeltaTime * IntroFadeSpeed;

		if (1.0f <= IntroProgress)
		{
			IntroProgress = 1.0f;
			IsFadeIntroValue = false;
		}

		Buffer.Color.a = EffectAlpha * IntroProgress;
	}

	if (true == IsFadeDeathValue)
	{
		DeathProgress += _DeltaTime * DeathFadeSpeed;

		if (1.0f <= DeathProgress)
		{
			DeathProgress = 1.0f;
			Death();
		}

		Buffer.Color.a = EffectAlpha - (DeathProgress * EffectAlpha);
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

	case EffectDeathTrigger::None:
		break;

	default:
		MsgAssert_Rtti<EffectActor>(" - 알 수 없는 이펙트 DeathTrigger 입니다");
		break;
	}

}

void EffectActor::Init(const EffectMetaData& _MetaData, const EffectParameter& _Parameter)
{
	DeathTime = _Parameter.Time;
	DeathTrigger = _Parameter.Triger;
	
	bool Loop = _Parameter.Triger != EffectDeathTrigger::AnimEnd;

	if (true == _Parameter.IsForceLoopOff)
	{
		Loop = false;
	}

	EffectRender->CreateAnimation({
	.AnimationName = _MetaData.SpriteName,
	.SpriteName = _MetaData.SpriteName,
	.Start = _MetaData.AnimStart,
	.End = _MetaData.AnimEnd,
	.FrameInter = _MetaData.AnimInter,
	.Loop = Loop,
	.ScaleToTexture = true,
	.FrameTime = _MetaData.FrameAnimIter,
	});

	GameEngineTransform* RenderTrans = EffectRender->GetTransform();
	RenderTrans->SetLocalPosition(_MetaData.RenderPivot);
	EffectRender->SetScaleRatio(_MetaData.ScaleRatio);
	EffectRender->ChangeAnimation(_MetaData.SpriteName);
	EffectRender->On();

	WaitTime = _Parameter.WaitTime;

	Buffer.Color = _MetaData.Color;
	EffectAlpha = Buffer.Color.a;

	IsFadeDeath = _Parameter.IsFadeDeath;
	IsFadeIntroValue = _Parameter.IsFadeIntro;
	DeathFadeSpeed = _Parameter.DeathFadeSpeed;
	IntroFadeSpeed = _Parameter.IntroFadeSpeed;
}
