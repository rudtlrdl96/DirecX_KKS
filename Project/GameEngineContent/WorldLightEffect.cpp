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
	LightUnit->SetPipeLine("Fade");

	//LightUnit->ShaderResHelper.SetConstantBufferLink("FADEDATA", FadeData);
	ResultTarget = GameEngineRenderTarget::Create(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, GameEngineWindow::GetScreenSize(), float4::Null);
}

void WorldLightEffect::Effect(GameEngineRenderTarget* _Target, float _DeltaTime)
{
}
