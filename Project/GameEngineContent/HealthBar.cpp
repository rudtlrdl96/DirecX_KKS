#include "PrecompileHeader.h"
#include "HealthBar.h"

HealthBar::HealthBar()
{
}

HealthBar::~HealthBar()
{
}

void HealthBar::SetTexture(const std::string_view& _FrameName, const std::string_view& _BarName)
{
	BarRedner->SetScaleToTexture(_BarName);
	FrameRedner->SetScaleToTexture(_FrameName);
	BarRedner->On();
	FrameRedner->On();
}

void HealthBar::Start()
{
	BarRedner = CreateComponent<ContentSpriteRenderer>();
	BarRedner->PipeSetting("2DTexture_ProgressUI");
	BarRedner->GetShaderResHelper().SetConstantBufferLink("ProgressBuffer", BarBuffer);
	BarRedner->GetTransform()->SetLocalPosition(float4(0, 0, 0.0f));
	BarRedner->Off();

	FrameRedner = CreateComponent<ContentSpriteRenderer>();
	FrameRedner->PipeSetting("2DTexture_ColorLight");
	FrameRedner->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", FrameBuffer);
	FrameRedner->GetTransform()->SetLocalPosition(float4(0, 0, 0.01f));
	FrameRedner->Off();
}

void HealthBar::UpdateBar(float _Progress)
{
	BarBuffer.ColorProgress.SizeX = _Progress;
}
