#include "PrecompileHeader.h"
#include "HealthBar.h"
#include "ContentUIRender.h"

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
	BarRedner = CreateComponent<ContentUIRender>();
	BarRedner->PipeSetting("2DTexture_ProgressUI");
	BarRedner->GetShaderResHelper().SetConstantBufferLink("ProgressBuffer", BarBuffer);
	BarRedner->Off();

	FrameRedner = CreateComponent<ContentUIRender>();
	FrameRedner->PipeSetting("2DTexture_ProgressUI");
	FrameRedner->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", FrameBuffer);
	FrameRedner->GetTransform()->SetLocalPosition(float4(0, 0, 0.01f));
	FrameRedner->Off();
}
