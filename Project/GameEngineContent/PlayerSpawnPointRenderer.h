#pragma once
#include "BaseContentActor.h"

class PlayerSpawnPointRenderer : public BaseContentActor
{
public:
	PlayerSpawnPointRenderer();
	~PlayerSpawnPointRenderer();

	PlayerSpawnPointRenderer(const PlayerSpawnPointRenderer& _Other) = delete;
	PlayerSpawnPointRenderer(PlayerSpawnPointRenderer&& _Other) noexcept = delete;
	PlayerSpawnPointRenderer& operator=(const PlayerSpawnPointRenderer& _Other) = delete;
	PlayerSpawnPointRenderer& operator=(PlayerSpawnPointRenderer&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> SpawnRender = nullptr;

};

