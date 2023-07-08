#include "PrecompileHeader.h"
#include "FadeActor.h"
#include "ContentFadeRender.h"
#include "ContentUIRender.h"

FadeActor::FadeActor()
{
}

FadeActor::~FadeActor()
{
}

void FadeActor::SetFade(const float4& _FadeColor /*= float4::Zero*/)
{
	IsFadeEndValue = true;
	Buffer.Color.x = _FadeColor.x;
	Buffer.Color.y = _FadeColor.y;
	Buffer.Color.z = _FadeColor.z;
	Buffer.Color.w = 1.0f;
	State = FadeState::Wait;
}

void FadeActor::SetUnFade(const float4& _FadeColor /*= float4::Zero*/)
{
	IsFadeEndValue = true;
	Buffer.Color.x = _FadeColor.x;
	Buffer.Color.y = _FadeColor.y;
	Buffer.Color.z = _FadeColor.z;
	Buffer.Color.w = 0.0f;
	State = FadeState::Wait;
}

void FadeActor::FadeIn(std::function<void()> _FadeEndCallback /*= nullptr*/, const float4& _FadeColor /*= float4::Zero*/)
{
	IsFadeEndValue = false;
	Buffer.Color.x = _FadeColor.x;
	Buffer.Color.y = _FadeColor.y;
	Buffer.Color.z = _FadeColor.z;
	Buffer.Color.w = 0.0f;
	State = FadeState::FadeIn;
	FadeEndCallback = _FadeEndCallback;

	CurWaitTime = 0.0f;
}

void FadeActor::FadeOut(std::function<void()> _FadeEndCallback /*= nullptr*/, const float4& _FadeColor /*= float4::Zero*/)
{
	IsFadeEndValue = false;
	Buffer.Color.x = _FadeColor.x;
	Buffer.Color.y = _FadeColor.y;
	Buffer.Color.z = _FadeColor.z;
	Buffer.Color.w = 1.0f;
	State = FadeState::FadeOut;
	FadeEndCallback = _FadeEndCallback;

	CurWaitTime = 0.0f;
}

void FadeActor::Reset()
{
	IsFadeEndValue = true;
	State = FadeState::Wait;
	Buffer.Color = float4::Zero;
	FadeSpeed = 1.0f;
}

void FadeActor::Start()
{
	MainRenderer = CreateComponent<ContentFadeRender>();
	MainRenderer->PipeSetting("2DTexture_Color");
	MainRenderer->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	MainRenderer->SetTexture("FadeImage.png");
	MainRenderer->GetTransform()->SetWorldScale(GameEngineWindow::GetScreenSize());
	MainRenderer->GetTransform()->SetLocalPosition({0, 0, 0, 1});
}

void FadeActor::Update(float _DeltaTime)
{
	CurWaitTime += _DeltaTime;

	if (CurWaitTime < WaitTime)
	{
		return;
	}

	switch (State)
	{
	case FadeActor::FadeState::FadeIn:
		Buffer.Color.w += _DeltaTime *= FadeSpeed;

		if (Buffer.Color.w >= 1.0f)
		{
			IsFadeEndValue = true;

			Buffer.Color.w = 1.0f;
			State = FadeState::Wait;

			if (nullptr != FadeEndCallback)
			{
				FadeEndCallback();
				FadeEndCallback = nullptr;
			}
		}

		break;
	case FadeActor::FadeState::FadeOut:
		Buffer.Color.w -= _DeltaTime *= FadeSpeed;

		if (Buffer.Color.w <= 0.0f)
		{
			IsFadeEndValue = true;

			Buffer.Color.w = 0;
			State = FadeState::Wait;

			if (nullptr != FadeEndCallback)
			{
				FadeEndCallback();
				FadeEndCallback = nullptr;
			}
		}
		break;
	default:
		return;
	}

}