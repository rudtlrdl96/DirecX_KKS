#include "PrecompileHeader.h"
#include "ContentSlice9UIRenderer.h"

ContentSlice9UIRenderer::ContentSlice9UIRenderer()
{
}

ContentSlice9UIRenderer::~ContentSlice9UIRenderer()
{
}

void ContentSlice9UIRenderer::Start()
{
	SetMesh("Rect");
	PushCameraRender(100);
	Init();
}
