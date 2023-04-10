#include "ContentInput.h"

float4 ContentInput::GetMousePos(GameEngineCamera* _MainCam)
{
    float4 ResultPos = GameEngineWindow::GetMousePosition();
    ResultPos -= GameEngineWindow::GetScreenSize().half();
    ResultPos.y = -ResultPos.y;


    //ResultPos *= _MainCam->GetViewPort().InverseReturn();
    //ResultPos *= _MainCam->GetProjection().InverseReturn();
    //ResultPos *= _MainCam->GetView().InverseReturn();

    return ResultPos;
}

ContentInput::ContentInput()
{
}

ContentInput::~ContentInput()
{
}
