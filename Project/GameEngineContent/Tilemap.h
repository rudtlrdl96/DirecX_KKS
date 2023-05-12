#pragma once
#include "BaseContentActor.h"
#include "TileMetaData.h"

class TilemapMetaData
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
	
	void SetDepth(UINT _DepthCount);
	void ResizeTilemap(UINT _SizeX, UINT _SizeY);

	void ChangeData(int _Depth, const float4& _WorldPos, UINT Index);
	void ChangeData(int _Depth, UINT _X, UINT _Y, UINT Index);
	void ChangeData(int _Depth, UINT _StartX, UINT _EndX, UINT _StartY, UINT _EndY,  size_t Index);
	void ChangeData(int _Depth, UINT _StartX, UINT _StartY, const std::vector<std::vector<size_t>>& _Indexs);

	void ClearTileMap();

	bool IsOver(UINT _X, UINT _Y);

	int2 GetTileIndex(const float4& _WorldPos);
	float4 GetTilePos(UINT _X, UINT _Y) const;

	inline UINT SizeX() const
	{
		return TilemapSize.x;
	}
	
	inline UINT SizeY() const
	{
		return TilemapSize.y;
	}

	inline int2 GetSize() const
	{
		return TilemapSize;
	}

	inline UINT GetDepthCount() const
	{
		return static_cast<UINT>(TilemapDatas.size());
	}

	inline UINT GetCurDepth() const
	{
		return Gui_TilemapCurDepth;
	}

	TilemapMetaData GetTilemapMetaData();

	void SaveBin(GameEngineSerializer& _SaveSerializer);
	void SaveBin_TileMetaData(TileMetaData _Meta, GameEngineSerializer& _SaveSerializer);

	void LoadBin(GameEngineSerializer& _LoadSerializer);
	TileMetaData LoadBin_TileMetaData(GameEngineSerializer& _SaveSerializer);

	void ShowGUI() override;

protected:
	
private:
	std::vector<std::vector<std::vector<std::shared_ptr<class TileActor>>>> TilemapDatas;
	
	UINT Gui_TilemapCurDepth = 0;
	UINT Gui_TilemapDepthCount = 0;
	int2 Gui_TilemapSize = int2::Zero;

	int2 TilemapSize = int2::Zero;
	float4 TileScale = float4::Zero;

	void CreateTile(UINT _Depth, UINT _X, UINT _Y);
	void ReleseTile(UINT _Depth, UINT _X, UINT _Y);

	void Push_Tilemap_Up(UINT _Depth);
	void Push_Tilemap_Down(UINT _Depth);
	void Push_Tilemap_Left(UINT _Depth);
	void Push_Tilemap_Right(UINT _Depth);
};