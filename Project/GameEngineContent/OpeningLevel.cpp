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
			CallEvent("StoryFadeIn");
			MainCamCtrl.ActiveForceLookAt(float4(1710, 250));

			std::function<void()> MongalTalk_0 = [this]()
			{
				TalkBoxPtr->ActiveTalkBox("오우거");
				TalkBoxPtr->SetMainText(L"...", [this]()
					{
						MainPlayer->InputUnlock();
						TalkBoxPtr->Off();
						CallEvent("UnLockCam");
						CallEvent("StoryFadeOut");
					});
			};


			std::function<void()> WitchTalk_1 = [this, MongalTalk_0]()
			{
				TalkBoxPtr->SetMainText(L"이봐 거기-!?", MongalTalk_0);
			};

			MainPlayer->InputLock();
			TalkBoxPtr->ActiveTalkBox("마녀");
			TalkBoxPtr->SetMainText(L"저기 성앞에 서있는 게 경비대장이 말한 오우가 아니냥-!?", WitchTalk_1);
		});

	AddEvent("MongalDeath", LevelCode, [this]()
		{
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

}

void OpeningLevel::Update(float _DeltaTime)
{
	BattleLevel::Update(_DeltaTime);
}

void OpeningLevel::AreaClear()
{
	MoveLevel("Castle");
}
