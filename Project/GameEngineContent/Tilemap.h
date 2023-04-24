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

	void ChangeData(UINT _X, UINT _Y, size_t Index);
	void ChangeData(UINT _StartX, UINT _EndX, UINT _StartY, UINT _EndY,  size_t Index);
	void ChangeData(UINT _X, UINT _Y, const std::vector<std::vector<size_t>>& _Indexs);

	// void CopyData(....);

protected:
	
private:
	std::map<int, std::vector<std::vector<std::shared_ptr<class TileActor>>>> TilemapDatas;

	float4 TilemapStart = float4::Zero;
};