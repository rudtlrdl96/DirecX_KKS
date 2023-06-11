#include "PrecompileHeader.h"
#include "StoryFrontImage.h"
#include "ContentUIRender.h"

StoryFrontImage::StoryFrontImage()
{
}

StoryFrontImage::~StoryFrontImage()
{
}

void StoryFrontImage::Start()
{
	TextureRenderer = CreateComponent<ContentUIRender>();
	TextureRenderer->PipeSetting("2DTexture_Color");
	TextureRenderer->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	TextureRenderer->GetTransform()->SetWorldPosition({0, 0, -900, 1});
	TextureRenderer->GetTransform()->SetWorldScale(GameEngineWindow::GetScreenSize());
	TextureRenderer->SetTexture("StoryDesk_Alpha.png");
}