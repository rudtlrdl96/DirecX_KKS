#include "PrecompileHeader.h"
#include "ShopLevel.h"

ShopLevel::ShopLevel()
{
}

ShopLevel::~ShopLevel()
{
}

void ShopLevel::Start()
{
	BattleLevel::Start();


	GameEngineDirectory DirectoryPath;
	DirectoryPath.MoveParentToDirectory("Resources");
	DirectoryPath.Move("Resources");
	DirectoryPath.Move("Data");
	DirectoryPath.Move("7_Shop");

	{
		DirectoryPath.Move("Background");
		BattleAreaPtr->LoadBackground(DirectoryPath, "DB_Shop_Background");
		DirectoryPath.MoveParent();
	}

	{
		DirectoryPath.Move("Map");
		BattleAreaPtr->LoadMap(DirectoryPath, "DB_Shop_Map");
		DirectoryPath.MoveParent();
	}

	StageNameInfos.reserve(1);

	StageNameInfos.push_back({ "DB_Shop_Map", "DB_Shop_Background" });

	CurStageIndex = 0;
	MainStageName = StageNameInfos[CurStageIndex].LoadMapName;
	MainBackgroundName = StageNameInfos[CurStageIndex].LoadBackgroundName;
}

void ShopLevel::Update(float _DeltaTime)
{
	BattleLevel::Update(_DeltaTime);
}
