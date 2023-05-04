#pragma once
#include "BaseContentActor.h"

class Tilemap_Meta
{
public:
	float Left = 0.0f;
	float Right = 0.0f;
	float Top = 0.0f;
	float Bottom = 0.0f;
};

class Tilemap : public BaseContentActor
{
public:
	Tilemap();
	~Tilemap();

	Tilemap(const Tilemap& _Other) = delete;
	Tilemap(Tilemap&& _Other) noexcept = delete;
	Tilemap& operator=(const Tilemap& _Other) = delete;
	Tilemap& operator=(Tilemap&& _Other) noexcept = delete;
	
	void ResizeTilemap(UINT _SizeX, UINT _SizeY, int _Depth);

	void ChangeData(int _Depth, const float4& _WorldPos, UINT Index);
	void ChangeData(int _Depth, UINT _X, UINT _Y, UINT Index);
	void ChangeData(int _Depth, UINT _StartX, UINT _EndX, UINT _StartY, UINT _EndY,  size_t Index);
	void ChangeData(int _Depth, UINT _StartX, UINT _StartY, const std::vector<std::vector<size_t>>& _Indexs);

	void ClearTileMap();

	bool IsOver(int _Depth, UINT _X, UINT _Y);

	int2 GetTileIndex(const float4& _WorldPos);
	float4 GetTilePos(UINT _X, UINT _Y) const;

	inline UINT SizeX(int _Depth)
	{
		return TilemapSizeDatas[_Depth].x;
	}
	
	inline UINT SizeY(int _Depth)
	{
		return TilemapSizeDatas[_Depth].y;
	}

	inline int2 GetSize(int _Depth)
	{
		return int2(SizeX(_Depth), SizeY(_Depth));
	}

	Tilemap_Meta GetTilemap_DESC(int _Depth);

	void SaveBin(GameEngineSerializer& _SaveSerializer);
	void LoadBin(GameEngineSerializer& _LoadSerializer);

protected:
	
private:
	std::map<int, std::vector<std::vector<std::shared_ptr<class TileActor>>>> TilemapDatas;
	std::map<int, int2> MemorySizeDatas;
	std::map<int, int2> TilemapSizeDatas;

	float4 TileScale = float4::Zero;

	void CreateTile(int _Depth, UINT _X, UINT _Y);
};