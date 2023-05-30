#include "PrecompileHeader.h"
#include "ScaleDebugRender.h"

ScaleDebugRender::ScaleDebugRender()
{
}

ScaleDebugRender::~ScaleDebugRender()
{
}

void ScaleDebugRender::Start()
{
	DebugRender = CreateComponent<ContentSpriteRenderer>();
	DebugRender->PipeSetting("2DTexture_ColorLight");
	DebugRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", DebugBuffer);
	DebugRender->SetTexture("ScaleCol.png");
	DebugRender->GetTransform()->SetLocalScale(float4::One);
}