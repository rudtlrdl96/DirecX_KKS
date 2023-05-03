#pragma once
#include "BaseContentActor.h"

class TilemapPallet : public BaseContentActor
{
public:
	TilemapPallet();
	~TilemapPallet();

	TilemapPallet(const TilemapPallet& _Other) = delete;
	TilemapPallet(TilemapPallet&& _Other) noexcept = delete;
	TilemapPallet& operator=(const TilemapPallet& _Other) = delete;
	TilemapPallet& operator=(TilemapPallet&& _Other) noexcept = delete;

	void ShowImGui();
	void SetPencleIndex(UINT _Index);

	inline UINT GetPencleIndex() const
	{
		return PencleTile;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	UINT PencleTile = 0;

	std::shared_ptr<class MouseCursorFollowTex> CursorActor = nullptr;
};

