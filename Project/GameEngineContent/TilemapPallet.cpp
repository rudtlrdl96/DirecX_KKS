#include "PrecompileHeader.h"
#include "TilemapPallet.h"
#include <GameEngineCore/GameEngineLevel.h>

#include "ContentDatabase.h"
#include "MouseCursorFollowTex.h"
#include "TilemapData.h"

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
	const TilemapData& TileDataRef = ContentDatabase<TilemapData, TileArea>::GetData(PencleTile);
	CursorActor->SetTexture(TileDataRef.Name);
}


void TilemapPallet::Start()
{
	CursorActor = GetLevel()->CreateActor<MouseCursorFollowTex>();
}

void TilemapPallet::Update(float _DeltaTime)
{
}
