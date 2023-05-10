#include "PrecompileHeader.h"
#include "OpeningLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>

#include "MultiBackground.h"

OpeningLevel::OpeningLevel()
{
}

OpeningLevel::~OpeningLevel()
{
}

void OpeningLevel::Start()
{
	BattleLevel::Start();

	if (false == GameEngineInput::IsKey("Opening_Debug_SetMap0"))
	{
		GameEngineInput::CreateKey("Opening_Debug_SetMap0", '1');
		GameEngineInput::CreateKey("Opening_Debug_SetMap1", '2');
		GameEngineInput::CreateKey("Opening_Debug_SetMap2", '3');
		GameEngineInput::CreateKey("Opening_Debug_SetMap3", '4');
	}

	GameEngineDirectory DirectoryPath;
	DirectoryPath.MoveParentToDirectory("Resources");
	DirectoryPath.Move("Resources");
	DirectoryPath.Move("Data");
	DirectoryPath.Move("1_Opening");

	{
		DirectoryPath.Move("Background");
		BattleAreaPtr->LoadBackground(DirectoryPath, "DB_Opening_Background");
		DirectoryPath.MoveParent();
	}

	{
		DirectoryPath.Move("Map");
		BattleAreaPtr->LoadMap(DirectoryPath, "DB_Opening_01_Map");
		BattleAreaPtr->LoadMap(DirectoryPath, "DB_Opening_02_Map");
		BattleAreaPtr->LoadMap(DirectoryPath, "DB_Opening_03_Map");
		BattleAreaPtr->LoadMap(DirectoryPath, "DB_Opening_04_Map");
		DirectoryPath.MoveParent();
	}

	BattleAreaPtr->ChangeBackground("DB_Opening_Background");
	BattleAreaPtr->ChangeMap("DB_Opening_01_Map");
}

void OpeningLevel::Update(float _DeltaTime)
{
	BattleLevel::Update(_DeltaTime);

	if (true == GameEngineInput::IsDown("Opening_Debug_SetMap0"))
	{
		BattleAreaPtr->ChangeMap("DB_Opening_01_Map");
	}
	if (true == GameEngineInput::IsDown("Opening_Debug_SetMap1"))
	{
		BattleAreaPtr->ChangeMap("DB_Opening_02_Map");
	}

	if (true == GameEngineInput::IsDown("Opening_Debug_SetMap2"))
	{
		BattleAreaPtr->ChangeMap("DB_Opening_03_Map");
	}

	if (true == GameEngineInput::IsDown("Opening_Debug_SetMap3"))
	{
		BattleAreaPtr->ChangeMap("DB_Opening_04_Map");
	}
}
