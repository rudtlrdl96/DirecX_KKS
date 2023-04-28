#pragma once
#include "BaseContentActor.h"
#include "TilemapData.h"

class TileActor : public BaseContentActor
{
public:
	TileActor();
	~TileActor();

	TileActor(const TileActor& _Other) = delete;
	TileActor(TileActor&& _Other) noexcept = delete;
	TileActor& operator=(const TileActor& _Other) = delete;
	TileActor& operator=(TileActor&& _Other) noexcept = delete;

	inline void SetTileData(size_t _Index)
	{
		SetTileData(ContentDatabase<TilemapData, TileArea>::GetData(_Index));
	}

	void SetTileData(const TilemapData& _Data);

	void SaveBin(GameEngineSerializer& _SaveSerializer) const;
	static size_t LoadBin(GameEngineSerializer& _LoadSerializer);

protected:
	void Start() override;

private:
	int2 TileIndex = int2::Zero;
	TilemapData Data = TilemapData();
	std::shared_ptr<class GameEngineSpriteRenderer> DrawRender = nullptr;

};

