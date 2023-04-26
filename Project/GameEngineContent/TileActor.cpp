#include "PrecompileHeader.h"
#include "TileActor.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

TileActor::TileActor()
{
}

TileActor::~TileActor()
{
}

void TileActor::SetTileData(const TilemapData& _Data)
{
	Data = _Data;

	//if (0 == Data.Index)
	//{
	//	DrawRender->Off();
	//	Off();
	//	return;
	//}

	DrawRender->GetTransform()->SetLocalPosition({0, -ContentConst::TileSize.hy()});
	DrawRender->SetTexture(Data.Name);
	DrawRender->On();
}

void TileActor::Start()
{
	DrawRender = CreateComponent<GameEngineSpriteRenderer>();
	DrawRender->GetTransform()->SetLocalScale(ContentConst::TileSize);	
	DrawRender->Off();
}