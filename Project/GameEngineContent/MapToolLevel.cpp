#include "PrecompileHeader.h"
#include "MapToolLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCamera.h>
#include "DebugSpriteActor.h"

MapToolLevel::MapToolLevel()
{
}

MapToolLevel::~MapToolLevel()
{
}

void MapToolLevel::Start()
{
	GetMainCamera()->GetTransform()->AddLocalPosition({ 1000, 0, 0 });
	ContentLevel::Start();

	if (false == GameEngineInput::IsKey("DebugMousePos"))
	{
		GameEngineInput::CreateKey("DebugMousePos", VK_SPACE);
	}


	CreateActor<DebugSpriteActor>();
}

void MapToolLevel::Update(float _DeltaTime)
{
	ContentLevel::Update(_DeltaTime);

	if (true == GameEngineInput::IsDown("DebugMousePos"))
	{
		float4 TestMousePos = GetMousePos();

		int a = 0;
	}
	
}
