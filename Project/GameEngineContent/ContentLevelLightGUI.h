#pragma once
#include <GameEngineCore/GameEngineCoreWindow.h>
#include "ContentLevel.h"

class ContentLevelLightGUI : public GameEngineCoreWindow
{
public:
	ContentLevelLightGUI();
	~ContentLevelLightGUI();

	ContentLevelLightGUI(const ContentLevelLightGUI& _Other) = delete;
	ContentLevelLightGUI(ContentLevelLightGUI&& _Other) noexcept = delete;
	ContentLevelLightGUI& operator=(const ContentLevelLightGUI& _Other) = delete;
	ContentLevelLightGUI& operator=(ContentLevelLightGUI&& _Other) noexcept = delete;

	inline void SetLevel(std::weak_ptr<ContentLevel> _Level)
	{
		LevelPtr = _Level;
	}

protected:
	
private:
	std::weak_ptr<ContentLevel> LevelPtr;

	void Start() override;
	void OnGUI(std::shared_ptr<class GameEngineLevel>, float _DeltaTime) override;

};

