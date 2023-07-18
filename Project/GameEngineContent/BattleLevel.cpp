#include "PrecompileHeader.h"
#include "BattleLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>

// Game
#include "GameEventManager.h"
#include "EffectManager.h"
#include "BattleArea.h"
#include "Player.h"
#include "BaseMonster.h"
#include "ResultInfo.h"

// UI
#include "FadeActor.h"
#include "StoryFade.h"
#include "TalkBox.h"
#include "Minimap.h"
#include "SkullGearPopup.h"
#include "StageInfoFrame.h"
#include "GoodsUI.h"
#include "ResultUI.h"

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
		GameEngineInput::CreateKey("IsDebugSwitch", '4');
	}

	ContentLevel::Start();

	MinimapCam = CreateNewCamera((int)CameraOrder::MiniMap).get();
	MinimapCam->SetSortType(0, SortType::ZSort);
	MinimapCam->SetProjectionType(CameraType::Orthogonal);
	MinimapCam->GetTransform()->SetLocalPosition(float4(0, 0, -5000.0f));
	MinimapCam->GetTransform()->SetLocalRotation(float4::Zero);
	MinimapCam->SetZoomRatio(1.75f);
	MinimapCam->MergeOff();

	float4 HalfWindowSize = GameEngineWindow::GetScreenSize().half();
	BattleAreaPtr = CreateActor<BattleArea>();

	MinimapPtr = CreateActor<Minimap>();
	MinimapPtr->MinimapOn();

	FadeActorPtr = CreateActor<FadeActor>();
	FadeActorPtr->GetTransform()->AddLocalPosition(float4(0, 0, -20.0f));

	FadeActorPtr_White = CreateActor<FadeActor>();
	FadeActorPtr_White->GetTransform()->AddLocalPosition(float4(0, 0, -1.0f));

	StoryFadePtr = CreateActor<StoryFade>();
	StoryFadePtr->GetTransform()->SetLocalPosition(float4(0, 0, -100.0f));

	TalkBoxPtr = CreateActor<TalkBox>();
	TalkBoxPtr->GetTransform()->SetLocalPosition(float4(0, -300, -110.0f));
	TalkBoxPtr->SetReadSpeed(25.0f);
	TalkBoxPtr->Off();

	SkullGearPopupPtr = CreateActor<SkullGearPopup>();
	SkullGearPopupPtr->Off();

	StageInfoFramePtr = CreateActor<StageInfoFrame>();

	GoodsUIPtr = CreateActor<GoodsUI>();
	GoodsUIPtr->GoodsUIOn(true);

	ResultUIPtr = CreateActor<ResultUI>();
	ResultUIPtr->GetTransform()->SetWorldPosition(float4(0, 0, -4500));
	ResultUIPtr->SetBattleLevel(this);
	ResultUIPtr->Off();

	PivotStart = float4(-225, -305, 0);
	PivotEnd = float4(-225, -130, 0);

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

	AddEvent("MinimapOn", LevelCode, [this]()
		{
			MinimapPtr->MinimapOn();
		});

	AddEvent("MinimapOff", LevelCode, [this]()
		{
			MinimapPtr->MinimapOff();
		});
	
	AddEvent("MinimapOff_Force", LevelCode, [this]()
		{
			MinimapPtr->MinimapOff(true);
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

	AddEvent("LockMonsterMove", LevelCode, [this]()
		{
			BaseMonster::SetMonstersMove(true);
		});

	AddEvent("UnlockMonsterMove", LevelCode, [this]()
		{
			BaseMonster::SetMonstersMove(false);
		});

	AddEvent("SkullGearPopupOn", LevelCode, [this]()
		{
			SkullGearPopupPtr->PopupOn();

			if (nullptr != MainPlayer)
			{
				if (ActorViewDir::Left == MainPlayer->GetViewDir())
				{
					SkullGearPopupPtr->GetTransform()->SetLocalPosition(float4(-300, 30));
				}
				else
				{
					SkullGearPopupPtr->GetTransform()->SetLocalPosition(float4(300, 30));
				}
			}
		});

	AddEvent("SkullGearPopupCheck", LevelCode, [this]()
		{
			if (false == SkullGearPopupPtr->IsUpdate())
			{
				SkullGearPopupPtr->PopupOn();
			}
		});

	AddEvent("SkullGearPopupOff", LevelCode, [this]()
		{
			SkullGearPopupPtr->PopupOff();
		});	

	AddEvent("GoodsUIOn", LevelCode, [this]()
		{
			GoodsUIPtr->GoodsUIOn(MinimapPtr->IsUpdate());
		});	
	
	AddEvent("GoodsUIOff", LevelCode, [this]()
		{
			GoodsUIPtr->GoodsUIOff(MinimapPtr->IsUpdate());
		});	
	
	AddEvent("ResultOn", LevelCode, [this]()
		{
			IsPlayerDeath = true;
		});	
	
	AddEvent("ResultOff", LevelCode, [this]()
		{
			ResultUIPtr->ResultUIOff();
		});

}

void BattleLevel::Update(float _DeltaTime)
{
	ResultInfo::PlayTime += _DeltaTime;

	ContentLevel::Update(_DeltaTime);

	MinimapPtr->MonsterCountUpdate(BattleAreaPtr->GetMonsterCount());


	if (true == IsPlayerDeath)
	{
		DeathTime += GameEngineTime::GlobalTime.GetDeltaTime();

		if (true == ResultUIPtr->IsUpdate())
		{
			MainCamCtrl.SetWorldPivot(PivotEnd);
		}

		if (false == ResultUIPtr->IsUpdate() && 2.5f <= DeathTime)
		{
			GameEngineTime::GlobalTime.SetAllUpdateOrderTimeScale(0.0f);
			GameEngineTime::GlobalTime.SetAllRenderOrderTimeScale(0.0f);

			ResultUIPtr->ResultUIOn();
		}

		return;
	}

	MinimapCam->GetTransform()->SetWorldPosition(GetMainCamera()->GetTransform()->GetWorldPosition() + float4(0, 256));

	if (true == GameEngineInput::IsDown("LevelMovePrev"))
	{
		MovePrevStage(true);
	}
	else if (true == GameEngineInput::IsDown("LevelMoveNext"))
	{
		MoveNextStage(true);
	} 
	else if (true == GameEngineInput::IsDown("IsDebugSwitch"))
	{
		IsDebugSwitch();
	}
	
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
	IsPlayerDeath = false;

	ContentLevel::LevelChangeStart();

	BaseMonster::SetMonstersMove(false);

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
	MainCamCtrl.SetWorldPivot(float4::Zero);

	GameEngineTime::GlobalTime.SetAllUpdateOrderTimeScale(1.0f);
	GameEngineTime::GlobalTime.SetAllRenderOrderTimeScale(1.0f);
}

void BattleLevel::LevelChangeEnd()
{
	ContentLevel::LevelChangeEnd();

	if (nullptr != MainPlayer)
	{
		MainPlayer->Death();
		MainPlayer = nullptr;
		MainCamCtrl.SetLookatTarget(nullptr);
	}

	EffectManager::SetLevel(nullptr);
	GameEngineTime::GlobalTime.SetAllUpdateOrderTimeScale(1.0f);
	GameEngineTime::GlobalTime.SetAllRenderOrderTimeScale(1.0f);

	BattleAreaPtr->ClearStage();
}

void BattleLevel::ChangeStage()
{
	BattleAreaPtr->ChangeBackground(MainBackgroundName, BackgroundPivot);
	BattleAreaPtr->ChangeMap(MainStageName);
	BattleAreaPtr->SetCameraLock(MainCamCtrl, CamCorrection);

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

void BattleLevel::MoveCastle()
{
	if (true == IsLevelMove)
	{
		return;
	}

	IsLevelMove = true;
	
	FadeActorPtr->SetWaitTime(0.0f);
	FadeActorPtr->SetSpeed(1.5f);
	FadeActorPtr->FadeIn([this]()
		{
			GameEngineTime::GlobalTime.SetAllUpdateOrderTimeScale(1.0f);
			GameEngineTime::GlobalTime.SetAllRenderOrderTimeScale(1.0f);

			GameEngineCore::ChangeLevel("Castle");
			IsLevelMove = false;
			ResultUIPtr->Off();
		});
}
