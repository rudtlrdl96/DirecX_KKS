#include "PrecompileHeader.h"
#include "PlayerHitFade.h"

#include "ContentUIRender.h"

PlayerHitFade::PlayerHitFade()
{
}

PlayerHitFade::~PlayerHitFade()
{
}

void PlayerHitFade::Active()
{
	IsFadeActive = true;
	Progress = 0.0f;
}

void PlayerHitFade::Start()
{
	if (nullptr == GameEngineTexture::Find("PlaherHitFade.png"))
	{
		GameEngineDirectory Path;
		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("UI");

		GameEngineTexture::Load(Path.GetPlusFileName("PlaherHitFade.png").GetFullPath());
	}

	FadeRender = CreateComponent<ContentUIRender>();
	FadeRender->PipeSetting("2DTexture_Color");
	FadeRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	FadeRender->SetTexture("PlaherHitFade.png");
	FadeRender->GetTransform()->SetWorldPosition(float4(0, 0, 50));
	FadeRender->GetTransform()->SetWorldScale(GameEngineWindow::GetScreenSize());
	FadeRender->Off();

	StartColor = float4(1, -1, -1, 0.7f);
	EndColor = float4(1, -1, -1, 0);
}

void PlayerHitFade::Update(float _DeltaTime)
{
	if (false == IsFadeActive)
	{
		FadeRender->Off();
	}
	else
	{
		FadeRender->On();
		Progress += _DeltaTime * Speed;

		Buffer.Color = float4::LerpClamp(StartColor, EndColor, Progress);

		if (1.0f <= Progress)
		{
			IsFadeActive = false;
		}
	}
}
