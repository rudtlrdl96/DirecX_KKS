#include "PrecompileHeader.h"
#include "SkulLogo.h"

SkulLogo::SkulLogo()
{
}

SkulLogo::~SkulLogo()
{
}

void SkulLogo::Start()
{
	TextureRenderer = CreateComponent<GameEngineSpriteRenderer>();
	TextureRenderer->GetTransform()->SetWorldPosition({ 0, 0, 10000, 1 });
	TextureRenderer->GetTransform()->SetWorldScale({1275 * 0.375f, 693 * 0.375f});
	TextureRenderer->SetTexture("Ending_Title_Logo_White.png");
}