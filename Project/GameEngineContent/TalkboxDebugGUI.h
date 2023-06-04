#pragma once
#include <GameEngineCore/GameEngineCoreWindow.h>

class TalkboxDebugGUI : public GameEngineCoreWindow
{
public:
	TalkboxDebugGUI();
	~TalkboxDebugGUI();

	TalkboxDebugGUI(const TalkboxDebugGUI& _Other) = delete;
	TalkboxDebugGUI(TalkboxDebugGUI&& _Other) noexcept = delete;
	TalkboxDebugGUI& operator=(const TalkboxDebugGUI& _Other) = delete;
	TalkboxDebugGUI& operator=(TalkboxDebugGUI&& _Other) noexcept = delete;

	void SetNameText(const std::string_view& _NameText);
	void SetMainText(const std::string_view& _MainText);

protected:
	
private:
	void Start() override {}
	void OnGUI(std::shared_ptr<class GameEngineLevel>, float _DeltaTime) override;

	std::string NameText = "";
	std::string MainText = "";
};

