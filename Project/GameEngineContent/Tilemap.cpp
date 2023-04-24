#include "PrecompileHeader.h"
#include "Tilemap.h"
#include <GameEngineCore/GameEngineLevel.h>
#include "TileActor.h"

Tilemap::Tilemap() :
	TileSize(ContentConst::TileSize)
{
}

Tilemap::~Tilemap()
{
}


void Tilemap::ResizeTilemap(size_t _SizeX, size_t _SizeY, int _Depth)
{
	std::vector<std::vector<std::shared_ptr<TileActor>>>& TilemapRef = TilemapDatas[_Depth];
	int2& TileSize = TilemapSizeDatas[_Depth];

	TileSize.x = _SizeX;
	TileSize.y = _SizeY;

	for (size_t y = 0; y < TilemapRef.size(); y++)
	{
		for (size_t x = 0; x < TilemapRef[y].size(); x++)
		{
			TilemapRef[y][x]->Death();
			TilemapRef[y][x] = nullptr;
		}
	}

	TilemapRef.resize(_SizeY);

	for (UINT y = 0; y < TilemapRef.size(); y++)
	{
		TilemapRef[y].resize(_SizeX);

		for (UINT x = 0; x < TilemapRef[y].size(); x++)
		{
			TilemapRef[y][x] = GetLevel()->CreateActor<TileActor>();
			TilemapRef[y][x]->GetTransform()->SetLocalPosition(GetTilePos(x, y));
			TilemapRef[y][x]->SetTileData(1);
		}
	}
}

void Tilemap::ChangeData(int _Depth, UINT _X, UINT _Y, size_t Index)
{
	//std::vector<std::vector<std::shared_ptr<TileActor>>>& TilemapRef = TilemapDatas[_Depth];
	//int2& TileSize = TilemapSizeDatas[_Depth];
	//
	//if (TileSize.x >= _X)
	//{
	//	MsgAssert("");
	//}
}

void Tilemap::ChangeData(int _Depth, UINT _StartX, UINT _EndX, UINT _StartY, UINT _EndY, size_t Index)
{

}

void Tilemap::ChangeData(int _Depth, UINT _X, UINT _Y, const std::vector<std::vector<size_t>>& _Indexs)
{

}

float4 Tilemap::GetTilePos(UINT _X, UINT _Y) const
{
	return TilemapStartPos + float4(static_cast<float>(_X), static_cast<float>(_Y), 0, 0) * TileSize;
}
