#include "PrecompileHeader.h"
#include "ForestOfHarmonyLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "FadeActor.h"

#include "Tilemap.h"
#include "StoryLevel.h"
#include "BossRoomFlop.h"
#include "StageInfoFrame.h"

#include "Minimap.h"
#include "ResultInfo.h"

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

	BgmName = "Chapter1.wav";

	IntroTilemap = CreateActor<Tilemap>();

	GameEngineDirectory DirectoryPath;
	DirectoryPath.MoveParentToDirectory("Resources");
	DirectoryPath.Move("Resources");
	DirectoryPath.Move("Data");
	DirectoryPath.Move("3_ForestOfHarmony");

	CamCorrection.z = 640;
	CamCorrection.w = -640;

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

	BattleAreaPtr->SetFiretDoorType("DB_ForestOfHarmony_Starting_Map", DoorType::Normal);
	BattleAreaPtr->SetSecondDoorType("DB_ForestOfHarmony_Starting_Map", DoorType::Skull);

	BattleAreaPtr->SetFiretDoorType("DB_ForestOfHarmony_Stage0_0_Map", DoorType::Normal);
	BattleAreaPtr->SetSecondDoorType("DB_ForestOfHarmony_Stage0_0_Map", DoorType::Skull);
	BattleAreaPtr->StageRewardOn("DB_ForestOfHarmony_Stage0_0_Map");

	BattleAreaPtr->SetFiretDoorType("DB_ForestOfHarmony_Stage0_1_Map", DoorType::Broken);
	BattleAreaPtr->SetSecondDoorType("DB_ForestOfHarmony_Stage0_1_Map", DoorType::Skull);
	BattleAreaPtr->StageRewardOn("DB_ForestOfHarmony_Stage0_1_Map");

	BattleAreaPtr->SetFiretDoorType("DB_ForestOfHarmony_Stage0_2_Map", DoorType::MiddleBoss);
	BattleAreaPtr->SetSecondDoorType("DB_ForestOfHarmony_Stage0_2_Map", DoorType::Broken);
	BattleAreaPtr->StageRewardOn("DB_ForestOfHarmony_Stage0_2_Map");	
	
	BattleAreaPtr->SetFiretDoorType("DB_ForestOfHarmony_MiddleBoss_Map", DoorType::Normal);
	BattleAreaPtr->SetSecondDoorType("DB_ForestOfHarmony_MiddleBoss_Map", DoorType::Broken);
	BattleAreaPtr->StageRewardOn("DB_ForestOfHarmony_MiddleBoss_Map");

	BattleAreaPtr->SetFiretDoorType("DB_ForestOfHarmony_SkullUpgrade_Map", DoorType::Skull);
	BattleAreaPtr->SetSecondDoorType("DB_ForestOfHarmony_SkullUpgrade_Map", DoorType::Broken);

	BattleAreaPtr->SetFiretDoorType("DB_ForestOfHarmony_Stage1_0_Map", DoorType::Normal);
	BattleAreaPtr->SetSecondDoorType("DB_ForestOfHarmony_Stage1_0_Map", DoorType::Normal);
	BattleAreaPtr->StageRewardOn("DB_ForestOfHarmony_Stage1_0_Map");

	BattleAreaPtr->SetFiretDoorType("DB_ForestOfHarmony_Stage1_1_Map", DoorType::Skull);
	BattleAreaPtr->SetSecondDoorType("DB_ForestOfHarmony_Stage1_1_Map", DoorType::Skull);
	BattleAreaPtr->StageRewardOn("DB_ForestOfHarmony_Stage1_1_Map");

	BattleAreaPtr->SetFiretDoorType("DB_ForestOfHarmony_Stage1_2_Map", DoorType::BossInter);
	BattleAreaPtr->SetSecondDoorType("DB_ForestOfHarmony_Stage1_2_Map", DoorType::Broken);
	BattleAreaPtr->StageRewardOn("DB_ForestOfHarmony_Stage1_2_Map");
		
	BattleAreaPtr->SetFiretDoorType("DB_ForestOfHarmony_BossEntrance_Map", DoorType::MainBoss);

	BossFlop = CreateActor<BossRoomFlop>();
	BattleAreaPtr->SetParentToBackground("DB_ForestOfHarmony_Background_04", 1, BossFlop->GetTransform());
	BossFlop->GetTransform()->SetLocalPosition(float4(170.0f, 310.0f, -0.1f));
	BossFlop->GetTransform()->SetLocalScale(float4(1.05f, 1.05f, 1.0f));
	
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

	// 스테이지 2
	StageNameInfos.push_back({ "DB_ForestOfHarmony_Stage1_0_Map", "DB_ForestOfHarmony_Background_02" });
	StageNameInfos.push_back({ "DB_ForestOfHarmony_Stage1_1_Map", "DB_ForestOfHarmony_Background_02" });
	StageNameInfos.push_back({ "DB_ForestOfHarmony_Stage1_2_Map", "DB_ForestOfHarmony_Background_02" });
	//StageNameInfos.push_back({ "DB_ForestOfHarmony_Stage1_3_Map", "DB_ForestOfHarmony_Background_02" });

	// 보스입장
	StageNameInfos.push_back({ "DB_ForestOfHarmony_BossEntrance_Map", "DB_ForestOfHarmony_Background_03" });

	// 보스방
	StageNameInfos.push_back({ "DB_ForestOfHarmony_BossRoom_Map", "DB_ForestOfHarmony_Background_04" });
	StageNameInfos.push_back({ "DB_ForestOfHarmony_BossRoomEnd_Map", "DB_ForestOfHarmony_Background_05" });
	
	//CurStageIndex = 0;
	CurStageIndex = 10;
	MainStageName = StageNameInfos[CurStageIndex].LoadMapName;
	MainBackgroundName = StageNameInfos[CurStageIndex].LoadBackgroundName;

	GameEngineGUI::GUIWindowCreate<FPSCheckGUI>("FPS_GUI");
	FPS_GUI = GameEngineGUI::FindGUIWindowConvert<FPSCheckGUI>("FPS_GUI");
	FPS_GUI->Off();
	
	CreateForestOfHarmonyEvent();
}


void ForestOfHarmonyLevel::Update(float _DeltaTime)
{
	BattleLevel::Update(_DeltaTime);

	if (true == IsBossClear)
	{
		ClearWaitTime += _DeltaTime;

		if (1.0f <= ClearWaitTime && true == FadeActorPtr->IsFadeEnd())
		{
			StoryLevel::SetLevelEnterStoryName(StoryLevel::StoryName::ForestOfHarmony);
			StoryLevel::SetStoryEndMoveLevel("EndingLogo");

			FadeActorPtr->FadeIn([this]()
				{
					IsFadeEndWait = true;
				});	

			IsBossClear = false;
			ClearWaitTime = 0.0f;
		}
	}

	if (true == IsFadeEndWait)
	{
		FadeWaitTime += _DeltaTime;

		if (4.0f <= FadeWaitTime)
		{
			FadeWaitTime = 0.0f;
			IsFadeEndWait = false;
			GameEngineCore::ChangeLevel("Story");
		}
	}

}

void ForestOfHarmonyLevel::ChangeStage()
{
	if (0 == CurStageIndex)
	{
		StageInfoFramePtr->FrameOn("조화의 숲", "1-1", "깊은 숲");
		ResultInfo::StageName = "깊은 숲";
	}
	else if (5 == CurStageIndex)
	{
		StageInfoFramePtr->FrameOn("조화의 숲", "1-2", "칼레온 국경지대");
		ResultInfo::StageName = "칼레온 국경지대";
	}

	if (4 == CurStageIndex)
	{
		if (nullptr != MinimapPtr && true == MinimapPtr->IsUpdate())
		{
			CallEvent("MinimapOff");
			CallEvent("GoodsUIOff");
		}
	}
	else if (9 == CurStageIndex)
	{
		if (nullptr != MinimapPtr && true == MinimapPtr->IsUpdate())
		{
			CallEvent("MinimapOff");
			CallEvent("GoodsUIOff");
		}

		StopBaseBGM();
	}
	else if(10 == CurStageIndex)
	{
		if (nullptr != MinimapPtr && true == MinimapPtr->IsUpdate())
		{
			CallEvent("MinimapOff");
			CallEvent("GoodsUIOff");
		}
	}
	else if (nullptr != MinimapPtr && false == MinimapPtr->IsUpdate())
	{
		CallEvent("MinimapOn");
		CallEvent("GoodsUIOn");
	}

	IntroTilemap->Off();
	BattleLevel::ChangeStage();
}

void ForestOfHarmonyLevel::LevelChangeStart()
{
	ResultInfo::PlayTime = 0.0f;
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
