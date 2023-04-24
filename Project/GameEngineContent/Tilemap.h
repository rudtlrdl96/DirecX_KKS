#pragma once
#include "BaseContentActor.h"

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
	void ChangeData(int _Depth, UINT _X, UINT _Y, const std::vector<std::vector<size_t>>& _Indexs);

	float4 GetTilePos(UINT _X, UINT _Y) const;

	size_t SizeX(int _Depth)
	{
		return TilemapSizeDatas[_Depth].x;
	}
	
	size_t SizeY(int _Depth)
	{
		return TilemapSizeDatas[_Depth].y;
	}

	// void CopyData(....);

protected:
	
private:
	std::map<int, std::vector<std::vector<std::shared_ptr<class TileActor>>>> TilemapDatas;
	std::map<int, int2> TilemapSizeDatas;

	float4 TileSize = float4::Zero;
	float4 TilemapStartPos = float4::Zero;
};