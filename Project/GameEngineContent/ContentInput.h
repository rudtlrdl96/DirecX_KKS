#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineCamera.h>

class ContentInput
{
public:
	static float4 GetMousePos(GameEngineCamera* _MainCam);

protected:
	
private:
	ContentInput();
	~ContentInput();

	ContentInput(const ContentInput& _Other) = delete;
	ContentInput(ContentInput&& _Other) noexcept = delete;
	ContentInput& operator=(const ContentInput& _Other) = delete;
	ContentInput& operator=(ContentInput&& _Other) noexcept = delete;


};

