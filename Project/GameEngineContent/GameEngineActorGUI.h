#pragma once
#include <GameEngineCore/GameEngineCoreWindow.h>

class GameEngineActorGUI : public GameEngineCoreWindow
{
public:
	GameEngineActorGUI();
	~GameEngineActorGUI();

	GameEngineActorGUI(const GameEngineActorGUI& _Other) = delete;
	GameEngineActorGUI(GameEngineActorGUI&& _Other) noexcept = delete;
	GameEngineActorGUI& operator=(const GameEngineActorGUI& _Other) = delete;
	GameEngineActorGUI& operator=(GameEngineActorGUI&& _Other) noexcept = delete;
	
	void SetTarget(GameEngineTransform* _Target, const std::vector<std::function<void()>>& _CustomActorGuiFunctions = {});

	inline void EditorGui(std::function<void()> _GuiFunction)
	{
		if (nullptr == _GuiFunction)
		{
			MsgAssert_Rtti<GameEngineActorGUI>(" - nullptr 콜백이 들어왔습니다");
			return;
		}

		CustomActorGuiFunctions.push_back(_GuiFunction);
	}

protected:
	
private:
	GameEngineTransform* TargetTransform = nullptr;

	bool IsWorldPosition = false;
	bool IsWorldRotation = false;
	bool IsWorldScale = false;

	float Position[4] = { 0, 0, 0, 1 };
	float Rotation[4] = { 0, 0, 0, 1 };
	float Scale[4] = { 1, 1, 1, 1 };
	
	std::vector<std::function<void()>> CustomActorGuiFunctions;

	void Start() override;
	void OnGUI(std::shared_ptr<class GameEngineLevel>, float _DeltaTime) override;
};

