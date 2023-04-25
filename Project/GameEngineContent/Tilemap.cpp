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

	TileSize.x = static_cast<int>(_SizeX);
	TileSize.y = static_cast<int>(_SizeY);

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
			TilemapRef[y][x]->GetTransform()->SetParent(GetTransform());
			TilemapRef[y][x]->GetTransform()->SetLocalPosition(GetTilePos(x, y));
			TilemapRef[y][x]->SetTileData(1);
		}
	}
}

void Tilemap::ChangeData(int _Depth, UINT _X, UINT _Y, size_t Index)
{
	std::vector<std::vector<std::shared_ptr<TileActor>>>& TilemapRef = TilemapDatas[_Depth];
	
	if (true == IsOver(_Depth, _X, _Y))
	{
		MsgAssert("타일맵 인덱스를 초과해 데이터를 변경하려 했습니다");
		return;
	}

	TilemapRef[_Y][_X]->SetTileData(Index);
}

void Tilemap::ChangeData(int _Depth, UINT _StartX, UINT _EndX, UINT _StartY, UINT _EndY, size_t Index)
{
	std::vector<std::vector<std::shared_ptr<TileActor>>>& TilemapRef = TilemapDatas[_Depth];

	if (true == IsOver(_Depth, _StartX, _StartY))
	{
		MsgAssert("타일맵 인덱스를 초과해 데이터를 변경하려 했습니다");
		return;
	}

	if (true == IsOver(_Depth, _EndX, _EndY))
	{
		MsgAssert("타일맵 인덱스를 초과해 데이터를 변경하려 했습니다");
		return;
	}

	for (UINT y = _StartY; y <= _EndY; y++)
	{
		for (UINT x = _StartX; x <= _EndX; x++)
		{
			TilemapRef[y][x]->SetTileData(Index);
		}
	}
}

void Tilemap::ChangeData(int _Depth, UINT _StartX, UINT _StartY, const std::vector<std::vector<size_t>>& _Indexs)
{
	std::vector<std::vector<std::shared_ptr<TileActor>>>& TilemapRef = TilemapDatas[_Depth];

	if (_Indexs.size() == 0)
	{
		return;
	}

	if (_Indexs[0].size() == 0)
	{
		return;
	}

	if (true == IsOver(_Depth, _StartX, _StartY))
	{
		MsgAssert("타일맵 인덱스를 초과해 데이터를 변경하려 했습니다");
		return;
	}

	for (UINT y = 0; y < _Indexs.size(); y++)
	{
		if (true == IsOver(_Depth, _StartX + static_cast<UINT>(_Indexs[y].size()), _StartY + y))
		{
			MsgAssert("타일맵 인덱스를 초과해 데이터를 변경하려 했습니다");
			return;
		}

		for (UINT x = 0; x < _Indexs[y].size(); x++)
		{
			TilemapRef[_StartY + y][_StartX + x]->SetTileData(_Indexs[y][x]);
		}
	}
}

bool Tilemap::IsOver(int _Depth, UINT _X, UINT _Y)
{
	int2& TileSize = TilemapSizeDatas[_Depth];

	if (TileSize.x <= static_cast<int>(_X) || TileSize.y <= static_cast<int>(_Y))
	{
		return true;
	}

	return false;
}

float4 Tilemap::GetTilePos(UINT _X, UINT _Y) const
{
	return TilemapStartPos + float4(static_cast<float>(_X), static_cast<float>(_Y), 0, 0) * TileSize;
}
