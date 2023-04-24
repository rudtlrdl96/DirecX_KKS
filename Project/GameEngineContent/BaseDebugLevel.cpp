#include "PrecompileHeader.h"
#include "BaseDebugLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>

BaseDebugLevel::BaseDebugLevel()
{
}

BaseDebugLevel::~BaseDebugLevel()
{
}

void BaseDebugLevel::Start()
{
	MainCam = GetMainCamera();
	MainCam->SetProjectionType(CameraType::Orthogonal);
	MainCam->GetTransform()->SetWorldPosition(float4(0, 0, -1000, 1));
}

void BaseDebugLevel::Update(float _DeltaTime)
{
	GameEngineLevel::Update(_DeltaTime);
			
	if (true == GameEngineInput::IsDown("LevelMove_ShaderDebug"))
	{
		GameEngineCore::ChangeLevel("ShaderDebug");
	}
	else if (true == GameEngineInput::IsDown("LevelMove_BattleDebug"))
	{
		GameEngineCore::ChangeLevel("BattleDebug");
	}
}
