#include "PrecompileHeader.h"
#include "FadeActor.h"

FadeActor::FadeActor()
{
}

FadeActor::~FadeActor()
{
}

void FadeActor::SetFade()
{
	FadeColor.w = 1.0f;
	State = FadeState::Wait;
}

void FadeActor::SetUnFade()
{
	FadeColor.w = 0.0f;
	State = FadeState::Wait;
}

void FadeActor::FadeIn(std::function<void()> _FadeEndCallback /*= nullptr*/)
{
	FadeColor.w = 0.0f;
	State = FadeState::FadeIn;
	FadeEndCallback = _FadeEndCallback;
}

void FadeActor::FadeOut(std::function<void()> _FadeEndCallback /*= nullptr*/)
{
	FadeColor.w = 1.0f;
	State = FadeState::FadeOut;
	FadeEndCallback = _FadeEndCallback;
}

void FadeActor::Reset()
{
	State = FadeState::Wait;
	FadeColor = float4(0, 0, 0, 1);
	FadeSpeed = 1.0f;
}

void FadeActor::Start()
{
	MainRenderer = CreateComponent<GameEngineSpriteRenderer>();
	MainRenderer->SetPipeLine("2DTexture_ColorLight");
	MainRenderer->GetShaderResHelper().SetConstantBufferLink("OutPixelColor", FadeColor);
	MainRenderer->SetTexture("FadeImage.png");
	MainRenderer->GetTransform()->SetWorldScale(GameEngineWindow::GetScreenSize());
	MainRenderer->GetTransform()->SetWorldPosition({0, 0, -999, 1});
}

void FadeActor::Update(float _DeltaTime)
{
	switch (State)
	{
	case FadeActor::FadeState::FadeIn:
		FadeColor.w += _DeltaTime *= FadeSpeed;

		if (FadeColor.w >= 1.0f)
		{
			FadeColor.w = 1.0f;
			State = FadeState::Wait;

			if (nullptr != FadeEndCallback)
			{
				FadeEndCallback();
				FadeEndCallback = nullptr;
			}
		}

		break;
	case FadeActor::FadeState::FadeOut:
		FadeColor.w -= _DeltaTime *= FadeSpeed;

		if (FadeColor.w <= 0.0f)
		{
			FadeColor.w = 0;
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