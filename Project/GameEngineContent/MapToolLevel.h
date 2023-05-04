#pragma once
#include "ContentLevel.h"

class MapToolLevel : public ContentLevel
{
public:
	enum class MapToolState
	{
		Tilemap,
		Object,
		Light
	};
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

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	std::shared_ptr<class Tilemap> TilemapPtr = nullptr;
	std::shared_ptr<class ObjectManager> ObjectMgr = nullptr;

	std::shared_ptr<class TilemapPallet> TilemapPalletPtr = nullptr;
	std::shared_ptr<class MapToolGUI> MapToolGuiPtr = nullptr;
	std::shared_ptr<class GameEngineActorGUI> ActorGUI = nullptr;

	std::shared_ptr<class TilemapHoverRenderActor> TilemapHoverPtr = nullptr;
		
	MapToolState MapToolType = MapToolState::Tilemap;

	UINT SelectIndex = 0;
	float CameraSpeed = 500.0f;

	void CameraMoveFunction(float _DeltaTime);
};