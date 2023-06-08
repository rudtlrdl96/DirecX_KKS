#pragma once
#include <GameEngineCore/GameEngineCoreWindow.h>
#include "BrokenObject.h"

class BrokenObjectToolGUI : public GameEngineCoreWindow
{
public:
	BrokenObjectToolGUI();
	~BrokenObjectToolGUI();

	BrokenObjectToolGUI(const BrokenObjectToolGUI& _Other) = delete;
	BrokenObjectToolGUI(BrokenObjectToolGUI&& _Other) noexcept = delete;
	BrokenObjectToolGUI& operator=(const BrokenObjectToolGUI& _Other) = delete;
	BrokenObjectToolGUI& operator=(BrokenObjectToolGUI&& _Other) noexcept = delete;

protected:
	void Start() override;
	void OnGUI(std::shared_ptr<class GameEngineLevel> _Level, float _DeltaTime) override;
	
private:


};

