#pragma once
#include <GameEngineCore/GameEngineCoreWindow.h>

class LevelMoveGUI : public GameEngineCoreWindow
{
public:
	LevelMoveGUI();
	~LevelMoveGUI();

	LevelMoveGUI(const LevelMoveGUI& _Other) = delete;
	LevelMoveGUI(LevelMoveGUI&& _Other) noexcept = delete;
	LevelMoveGUI& operator=(const LevelMoveGUI& _Other) = delete;
	LevelMoveGUI& operator=(LevelMoveGUI&& _Other) noexcept = delete;

protected:
	
private:
	const char* LevelComboText[14] = { "Opening" ,"Castle", "ForestOfHarmony", "GrandHall", "HolyCourtyard", "Shop", "Title", "Story", "EndingLogo", "MapTool", "BackgroundTool", "Debug_Battle", "Debug_Shader", "Debug_Inventory"};

	int CurrentLevelIndex = 6;

	void Start() override {}
	void OnGUI(std::shared_ptr<class GameEngineLevel>, float _DeltaTime) override;
};

