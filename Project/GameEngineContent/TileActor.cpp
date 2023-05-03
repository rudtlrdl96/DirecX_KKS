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
	_SaveSerializer.Write(&Data.Index, sizeof(UINT));
}

UINT TileActor::LoadBin(GameEngineSerializer& _LoadSerializer)
{
	UINT LoadIndex = 0;
	_LoadSerializer.Write(&LoadIndex, sizeof(UINT));
	return LoadIndex;
}

void TileActor::Start()
{
	DrawRender = CreateComponent<GameEngineSpriteRenderer>();

	DrawRender->SetPipeLine("2DTexture_ColorLight");
	DrawRender->GetShaderResHelper().SetConstantBufferLink("OutPixelColor", TileColor);
	DrawRender->GetTransform()->SetLocalScale(ContentConst::TileSize);	
	DrawRender->GetTransform()->SetLocalPosition({ 0, -ContentConst::TileSize.hy(), 0, 0 });
	DrawRender->Off();
}