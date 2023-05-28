#include "PrecompileHeader.h"
#include "GrandHallLevel.h"

GrandHallLevel::GrandHallLevel()
{
}

GrandHallLevel::~GrandHallLevel()
{
}

void GrandHallLevel::Start()
{
	BattleLevel::Start();

	GameEngineDirectory DirectoryPath;
	DirectoryPath.MoveParentToDirectory("Resources");
	DirectoryPath.Move("Resources");
	DirectoryPath.Move("Data");
	DirectoryPath.Move("4_GrandHall");

	{
		DirectoryPath.Move("Background");
		BattleAreaPtr->LoadBackground(DirectoryPath, "DB_GrandHall_Background_0");
		BattleAreaPtr->LoadBackground(DirectoryPath, "DB_GrandHall_Background_1");
		DirectoryPath.MoveParent();
	}

	{
		DirectoryPath.Move("Map");
		BattleAreaPtr->LoadMap(DirectoryPath, "DB_GrandHall_BossEntrance_Map");
		BattleAreaPtr->LoadMap(DirectoryPath, "DB_GrandHall_BossRoom_Map");
		DirectoryPath.MoveParent();
	}

	StageNameInfos.reserve(2);

	StageNameInfos.push_back({ "DB_GrandHall_BossEntrance_Map", "DB_GrandHall_Background_0" });
	StageNameInfos.push_back({ "DB_GrandHall_BossRoom_Map", "DB_GrandHall_Background_1" });

	CurStageIndex = 0;
	MainStageName = StageNameInfos[CurStageIndex].LoadMapName;
	MainBackgroundName = StageNameInfos[CurStageIndex].LoadBackgroundName;
}

void GrandHallLevel::Update(float _DeltaTime)
{
	BattleLevel::Update(_DeltaTime);
}
