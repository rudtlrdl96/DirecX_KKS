#include "PrecompileHeader.h"
#include "StoryBackImage.h"

StoryBackImage::StoryBackImage()
{
}

StoryBackImage::~StoryBackImage()
{
}

void StoryBackImage::Start()
{
	TextureRenderer = CreateComponent<GameEngineSpriteRenderer>();
	TextureRenderer->GetTransform()->SetWorldPosition({ 0, 0, 10000, 1 });
	TextureRenderer->GetTransform()->SetWorldScale(GameEngineWindow::GetScreenSize());
	TextureRenderer->SetTexture("StoryDesk.png");
}
