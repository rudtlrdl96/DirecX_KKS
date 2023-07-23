#include "PrecompileHeader.h"
#include "EffectUI_Linear.h"
#include "ContentSpriteUIRenderer.h"

EffectUI_Linear::EffectUI_Linear()
{
}

EffectUI_Linear::~EffectUI_Linear()
{
}

void EffectUI_Linear::Start()
{
	EffectRender = CreateComponent<ContentSpriteUIRenderer>();
	EffectRender->PipeSetting("2DTexture_ColorLinear");
	EffectRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	EffectRender->SetTexture("Empty.png");
	EffectRender->Off();
}
