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
	const char* LevelComboText[13] = { 
		"Opening" ,"Castle", "ForestOfHarmony", "GrandHall", "HolyCourtyard", "Shop", "Title", "Story", "EndingLogo", 
		"MapTool", "BackgroundTool", "AnimationColTool", "BrokenObjectTool",};

	int CurrentLevelIndex = 6;

	bool LightGuiOn = false;

	void Start() override;
	void OnGUI(std::shared_ptr<class GameEngineLevel>, float _DeltaTime) override;
};

