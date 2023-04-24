#include "PrecompileHeader.h"
#include "BattleDebugLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include "Tilemap.h"

BattleDebugLevel::BattleDebugLevel()
{

}

BattleDebugLevel::~BattleDebugLevel()
{
}

void BattleDebugLevel::Start()
{
	BaseDebugLevel::Start();

	if (false == GameEngineInput::IsKey("CameraMoveX++"))
	{
		GameEngineInput::CreateKey("CameraMoveX++", 'L');
		GameEngineInput::CreateKey("CameraMoveY++", 'I');
		GameEngineInput::CreateKey("CameraMoveX--", 'J');
		GameEngineInput::CreateKey("CameraMoveY--", 'K');
	}

	DebugTilemap = CreateActor<Tilemap>();
	DebugTilemap->ResizeTilemap(40, 12, 0);

	for (UINT i = 0; i < DebugTilemap->SizeX(0); i++)
	{
		//DebugTilemap->ChangeData(i, 0, 1);
	}
}

void BattleDebugLevel::Update(float _DeltaTime)
{
	BaseDebugLevel::Update(_DeltaTime);

	if (true == GameEngineInput::IsPress("CameraMoveX++"))
	{
		MainCam->GetTransform()->AddLocalPosition({_DeltaTime * CameraSpeed, 0, 0, 0});
	}
	else if (true == GameEngineInput::IsPress("CameraMoveX--"))
	{
		MainCam->GetTransform()->AddLocalPosition({-_DeltaTime * CameraSpeed, 0, 0, 0});
	}
	else if (true == GameEngineInput::IsPress("CameraMoveY++"))
	{
		MainCam->GetTransform()->AddLocalPosition({0,_DeltaTime * CameraSpeed, 0, 0});
	}
	else if (true == GameEngineInput::IsPress("CameraMoveY--"))
	{
		MainCam->GetTransform()->AddLocalPosition({0, -_DeltaTime * CameraSpeed, 0, 0});
	}
}
