#include "PrecompileHeader.h"
#include "StoryFade.h"
#include "ContentUIRender.h"

StoryFade::StoryFade()
{
}

StoryFade::~StoryFade()
{
}

void StoryFade::FadeIn()
{
	State = StoryFadeState::FadeIn;
	FadeProgress = 0.0f;
}

void StoryFade::FadeOut()
{
	State = StoryFadeState::FadeOut;
	FadeProgress = 0.0f;
}

void StoryFade::Reset()
{
	State = StoryFadeState::None;
	FadeProgress = 0.0f;

	UpRenderer->GetTransform()->SetLocalPosition(UpStart);
	DownRenderer->GetTransform()->SetLocalPosition(DownStart);
}

void StoryFade::Start()
{
	if (nullptr == GameEngineTexture::Find("StoryFade.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("UI");

		GameEngineTexture::Load(Path.GetPlusFileName("StoryFade.png").GetFullPath());
	}

	float4 WindowSize = GameEngineWindow::GetScreenSize();

	UpRenderer = CreateComponent<ContentUIRender>();
	UpRenderer->PipeSetting("2DTexture_Color");
	UpRenderer->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", UpRenderBuffer);
	UpRenderer->SetScaleToTexture("StoryFade.png");

	DownRenderer = CreateComponent<ContentUIRender>();
	DownRenderer->PipeSetting("2DTexture_Color");
	DownRenderer->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", DownRenderBuffer);
	DownRenderer->SetScaleToTexture("StoryFade.png");

	float4 TextureScale = DownRenderer->GetTransform()->GetLocalScale();

	UpStart = float4(0, WindowSize.hy() + TextureScale.hy(), 0);
	UpEnd = float4(0, WindowSize.hy() - TextureScale.hy(), 0);

	UpRenderer->GetTransform()->SetLocalPosition(UpStart);

	DownStart = float4(0, -WindowSize.hy() - TextureScale.hy(), 0);
	DownEnd = float4(0, -WindowSize.hy() + TextureScale.hy(), 0);

	DownRenderer->GetTransform()->SetLocalPosition(DownStart);
}

void StoryFade::Update(float _DeltaTime)
{
	switch (State)
	{
	case StoryFade::StoryFadeState::FadeIn:
	{
		FadeProgress += _DeltaTime * FadeSpeed;

		float4 UpRenderPos = float4::LerpClamp(UpStart, UpEnd, FadeProgress);
		UpRenderer->GetTransform()->SetLocalPosition(UpRenderPos);

		float4 DownRenderPos = float4::LerpClamp(DownStart, DownEnd, FadeProgress);
		DownRenderer->GetTransform()->SetLocalPosition(DownRenderPos);
	}
		break;
	case StoryFade::StoryFadeState::FadeOut:
	{
		FadeProgress += _DeltaTime * FadeSpeed;

		float4 UpRenderPos = float4::LerpClamp(UpEnd, UpStart, FadeProgress);
		UpRenderer->GetTransform()->SetLocalPosition(UpRenderPos);

		float4 DownRenderPos = float4::LerpClamp(DownEnd, DownStart, FadeProgress);
		DownRenderer->GetTransform()->SetLocalPosition(DownRenderPos);
	}
		break;
	}
}
