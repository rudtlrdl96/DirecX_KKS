#include "PrecompileHeader.h"
#include "TileActor.h"

TileActor::TileActor()
{
}

TileActor::~TileActor()
{
}

void TileActor::SetTileData(const TilemapData& _Data)
{
	Data = _Data;

	DrawRender->GetShaderResHelper().SetConstantBufferLink("DiffuseTex", GameEngineTexture::Find(Data.Name));
	DrawRender->On();
}

void TileActor::Start()
{
	DrawRender = CreateComponent<GameEngineRenderer>();
	DrawRender->GetTransform()->SetLocalScale(ContentConst::TileSize);
	DrawRender->SetPipeLine("2DTexture");
	DrawRender->Off();
}