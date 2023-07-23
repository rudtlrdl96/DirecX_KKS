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
	const char* LevelComboText[10] = { 
		"Opening" ,"Castle", "ForestOfHarmony", "Title", "Story", "EndingLogo", 
		"MapTool", "BackgroundTool", "AnimationColTool", "BrokenObjectTool",};

	int CurrentLevelIndex = 3;

	bool LightGuiOn = false;

	void Start() override;
	void OnGUI(std::shared_ptr<class GameEngineLevel>, float _DeltaTime) override;
};

