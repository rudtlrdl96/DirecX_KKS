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

void TileActor::SaveBin(GameEngineSerializer& _SaveSerializer) const
{
	_SaveSerializer.Write(&Data.Index, sizeof(size_t));
}

size_t TileActor::LoadBin(GameEngineSerializer& _LoadSerializer)
{
	size_t LoadIndex = 0;
	_LoadSerializer.Write(&LoadIndex, sizeof(size_t));
	return LoadIndex;
}

void TileActor::Start()
{
	DrawRender = CreateComponent<GameEngineSpriteRenderer>();
	DrawRender->GetTransform()->SetLocalScale(ContentConst::TileSize);	
	DrawRender->GetTransform()->SetLocalPosition({ 0, -ContentConst::TileSize.hy(), 0, 0 });
	DrawRender->Off();
}