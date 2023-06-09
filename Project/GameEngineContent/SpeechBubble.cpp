#include "PrecompileHeader.h"
#include "SpeechBubble.h"
#include "ContentUIRender.h"

SpeechBubble::SpeechBubble()
{
}

SpeechBubble::~SpeechBubble()
{
}

void SpeechBubble::PlayBubble(const SpeechBubbleParameter& _BubbleParameter)
{
	Target = _BubbleParameter.Target;

	if (nullptr == Target.lock())
	{
		BubbleRender->Off();
		return;
	}

	TalkText = _BubbleParameter.Text;
	Pivot = _BubbleParameter.Pivot;

	IsLoop = _BubbleParameter.IsLoop;

	if (true == _BubbleParameter.IsLarge)
	{
		BubbleRender->SetScaleToTexture("SpeechBubble_Large.png");
	}
	else
	{
		BubbleRender->SetScaleToTexture("SpeechBubble.png");
	}

	BubbleRender->On();

	LiveTime = _BubbleParameter.LiveTime;
	LoopInter = _BubbleParameter.LoopInter;
}

void SpeechBubble::Start()
{
	if (nullptr == GameEngineTexture::Find("SpeechBubble.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("UI");

		GameEngineTexture::Load(Path.GetPlusFileName("SpeechBubble.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("SpeechBubble_Large.png").GetFullPath());
	}

	BubbleRender = CreateComponent<ContentSpriteRenderer>();
	BubbleRender->PipeSetting("2DTexture_ColorLight");
	BubbleRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	BubbleRender->Off();
}

void SpeechBubble::Update(float _DeltaTime)
{
	if (nullptr != Target.lock() && true == Target.lock()->IsDeath())
	{
		Target.lock() = nullptr;
	}

	if (nullptr == Target.lock())
	{
		BubbleRender->Off();
		return;
	}
	else
	{
		BubbleRender->On();
	}

	OffTime += _DeltaTime;

	if (0.0f > OffTime)
	{
		BubbleRender->Off();
		ResetLiveTime();
	}

	float4 TargetPos = Target.lock()->GetTransform()->GetWorldPosition();
	TargetPos.z = 0.0f;

	GetTransform()->SetWorldPosition(TargetPos + Pivot);
	
	if (GetLiveTime() >= LiveTime)
	{
		if (false == IsLoop)
		{
			Death();
		}
		else
		{
			ResetLiveTime();
			OffTime = -LoopInter;
		}
	}

}