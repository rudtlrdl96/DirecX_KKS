#include "PrecompileHeader.h"
#include "Tilemap.h"
#include <GameEngineCore/GameEngineLevel.h>
#include "TileActor.h"

Tilemap::Tilemap() :
	TileScale(ContentConst::TileSize)
{
}

Tilemap::~Tilemap()
{
}


void Tilemap::ResizeTilemap(UINT _SizeX, UINT _SizeY, int _Depth)
{
	using namespace std;

	int2& MemorySize = MemorySizeDatas[_Depth];
	int2& TilemapSize = TilemapSizeDatas[_Depth];

	vector<vector<shared_ptr<TileActor>>>& TilemapRef = TilemapDatas[_Depth];
	
	if (MemorySize.y < static_cast<int>(_SizeY))
	{
		TilemapRef.resize(_SizeY);
		MemorySize.y = _SizeY;
	}

	if (MemorySize.x < static_cast<int>(_SizeX))
	{
		for (UINT y = 0; y < TilemapRef.size(); y++)
		{
			TilemapRef[y].resize(_SizeX);
		}

		MemorySize.x = _SizeX;
	}

	for (int y = MemorySize.y; y < TilemapSize.y; y++)
	{
		for (int x = MemorySize.x; x < TilemapSize.x; x++)
		{
			TilemapRef[y][x]->Off();
		}
	}

	TilemapSize.x = _SizeX;
	TilemapSize.y = _SizeY;

	for (int y = 0; y < TilemapSize.y; y++)
	{
		for (int x = 0; x < TilemapSize.x; x++)
		{
			if (nullptr == TilemapRef[y][x])
			{
				CreateTile(_Depth, x, y);
			}
			else
			{
				TilemapRef[y][x]->On();
			}
		}
	}
}

void Tilemap::ChangeData(int _Depth, const float4& _WorldPos, UINT Index)
{
	float4 LocalPos = _WorldPos - GetTransform()->GetWorldPosition();

	LocalPos.x += TileScale.hx();
	LocalPos.y += TileScale.y;

	int2 InputIndex;

	float IndexFloatX = LocalPos.x / TileScale.x;
	float IndexFloatY = LocalPos.y / TileScale.y;

	if (IndexFloatX < 0)
	{
		return;
	}

	if (IndexFloatY < 0)
	{
		return;
	}

	InputIndex.x = static_cast<int>(IndexFloatX);
	InputIndex.y = static_cast<int>(IndexFloatY);

	ChangeData(_Depth, InputIndex.x, InputIndex.y, Index);
}

void Tilemap::ChangeData(int _Depth, UINT _X, UINT _Y, UINT Index)
{
	std::vector<std::vector<std::shared_ptr<TileActor>>>& TilemapRef = TilemapDatas[_Depth];
	
	if (true == IsOver(_Depth, _X, _Y))
	{
		return;
	}

	TilemapRef[_Y][_X]->SetTileData(Index);
}

void Tilemap::ChangeData(int _Depth, UINT _StartX, UINT _EndX, UINT _StartY, UINT _EndY, size_t Index)
{
	std::vector<std::vector<std::shared_ptr<TileActor>>>& TilemapRef = TilemapDatas[_Depth];

	if (true == IsOver(_Depth, _StartX, _StartY))
	{
		return;
	}

	if (true == IsOver(_Depth, _EndX, _EndY))
	{
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
		return;
	}

	for (UINT y = 0; y < _Indexs.size(); y++)
	{
		if (true == IsOver(_Depth, _StartX + static_cast<UINT>(_Indexs[y].size()), _StartY + y))
		{
			return;
		}

		for (UINT x = 0; x < _Indexs[y].size(); x++)
		{
			TilemapRef[_StartY + y][_StartX + x]->SetTileData(_Indexs[y][x]);
		}
	}
}

void Tilemap::ClearTileMap()
{
	using namespace std;

	for (const pair<int, vector<vector<shared_ptr<TileActor>>>>& TilemapRef : TilemapDatas)
	{
		vector<vector<shared_ptr<TileActor>>>& TileRef = TilemapDatas[TilemapRef.first];

		for (size_t y = 0; y < TileRef.size(); y++)
		{
			for (size_t x = 0; x < TileRef[y].size(); x++)
			{
				if (nullptr != TileRef[y][x])
				{
					TileRef[y][x]->Off();
					TileRef[y][x]->Death();
					TileRef[y][x] = nullptr;
				}
			}

			TileRef[y].clear();
		}

		TileRef.clear();
	}

	TilemapDatas.clear();
	TilemapSizeDatas.clear();
	MemorySizeDatas.clear();
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
	return float4(static_cast<float>(_X), static_cast<float>(_Y), 0, 0) * TileScale;
}

Tilemap_Meta Tilemap::GetTilemap_DESC(int _Depth)
{
	int2& TileCount = TilemapSizeDatas[_Depth];

	Tilemap_Meta Result = Tilemap_Meta();

	float4 TilemapPos = GetTransform()->GetWorldPosition();

	TilemapPos.x -= ContentConst::TileSize.hx();
	TilemapPos.y -= ContentConst::TileSize.y;

	Result.Bottom = TilemapPos.y;
	Result.Top	  = TilemapPos.y + (TileCount.y * TileScale.y);
	Result.Left   = TilemapPos.x;
	Result.Right  = TilemapPos.x + (TileCount.x * TileScale.x);

	return Result;
}

void Tilemap::SaveBin(GameEngineSerializer& _SaveSerializer)
{
	_SaveSerializer.Write(static_cast<int>(TilemapDatas.size()));

	using namespace std;

	for (const pair<int, vector<vector<shared_ptr<TileActor>>>>& DepthTilemapRef : TilemapDatas)
	{
		if (TilemapSizeDatas.find(DepthTilemapRef.first) == TilemapSizeDatas.end())
		{
			MsgAssert_Rtti<Tilemap>(" - 타일맵 정보의 크기 데이터가 존재하지 않습니다");
		}


		int2& TilemapSize = TilemapSizeDatas[DepthTilemapRef.first];

		if (0 >= TilemapSize.x)
		{
			MsgAssert_Rtti<Tilemap>(" - X 사이즈가 0인 타일맵은 저장할 수 없습니다");
			return;
		}

		if (0 >= TilemapSize.y)
		{
			MsgAssert_Rtti<Tilemap>(" - Y 사이즈가 0인 타일맵은 저장할 수 없습니다");
			return;
		}

		_SaveSerializer.Write(static_cast<int>(DepthTilemapRef.first));
		_SaveSerializer.Write(static_cast<int>(TilemapSize.x));
		_SaveSerializer.Write(static_cast<int>(TilemapSize.y));

		const vector<vector<shared_ptr<TileActor>>>& TileRef = DepthTilemapRef.second;

		for (int y = 0; y < TilemapSize.y; y++)
		{
			for (int x = 0; x < TilemapSize.x; x++)
			{
				TileRef[y][x]->SaveBin(_SaveSerializer);
			}
		}
	}
}

void Tilemap::LoadBin(GameEngineSerializer& _LoadSerializer)
{
	ClearTileMap();

	int DepthCount = 0;
	_LoadSerializer.Read(DepthCount);

	for (int i = 0; i < DepthCount; i++)
	{
		int Depth = 0;
		_LoadSerializer.Read(Depth);

		int2& SizeRef = TilemapSizeDatas[Depth];

		_LoadSerializer.Read(SizeRef.x);
		_LoadSerializer.Read(SizeRef.y);

		int2& MemoryRef = MemorySizeDatas[Depth];
		MemoryRef = SizeRef;

		ResizeTilemap(SizeRef.x, SizeRef.y, Depth);

		for (int y = 0; y < SizeRef.y; y++)
		{
			for (int x = 0; x < SizeRef.x; x++)
			{
				UINT LoadIndex = TileActor::LoadBin(_LoadSerializer);
				ChangeData(Depth, x, y, LoadIndex);
			}
		}
	}
}

void Tilemap::CreateTile(int _Depth, UINT _X, UINT _Y)
{
	std::shared_ptr<TileActor> NewTile = GetLevel()->CreateActor<TileActor>();

	NewTile->GetTransform()->SetParent(GetTransform());

	float4 TilePos = GetTilePos(_X, _Y);
	TilePos.z = _Depth * 10.0f;

	NewTile->GetTransform()->SetLocalPosition(TilePos);
	NewTile->SetTileData(1);

	TilemapDatas[_Depth][_Y][_X] = NewTile;
}
