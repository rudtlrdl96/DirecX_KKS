#include "PrecompileHeader.h"
#include "ContentUIRender.h"

ContentUIRender::ContentUIRender()
{
}

ContentUIRender::~ContentUIRender()
{
}

void ContentUIRender::Start()
{
	SetMesh("Rect");
	PushCameraRender(static_cast<int>(CameraOrder::UI));
}
