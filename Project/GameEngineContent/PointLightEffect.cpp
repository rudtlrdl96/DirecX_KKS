#include "PrecompileHeader.h"
#include "PointLightEffect.h"

PointLightEffect::PointLightEffect()
{
}

PointLightEffect::~PointLightEffect()
{
}

void PointLightEffect::SetState(LightType _State)
{
	if (LightType::None == _State)
	{
		MsgAssert_Rtti<PointLightEffect>(" - 라이트의 타입은 None으로 설정할 수 없습니다");
		return;
	}

	State = _State;

	switch (State)
	{
	case LightType::Circle:
		LightUnit->SetPipeLine("CirclePointLight");
		break;
	case LightType::Box:
		LightUnit->SetPipeLine("CirclePointLight");
		break;
	}


	LightUnit->ShaderResHelper.SetConstantBufferLink("RenderBaseValue", BaseValue);
	LightUnit->ShaderResHelper.SetConstantBufferLink("ColorData", LightBuffer);
}

void PointLightEffect::Start(GameEngineRenderTarget* _Target)
{
	LightUnit = std::make_shared<GameEngineRenderUnit>();
	LightUnit->SetMesh("FullRect");

	ResultTarget = GameEngineRenderTarget::Create(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, GameEngineWindow::GetScreenSize(), float4::Null);

	BaseValue.ScreenScale = GameEngineWindow::GetScreenSize();
}

void PointLightEffect::Effect(GameEngineRenderTarget* _Target, float _DeltaTime)
{
	if (LightType::None == State)
	{
		MsgAssert_Rtti<PointLightEffect>(" - 포인트 라이트의 타입을 설정하지 않았습니다.");
		return;
	}

	BaseValue.Mouse = GameEngineWindow::GetMousePosition();
	BaseValue.Mouse.z = GameEngineInput::IsPress("EngineMouseLeft");
	BaseValue.Mouse.w = GameEngineInput::IsPress("EngineMouseLeft");

	BaseValue.Time.x += _DeltaTime;
	BaseValue.Time.y = _DeltaTime;

	ResultTarget->Clear();
	ResultTarget->Setting();

	LightUnit->ShaderResHelper.SetTexture("DiffuseTex", _Target->GetTexture(0));
	LightUnit->Render(_DeltaTime);
	LightUnit->ShaderResHelper.AllResourcesReset();

	_Target->Clear();
	_Target->Merge(ResultTarget);
}
