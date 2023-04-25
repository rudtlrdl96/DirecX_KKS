#include "PrecompileHeader.h"
#include "ContentLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCamera.h>
#include <GameEngineCore/GameEngineCore.h>

ContentLevel::ContentLevel()
{
}

ContentLevel::~ContentLevel()
{
}

void ContentLevel::Start()
{
	GameEngineLevel::Start();

	std::shared_ptr<GameEngineCamera> Cam = GetMainCamera();
	MainCamCtrl.Start(Cam);
	MainCamCtrl.SetCamPos(float4(0, 0, -1000, 1));
	MainCamCtrl.SetCamRot(float4::Zero);
}

void ContentLevel::Update(float _DeltaTime)
{
	GameEngineLevel::Update(_DeltaTime);
	MainCamCtrl.Update(_DeltaTime);

	if (true == GameEngineInput::IsDown("LevelMove_ShaderDebug"))
	{
		GameEngineCore::ChangeLevel("ShaderDebug");
	}
	else if (true == GameEngineInput::IsDown("LevelMove_BattleDebug"))
	{
		GameEngineCore::ChangeLevel("BattleDebug");
	}
}