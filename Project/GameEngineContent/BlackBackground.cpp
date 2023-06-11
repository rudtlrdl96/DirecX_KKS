#include "PrecompileHeader.h"
#include "BlackBackground.h"
#include "ContentUIRender.h"

BlackBackground::BlackBackground()
{
}

BlackBackground::~BlackBackground()
{
}

void BlackBackground::SetRenderSize(const float4& _Size)
{
	if (nullptr == TextureRenderer)
	{
		MsgAssert_Rtti<BlackBackground>(" - 랜더를 생성하지 않고 사용했습니다.");
	}

	TextureRenderer->GetTransform()->SetLocalScale(_Size);
}

void BlackBackground::Start()
{
	TextureRenderer = CreateComponent<ContentUIRender>();
	TextureRenderer->PipeSetting("2DTexture_Color");
	TextureRenderer->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	TextureRenderer->GetTransform()->SetWorldPosition({ 0, 0, 10000, 1 });
	TextureRenderer->GetTransform()->SetLocalScale(GameEngineWindow::GetScreenSize());
	TextureRenderer->SetTexture("FadeImage.png");
}
