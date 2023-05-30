#include "PrecompileHeader.h"
#include "BattleLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>

#include "EffectManager.h"
#include "BattleArea.h"
#include "Player.h"

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
	}

	ContentLevel::Start();

	float4 HalfWindowSize = GameEngineWindow::GetScreenSize().half();
	BattleAreaPtr = CreateActor<BattleArea>();
}

void BattleLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::IsDown("LevelMovePrev"))
	{
		MovePrevStage();
	}
	else if (true == GameEngineInput::IsDown("LevelMoveNext"))
	{
		MoveNextStage();
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
	EffectManager::SetLevel(DynamicThis<GameEngineLevel>());

	if (nullptr == MainPlayer)
	{
		MainPlayer = CreateActor<Player>();
		MainPlayer->SetInventoryData();
		MainCamCtrl.SetLookatTarget(MainPlayer);
	}

	ChangeStage();
	MainCamCtrl.ResetScale();

	GameEngineTime::GlobalTime.SetTimeScale(1.0f);
}

void BattleLevel::LevelChangeEnd()
{
	if (nullptr != MainPlayer)
	{
		MainPlayer->Death();
		MainPlayer = nullptr;
		MainCamCtrl.SetLookatTarget(nullptr);
	}

	EffectManager::SetLevel(nullptr);
	GameEngineTime::GlobalTime.SetTimeScale(1.0f);
}

void BattleLevel::ChangeStage()
{
	BattleAreaPtr->ChangeBackground(MainBackgroundName);
	BattleAreaPtr->ChangeMap(MainStageName);
	BattleAreaPtr->SetCameraLock(MainCamCtrl);

	float4 SpawnPos = BattleAreaPtr->GetSpawnPoint();

	SetPlayerPos(SpawnPos);
	MainCamCtrl.SetCameraPos(SpawnPos);
}

void BattleLevel::MovePrevStage()
{
	if (0 < CurStageIndex)
	{
		--CurStageIndex;
	}
	else
	{
		CurStageIndex = 0;
	}

	MainStageName = StageNameInfos[CurStageIndex].LoadMapName;
	MainBackgroundName = StageNameInfos[CurStageIndex].LoadBackgroundName;

	ChangeStage();
}

void BattleLevel::MoveNextStage()
{
	++CurStageIndex;

	if (StageNameInfos.size() <= CurStageIndex)
	{
		AreaClear();
		CurStageIndex = static_cast<UINT>(StageNameInfos.size() - 1);
	}
	else
	{
		MainStageName = StageNameInfos[CurStageIndex].LoadMapName;
		MainBackgroundName = StageNameInfos[CurStageIndex].LoadBackgroundName;
		ChangeStage();
	}
}
