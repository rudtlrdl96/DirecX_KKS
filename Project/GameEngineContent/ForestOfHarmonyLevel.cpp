#include "PrecompileHeader.h"
#include "ForestOfHarmonyLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineRandom.h>

// Debug�� ���� ����
#include "FPSCheckGUI.h"
#include "CarleonRecruit.h"
#include "CarleonArcher.h"
#include "CarleonManAtArms.h"
#include "Ent.h"
#include "RootEnt.h"
#include "BlossomEnt.h"
#include "GiantEnt.h"
#include "FlameWizard.h"
#include "GlacialWizard.h"

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
		//BattleAreaPtr->LoadMap(DirectoryPath, "DB_ForestOfHarmony_Stage1_3_Map");
		BattleAreaPtr->LoadMap(DirectoryPath, "DB_ForestOfHarmony_Starting_Map");
		DirectoryPath.MoveParent();
	}

	StageNameInfos.reserve(12);

	// ��Ÿ��
	StageNameInfos.push_back({ "DB_ForestOfHarmony_Starting_Map", "DB_ForestOfHarmony_Background_00" });

	// �������� 1
	StageNameInfos.push_back({ "DB_ForestOfHarmony_Stage0_0_Map", "DB_ForestOfHarmony_Background_01" });
	StageNameInfos.push_back({ "DB_ForestOfHarmony_Stage0_1_Map", "DB_ForestOfHarmony_Background_01" });
	StageNameInfos.push_back({ "DB_ForestOfHarmony_Stage0_2_Map", "DB_ForestOfHarmony_Background_01" });

	// �߰� ����
	StageNameInfos.push_back({ "DB_ForestOfHarmony_MiddleBoss_Map", "DB_ForestOfHarmony_Background_01" });

	// ���׷��̵�
	StageNameInfos.push_back({ "DB_ForestOfHarmony_SkullUpgrade_Map", "DB_ForestOfHarmony_Background_02" });

	// �������� 2
	StageNameInfos.push_back({ "DB_ForestOfHarmony_Stage1_0_Map", "DB_ForestOfHarmony_Background_02" });
	StageNameInfos.push_back({ "DB_ForestOfHarmony_Stage1_1_Map", "DB_ForestOfHarmony_Background_02" });
	StageNameInfos.push_back({ "DB_ForestOfHarmony_Stage1_2_Map", "DB_ForestOfHarmony_Background_02" });
	//StageNameInfos.push_back({ "DB_ForestOfHarmony_Stage1_3_Map", "DB_ForestOfHarmony_Background_02" });

	// ��������
	StageNameInfos.push_back({ "DB_ForestOfHarmony_BossEntrance_Map", "DB_ForestOfHarmony_Background_02" });

	// ������
	StageNameInfos.push_back({ "DB_ForestOfHarmony_BossRoom_Map", "DB_ForestOfHarmony_Background_04" });
	StageNameInfos.push_back({ "DB_ForestOfHarmony_BossRoomEnd_Map", "DB_ForestOfHarmony_Background_05" });

	CurStageIndex = 0;
	MainStageName = StageNameInfos[CurStageIndex].LoadMapName;
	MainBackgroundName = StageNameInfos[CurStageIndex].LoadBackgroundName;

	GameEngineGUI::GUIWindowCreate<FPSCheckGUI>("FPS_GUI");
	FPS_GUI = GameEngineGUI::FindGUIWindowConvert<FPSCheckGUI>("FPS_GUI");
	FPS_GUI->Off();

}

void ForestOfHarmonyLevel::Update(float _DeltaTime)
{
	BattleLevel::Update(_DeltaTime);

	if (true == GameEngineInput::IsDown("MonsterSpawn"))
	{
		float4 RandSpawnPos = float4(GameEngineRandom::MainRandom.RandomFloat(400.0f, 800.0f), 400, GameEngineRandom::MainRandom.RandomFloat(-20.0f, -10.0f));

		//std::shared_ptr<GlacialWizard> NewMonster = CreateActor<GlacialWizard>();
		//NewMonster->GetTransform()->SetLocalPosition(RandSpawnPos);

		GameEngineRandom& MainRand = GameEngineRandom::MainRandom;
		
		switch (MainRand.RandomInt(0, 8))
		{
		case 0: // Į���� �ź�
		{
			std::shared_ptr<CarleonRecruit> NewMonster = CreateActor<CarleonRecruit>();
			NewMonster->GetTransform()->SetLocalPosition(RandSpawnPos);
			break;
		}
		case 1: // Į���� �ü�
		{
			std::shared_ptr<CarleonArcher> NewMonster = CreateActor<CarleonArcher>();
			NewMonster->GetTransform()->SetLocalPosition(RandSpawnPos);
			break;
		}
		case 2: // Į���� �ߺ���
		{
			std::shared_ptr<CarleonManAtArms> NewMonster = CreateActor<CarleonManAtArms>();
			NewMonster->GetTransform()->SetLocalPosition(RandSpawnPos);
			break;
		}
		case 3: // ��Ʈ
		{
			std::shared_ptr<Ent> NewMonster = CreateActor<Ent>();
			NewMonster->GetTransform()->SetLocalPosition(RandSpawnPos);
			break;
		}
		case 4: // �Ѹ� ��Ʈ
		{
			std::shared_ptr<RootEnt> NewMonster = CreateActor<RootEnt>();
			NewMonster->GetTransform()->SetLocalPosition(RandSpawnPos);
			break;
		}
		case 5: // ������ (���̾�Ʈ ��Ʈ)
		{
			std::shared_ptr<GiantEnt> NewMonster = CreateActor<GiantEnt>();
			NewMonster->GetTransform()->SetLocalPosition(RandSpawnPos);
			break;
		}
		case 6: // �� ��Ʈ
		{
			std::shared_ptr<BlossomEnt> NewMonster = CreateActor<BlossomEnt>();
			NewMonster->GetTransform()->SetLocalPosition(RandSpawnPos);
			break;
		}
		case 7: // ȭ�� ������
		{
			std::shared_ptr<FlameWizard> NewMonster = CreateActor<FlameWizard>();
			NewMonster->GetTransform()->SetLocalPosition(RandSpawnPos);
			break;
		}
		case 8: // ���� ������
		{
			std::shared_ptr<GlacialWizard> NewMonster = CreateActor<GlacialWizard>();
			NewMonster->GetTransform()->SetLocalPosition(RandSpawnPos);
			break;
		}
		default:
			break;
		}
	}
}

void ForestOfHarmonyLevel::LevelChangeStart()
{
	BattleLevel::LevelChangeStart();
	FPS_GUI->Reset();
	FPS_GUI->On();
}

void ForestOfHarmonyLevel::AreaClear()
{
	MoveLevel("GrandHall");
}
