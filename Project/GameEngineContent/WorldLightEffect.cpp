#include "PrecompileHeader.h"
#include "WorldLightEffect.h"

WorldLightEffect::WorldLightEffect()
{
}

WorldLightEffect::~WorldLightEffect()
{
}

void WorldLightEffect::Start(GameEngineRenderTarget* _Target)
{
	LightUnit = std::make_shared<GameEngineRenderUnit>();
	LightUnit->SetMesh("FullRect");
	LightUnit->SetPipeLine("WorldLight");

	LightUnit->ShaderResHelper.SetConstantBufferLink("ColorData", WorldLight);
	ResultTarget = GameEngineRenderTarget::Create(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, GameEngineWindow::GetScreenSize(), float4::Null);
}

void WorldLightEffect::Effect(GameEngineRenderTarget* _Target, float _DeltaTime)
{
	ResultTarget->Clear();
	ResultTarget->Setting();

	LightUnit->ShaderResHelper.SetTexture("DiffuseTex", _Target->GetTexture(0));
	LightUnit->Render(_DeltaTime);
	LightUnit->ShaderResHelper.AllResourcesReset();

	_Target->Clear();
	_Target->Merge(ResultTarget);
}