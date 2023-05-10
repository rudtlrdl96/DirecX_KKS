#include "PrecompileHeader.h"
#include "CastleLevel.h"
#include <GameEngineCore/GameEngineTexture.h>
#include "MultiBackground.h"

CastleLevel::CastleLevel()
{
}

CastleLevel::~CastleLevel()
{
}

void CastleLevel::Start()
{
	BattleLevel::Start();

	GameEngineDirectory DirectoryPath;
	DirectoryPath.MoveParentToDirectory("Resources");
	DirectoryPath.Move("Resources");
	DirectoryPath.Move("Data");
	DirectoryPath.Move("2_Castle");

	{
		DirectoryPath.Move("Background");
		BattleAreaPtr->LoadBackground(DirectoryPath, "DB_Castle_Background");
		DirectoryPath.MoveParent();
	}

	{
		DirectoryPath.Move("Map");
		BattleAreaPtr->LoadMap(DirectoryPath, "DB_Castle_Map");
		DirectoryPath.MoveParent();
	}

	BattleAreaPtr->ChangeBackground("DB_Castle_Background", float4(640.0f, 20, 0));
	BattleAreaPtr->ChangeMap("DB_Castle_Map", float4(0, -64.0f * 3, 0, 0));
	BattleAreaPtr->SetCameraLock(MainCamCtrl);

	MainCamCtrl.SetMaxWidth(D3D11_FLOAT32_MAX);
}

void CastleLevel::Update(float _DeltaTime)
{
	BattleLevel::Update(_DeltaTime);
}
