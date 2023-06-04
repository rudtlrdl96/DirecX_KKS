#include "PrecompileHeader.h"
#include "OpeningLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>

#include "MultiBackground.h"
#include "FadeActor.h"
#include "TalkBox.h"
#include "Player.h"

OpeningLevel::OpeningLevel()
{
}

OpeningLevel::~OpeningLevel()
{
}

void OpeningLevel::Start()
{
	BattleLevel::Start();

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

	StageNameInfos.reserve(4);

	StageNameInfos.push_back({"DB_Opening_01_Map", "DB_Opening_Background"});
	StageNameInfos.push_back({"DB_Opening_02_Map", "DB_Opening_Background"});
	StageNameInfos.push_back({"DB_Opening_03_Map", "DB_Opening_Background"});
	StageNameInfos.push_back({"DB_Opening_04_Map", "DB_Opening_Background"});

	CurStageIndex = 0;
	MainStageName = StageNameInfos[CurStageIndex].LoadMapName;
	MainBackgroundName = StageNameInfos[CurStageIndex].LoadBackgroundName;

	AddEvent("MongalDeath_Appear", LevelCode, [this]()
		{
			if (true == IsMongalEncounter)
			{
				return;
			}

			IsMongalEncounter = true;

			CallEvent("StoryFadeIn");
			MainCamCtrl.SetLookatSpeed(3.5F);
			MainCamCtrl.ActiveForceLookAt(float4(1710, 250));

			std::function<void()> MongalTalk_0 = [this]()
			{
				TalkBoxPtr->ActiveTalkBox("�����");
				TalkBoxPtr->SetMainText(L"...", [this]()
					{
						MainCamCtrl.SetLookatSpeed();
						MainPlayer->InputUnlock();
						TalkBoxPtr->Off();
						CallEvent("UnLockCam");
						CallEvent("StoryFadeOut");
					});
			};


			std::function<void()> WitchTalk_1 = [this, MongalTalk_0]()
			{
				TalkBoxPtr->SetMainText(L"�̺� �ű�-!?", MongalTalk_0);
			};

			MainPlayer->InputLock();
			TalkBoxPtr->ActiveTalkBox("����");
			TalkBoxPtr->SetMainText(L"���� ���տ� ���ִ� �� �������� ���� ���찡 �ƴϳ�-!?", WitchTalk_1);
		});

	AddEvent("MongalWalkUp_Talk", LevelCode, [this]()
		{
			std::function<void()> WitchTalk_2 = [this]()
			{
				TalkBoxPtr->SetMainText(L"�� ������ ������ ���δٳ�-! �ϴ� ���ϴ� ������ ���� �̾߱� ���ڳ�-!!", [this]()
					{
						CallEvent("Mongal_Laugh");
						TalkBoxPtr->Off();
					});
			};

			std::function<void()> WitchTalk_1 = [this, WitchTalk_2]()
			{
				TalkBoxPtr->SetMainText(L"���� �������-!", WitchTalk_2);
			};

			TalkBoxPtr->ActiveTalkBox("����");
			TalkBoxPtr->SetMainText(L"�������� ���� ����Ű� �̳༮�̾���.", WitchTalk_1);
		});

	AddEvent("MongalDeath", LevelCode, [this]()
		{
			MainPlayer->InputLock();

			FadeActorPtr->SetSpeed(1.5f);
			FadeActorPtr->SetWaitTime(0.0f);

			FadeActorPtr->FadeIn([this]()
				{
					FadeActorPtr->FadeOut([this]()
						{
							FadeActorPtr->Reset();
							FadeActorPtr->SetWaitTime(0.5f);
						}, float4::One);				
				}, float4::One);
		});

	AddEvent("PlayerMove_MongalWalkup", LevelCode, [this]()
		{
			MainCamCtrl.SetCameraPos(float4(1410, 250));
			MainPlayer->GetTransform()->SetLocalPosition(float4(1410, 250));
		});
}

void OpeningLevel::Update(float _DeltaTime)
{
	BattleLevel::Update(_DeltaTime);
}

void OpeningLevel::LevelChangeStart()
{
	BattleLevel::LevelChangeStart();
	IsMongalEncounter = false;
}

void OpeningLevel::AreaClear()
{
	MoveLevel("Castle");
}
