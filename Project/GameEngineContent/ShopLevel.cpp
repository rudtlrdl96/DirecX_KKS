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

	MainStageName = "DB_Shop_Map";
	MainBackgroundName = "DB_Shop_Background";
}

void ShopLevel::Update(float _DeltaTime)
{
	BattleLevel::Update(_DeltaTime);
}
