#include "PrecompileHeader.h"
#include "ScaleDebugRender.h"

ScaleDebugRender::ScaleDebugRender()
{
}

ScaleDebugRender::~ScaleDebugRender()
{
}

void ScaleDebugRender::SetTexture(const std::string_view& _TexName)
{
	DebugRender->SetTexture(_TexName);
}

void ScaleDebugRender::Start()
{
	DebugRender = CreateComponent<ContentSpriteRenderer>();
	DebugRender->PipeSetting("2DTexture_Color");
	DebugRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", DebugBuffer);
	DebugRender->SetTexture("ScaleCol.png");
	DebugRender->GetTransform()->SetLocalScale(float4::One);
}