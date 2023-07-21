#include "PrecompileHeader.h"
#include "CastleLevel.h"
#include <GameEngineCore/GameEngineTexture.h>
#include "MultiBackground.h"
#include "Inventory.h"
#include "PlayerState.h"
#include "ResultInfo.h"

CastleLevel::CastleLevel()
{
}

CastleLevel::~CastleLevel()
{
}

void CastleLevel::Start()
{
	BattleLevel::Start();

	BgmName = "DemonCastle.wav";

	GameEngineDirectory DirectoryPath;
	DirectoryPath.MoveParentToDirectory("Resources");
	DirectoryPath.Move("Resources");
	DirectoryPath.Move("Data");
	DirectoryPath.Move("2_Castle");

	{
		DirectoryPath.Move("Background");
		BattleAreaPtr->LoadBackground(DirectoryPath, "DB_Castle_Background");
		DirectoryPath.MoveParent();
	}

	{
		DirectoryPath.Move("Map");
		BattleAreaPtr->LoadMap(DirectoryPath, "DB_Castle_Map");
		DirectoryPath.MoveParent();
	}

	StageNameInfos.reserve(1);
	StageNameInfos.push_back({ "DB_Castle_Map", "DB_Castle_Background" });

	CurStageIndex = 0;
	MainStageName = StageNameInfos[CurStageIndex].LoadMapName;
	MainBackgroundName = StageNameInfos[CurStageIndex].LoadBackgroundName;

	AddEvent("CastleInCameraLock", -1, [this]()
		{
			MainCamCtrl.SetMinHeight(64);
			MainCamCtrl.SetMaxHeight(64 + GameEngineWindow::GetScreenSize().y);
		});

	AddEvent("CastleOutCameraLock", -1, [this]()
		{
			MainCamCtrl.SetMinHeight(-3800);
		});
}

void CastleLevel::Update(float _DeltaTime)
{
	BattleLevel::Update(_DeltaTime);
}

void CastleLevel::LevelChangeStart()
{
	Inventory::ResetSkull();
	Inventory::GoodsReset();
	Inventory::ItemReset();

	ResultInfo::ResultReset();
	PlayerState::SetHP(PlayerState::GetMaxHP() + Inventory::GetMaxHP());

	BattleLevel::LevelChangeStart();

	CallEvent("CastleReborn");
	CallEvent("GoodsUIOff");
	CallEvent("MinimapOff");

	MainCamCtrl.SetMinHeight(64);
	MainCamCtrl.SetMaxHeight(64 + GameEngineWindow::GetScreenSize().y);

	MainCamCtrl.SetMaxWidth(D3D11_FLOAT32_MAX);

}

void CastleLevel::AreaClear()
{
	MoveLevel("ForestOfHarmony");
}
