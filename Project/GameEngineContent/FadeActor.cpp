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
	Buffer.Color.w = 1.0f;
	State = FadeState::Wait;
}

void FadeActor::SetUnFade()
{
	Buffer.Color.w = 0.0f;
	State = FadeState::Wait;
}

void FadeActor::FadeIn(std::function<void()> _FadeEndCallback /*= nullptr*/)
{
	Buffer.Color.w = 0.0f;
	State = FadeState::FadeIn;
	FadeEndCallback = _FadeEndCallback;
}

void FadeActor::FadeOut(std::function<void()> _FadeEndCallback /*= nullptr*/)
{
	Buffer.Color.w = 1.0f;
	State = FadeState::FadeOut;
	FadeEndCallback = _FadeEndCallback;
}

void FadeActor::Reset()
{
	State = FadeState::Wait;
	Buffer.Color = float4(0, 0, 0, 1);
	FadeSpeed = 1.0f;
}

void FadeActor::Start()
{
	MainRenderer = CreateComponent<ContentSpriteRenderer>();
	MainRenderer->SetPipeLine("2DTexture_Fade");
	MainRenderer->SetAtlasConstantBuffer();
	MainRenderer->GetShaderResHelper().SetConstantBufferLink("FadeBuffer", Buffer);
	MainRenderer->SetTexture("FadeImage.png");
	MainRenderer->GetTransform()->SetWorldScale(GameEngineWindow::GetScreenSize());
	MainRenderer->GetTransform()->SetWorldPosition({0, 0, -999, 1});
}

void FadeActor::Update(float _DeltaTime)
{
	switch (State)
	{
	case FadeActor::FadeState::FadeIn:
		Buffer.Color.w += _DeltaTime *= FadeSpeed;

		if (Buffer.Color.w >= 1.0f)
		{
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