#include "PrecompileHeader.h"
#include "StoryBackImage.h"
#include "ContentUIRender.h"

StoryBackImage::StoryBackImage()
{
}

StoryBackImage::~StoryBackImage()
{
}

void StoryBackImage::Start()
{
	TextureRenderer = CreateComponent<ContentUIRender>();
	TextureRenderer->PipeSetting("2DTexture_Color");
	TextureRenderer->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	TextureRenderer->GetTransform()->SetWorldPosition({ 0, 0, 10000, 1 });
	TextureRenderer->GetTransform()->SetWorldScale(GameEngineWindow::GetScreenSize());
	TextureRenderer->SetTexture("StoryDesk.png");
}
