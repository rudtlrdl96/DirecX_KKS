#include "PrecompileHeader.h"
#include "TilemapOutlineRenderActor.h"

TilemapOutlineRenderActor::TilemapOutlineRenderActor()
{
}

TilemapOutlineRenderActor::~TilemapOutlineRenderActor()
{
}

void TilemapOutlineRenderActor::SetSize(const float4& _Size)
{
	Render->GetTransform()->SetWorldScale(_Size);

	float4 CenterPos = _Size.half();

	CenterPos.x -= ContentConst::TileSize.hx();
	CenterPos.y -= ContentConst::TileSize.y;

	GetTransform()->SetWorldPosition(CenterPos);
}

void TilemapOutlineRenderActor::Start()
{
	Render = CreateComponent<GameEngineSpriteRenderer>();
	Render->SetTexture("Debug_1_MapToolEmpty.png");
}
