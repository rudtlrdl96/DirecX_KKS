#include "PrecompileHeader.h"
#include "ForestOfHarmonyLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineRandom.h>

// Debug용 추후 삭제
#include "FPSCheckGUI.h"
#include "CarleonRecruit.h"
#include "CarleonArcher.h"
#include "CarleonManAtArms.h"
#include "Ent.h"
#include "RootEnt.h"

ForestOfHarmonyLevel::ForestOfHarmonyLevel()
{
}

ForestOfHarmonyLevel::~ForestOfHarmonyLevel()
{
}

void ForestOfHarmonyLevel::Start()
{
	if (false == GameEngineInput::IsKey("MonsterSpawn"))
	{
		GameEngineInput::CreateKey("MonsterSpawn", 'T');
	}

	BattleLevel::Start();

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
		BattleAreaPtr->LoadMap(DirectoryPath, "DB_ForestOfHarmony_Stage1_3_Map");
		BattleAreaPtr->LoadMap(DirectoryPath, "DB_ForestOfHarmony_Starting_Map");
		DirectoryPath.MoveParent();
	}

	MainStageName = "DB_ForestOfHarmony_Stage0_0_Map";
	MainBackgroundName = "DB_ForestOfHarmony_Background_01";
	GameEngineGUI::GUIWindowCreate<FPSCheckGUI>("FPS_GUI");
	FPS_GUI = GameEngineGUI::FindGUIWindowConvert<FPSCheckGUI>("FPS_GUI");
	FPS_GUI->Off();

}

void ForestOfHarmonyLevel::Update(float _DeltaTime)
{
	BattleLevel::Update(_DeltaTime);

	if (true == GameEngineInput::IsDown("MonsterSpawn"))
	{
		std::shared_ptr<RootEnt> NewMonster = CreateActor<RootEnt>();
		NewMonster->GetTransform()->SetLocalPosition(float4(400, 500, -100));

		//GameEngineRandom& MainRand = GameEngineRandom::MainRandom;
		//
		//switch (MainRand.RandomInt(0, 3))
		//{
		//case 0: // 칼레온 신병
		//{
		//	std::shared_ptr<CarleonRecruit> NewMonster = CreateActor<CarleonRecruit>();
		//	NewMonster->GetTransform()->SetLocalPosition(float4(400, 500, -100));
		//	break;
		//}
		//case 1: // 칼레온 궁수
		//{
		//	std::shared_ptr<CarleonArcher> NewMonster = CreateActor<CarleonArcher>();
		//	NewMonster->GetTransform()->SetLocalPosition(float4(400, 500, -100));
		//	break;
		//}
		//case 2: // 칼레온 중보병
		//{
		//	std::shared_ptr<CarleonManAtArms> NewMonster = CreateActor<CarleonManAtArms>();
		//	NewMonster->GetTransform()->SetLocalPosition(float4(400, 500, -100));
		//	break;
		//}
		//case 3: // 엔트
		//{
		//	std::shared_ptr<Ent> NewMonster = CreateActor<Ent>();
		//	NewMonster->GetTransform()->SetLocalPosition(float4(400, 500, -100));
		//	break;
		//}
		//case 4: // 뿌리 엔트
		//{
		//	std::shared_ptr<Ent> NewMonster = CreateActor<Ent>();
		//	NewMonster->GetTransform()->SetLocalPosition(float4(400, 500, -100));
		//	break;
		//}
		//default:
		//	break;
		//}


	}
}

void ForestOfHarmonyLevel::LevelChangeStart()
{
	BattleLevel::LevelChangeStart();
	FPS_GUI->Reset();
	FPS_GUI->On();
}
