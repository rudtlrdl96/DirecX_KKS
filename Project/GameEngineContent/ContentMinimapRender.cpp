#include "PrecompileHeader.h"
#include "ContentMinimapRender.h"

ContentMinimapRender::ContentMinimapRender()
{
}

ContentMinimapRender::~ContentMinimapRender()
{
}

void ContentMinimapRender::Start()
{
	PushCameraRender((int)CameraOrder::MiniMap);
	SpriteRenderInit();
}
