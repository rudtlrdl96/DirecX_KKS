#include "PrecompileHeader.h"
#include "CaptureAnimation.h"

CaptureAnimation::CaptureAnimation()
{
}

CaptureAnimation::~CaptureAnimation()
{
}

void CaptureAnimation::PlayCapture(const CaptureAnimParameter& _Parameter)
{
	Progress = 0.0f;

	TargetRender = _Parameter.SpriteRender;	
	StartColor = _Parameter.StartColor;
	EndColor = _Parameter.EndColor;
	Speed = _Parameter.Speed;
	WaitTime = _Parameter.WaitTime;

	CaptureRender->On();
}

void CaptureAnimation::Start()
{
	CaptureRender = CreateComponent<ContentSpriteRenderer>();
	CaptureRender->SetPipeLine("2DTexture_FixedColor");
	CaptureRender->GetShaderResHelper().SetConstantBufferLink("AtlasData", AtlasData);
	CaptureRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	CaptureRender->SetTexture("Empty.png");
	CaptureRender->Off();
}

void CaptureAnimation::Update(float _DeltaTime)
{
	if (true == CaptureRender->IsUpdate())
	{
		Progress += _DeltaTime * Speed;

		std::shared_ptr<ContentSpriteRenderer> Target = TargetRender.lock();

		if (nullptr == Target)
		{
			Death();
			return;
		}

		CaptureRender->SetTexture(Target->GetTexName());
		CaptureRender->GetTransform()->SetWorldScale(Target->GetTransform()->GetWorldScale());
		GetTransform()->SetWorldPosition(Target->GetTransform()->GetWorldPosition() + float4(0, 0, -1.0f));

		AtlasData = Target->GetAtlasData();
		Buffer.Color = float4::LerpClamp(StartColor, EndColor, Progress - WaitTime);

		if (1.0f <= Progress - WaitTime)
		{
			Death();
			return;
		}
	}
}
