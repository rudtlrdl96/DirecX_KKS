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

	BattleAreaPtr->ChangeBackground("DB_Shop_Background");
	BattleAreaPtr->ChangeMap("DB_Shop_Map");
	BattleAreaPtr->SetCameraLock(MainCamCtrl);
}

void ShopLevel::Update(float _DeltaTime)
{
	BattleLevel::Update(_DeltaTime);
}
