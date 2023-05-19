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
	const char* LevelComboText[15] = { 
		"Opening" ,"Castle", "ForestOfHarmony", "GrandHall", "HolyCourtyard", "Shop", "Title", "Story", "EndingLogo", 
		"MapTool", "BackgroundTool", "AnimationColTool",
		"Debug_Shader", "Debug_Inventory", "Debug_Physics"};

	int CurrentLevelIndex = 6;

	void Start() override {}
	void OnGUI(std::shared_ptr<class GameEngineLevel>, float _DeltaTime) override;
};

