#include "PrecompileHeader.h"
#include "ContentSpriteUIRenderer.h"

ContentSpriteUIRenderer::ContentSpriteUIRenderer()
{
}

ContentSpriteUIRenderer::~ContentSpriteUIRenderer()
{
}

void ContentSpriteUIRenderer::Start()
{
	SetMesh("Rect");
	PushCameraRender(100);
}
