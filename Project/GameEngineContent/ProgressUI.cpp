#include "PrecompileHeader.h"
#include "ProgressUI.h"
#include "ContentUIRender.h"

ProgressUI::ProgressUI()
{
}

ProgressUI::~ProgressUI()
{
}

void ProgressUI::Start()
{
	if (nullptr == GameEngineTexture::Find("FrameFill_Box.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("UI");

		GameEngineTexture::Load(Path.GetPlusFileName("FrameFill_Box.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("FrameFill_Circle.png").GetFullPath());
	}


	ProgressRender = CreateComponent<ContentUIRender>();
	ProgressRender->PipeSetting("2DTexture_ProgressUI");
	ProgressRender->GetShaderResHelper().SetConstantBufferLink("ProgressBuffer", Buffer);
	ProgressRender->Off();
}

void ProgressUI::InitValue(const float4& _Size, const float4& _Color)
{
	ProgressRender->GetTransform()->SetLocalScale(_Size);
	Buffer.OutColor = _Color;
}

void ProgressUI::InitProgressType(ProgressType _ProgressType, FillType _FillType)
{
	ProgressTypeValue = _ProgressType;
	FillTypeValue = _FillType;

	switch (ProgressTypeValue)
	{
	case ProgressType::Box:
		ProgressRender->SetTexture("FrameFill_Box.png");
		break;
	case ProgressType::Circle:
		ProgressRender->SetTexture("FrameFill_Circle.png");
		break;
	default:
		break;
	}

	ProgressRender->On();
}

void ProgressUI::UpdateProgress(float _Progress)
{
	Buffer.ColorProgress = float4(0, 0, 1, 1);

	switch (FillTypeValue)
	{
	case FillType::Left:
		Buffer.ColorProgress.z = 1.0f - _Progress;
		break;
	case FillType::Right:
		Buffer.ColorProgress.x = _Progress;
		break;
	case FillType::Up:
		Buffer.ColorProgress.w = 1.0f - _Progress;
		break;
	case FillType::Down:
		Buffer.ColorProgress.y = _Progress;
		break;
	default:
		break;
	}
}