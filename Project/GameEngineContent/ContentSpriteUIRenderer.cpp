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
	PushCameraRender(static_cast<int>(CameraOrder::UI));
}
