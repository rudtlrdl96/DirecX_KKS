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
		Path.Move("DebugTex");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("TilemapDebugTex_Red.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("TilemapDebugTex_Green.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("TilemapDebugTex_Magenta.png").GetFullPath(), 1, 1);
	}

	TilemapRender = CreateComponent<GameEngineTileMapRenderer>();

	TilemapRender->CreateTileMap(10, 10, float4(64, 64, 1));

	float4 TilemapCount = TilemapRender->GetCount();

	for (int y = 0; y < TilemapCount.iy(); y++)
	{
		for (int x = 0; x < TilemapCount.ix(); x++)
		{
			TilemapRender->SetTile(x, y, "TilemapDebugTex_Red.png", 0);
		}
	}

	TilemapRender->SetTile(0, 0, "TilemapDebugTex_Green.png", 0);
	TilemapRender->SetTile(3, 5, "TilemapDebugTex_Green.png", 0);
	TilemapRender->SetTile(8, 2, "TilemapDebugTex_Magenta.png", 0);
	TilemapRender->SetTile(2, 8, "TilemapDebugTex_Magenta.png", 0);
}
