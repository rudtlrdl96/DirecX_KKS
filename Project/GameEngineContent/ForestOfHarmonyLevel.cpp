#include "PrecompileHeader.h"
#include "ForestOfHarmonyLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineRandom.h>

#include "Tilemap.h"

// Debug용
#include "FPSCheckGUI.h"

ForestOfHarmonyLevel::ForestOfHarmonyLevel()
{
}

ForestOfHarmonyLevel::~ForestOfHarmonyLevel()
{
}

void ForestOfHarmonyLevel::Start()
{
	BattleLevel::Start();

	IntroTilemap = CreateActor<Tilemap>();

	GameEngineDirectory DirectoryPath;
	DirectoryPath.MoveParentToDirectory("Resources");
	DirectoryPath.Move("Resources");
	DirectoryPath.Move("Data");
	DirectoryPath.Move("3_ForestOfHarmony");

	{
		DirectoryPath.Move("Background");
		BattleAreaPtr->LoadBackground(DirectoryPath, "DB_ForestOfHarmony_Background_00");
		BattleAreaPtr->LoadBackground(DirectoryPath, "DB_ForestOfHarmony_Background_01");
		BattleAreaPtr->LoadBackground(DirectoryPath, "DB_ForestOfHarmony_Background_02");
		BattleAreaPtr->LoadBackground(DirectoryPath, "DB_ForestOfHarmony_Background_03");
		BattleAreaPtr->LoadBackground(DirectoryPath, "DB_ForestOfHarmony_Background_04");
		BattleAreaPtr->LoadBackground(DirectoryPath, "DB_ForestOfHarmony_Background_05");
		DirectoryPath.MoveParent();
	}

	{
		DirectoryPath.Move("Map");
		BattleAreaPtr->LoadMap(DirectoryPath, "DB_ForestOfHarmony_BossEntrance_Map");
		BattleAreaPtr->LoadMap(DirectoryPath, "DB_ForestOfHarmony_BossEntranceFade_Map");
		BattleAreaPtr->LoadMap(DirectoryPath, "DB_ForestOfHarmony_BossRoom_Map");
		BattleAreaPtr->LoadMap(DirectoryPath, "DB_ForestOfHarmony_BossRoomEnd_Map");
		BattleAreaPtr->LoadMap(DirectoryPath, "DB_ForestOfHarmony_MiddleBoss_Map");
		BattleAreaPtr->LoadMap(DirectoryPath, "DB_ForestOfHarmony_SkullUpgrade_Map");
		BattleAreaPtr->LoadMap(DirectoryPath, "DB_ForestOfHarmony_Stage0_0_Map");
		BattleAreaPtr->LoadMap(DirectoryPath, "DB_ForestOfHarmony_Stage0_1_Map");
		BattleAreaPtr->LoadMap(DirectoryPath, "DB_ForestOfHarmony_Stage0_2_Map");
		BattleAreaPtr->LoadMap(DirectoryPath, "DB_ForestOfHarmony_Stage1_0_Map");
		BattleAreaPtr->LoadMap(DirectoryPath, "DB_ForestOfHarmony_Stage1_1_Map");
		BattleAreaPtr->LoadMap(DirectoryPath, "DB_ForestOfHarmony_Stage1_2_Map");
		//BattleAreaPtr->LoadMap(DirectoryPath, "DB_ForestOfHarmony_Stage1_3_Map");
		BattleAreaPtr->LoadMap(DirectoryPath, "DB_ForestOfHarmony_Starting_Map");


		GameEngineFile LoadFile = GameEngineFile(DirectoryPath.GetPlusFileName("DB_ForestOfHarmony_BossEntranceFade_Map").GetFullPath());
		GameEngineSerializer LoadSer;

		LoadSer.BufferResize(131072);
		LoadFile.LoadBin(LoadSer);

		IntroTilemap->LoadBin(LoadSer);
		IntroTilemap->Off();

		DirectoryPath.MoveParent();
	}

	IntroTilemap->GetTransform()->SetLocalPosition(float4(0, 448, -1));

	StageNameInfos.reserve(12);

	// 스타팅
	StageNameInfos.push_back({ "DB_ForestOfHarmony_Starting_Map", "DB_ForestOfHarmony_Background_00" });

	// 스테이지 1
	StageNameInfos.push_back({ "DB_ForestOfHarmony_Stage0_0_Map", "DB_ForestOfHarmony_Background_01"});
	StageNameInfos.push_back({ "DB_ForestOfHarmony_Stage0_1_Map", "DB_ForestOfHarmony_Background_01", float4(0, 400, 0)});
	StageNameInfos.push_back({ "DB_ForestOfHarmony_Stage0_2_Map", "DB_ForestOfHarmony_Background_01" });

	// 중간 보스
	StageNameInfos.push_back({ "DB_ForestOfHarmony_MiddleBoss_Map", "DB_ForestOfHarmony_Background_01" });

	// 업그레이드
	StageNameInfos.push_back({ "DB_ForestOfHarmony_SkullUpgrade_Map", "DB_ForestOfHarmony_Background_02" });

	// 스테이즈 2
	StageNameInfos.push_back({ "DB_ForestOfHarmony_Stage1_0_Map", "DB_ForestOfHarmony_Background_02" });
	StageNameInfos.push_back({ "DB_ForestOfHarmony_Stage1_1_Map", "DB_ForestOfHarmony_Background_02" });
	StageNameInfos.push_back({ "DB_ForestOfHarmony_Stage1_2_Map", "DB_ForestOfHarmony_Background_02" });
	//StageNameInfos.push_back({ "DB_ForestOfHarmony_Stage1_3_Map", "DB_ForestOfHarmony_Background_02" });

	// 보스입장
	StageNameInfos.push_back({ "DB_ForestOfHarmony_BossEntrance_Map", "DB_ForestOfHarmony_Background_03" });

	// 보스방
	StageNameInfos.push_back({ "DB_ForestOfHarmony_BossRoom_Map", "DB_ForestOfHarmony_Background_04" });
	StageNameInfos.push_back({ "DB_ForestOfHarmony_BossRoomEnd_Map", "DB_ForestOfHarmony_Background_05" });

	CurStageIndex = 0;
	MainStageName = StageNameInfos[CurStageIndex].LoadMapName;
	MainBackgroundName = StageNameInfos[CurStageIndex].LoadBackgroundName;

	GameEngineGUI::GUIWindowCreate<FPSCheckGUI>("FPS_GUI");
	FPS_GUI = GameEngineGUI::FindGUIWindowConvert<FPSCheckGUI>("FPS_GUI");
	FPS_GUI->Off();
	
	

	GameEventManager::AddEvent("BossIntroDown", LevelCode, [this]()
		{
			static bool FirstCheck = false;

			if (false == FirstCheck)
			{
				MainCamCtrl.SetMaxHeight(1460);
				FirstCheck = true;
			}
			else
			{
				MainCamCtrl.DisalbeForceLookAt();
			}
		});

	GameEventManager::AddEvent("BossIntroUp", LevelCode, [this]()
		{
			MainCamCtrl.SetLookatSpeed(0.5f);
			MainCamCtrl.SetMaxHeight(7000);

			MainCamCtrl.ActiveForceLookAt(float4(896, 1600, 0));
			IntroTilemap->FadeOut(1.0f);
		});

	GameEventManager::AddEvent("BossIntroUpOut", LevelCode, [this]()
		{
			MainCamCtrl.SetLookatSpeed(7.0f);
			IntroTilemap->FadeIn(1.0f);
		});
}

void ForestOfHarmonyLevel::Update(float _DeltaTime)
{
	BattleLevel::Update(_DeltaTime);
}

void ForestOfHarmonyLevel::ChangeStage()
{
	IntroTilemap->Off();
	BattleLevel::ChangeStage();
}

void ForestOfHarmonyLevel::LevelChangeStart()
{
	BattleLevel::LevelChangeStart();
	FPS_GUI->Reset();
	FPS_GUI->On();
}

void ForestOfHarmonyLevel::LevelChangeEnd()
{
	BattleLevel::LevelChangeEnd();
	FPS_GUI->Reset();
	FPS_GUI->Off();
}

void ForestOfHarmonyLevel::AreaClear()
{
	MoveLevel("GrandHall");
}
