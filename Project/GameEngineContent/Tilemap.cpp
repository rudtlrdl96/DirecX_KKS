#include "PrecompileHeader.h"
#include "Tilemap.h"
#include <GameEngineCore/GameEngineLevel.h>
#include "TileActor.h"

Tilemap::Tilemap()
{
}

Tilemap::~Tilemap()
{
}


void Tilemap::ResizeTilemap(size_t _SizeX, size_t _SizeY, int _Depth)
{
	std::vector<std::vector<std::shared_ptr<TileActor>>> TilemapRef = TilemapDatas[_Depth];

	for (size_t y = 0; y < TilemapRef.size(); y++)
	{
		for (size_t x = 0; x < TilemapRef[y].size(); x++)
		{
			TilemapRef[y][x]->Death();
			TilemapRef[y][x] = nullptr;
		}
	}

	TilemapRef.resize(_SizeY);

	for (size_t y = 0; y < TilemapRef.size(); y++)
	{
		TilemapRef[y].resize(_SizeX);

		for (size_t x = 0; x < TilemapRef[y].size(); x++)
		{
			TilemapRef[y][x] = GetLevel()->CreateActor<TileActor>();
		}
	}
}

void Tilemap::ChangeData(UINT _X, UINT _Y, size_t Index)
{

}

void Tilemap::ChangeData(UINT _StartX, UINT _EndX, UINT _StartY, UINT _EndY, size_t Index)
{

}

void Tilemap::ChangeData(UINT _X, UINT _Y, const std::vector<std::vector<size_t>>& _Indexs)
{

}