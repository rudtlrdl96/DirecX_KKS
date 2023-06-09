#include "PrecompileHeader.h"
#include "ContentFadeRender.h"

ContentFadeRender::ContentFadeRender()
{
}

ContentFadeRender::~ContentFadeRender()
{
}

void ContentFadeRender::Start()
{
	SetMesh("Rect");
	PushCameraRender(static_cast<int>(CameraOrder::Fade));
}
