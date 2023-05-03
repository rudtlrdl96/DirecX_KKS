#pragma once
#include <GameEngineCore/GameEngineCoreWindow.h>

class TransformGUI : public GameEngineCoreWindow
{
public:
	TransformGUI();
	~TransformGUI();

	TransformGUI(const TransformGUI& _Other) = delete;
	TransformGUI(TransformGUI&& _Other) noexcept = delete;
	TransformGUI& operator=(const TransformGUI& _Other) = delete;
	TransformGUI& operator=(TransformGUI&& _Other) noexcept = delete;
	
	void OnGUI(std::shared_ptr<class GameEngineLevel>, float _DeltaTime) override;

	void SetTarget(GameEngineTransform* _Target);

protected:
	
private:
	GameEngineTransform* TargetTransform = nullptr;

	bool IsWorldPostion = false;
	bool IsWorldRotation = false;
	bool IsWorldScale = false;

	float Postion[4] = { 0, 0, 0, 1 };
	float Rotation[4] = { 0, 0, 0, 1 };
	float Scale[4] = { 1, 1, 1, 1 };

	void HelpMarker(const std::string_view& _Text);

	static float4 ConvertFloat4(float _FloatArr[4]);
};

