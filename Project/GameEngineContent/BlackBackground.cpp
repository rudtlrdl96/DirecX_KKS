#include "PrecompileHeader.h"
#include "BlackBackground.h"

BlackBackground::BlackBackground()
{
}

BlackBackground::~BlackBackground()
{
}

void BlackBackground::Start()
{
	TextureRenderer = CreateComponent<GameEngineSpriteRenderer>();
	TextureRenderer->GetTransform()->SetWorldPosition({ 0, 0, 10000, 1 });
	TextureRenderer->GetTransform()->SetWorldScale(GameEngineWindow::GetScreenSize());
	TextureRenderer->SetTexture("FadeImage.png");
}
