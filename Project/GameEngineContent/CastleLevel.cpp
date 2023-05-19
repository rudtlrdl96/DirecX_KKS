#include "PrecompileHeader.h"
#include "CastleLevel.h"
#include <GameEngineCore/GameEngineTexture.h>
#include "MultiBackground.h"

CastleLevel::CastleLevel()
{
}

CastleLevel::~CastleLevel()
{
}

void CastleLevel::Start()
{
	BattleLevel::Start();

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

	MainStageName = "DB_Castle_Map";
	MainBackgroundName = "DB_Castle_Background";


}

void CastleLevel::Update(float _DeltaTime)
{
	BattleLevel::Update(_DeltaTime);
}

void CastleLevel::LevelChangeStart()
{
	BattleLevel::LevelChangeStart();

	MainCamCtrl.SetMinHeight(128);
	MainCamCtrl.SetMaxHeight(128 + GameEngineWindow::GetScreenSize().y);

	MainCamCtrl.SetMaxWidth(D3D11_FLOAT32_MAX);

}
