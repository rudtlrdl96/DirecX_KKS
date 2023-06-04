#include "PrecompileHeader.h"
#include "TalkArrow.h"
#include "ContentUIRender.h"

TalkArrow::TalkArrow()
{
}

TalkArrow::~TalkArrow()
{
}

void TalkArrow::Start()
{
	if (nullptr == GameEngineTexture::Find("TalkboxArrow.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resrouces");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("UI");

		GameEngineTexture::Load(Path.GetPlusFileName("TalkboxArrow.png").GetFullPath());
	}

	ArrowRender = CreateComponent<ContentUIRender>();
	ArrowRender->PipeSetting("2DTexture_ColorLight");
	ArrowRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", ArrowBuffer);
	ArrowRender->SetScaleToTexture("TalkboxArrow.png");
}

void TalkArrow::Update(float _DeltaTime)
{
	ArrowProgress += _DeltaTime * ArrowSpeed;

	switch (State)
	{
	case TalkArrow::ArrowState::FadeIn:
	{
		ArrowBuffer.Color.a = 1.0f - ArrowProgress;
		break;
	}
	case TalkArrow::ArrowState::FadeOut:
	{
		ArrowBuffer.Color.a = ArrowProgress;
		break;
	}
	}

	if (1.0f <= ArrowProgress)
	{
		switch (State)
		{
		case TalkArrow::ArrowState::FadeIn:
		{		
			State = ArrowState::FadeOut;
			ArrowProgress -= 1.0f;
		}
			break;
		case TalkArrow::ArrowState::FadeOut:
		{
			State = ArrowState::FadeIn;
			ArrowProgress -= 1.0f;
		}
			break;
		}	
	}
}
