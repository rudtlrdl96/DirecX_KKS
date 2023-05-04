#include "PrecompileHeader.h"
#include "TilemapPallet.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineGUI.h>

#include "ContentDatabase.h"
#include "MouseCursorFollowTex.h"
#include "TilemapData.h"

#include "MapToolGUI.h"

TilemapPallet::TilemapPallet()
{
}

TilemapPallet::~TilemapPallet()
{
}

void TilemapPallet::ShowImGui()
{
}

void TilemapPallet::SetPencleIndex(UINT _Index)
{
	if (nullptr == CursorActor)
	{
		MsgAssert_Rtti<TilemapPallet>(" - 커서가 생성되지 않았습니다");
		return;
	}

	PencleTile = _Index;
	const TilemapData& TileDataRef = ContentDatabase<TilemapData, LevelArea>::GetData(PencleTile);
	CursorActor->SetTexture(TileDataRef.Name);
}


void TilemapPallet::SetActiveCursor(bool _Active)
{
	if (true == _Active)
	{
		CursorActor->On();
	}
	else
	{
		CursorActor->Off();
	}
}
void TilemapPallet::Start()
{
	CursorActor = GetLevel()->CreateActor<MouseCursorFollowTex>();

	MapToolGuiPtr = GameEngineGUI::FindGUIWindowConvert<MapToolGUI>("MapToolGUI");

	if (nullptr == MapToolGuiPtr)
	{
		MsgAssert_Rtti<TilemapPallet>(" - 맵툴 Gui가 생성되지 않았습니다.");
	}
}

void TilemapPallet::Update(float _DeltaTime)
{
	PencleTile = MapToolGuiPtr->GetSelectTileIndex();
	const TilemapData& TileDataRef = ContentDatabase<TilemapData, LevelArea>::GetData(PencleTile);
	CursorActor->SetTexture(TileDataRef.Name);
}
