#include "PrecompileHeader.h"
#include "BattleLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>

#include "GameEventManager.h"
#include "EffectManager.h"
#include "BattleArea.h"
#include "Player.h"
#include "FadeActor.h"
#include "StoryFade.h"
#include "TalkBox.h"

#include "GameEngineActorGUI.h"

BattleLevel::BattleLevel()
{
}

BattleLevel::~BattleLevel()
{
}

void BattleLevel::Start()
{
	if (false == GameEngineInput::IsKey("LevelMovePrev"))
	{
		GameEngineInput::CreateKey("LevelMovePrev", '1');
		GameEngineInput::CreateKey("LevelMoveNext", '2');
		GameEngineInput::CreateKey("DebugTextRead", '3');
	}

	ContentLevel::Start();

	float4 HalfWindowSize = GameEngineWindow::GetScreenSize().half();
	BattleAreaPtr = CreateActor<BattleArea>();

	FadeActorPtr = CreateActor<FadeActor>();
	FadeActorPtr->GetTransform()->AddLocalPosition(float4(0, 0, -20.0f));

	FadeActorPtr_White = CreateActor<FadeActor>();
	FadeActorPtr_White->GetTransform()->AddLocalPosition(float4(0, 0, -1.0f));

	StoryFadePtr = CreateActor<StoryFade>();
	StoryFadePtr->GetTransform()->SetLocalPosition(float4(0, 0, -100.0f));

	TalkBoxPtr = CreateActor<TalkBox>();
	TalkBoxPtr->GetTransform()->SetLocalPosition(float4(0, -300, -110.0f));
	TalkBoxPtr->SetReadSpeed(20.0f);
	TalkBoxPtr->Off();

	AddEvent("NextLevelMove", LevelCode, [this]()
		{
			AreaClear();
		}); 

	AddEvent("PlayerFrameActive", LevelCode, [this]()
		{
			MainPlayer->ActivePlayerFrame();
		});

	AddEvent("PlayerFrameDisable", LevelCode, [this]()
		{
			MainPlayer->DisablePlayerFrame();
		});

	AddEvent("FadeIn", LevelCode, [this]()
		{
			FadeActorPtr->FadeIn();
		});

	AddEvent("FadeOut", LevelCode, [this]()
		{
			FadeActorPtr->FadeOut();
		});

	AddEvent("FadeIn_White", LevelCode, [this]()
		{
			FadeActorPtr_White->SetWaitTime(0.0f);
			FadeActorPtr_White->SetSpeed(2.0f);
			FadeActorPtr_White->FadeIn(nullptr, float4::White);
		});

	AddEvent("FadeOut_White", LevelCode, [this]()
		{
			FadeActorPtr_White->SetWaitTime(0.0f);
			FadeActorPtr_White->SetSpeed(2.0f);
			FadeActorPtr_White->FadeOut(nullptr, float4::White);
		});

	AddEvent("StoryFadeIn", LevelCode, [this]()
		{
			StoryFadePtr->SetSpeed(2.0f);
			StoryFadePtr->FadeIn();
		});

	AddEvent("StoryFadeOut", LevelCode, [this]()
		{
			StoryFadePtr->SetSpeed(2.0f);
			StoryFadePtr->FadeOut();
		});

	AddEvent("UnLockCam", LevelCode, [this]()
		{
			MainCamCtrl.DisalbeForceLookAt();
		});

	ActorGUIPtr = GameEngineGUI::FindGUIWindowConvert<GameEngineActorGUI>("GameEngineActorGUI");
}

void BattleLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("LevelMovePrev"))
	{
		MovePrevStage(true);
	}
	else if (true == GameEngineInput::IsDown("LevelMoveNext"))
	{
		MoveNextStage(true);
	}

	ContentLevel::Update(_DeltaTime);
	BattleAreaPtr->UpdateBackground(_DeltaTime, MainCamCtrl.GetCameraPos());
}

void BattleLevel::SetPlayerPos(const float4& _Pos)
{
	float4 SpawnPos = _Pos;
	SpawnPos.z = -25.0f;

	MainPlayer->GetTransform()->SetLocalPosition(SpawnPos);
}

void BattleLevel::LevelChangeStart()
{
	//ActorGUIPtr->On();
	//ActorGUIPtr->SetTarget(TalkBoxPtr->ArrowPtr->GetTransform());

	StoryFadePtr->Reset();

	FadeActorPtr->SetWaitTime(0.5f);
	FadeActorPtr->SetSpeed(2.0f);
	FadeActorPtr->FadeOut();

	FadeActorPtr_White->SetUnFade();

	EffectManager::SetLevel(DynamicThis<GameEngineLevel>());

	if (nullptr == MainPlayer)
	{
		MainPlayer = CreateActor<Player>();
		MainPlayer->SetInventoryData();
		MainCamCtrl.SetLookatTarget(MainPlayer);
	}

	ChangeStage();
	MainCamCtrl.ResetScale();

	GameEngineTime::GlobalTime.SetAllUpdateOrderTimeScale(1.0f);
	GameEngineTime::GlobalTime.SetAllRenderOrderTimeScale(1.0f);
}

void BattleLevel::LevelChangeEnd()
{
	ActorGUIPtr->Off();

	if (nullptr != MainPlayer)
	{
		MainPlayer->Death();
		MainPlayer = nullptr;
		MainCamCtrl.SetLookatTarget(nullptr);
	}

	EffectManager::SetLevel(nullptr);
	GameEngineTime::GlobalTime.SetAllUpdateOrderTimeScale(1.0f);
	GameEngineTime::GlobalTime.SetAllRenderOrderTimeScale(1.0f);
}

void BattleLevel::ChangeStage()
{
	BattleAreaPtr->ChangeBackground(MainBackgroundName, BackgroundPivot);
	BattleAreaPtr->ChangeMap(MainStageName);
	BattleAreaPtr->SetCameraLock(MainCamCtrl);

	float4 SpawnPos = BattleAreaPtr->GetSpawnPoint();

	CallEvent("MoveStage");

	MainCamCtrl.SetLookatSpeed(7.0f);
	MainCamCtrl.DisalbeForceLookAt();
	SetPlayerPos(SpawnPos);
	MainCamCtrl.SetCameraPos(SpawnPos);
}

void BattleLevel::MovePrevStage(bool _ForceMove /*= false*/)
{
	if (false == FadeActorPtr->IsFadeEnd())
	{
		return;
	}

	if (0 < CurStageIndex)
	{
		--CurStageIndex;
	}
	else
	{
		CurStageIndex = 0;
	}

	if (true == _ForceMove)
	{
		MainStageName = StageNameInfos[CurStageIndex].LoadMapName;
		MainBackgroundName = StageNameInfos[CurStageIndex].LoadBackgroundName;
		BackgroundPivot = StageNameInfos[CurStageIndex].BackgroundPivot;
		ChangeStage();
	}
	else
	{
		FadeActorPtr->SetWaitTime(0.0f);
		FadeActorPtr->SetSpeed(3.0f);
		FadeActorPtr->FadeIn([this]()
			{
				MainStageName = StageNameInfos[CurStageIndex].LoadMapName;
				MainBackgroundName = StageNameInfos[CurStageIndex].LoadBackgroundName;
				BackgroundPivot = StageNameInfos[CurStageIndex].BackgroundPivot;
				ChangeStage();

				FadeActorPtr->SetWaitTime(0.3f);
				FadeActorPtr->SetSpeed(3.0f);
				FadeActorPtr->FadeOut();
			});
	}

}

void BattleLevel::MoveNextStage(bool _ForceMove /*= false*/)
{
	if (false == FadeActorPtr->IsFadeEnd())
	{
		return;
	}

	++CurStageIndex;


	if (StageNameInfos.size() <= CurStageIndex)
	{
		AreaClear();
		CallEvent("MoveStage");
		CurStageIndex = static_cast<UINT>(StageNameInfos.size() - 1);
	}
	else
	{
		if (true == _ForceMove)
		{
			MainStageName = StageNameInfos[CurStageIndex].LoadMapName;
			MainBackgroundName = StageNameInfos[CurStageIndex].LoadBackgroundName;
			BackgroundPivot = StageNameInfos[CurStageIndex].BackgroundPivot;
			ChangeStage();
		}
		else
		{
			FadeActorPtr->SetWaitTime(0.0f);
			FadeActorPtr->SetSpeed(3.0f);
			FadeActorPtr->FadeIn([this]()
				{
					MainStageName = StageNameInfos[CurStageIndex].LoadMapName;
					MainBackgroundName = StageNameInfos[CurStageIndex].LoadBackgroundName;
					BackgroundPivot = StageNameInfos[CurStageIndex].BackgroundPivot;
					ChangeStage();

					FadeActorPtr->SetWaitTime(0.3f);
					FadeActorPtr->SetSpeed(3.0f);
					FadeActorPtr->FadeOut();
				});
		}
	}
}

void BattleLevel::MoveLevel(const std::string_view& _Level)
{
	if (true == IsLevelMove)
	{
		return;
	}

	IsLevelMove = true;

	FadeActorPtr->SetWaitTime(0.0f);
	FadeActorPtr->SetSpeed(1.5f);
	FadeActorPtr->FadeIn([this, _Level]()
		{
			GameEngineCore::ChangeLevel(_Level);
			IsLevelMove = false;
		});

}