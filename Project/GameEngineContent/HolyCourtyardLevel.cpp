#include "PrecompileHeader.h"
#include "HolyCourtyardLevel.h"
#include "ItemData.h"

HolyCourtyardLevel::HolyCourtyardLevel()
{
}

HolyCourtyardLevel::~HolyCourtyardLevel()
{
}

void HolyCourtyardLevel::Start()
{
	BattleLevel::Start();

	GameEngineDirectory DirectoryPath;
	DirectoryPath.MoveParentToDirectory("Resources");
	DirectoryPath.Move("Resources");
	DirectoryPath.Move("Data");
	DirectoryPath.Move("5_HolyCourtyard");

	{
		DirectoryPath.Move("Background");
		BattleAreaPtr->LoadBackground(DirectoryPath, "DB_BossPahse0_Background_1");
		BattleAreaPtr->LoadBackground(DirectoryPath, "DB_HolyCourtyard_Background_1");
		BattleAreaPtr->LoadBackground(DirectoryPath, "DB_HolyCourtyard_Background_2");
		BattleAreaPtr->LoadBackground(DirectoryPath, "DB_HolyCourtyard_Background_3");
		BattleAreaPtr->LoadBackground(DirectoryPath, "DB_HolyCourtyard_Background_4");
		BattleAreaPtr->LoadBackground(DirectoryPath, "DB_HolyCourtyard_Background_5");
		DirectoryPath.MoveParent();
	}

	{
		DirectoryPath.Move("Map");
		BattleAreaPtr->LoadMap(DirectoryPath, "DB_HoluCourtyard_BossEntranceFade_Map");
		BattleAreaPtr->LoadMap(DirectoryPath, "DB_HoluCourtyard_BossPhase0_Map");
		DirectoryPath.MoveParent();
	}


	StageNameInfos.reserve(2);

	StageNameInfos.push_back({ "DB_HoluCourtyard_BossEntranceFade_Map", "DB_BossPahse0_Background_1" });
	StageNameInfos.push_back({ "DB_HoluCourtyard_BossPhase0_Map", "DB_HolyCourtyard_Background_2" });

	CurStageIndex = 0;
	MainStageName = StageNameInfos[CurStageIndex].LoadMapName;
	MainBackgroundName = StageNameInfos[CurStageIndex].LoadBackgroundName;
}

void HolyCourtyardLevel::Update(float _DeltaTime)
{
	BattleLevel::Update(_DeltaTime);
}
