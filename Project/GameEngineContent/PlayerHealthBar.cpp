#include "PrecompileHeader.h"
#include "PlayerHealthBar.h"
#include "ContentUIRender.h"

PlayerHealthBar::PlayerHealthBar()
{
}

PlayerHealthBar::~PlayerHealthBar()
{
}

void PlayerHealthBar::SetTexture(const std::string_view& _BarName, const std::string_view& _SubBarName)
{
	BarRedner->SetScaleToTexture(_BarName);
	BarRedner->GetTransform()->SetWorldScale(BarRedner->GetTransform()->GetWorldScale() * 1.5f);

	SubBarRedner->SetScaleToTexture(_SubBarName);
	SubBarRedner->GetTransform()->SetWorldScale(SubBarRedner->GetTransform()->GetWorldScale() * 1.5f);

	BarRedner->On();
	SubBarRedner->On();
	HpFontRender->On();
}

void PlayerHealthBar::SetScale(float _Scale)
{
	BarRedner->GetTransform()->SetWorldScale(BarRedner->GetTransform()->GetWorldScale() * _Scale);
	SubBarRedner->GetTransform()->SetWorldScale(SubBarRedner->GetTransform()->GetWorldScale() * _Scale);
}

void PlayerHealthBar::Start()
{
	BarRedner = CreateComponent<ContentUIRender>();
	BarRedner->PipeSetting("2DTexture_ProgressUI");
	BarRedner->GetShaderResHelper().SetConstantBufferLink("ProgressBuffer", BarBuffer);
	BarRedner->GetTransform()->SetLocalPosition(float4(0, 0, 0.0f));
	BarRedner->GetTransform()->SetWorldRotation(float4(0, 0, 0));
	BarRedner->Off();

	SubBarRedner = CreateComponent<ContentUIRender>();
	SubBarRedner->PipeSetting("2DTexture_ProgressUI");
	SubBarRedner->GetShaderResHelper().SetConstantBufferLink("ProgressBuffer", SubBarBuffer);
	SubBarRedner->GetTransform()->SetLocalPosition(float4(0, 0, 0.01f));
	SubBarRedner->GetTransform()->SetWorldRotation(float4(0, 0, 0));
	SubBarRedner->Off();

	HpFontRender = CreateComponent<ContentUIFontRenderer>();
	HpFontRender->SetFont("ÈÞ¸ÕµÕ±ÙÇìµå¶óÀÎ");
	HpFontRender->GetTransform()->SetLocalPosition(float4(0, 0, -1));
	HpFontRender->SetScale(18);
	HpFontRender->SetFontFlag(static_cast<FW1_TEXT_FLAG>(FW1_CENTER | FW1_VCENTER));
	HpFontRender->SetColor(float4(0.9f, 0.9f, 0.9f, 1));
	HpFontRender->Off();

	GetTransform()->SetWorldRotation(float4::Zero);
}

void PlayerHealthBar::UpdateBar(float _CurHP, float _MaxHP, float _DeltaTime)
{
	float Progress = _CurHP / _MaxHP;

	HpFontRender->SetText(std::to_string((int)_CurHP) +  " / " + std::to_string((int)_MaxHP));

	GameEngineTransform* GetTrans = GetTransform();

	BarBuffer.ColorProgress.SizeX = Progress;

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
