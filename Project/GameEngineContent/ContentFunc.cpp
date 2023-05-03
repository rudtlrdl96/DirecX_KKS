#include "PrecompileHeader.h"
#include "ContentFunc.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCamera.h>

float4 ContentFunc::GetMousePos(std::shared_ptr<GameEngineCamera> _MainCam)
{
	float4 Result = GameEngineWindow::GetMousePosition();
	float4 CameraPos = _MainCam->GetTransform()->GetWorldPosition();

	Result *= _MainCam->GetViewPort().InverseReturn();
	Result *= _MainCam->GetProjection().InverseReturn();
	Result *= _MainCam->GetView().InverseReturn();

	return Result;
}

ContentFunc::ContentFunc()
{
}

ContentFunc::~ContentFunc()
{
}
