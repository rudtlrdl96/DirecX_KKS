#pragma once
#include <GameEngineCore/GameEngineCoreWindow.h>


class FPSCheckGUI : public GameEngineCoreWindow
{
public:
	FPSCheckGUI();
	~FPSCheckGUI();

	FPSCheckGUI(const FPSCheckGUI& _Other) = delete;
	FPSCheckGUI(FPSCheckGUI&& _Other) noexcept = delete;
	FPSCheckGUI& operator=(const FPSCheckGUI& _Other) = delete;
	FPSCheckGUI& operator=(FPSCheckGUI&& _Other) noexcept = delete;

	void Reset();

protected:
	
private:

	void Start() override;
	void OnGUI(std::shared_ptr<class GameEngineLevel>, float _DeltaTime) override;

	size_t TotalFrameCount = 0;
	size_t FPS = 0;

	float Time = 0.0f;
};

