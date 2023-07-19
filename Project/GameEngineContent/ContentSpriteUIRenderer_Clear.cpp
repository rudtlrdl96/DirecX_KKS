#include "PrecompileHeader.h"
#include "ContentSpriteUIRenderer_Clear.h"

ContentSpriteUIRenderer_Clear::ContentSpriteUIRenderer_Clear()
{
}

ContentSpriteUIRenderer_Clear::~ContentSpriteUIRenderer_Clear()
{
}

void ContentSpriteUIRenderer_Clear::Render(float _DeltaTime)
{
	ContentSpriteUIRenderer::Render(_DeltaTime);

	for (size_t i = 0; i < Units.size(); i++)
	{
		Units[i]->ShaderResHelper.AllResourcesReset();
	}
}
