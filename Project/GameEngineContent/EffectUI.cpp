#include "PrecompileHeader.h"
#include "EffectUI.h"
#include "ContentSpriteUIRenderer.h"

EffectUI::EffectUI()
{
}

EffectUI::~EffectUI()
{
}

void EffectUI::Start()
{
	EffectRender = CreateComponent<ContentSpriteUIRenderer>();
	EffectRender->PipeSetting("2DTexture_ColorLight");
	EffectRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	EffectRender->SetTexture("Empty.png");
	EffectRender->Off();
}
