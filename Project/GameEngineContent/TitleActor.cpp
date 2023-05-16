#include "PrecompileHeader.h"
#include "TitleActor.h"

TitleActor::TitleActor()
{
}

TitleActor::~TitleActor()
{

}

void TitleActor::TitleOn(float _LogoWaitTime, float _LogoFadeSpeed)
{
	WaitTime = _LogoWaitTime;
	TextureRender->On();
	LogoRender->Off();
	ProgressTime = 0.0f;
	LogoFadeProgress = 0.0f;
	LogoFadeSpeed = _LogoFadeSpeed;
}

void TitleActor::Start()
{
	TextureRender = CreateComponent<ContentSpriteRenderer>();
	TextureRender->SetPipeLine("2DTexture_ColorLight");
	TextureRender->SetAtlasConstantBuffer();
	TextureRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", BackTexBuffer);
	TextureRender->SetTexture("DarkMirror_Title_Art_1.png");
	TextureRender->GetTransform()->SetWorldScale(GameEngineWindow::GetScreenSize());
	TextureRender->Off();

	std::shared_ptr<GameEngineTexture> FindTex = GameEngineTexture::Find("Title_Logo2.png");

	if (nullptr == FindTex)
	{
		MsgAssert_Rtti<TitleActor>(" - 타이틀 로고 텍스쳐를 찾지 못했습니다");
	}

	float4 LogoSize = {static_cast<float>(FindTex->GetWidth()), static_cast<float>(FindTex->GetHeight())};
	LogoSize *= 0.7f;

	LogoRender = CreateComponent<ContentSpriteRenderer>();
	LogoRender->SetPipeLine("2DTexture_ColorLight");
	LogoRender->SetAtlasConstantBuffer();
	LogoRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", LogoBuffer);
	LogoRender->SetTexture("Title_Logo2.png");
	LogoRender->GetTransform()->SetWorldScale(LogoSize);
	LogoRender->GetTransform()->SetWorldPosition({0, -150, -100});

	LogoRender->Off();
}

void TitleActor::Update(float _DeltaTime)
{
	if (false == TextureRender->IsUpdate())
	{
		return;
	}

	ProgressTime += _DeltaTime;

	if (ProgressTime >= WaitTime)
	{
		LogoRender->On();
		LogoFadeProgress += _DeltaTime * LogoFadeSpeed;

		if (LogoFadeProgress > 1.0f)
		{
			LogoFadeProgress = 1.0f;
			IsLogoFadeValue = true;
		}

		LogoBuffer.Color.w = LogoFadeProgress;
	}
}
