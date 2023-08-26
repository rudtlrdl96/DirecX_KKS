#include "PrecompileHeader.h"
#include "GameConsoleGUI.h"
#include <GameEngineCore/GameEngineCore.h>

#include "ContentLevelLightGUI.h"
#include "FPSCheckGUI.h"

GameConsoleGUI::GameConsoleGUI()
{
}

GameConsoleGUI::~GameConsoleGUI()
{
}

void GameConsoleGUI::Start()
{
}

void GameConsoleGUI::OnGUI(std::shared_ptr<class GameEngineLevel>, float _DeltaTime)
{
	int InputLevelIndex = CurrentLevelIndex;
	ImGui::Combo("Level", &InputLevelIndex, LevelComboText, IM_ARRAYSIZE(LevelComboText));

	ImGui::Checkbox("Light GUI", &LightGuiOn);

	if (true == LightGuiOn)
	{
		std::shared_ptr<ContentLevelLightGUI> FindGUI = GameEngineGUI::FindGUIWindowConvert<ContentLevelLightGUI>("ContentLevelLightGUI");
		FindGUI->On();
	}
	else
	{
		std::shared_ptr<ContentLevelLightGUI> FindGUI = GameEngineGUI::FindGUIWindowConvert<ContentLevelLightGUI>("ContentLevelLightGUI");
		FindGUI->Off();
	}	
	
	ImGui::Checkbox("FPS GUI", &FPSGuiOn);

	if (true == FPSGuiOn)
	{
		std::shared_ptr<FPSCheckGUI> FindGUI = GameEngineGUI::FindGUIWindowConvert<FPSCheckGUI>("FPSCheckGUI");
		FindGUI->On();
	}
	else
	{
		std::shared_ptr<FPSCheckGUI> FindGUI = GameEngineGUI::FindGUIWindowConvert<FPSCheckGUI>("FPSCheckGUI");
		FindGUI->Off();
	}

	if (InputLevelIndex != CurrentLevelIndex)
	{
		CurrentLevelIndex = InputLevelIndex;

		switch (CurrentLevelIndex)
		{
		case 0: // Opening
			GameEngineCore::ChangeLevel("Opening");
			break;
		case 1: // Castle
			GameEngineCore::ChangeLevel("Castle");
			break;
		case 2: // ForestOfHarmony
			GameEngineCore::ChangeLevel("ForestOfHarmony");
			break;
		case 3: // Title
			GameEngineCore::ChangeLevel("Title");
			break;
		case 4: // Story
			GameEngineCore::ChangeLevel("Story");
			break;
		case 5: // EndingLogo
			GameEngineCore::ChangeLevel("EndingLogo");
			break;
		case 6: // MapTool
			GameEngineCore::ChangeLevel("MapTool");
			break;
		case 7: // BackgroundTool
			GameEngineCore::ChangeLevel("BackgroundTool");
			break;
		case 8: // AnimationColTool
			GameEngineCore::ChangeLevel("AnimationColTool");
			break;
		case 9: // BrokenObjectTool
			GameEngineCore::ChangeLevel("BrokenObjectTool");
			break;
		default:
			break;
		}
	}

	if (ImGui::Button("Cheat Attack"))
	{
		if (nullptr == Level)
		{
			return;
		}

		Level->Cheat_Switch_Attack();
	}

	if (ImGui::Button("Cheat HP"))
	{
		if (nullptr == Level)
		{
			return;
		}

		Level->Cheat_Switch_HP();
	}

	if (ImGui::Button("Cheat Death"))
	{
		if (nullptr == Level)
		{
			return;
		}

		Level->Cheat_ForceDeath();
	}

	ImGui::InputInt("Cheat Skull", &CheatSkullIndex);

	if (ImGui::Button("Get Skull"))
	{
		if (nullptr == Level)
		{
			return;
		}

		Level->Cheat_GetSkull(static_cast<size_t>(CheatSkullIndex));
	}

	ImGui::InputInt("Cheat Item", &CheatItemIndex);

	if (ImGui::Button("Get Item"))
	{
		if (nullptr == Level)
		{
			return;
		}

		Level->Cheat_GetItem(static_cast<size_t>(CheatItemIndex));
	}
}
