#pragma once
#include "ContentLevel.h"

class MapToolLevel : public ContentLevel
{
public:
	MapToolLevel();
	~MapToolLevel();

	MapToolLevel(const MapToolLevel& _Other) = delete;
	MapToolLevel(MapToolLevel&& _Other) noexcept = delete;
	MapToolLevel& operator=(const MapToolLevel& _Other) = delete;
	MapToolLevel& operator=(MapToolLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void Save();
	void Load();

private:
	std::shared_ptr<class Tilemap> TilemapPtr = nullptr;
	std::shared_ptr<class ObjectManager> ObjectMgr = nullptr;

	std::shared_ptr<class TilemapPallet> TilemapPalletPtr = nullptr;

	float CameraSpeed = 500.0f;
};