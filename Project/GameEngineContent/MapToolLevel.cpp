#include "PrecompileHeader.h"
#include "MapToolLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "Tilemap.h"
#include "ObjectManager.h"

MapToolLevel::MapToolLevel()
{
}

MapToolLevel::~MapToolLevel()
{
}

void MapToolLevel::Start()
{
	ContentLevel::Start();

	if (false == GameEngineInput::IsKey("ToolActive"))
	{
		GameEngineInput::CreateKey("ToolActive", VK_LBUTTON);
		GameEngineInput::CreateKey("ToolDisable", VK_RBUTTON);

		GameEngineInput::CreateKey("TempSizeUp", VK_OEM_PLUS);
		GameEngineInput::CreateKey("TempSizeDown", VK_OEM_MINUS);

		GameEngineInput::CreateKey("CameraMoveUp", VK_UP);
		GameEngineInput::CreateKey("CameraMoveDown", VK_DOWN);
		GameEngineInput::CreateKey("CameraMoveLeft", VK_LEFT);
		GameEngineInput::CreateKey("CameraMoveRight", VK_RIGHT);

		GameEngineInput::CreateKey("CameraMoveBoost", VK_LSHIFT);
	}

	TilemapPtr = CreateActor<Tilemap>();
	TilemapPtr->ResizeTilemap(20, 20, 0);

	ObjectMgr = CreateActor<ObjectManager>();
}

void MapToolLevel::Update(float _DeltaTime)
{
	ContentLevel::Update(_DeltaTime);

	if (true == GameEngineInput::IsDown("ToolActive"))
	{
		float4 TestMousePos = GetMousePos();

		TilemapPtr->ChangeData(0, TestMousePos, 1000);
		int a = 0;
	}

	float CurFrameCameraSpeed = CameraSpeed * _DeltaTime;

	if (GameEngineInput::IsPress("CameraMoveBoost"))
	{
		CurFrameCameraSpeed *= 2.0f;
	}

	if (GameEngineInput::IsDown("TempSizeUp"))
	{
		TilemapPtr->ResizeTilemap(TilemapPtr->SizeX(0) + 1, TilemapPtr->SizeY(0) + 1, 0);
	}
	
	if (GameEngineInput::IsDown("TempSizeDown"))
	{
		TilemapPtr->ResizeTilemap(TilemapPtr->SizeX(0) - 1, TilemapPtr->SizeY(0) - 1, 0);
	}

	if (GameEngineInput::IsPress("CameraMoveUp"))
	{
		GetMainCamera()->GetTransform()->AddLocalPosition(float4::Up * CurFrameCameraSpeed);
	}
	else if (GameEngineInput::IsPress("CameraMoveDown"))
	{
		GetMainCamera()->GetTransform()->AddLocalPosition(float4::Down * CurFrameCameraSpeed);
	}
	if (GameEngineInput::IsPress("CameraMoveLeft"))
	{
		GetMainCamera()->GetTransform()->AddLocalPosition(float4::Left * CurFrameCameraSpeed);
	}
	else if (GameEngineInput::IsPress("CameraMoveRight"))
	{
		GetMainCamera()->GetTransform()->AddLocalPosition(float4::Right * CurFrameCameraSpeed);
	}
}

void MapToolLevel::Save()
{
}

void MapToolLevel::Load()
{
}
