#pragma once
#include <GameEngineCore/GameEngineCoreWindow.h>
#include "Background.h"

class BackgroundToolGUI : public GameEngineCoreWindow
{
private:
	class BackgroundToolData
	{
	public:
		BG_DESC Data;
		std::shared_ptr<class GameEngineTexture> TexturePtr = nullptr;

		BackgroundToolData(const BG_DESC& _Data, const std::shared_ptr<class GameEngineTexture> _TexturePtr) :
			Data(_Data),
			TexturePtr(_TexturePtr)
		{
		}
	};
public:
	BackgroundToolGUI();
	~BackgroundToolGUI();

	BackgroundToolGUI(const BackgroundToolGUI& _Other) = delete;
	BackgroundToolGUI(BackgroundToolGUI&& _Other) noexcept = delete;
	BackgroundToolGUI& operator=(const BackgroundToolGUI& _Other) = delete;
	BackgroundToolGUI& operator=(BackgroundToolGUI&& _Other) noexcept = delete;

	inline void Pushback_OnGuiCallbackFunc(std::function<void()> _FunctionPtr)
	{
		OnGuiCallback.push_back(_FunctionPtr);
	}

	bool CheckCreateTrigger();

	inline int GetSelectBackgroundIndex() const
	{
		return SelectBackgroundIndex;
	}

protected:
	void Start() override;
	void OnGUI(std::shared_ptr<class GameEngineLevel>, float _DeltaTime) override;

private:
	std::map<LevelArea, std::vector<BackgroundToolData>> BackgroundDatas;

	LevelArea CurShowAreaTile = LevelArea::None;
	const char* AreaComboText[6] = { "None" ,"Opening", "Castle", "ForestOfHarmony", "GrandHall", "HolyCourtyard" };

	bool IsSaveTrigger = false;
	bool IsLoadTrigger = false;
	bool IsCreateTrigger = false;

	std::vector<std::function<void()>> OnGuiCallback;

	int SelectBackgroundIndex = 0;

	void BackgroundDatasLoad(LevelArea _Area);

};

