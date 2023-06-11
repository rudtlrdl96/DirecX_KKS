#include "PrecompileHeader.h"
#include "TileActor.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

TileActor::TileActor()
{
}

TileActor::~TileActor()
{
}

void TileActor::SetTileData(const TileMetaData& _Data)
{
	Data = _Data;

	if (0 == Data.Index)
	{
		TileOff();
		return;
	}

	DrawRender->GetTransform()->SetLocalPosition({ 0, -ContentConst::TileSize.hy() });
	DrawRender->SetTexture(Data.Name);

	TileOn();
}

void TileActor::SaveEmptyBin(GameEngineSerializer& _SaveSerializer)
{
	UINT EmptyIndex = 0;
	_SaveSerializer.Write(&EmptyIndex, sizeof(UINT));
}

void TileActor::SaveBin(GameEngineSerializer& _SaveSerializer) const
{
	_SaveSerializer.Write(&Data.Index, sizeof(UINT));
}

UINT TileActor::LoadBin(GameEngineSerializer& _LoadSerializer)
{
	UINT LoadIndex = 0;
	_LoadSerializer.Read(&LoadIndex, sizeof(UINT));
	return LoadIndex;
}

void TileActor::TileOn()
{
	DrawRender->On();
	On();
}

void TileActor::TileOff()
{
	Off();
	DrawRender->Off();
}

void TileActor::Start()
{
	DrawRender = CreateComponent<ContentSpriteRenderer>();

	DrawRender->PipeSetting("2DTexture_Color");
	DrawRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	DrawRender->GetTransform()->SetLocalScale(ContentConst::TileSize);	
	DrawRender->GetTransform()->SetLocalPosition({ 0, -ContentConst::TileSize.hy(), 0, 0 });
	DrawRender->Off();
}