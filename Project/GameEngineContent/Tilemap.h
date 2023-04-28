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
	
	void ResizeTilemap(size_t _SizeX, size_t _SizeY, int _Depth);

	void ChangeData(int _Depth, UINT _X, UINT _Y, size_t Index);
	void ChangeData(int _Depth, UINT _StartX, UINT _EndX, UINT _StartY, UINT _EndY,  size_t Index);
	void ChangeData(int _Depth, UINT _StartX, UINT _StartY, const std::vector<std::vector<size_t>>& _Indexs);

	bool IsOver(int _Depth, UINT _X, UINT _Y);

	float4 GetTilePos(UINT _X, UINT _Y) const;

	size_t SizeX(int _Depth)
	{
		return TilemapSizeDatas[_Depth].x;
	}
	
	size_t SizeY(int _Depth)
	{
		return TilemapSizeDatas[_Depth].y;
	}

	Tilemap_Meta GetTilemap_DESC(int _Depth);

	// void CopyData(....);
	void SaveBin(GameEngineSerializer& _SaveSerializer);
	void LoadBin(GameEngineSerializer& _LoadSerializer);

protected:
	
private:
	std::map<int, std::vector<std::vector<std::shared_ptr<class TileActor>>>> TilemapDatas;
	std::map<int, int2> TilemapSizeDatas;

	float4 TileSize = float4::Zero;
	float4 TilemapStartPos = float4::Zero;
};