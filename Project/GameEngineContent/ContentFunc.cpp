#include "PrecompileHeader.h"
#include "ContentFunc.h"

#include <fstream>
#include <ostream>
#include <sstream>

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/imgui.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCollision.h>

float4 ContentFunc::GetMousePos(std::shared_ptr<GameEngineCamera> _MainCam)
{
	float4 Result = GameEngineWindow::GetMousePosition();
	float4 CameraPos = _MainCam->GetTransform()->GetWorldPosition();

	Result *= _MainCam->GetViewPort().InverseReturn();
	Result *= _MainCam->GetProjection().InverseReturn();
	Result *= _MainCam->GetView().InverseReturn();

	return Result;
}


std::shared_ptr<class GameEngineCollision> ContentFunc::PlatformColCheck(const std::shared_ptr<class GameEngineCollision>& _Col, bool _IsHalf /*= false*/)
{
    std::shared_ptr<GameEngineCollision> ReslutCol = nullptr;

    ReslutCol = _Col->Collision(CollisionOrder::Platform_Normal, ColType::AABBBOX2D, ColType::AABBBOX2D);

    if (nullptr != ReslutCol)
    {
        return ReslutCol;
    }

    if (false == _IsHalf)
    {
        return ReslutCol;
    }

    ReslutCol = _Col->Collision(CollisionOrder::Platform_Half, ColType::AABBBOX2D, ColType::AABBBOX2D);

    if (nullptr != ReslutCol)
    {
        return ReslutCol;
    }

    return ReslutCol;
}

void ContentFunc::ImGuiHelpMarker(const std::string_view& _Text)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort) && ImGui::BeginTooltip())
	{
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(_Text.data());
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

std::string ContentFunc::GetOpenFilePath()
{
    OPENFILENAME ofn;       // common dialog box structure
    wchar_t szFile[260];       // buffer for file name
    wchar_t PrevPath[260];
    GetCurrentDirectory(260, PrevPath);

    // Initialize OPENFILENAME
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = GameEngineWindow::GetHWnd();
    ofn.lpstrFile = szFile;
    // Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
    // use the contents of szFile to initialize itself.
    ofn.lpstrFile[0] = L'\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    // Display the Open dialog box. 

    if (GetOpenFileName(&ofn) == TRUE)
    {
        SetCurrentDirectory(PrevPath);
        return GameEngineString::UniCodeToAnsi(ofn.lpstrFile);
    }

    SetCurrentDirectory(PrevPath);
    return "";
}

std::string ContentFunc::GetSaveFilePath()
{
    OPENFILENAME ofn;       // common dialog box structure
    wchar_t szFile[260];       // buffer for file name
    wchar_t PrevPath[260];
    GetCurrentDirectory(260, PrevPath);

    // Initialize OPENFILENAME
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = GameEngineWindow::GetHWnd();
    ofn.lpstrFile = szFile;
    // Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
    // use the contents of szFile to initialize itself.
    ofn.lpstrFile[0] = L'\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    // Display the Open dialog box. 

    if (GetSaveFileName(&ofn) == TRUE)
    {
        SetCurrentDirectory(PrevPath);
        return GameEngineString::UniCodeToAnsi(ofn.lpstrFile);
    }

    SetCurrentDirectory(PrevPath);
    return "";
}

float4 ContentFunc::ConvertFloat4(float _FloatArr[4])
{
    return float4(_FloatArr[0], _FloatArr[1], _FloatArr[2], _FloatArr[3]);
}

AnimationAttackMetaData ContentFunc::LoadAnimAttackMetaData(const std::string_view& _Path)
{
    AnimationAttackMetaData LoadData;
    GameEngineFile LoadFile = GameEngineFile(_Path);

    GameEngineSerializer LoadSerializer;
    LoadSerializer.BufferResize(2048);
    LoadFile.LoadBin(LoadSerializer);
    LoadData.LoadBin(LoadSerializer);

    return LoadData;
}

ContentFunc::ContentFunc()
{
}

ContentFunc::~ContentFunc()
{
}
