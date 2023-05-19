#include "PrecompileHeader.h"
#include "LevelMoveGUI.h"
#include <GameEngineCore/GameEngineCore.h>

LevelMoveGUI::LevelMoveGUI()
{
}

LevelMoveGUI::~LevelMoveGUI()
{
}

void LevelMoveGUI::OnGUI(std::shared_ptr<class GameEngineLevel>, float _DeltaTime)
{
	int InputLevelIndex = CurrentLevelIndex;
	ImGui::Combo("Level", &InputLevelIndex, LevelComboText, IM_ARRAYSIZE(LevelComboText));

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
		case 3: // GrandHall
			GameEngineCore::ChangeLevel("GrandHall");
			break;
		case 4: // HolyCourtyard
			GameEngineCore::ChangeLevel("HolyCourtyard");
			break;
		case 5: // Shop
			GameEngineCore::ChangeLevel("Shop");
			break;
		case 6: // Title
			GameEngineCore::ChangeLevel("Title");
			break;
		case 7: // Story
			GameEngineCore::ChangeLevel("Story");
			break;
		case 8: // EndingLogo
			GameEngineCore::ChangeLevel("EndingLogo");
			break;
		case 9: // MapTool
			GameEngineCore::ChangeLevel("MapTool");
			break;
		case 10: // BackgroundTool
			GameEngineCore::ChangeLevel("BackgroundTool");
			break;
		case 11: // AnimationColTool
			GameEngineCore::ChangeLevel("AnimationColTool");
			break;
		case 12: // Shader
			GameEngineCore::ChangeLevel("ShaderDebug");
			break;
		case 13: // Inventory
			GameEngineCore::ChangeLevel("InventoryDebug");
			break;
		case 14://Debug_Physics
			GameEngineCore::ChangeLevel("PhysicsDebug");
			break;
		default:
			break;
		}
	}
}
