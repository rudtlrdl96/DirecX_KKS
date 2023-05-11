#pragma once
#include "BaseContentActor.h"
#include "TileMetaData.h"

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
		SetTileData(ContentDatabase<TileMetaData, LevelArea>::GetData(_Index));
	}

	void SetTileData(const TileMetaData& _Data);

	inline UINT GetTileIndex() const
	{
		return Data.Index;
	}

	static void SaveEmptyBin(GameEngineSerializer& _SaveSerializer);
	void SaveBin(GameEngineSerializer& _SaveSerializer) const;
	static UINT LoadBin(GameEngineSerializer& _LoadSerializer);

	void TileOn();
	void TileOff();

protected:
	void Start() override;


private:
	ColorBuffer Buffer;
	float4 TileColor = float4::Zero;

	TileMetaData Data = TileMetaData();
	std::shared_ptr<class GameEngineSpriteRenderer> DrawRender = nullptr;

};

