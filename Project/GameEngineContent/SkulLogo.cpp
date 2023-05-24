#include "PrecompileHeader.h"
#include "SkulLogo.h"
#include "ContentUIRender.h"

SkulLogo::SkulLogo()
{
}

SkulLogo::~SkulLogo()
{
}

void SkulLogo::Start()
{
	TextureRenderer = CreateComponent<ContentUIRender>();
	TextureRenderer->PipeSetting("2DTexture_ColorLight");
	TextureRenderer->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);

	TextureRenderer->GetTransform()->SetWorldPosition({ 0, 0, 10000, 1 });
	TextureRenderer->GetTransform()->SetWorldScale({1275 * 0.375f, 693 * 0.375f});
	TextureRenderer->SetTexture("Ending_Title_Logo_White.png");
}