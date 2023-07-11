#include "PrecompileHeader.h"
#include "Minimap.h"
#include "ContentUIRender.h"

Minimap::Minimap()
{
}

Minimap::~Minimap()
{
}

void Minimap::MinimapOn()
{
	State = MinimapState::On;
	Progress = 0.0f;
	On();
}

void Minimap::MinimapOff(bool _Force /*= false*/)
{
	if (true == _Force)
	{
		GetTransform()->SetWorldPosition(EndPos);
		Off();
	}
	else
	{
		State = MinimapState::Off;
		Progress = 0.0f;
	}
}

void Minimap::Start()
{
	if (nullptr == GameEngineTexture::Find("Minimap_Frame.png"))
	{
		GameEngineDirectory Path;
		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("UI");

		GameEngineTexture::Load(Path.GetPlusFileName("Minimap_Frame.png").GetFullPath());
	}

	MinimapFrameRender = CreateComponent<ContentUIRender>();
	MinimapFrameRender->PipeSetting("2DTexture_Color");
	MinimapFrameRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	MinimapFrameRender->SetScaleToTexture("Minimap_Frame.png");
	float4 FrameScale = MinimapFrameRender->GetTransform()->GetLocalScale();
	MinimapFrameRender->GetTransform()->SetLocalScale(FrameScale * 2.0f);


	StartPos = float4(530, -430);
	EndPos = float4(530, -295);

	GetTransform()->SetWorldPosition(StartPos);
}

void Minimap::Update(float _DeltaTime)
{
	switch (State)
	{
	case MinimapState::On:
	{
		Progress += _DeltaTime * 2.0f;

		GetTransform()->SetWorldPosition(float4::LerpClamp(StartPos, EndPos, Progress));

		if (1.0f <= Progress)
		{
			State = MinimapState::None;
		}
	}
		break;
	case MinimapState::Off:
	{
		Progress += _DeltaTime * 2.0f;
	
		GetTransform()->SetWorldPosition(float4::LerpClamp(EndPos, StartPos, Progress));

		if (1.0f <= Progress)
		{
			Off();
			State = MinimapState::None;
		}

	}
		break;
	}
}
