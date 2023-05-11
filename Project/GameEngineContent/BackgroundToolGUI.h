#pragma once
#include <GameEngineCore/GameEngineCoreWindow.h>
#include "Background.h"

class BackgroundToolGUI : public GameEngineCoreWindow
{
private:
	class BackgroundToolData
	{
	public:
		BackgroundMetaData Data;
		std::shared_ptr<class GameEngineTexture> TexturePtr = nullptr;

		BackgroundToolData(const BackgroundMetaData& _Data, const std::shared_ptr<class GameEngineTexture> _TexturePtr) :
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
	bool CheckSaveTrigger();
	bool CheckLoadTrigger();

	inline int GetSelectBackgroundIndex() const
	{
		return SelectBackgroundIndex;
	}

protected:

private:
	std::map<LevelArea, std::vector<BackgroundToolData>> BackgroundDatas;

	LevelArea CurShowAreaTile = LevelArea::None;
	const char* AreaComboText[7] = { "None" ,"Opening", "Castle", "ForestOfHarmony", "GrandHall", "HolyCourtyard", "Shop"};

	bool IsSaveTrigger = false;
	bool IsLoadTrigger = false;
	bool IsCreateTrigger = false;

	std::vector<std::function<void()>> OnGuiCallback;

	int SelectBackgroundIndex = 0;

	void Start() override;
	void OnGUI(std::shared_ptr<class GameEngineLevel>, float _DeltaTime) override;

	void BackgroundDatasLoad(LevelArea _Area);

};

