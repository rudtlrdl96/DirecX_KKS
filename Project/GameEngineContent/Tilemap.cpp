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
	int2& TileCount = TilemapSizeDatas[_Depth];

	TileCount.x = static_cast<int>(_SizeX);
	TileCount.y = static_cast<int>(_SizeY);

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

			float4 TilePos = GetTilePos(x, y);
			TilePos.z = _Depth * 100.0f;

			TilemapRef[y][x]->GetTransform()->SetLocalPosition(TilePos);
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
	int2& TileCount = TilemapSizeDatas[_Depth];

	if (TileCount.x <= static_cast<int>(_X) || TileCount.y <= static_cast<int>(_Y))
	{
		return true;
	}

	return false;
}

float4 Tilemap::GetTilePos(UINT _X, UINT _Y) const
{
	return TilemapStartPos + float4(static_cast<float>(_X), static_cast<float>(_Y), 0, 0) * TileSize;
}

Tilemap_Meta Tilemap::GetTilemap_DESC(int _Depth)
{
	int2& TileCount = TilemapSizeDatas[_Depth];

	Tilemap_Meta Result = Tilemap_Meta();

	float4 TilemapPos = TilemapStartPos;

	TilemapPos.x -= ContentConst::TileSize.hx();
	TilemapPos.y -= ContentConst::TileSize.y;

	Result.Bottom = TilemapPos.y;
	Result.Top	  = TilemapPos.y + (TileCount.y * TileSize.y);
	Result.Left   = TilemapPos.x;
	Result.Right  = TilemapPos.x + (TileCount.x * TileSize.x);

	return Result;
}

void Tilemap::SaveBin(GameEngineSerializer& _SaveSerializer)
{
	_SaveSerializer.Write(static_cast<int>(TilemapSizeDatas.size()));

	for (const std::pair<int, int2>& SizeRef : TilemapSizeDatas)
	{
		_SaveSerializer.Write(static_cast<int>(SizeRef.first));
		_SaveSerializer.Write(static_cast<int>(SizeRef.second.x));
		_SaveSerializer.Write(static_cast<int>(SizeRef.second.y));

		std::vector<std::vector<std::shared_ptr<TileActor>>>& DepthTiles = TilemapDatas[SizeRef.first];

		for (size_t y = 0; y < DepthTiles.size(); y++)
		{
			for (size_t x = 0; x < DepthTiles[y].size(); x++)
			{
				DepthTiles[y][x]->SaveBin(_SaveSerializer);
			}
		}
	}
}

void Tilemap::LoadBin(GameEngineSerializer& _LoadSerializer)
{
	int DepthCount = 0;
	_LoadSerializer.Read(DepthCount);

	for (int i = 0; i < DepthCount; i++)
	{
		int Depth = 0;
		_LoadSerializer.Read(Depth);

		int2& SizeRef = TilemapSizeDatas[Depth];

		_LoadSerializer.Read(SizeRef.x);
		_LoadSerializer.Read(SizeRef.y);

		ResizeTilemap(SizeRef.x, SizeRef.y, Depth);

		for (int y = 0; y < SizeRef.y; y++)
		{
			for (int x = 0; x < SizeRef.x; x++)
			{
				size_t LoadIndex = TileActor::LoadBin(_LoadSerializer);
				ChangeData(Depth, x, y, LoadIndex);
			}
		}
	}
}