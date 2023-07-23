#include "PrecompileHeader.h"
#include "EffectActor_Linear.h"

EffectActor_Linear::EffectActor_Linear()
{
}

EffectActor_Linear::~EffectActor_Linear()
{
}

void EffectActor_Linear::Start()
{
	EffectRender = CreateComponent<ContentSpriteRenderer>();
	EffectRender->PipeSetting("2DTexture_ColorLinear");
	EffectRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	EffectRender->SetTexture("Empty.png");
	EffectRender->Off();
}
