#include "PrecompileHeader.h"
#include "TilemapDebugActor.h"

TilemapDebugActor::TilemapDebugActor()
{
}

TilemapDebugActor::~TilemapDebugActor()
{
}

void TilemapDebugActor::Start()
{
	if (nullptr == GameEngineSprite::Find(""))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BoxCol.png").GetFullPath(), 1, 1);

	}

	TilemapRender = CreateComponent<GameEngineTileMapRenderer>();

	TilemapRender->CreateTileMap(10, 10, float4(64, 64, 1));

	float4 TilemapCount = TilemapRender->GetCount();

	for (int y = 0; y < TilemapCount.iy(); y++)
	{
		for (int x = 0; x < TilemapCount.ix(); x++)
		{
			TilemapRender->SetTile(x, y, "BoxCol.png", 0);
		}
	}

}
