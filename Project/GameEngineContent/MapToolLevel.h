#pragma once
#include "ContentLevel.h"

class MapToolLevel : public ContentLevel
{
public:
	enum class MapToolState
	{
		Tilemap,
		SObject,
		BObject,
		Platform,
		Event,
		Particle,
		Light,
		Monster
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

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	std::shared_ptr<class Tilemap> TilemapPtr = nullptr;
	std::shared_ptr<class ObjectManager> ObjectMgrPtr = nullptr;
	std::shared_ptr<class GameEventManager> EventMgrPtr = nullptr;
	std::shared_ptr<class ParticleManager> ParticleMgrPtr = nullptr;

	std::shared_ptr<class TilemapPallet> TilePalletPtr = nullptr;
	std::shared_ptr<class MapToolGUI> MapToolGuiPtr = nullptr;
	std::shared_ptr<class GameEngineActorGUI> ActorGUIPtr = nullptr;

	std::shared_ptr<class TilemapHoverRenderActor> TilemapHoverPtr = nullptr;
	std::shared_ptr<class TilemapOutlineRenderActor> TilemapOutLinePtr = nullptr;
	
	std::shared_ptr<class PlayerSpawnPointRenderer> PlayerSpawnRender = nullptr;

	MapToolState MapToolType = MapToolState::Tilemap;

	float CameraSpeed = 500.0f;

	void Save();
	void Load();

	void CameraMoveFunction(float _DeltaTime);

	void Update_Tilemap(float _DeltaTime);
	void Update_SObject(float _DeltaTime);
	void Update_BObject(float _DeltaTime);
	void Update_Platfrom(float _DeltaTime);
	void Update_Event(float _DeltaTime);
	void Update_Particle(float _DeltaTime);


};