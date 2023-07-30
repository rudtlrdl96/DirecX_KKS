#pragma once
#include <GameEngineCore/GameEngineCoreWindow.h>
#include "BattleLevel.h"

class GameConsoleGUI : public GameEngineCoreWindow
{
public:
	GameConsoleGUI();
	~GameConsoleGUI();

	GameConsoleGUI(const GameConsoleGUI& _Other) = delete;
	GameConsoleGUI(GameConsoleGUI&& _Other) noexcept = delete;
	GameConsoleGUI& operator=(const GameConsoleGUI& _Other) = delete;
	GameConsoleGUI& operator=(GameConsoleGUI&& _Other) noexcept = delete;

	const void SetLevel(BattleLevel* _LevelPtr)
	{
		Level = _LevelPtr;
	}

protected:
	
private:
	const char* LevelComboText[10] = { 
		"Opening" ,"Castle", "ForestOfHarmony", "Title", "Story", "EndingLogo", 
		"MapTool", "BackgroundTool", "AnimationColTool", "BrokenObjectTool",};

	int CurrentLevelIndex = 3;

	bool LightGuiOn = false;
	bool FPSGuiOn = false;

	void Start() override;
	void OnGUI(std::shared_ptr<class GameEngineLevel>, float _DeltaTime) override;

	BattleLevel* Level = nullptr;

	int CheatSkullIndex = 0;
	int CheatItemIndex = 0;

};

