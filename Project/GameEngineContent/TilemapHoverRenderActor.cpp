#include "PrecompileHeader.h"
#include "TilemapHoverRenderActor.h"

TilemapHoverRenderActor::TilemapHoverRenderActor()
{
}

TilemapHoverRenderActor::~TilemapHoverRenderActor()
{
}

void TilemapHoverRenderActor::HoverOn()
{
	TilemapHoverRender->On();
	On();
}

void TilemapHoverRenderActor::HoverOff()
{
	Off();
	TilemapHoverRender->Off();
}

void TilemapHoverRenderActor::Start()
{
	TilemapHoverRender = CreateComponent<GameEngineSpriteRenderer>();
	TilemapHoverRender->SetTexture("Debug_2_MapToolHover.png");
	TilemapHoverRender->GetTransform()->SetLocalScale(ContentConst::TileSize);
	TilemapHoverRender->GetTransform()->SetLocalPosition(float4(0, -ContentConst::TileSize.hy(), 0, 1));
}
