#include "PrecompileHeader.h"
#include "RookieHero_HealthBar.h"
#include "ContentUIRender.h"

RookieHero_HealthBar::RookieHero_HealthBar()
{
}

RookieHero_HealthBar::~RookieHero_HealthBar()
{
}

void RookieHero_HealthBar::SetDeathPicture()
{
	PictureRedner->SetTexture("RookieHero_UI_Dead.png");
}


void RookieHero_HealthBar::UpdateBar(float _Progress, float _DeltaTime)
{
	GameEngineTransform* GetTrans = GetTransform();

	BarBuffer.ColorProgress.SizeX = _Progress;

	if (false == IsSubUpdate && BarBuffer.ColorProgress.SizeX != SubBarBuffer.ColorProgress.SizeX)
	{
		StartProgress = SubBarBuffer.ColorProgress;
		EndProgress = BarBuffer.ColorProgress;

		IsSubUpdate = true;
		ProgressTime = 0.0f;
	}

	if (true == IsSubUpdate)
	{
		ProgressTime += _DeltaTime * 6.0f;

		if (BarBuffer.ColorProgress != EndProgress)
		{
			ProgressTime = 0.0f;

			StartProgress = SubBarBuffer.ColorProgress;
			EndProgress = BarBuffer.ColorProgress;
		}

		SubBarBuffer.ColorProgress = float4::Lerp(StartProgress, BarBuffer.ColorProgress, ProgressTime);

		if (1.0f <= ProgressTime)
		{
			IsSubUpdate = false;
		}
	}
}

void RookieHero_HealthBar::Destroy()
{
	GetContentLevel()->RemoveEvent("MoveStage", GetActorCode());
}

void RookieHero_HealthBar::Start()
{
	if (nullptr == GameEngineTexture::Find("EnemyHpBar.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("UI");

		GameEngineTexture::Load(Path.GetPlusFileName("EnemyHpBar.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("EnemySubBar.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("EnemyHpFrame.png").GetFullPath());
	}


	if (nullptr == GameEngineTexture::Find("AdventurerHealthBar_Frame.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("UI");

		GameEngineTexture::Load(Path.GetPlusFileName("AdventurerHealthBar_Frame.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("RookieHero_UI_Dead.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("RookieHero_UI_Portrait.png").GetFullPath());
	}

	BarRedner = CreateComponent<ContentUIRender>();
	BarRedner->PipeSetting("2DTexture_ProgressUI");
	BarRedner->GetShaderResHelper().SetConstantBufferLink("ProgressBuffer", BarBuffer);
	BarRedner->GetTransform()->SetLocalPosition(float4(-36, -21, 0.0f));
	BarRedner->GetTransform()->SetWorldRotation(float4(0, 0, 0));
	BarRedner->SetScaleToTexture("EnemyHpBar.png");
	BarRedner->GetTransform()->SetLocalScale(float4(148, 15, 1));

	SubBarRedner = CreateComponent<ContentUIRender>();
	SubBarRedner->PipeSetting("2DTexture_ProgressUI");
	SubBarRedner->GetShaderResHelper().SetConstantBufferLink("ProgressBuffer", SubBarBuffer);
	SubBarRedner->GetTransform()->SetLocalPosition(float4(-36, -21, 0.01f));
	SubBarRedner->GetTransform()->SetWorldRotation(float4(0, 0, 0));
	SubBarRedner->SetScaleToTexture("EnemySubBar.png");
	SubBarRedner->GetTransform()->SetLocalScale(float4(148, 15, 1));

	FrameRedner = CreateComponent<ContentUIRender>();
	FrameRedner->PipeSetting("2DTexture_Color");
	FrameRedner->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", FrameBuffer);
	FrameRedner->GetTransform()->SetLocalPosition(float4(0, 0, 0.02f));
	FrameRedner->GetTransform()->SetWorldRotation(float4(0, 0, 0));
	FrameRedner->SetScaleToTexture("AdventurerHealthBar_Frame.png");

	float4 FrameScale = FrameRedner->GetTransform()->GetLocalScale();
	FrameRedner->GetTransform()->SetLocalScale(FrameScale * 2.0f);

	PictureRedner = CreateComponent<ContentUIRender>();
	PictureRedner->PipeSetting("2DTexture_Color");
	PictureRedner->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", PictureBuffer);
	PictureRedner->GetTransform()->SetLocalPosition(float4(78, 0, 0.02f));
	PictureRedner->GetTransform()->SetWorldRotation(float4(0, 0, 0));
	PictureRedner->SetScaleToTexture("RookieHero_UI_Portrait.png");
	PictureRedner->GetTransform()->SetLocalScale(float4(52, 52, 1));



	NameFontRender = CreateComponent<ContentUIFontRenderer>();
	NameFontRender->SetFont("≥ÿΩºLv2∞ÌµÒ");
	NameFontRender->GetTransform()->SetLocalPosition(float4(-32, 4, -1));
	NameFontRender->SetScale(16);
	NameFontRender->SetFontFlag(static_cast<FW1_TEXT_FLAG>(FW1_CENTER | FW1_VCENTER));
	NameFontRender->SetColor(float4(0.7647f, 0.7098f, 0.6627f, 1));
	NameFontRender->SetText("æ»µÂ∑π¿Ã 13ºº");

	LevelFontRender = CreateComponent<ContentUIFontRenderer>();
	LevelFontRender->SetFont("≥ÿΩºLv2∞ÌµÒ");
	LevelFontRender->GetTransform()->SetLocalPosition(float4(53, -15, -1));
	LevelFontRender->SetScale(14);
	LevelFontRender->SetFontFlag(static_cast<FW1_TEXT_FLAG>(FW1_CENTER | FW1_VCENTER));
	LevelFontRender->SetColor(float4(0.7647f, 0.7098f, 0.6627f, 1));
	LevelFontRender->SetText("6");


	GetContentLevel()->AddEvent("MoveStage", GetActorCode(), [this]()
		{
			Death();
		});

	GetTransform()->SetWorldRotation(float4::Zero);
}
