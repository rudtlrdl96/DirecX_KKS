#include "PrecompileHeader.h"
#include "GameEngineGUI.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include "GameEngineDevice.h"
#include "GameEngineLevel.h"

std::map<std::string, std::shared_ptr<GameEngineGUIWindow>> GameEngineGUI::AllWindow;


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

GameEngineGUI::GameEngineGUI()
{
}

GameEngineGUI::~GameEngineGUI()
{
}

bool GameEngineGUI::IsInit = false;

void GameEngineGUI::Initialize()
{
    if (true == IsInit)
    {
        return;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();

    ImGui_ImplWin32_Init(GameEngineWindow::GetHWnd());
    ImGui_ImplDX11_Init(GameEngineDevice::GetDevice(), GameEngineDevice::GetContext());

    GameEngineWindow::SetUserMessageFunction(ImGui_ImplWin32_WndProcHandler);

    GameEngineDirectory NewDir;
    NewDir.MoveParentToDirectory("EngineResources");
    NewDir.Move("EngineResources");
    NewDir.Move("Font");
    io.Fonts->AddFontFromFileTTF(NewDir.GetPlusFileName("malgun.ttf").GetFullPath().c_str(), 18.0f, nullptr, io.Fonts->GetGlyphRangesKorean());

    IsInit = true;
}

void GameEngineGUI::Render(std::shared_ptr<class GameEngineLevel> Level, float _DeltaTime)
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();


    for (const std::pair<std::string, std::shared_ptr<GameEngineGUIWindow>>& WindowPair : AllWindow)
    {
        std::shared_ptr<GameEngineGUIWindow> WindowPtr = WindowPair.second;

        if (false == WindowPtr->IsUpdate())
        {
            continue;
        }

        WindowPtr->Begin();
        WindowPtr->OnGUI(Level, _DeltaTime);
        WindowPtr->End();
    }

    ImGui::Render();

    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    ImGuiIO& io = ImGui::GetIO();
}

void GameEngineGUI::Release()
{
    if (false == IsInit)
    {
        return;
    }

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    IsInit = false;
}

