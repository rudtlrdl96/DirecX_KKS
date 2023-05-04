#include "PrecompileHeader.h"
#include "ContentFunc.h"

#include <fstream>
#include <ostream>
#include <sstream>

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/imgui.h>
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

ContentFunc::ContentFunc()
{
}

ContentFunc::~ContentFunc()
{
}
