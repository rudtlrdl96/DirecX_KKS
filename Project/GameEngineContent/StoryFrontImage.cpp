#include "PrecompileHeader.h"
#include "StoryFrontImage.h"

StoryFrontImage::StoryFrontImage()
{
}

StoryFrontImage::~StoryFrontImage()
{
}

void StoryFrontImage::Start()
{
	TextureRenderer = CreateComponent<GameEngineSpriteRenderer>();
	TextureRenderer->GetTransform()->SetWorldPosition({0, 0, -900, 1});
	TextureRenderer->GetTransform()->SetWorldScale(GameEngineWindow::GetScreenSize());
	TextureRenderer->SetTexture("StoryDesk_Alpha.png");
}