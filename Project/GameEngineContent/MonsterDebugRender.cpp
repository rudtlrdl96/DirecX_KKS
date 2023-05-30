#include "PrecompileHeader.h"
#include "MonsterDebugRender.h"

MonsterDebugRender::MonsterDebugRender()
{
}

MonsterDebugRender::~MonsterDebugRender()
{
}

void MonsterDebugRender::SetScaleToTexture(const std::string_view& _TextureName)
{
	Redner->SetScaleToTexture(_TextureName);

	float4 Scale = Redner->GetTransform()->GetWorldScale();
	Redner->GetTransform()->SetWorldScale(Scale * 2.0f);
}

void MonsterDebugRender::Start()
{
	Redner = CreateComponent<ContentSpriteRenderer>();
	Redner->PipeSetting("2DTexture_Outline");
	Redner->GetShaderResHelper().SetConstantBufferLink("OutlineColorBuffer", Buffer);
}
