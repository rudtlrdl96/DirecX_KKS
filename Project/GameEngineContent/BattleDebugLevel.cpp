#include "PrecompileHeader.h"
#include "BattleDebugLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include "DebugSpriteActor.h"
#include "Tilemap.h"
#include "MultiBackground.h"

BattleDebugLevel::BattleDebugLevel()
{

}

BattleDebugLevel::~BattleDebugLevel()
{
}

void BattleDebugLevel::Start()
{
	ContentLevel::Start();

	if (false == GameEngineInput::IsKey("CameraMoveX++"))
	{
		GameEngineInput::CreateKey("CameraMoveX++", 'L');
		GameEngineInput::CreateKey("CameraMoveY++", 'I');
		GameEngineInput::CreateKey("CameraMoveX--", 'J');
		GameEngineInput::CreateKey("CameraMoveY--", 'K');
		GameEngineInput::CreateKey("CameraShake", VK_SPACE);		
	}

	DebugTilemap = CreateActor<Tilemap>();
	DebugTilemap->ResizeTilemap(40, 12, 0);

	DebugTilemap->ChangeData(0, 0, 39, 0, 0, 2);
	DebugTilemap->ChangeData(0, 0, 1, {{1000, 1001, 1002}});
	DebugTilemap->ChangeData(0, 0, 2, {{1000, 1001, 1002}});
	DebugTilemap->ChangeData(0, 0, 3, {{1000, 1001, 1002}});

	//MainCamCtrl.MoveLerp_ExceptionZ(MainCamCtrl.GetCameraPos(), float4(2000, 300), 5.0f);

	DeubgActor = CreateActor<DebugSpriteActor>();
	DeubgActor->Off();
	

	MainCamCtrl.SetLookatTarget(DeubgActor);
	Tilemap_DESC DESC = DebugTilemap->GetTilemap_DESC(0);

	MainCamCtrl.SetMinHeight(DESC.Bottom);
	MainCamCtrl.SetMaxHeight(DESC.Top);

	MainCamCtrl.SetMinWidth(DESC.Left);
	MainCamCtrl.SetMaxWidth(DESC.Right);

	DebugBackground = CreateActor<MultiBackground>();

	//Background::BG_DESC Desc;
	//
	//Desc.TextureName = "";
	//Desc.Center = {};
	//Desc.Ratio = 0.01f;
	//Desc.Size = {};
	//
	//DebugBackground->CreateBackground(Desc, 0);
	

	//for (UINT i = 0; i < DebugTilemap->SizeX(0); i++)
	//{
	//	DebugTilemap->ChangeData(0, i, 0, 2);
	//}
}

void BattleDebugLevel::Update(float _DeltaTime)
{
	ContentLevel::Update(_DeltaTime);

	if (true == GameEngineInput::IsPress("CameraMoveX++"))
	{
		MainCamCtrl.AddCamPos({_DeltaTime * CameraSpeed, 0, 0, 0});
	}
	else if (true == GameEngineInput::IsPress("CameraMoveX--"))
	{
		MainCamCtrl.AddCamPos({-_DeltaTime * CameraSpeed, 0, 0, 0});
	}
	else if (true == GameEngineInput::IsPress("CameraMoveY++"))
	{
		MainCamCtrl.AddCamPos({0,_DeltaTime * CameraSpeed, 0, 0});
	}
	else if (true == GameEngineInput::IsPress("CameraMoveY--"))
	{
		MainCamCtrl.AddCamPos({0, -_DeltaTime * CameraSpeed, 0, 0});
	}
	else if (true == GameEngineInput::IsPress("CameraShake"))
	{
		MainCamCtrl.CameraShake( 4.0f, 30.0f, 40);
	}
}