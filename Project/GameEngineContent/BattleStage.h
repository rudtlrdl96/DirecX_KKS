#pragma once
#include "BaseContentActor.h"

class BattleStage : public BaseContentActor
{
public:
	BattleStage();
	~BattleStage();

	BattleStage(const BattleStage& _Other) = delete;
	BattleStage(BattleStage&& _Other) noexcept = delete;
	BattleStage& operator=(const BattleStage& _Other) = delete;
	BattleStage& operator=(BattleStage&& _Other) noexcept = delete;

	void Init(GameEngineSerializer& _LoadSerializer);
	
	class TilemapMetaData GetTilemapMetaData() const;

	float4 GetSpawnPoint() const;

protected:
	void Start() override;
	
private:
	std::shared_ptr<class Tilemap> TilemapPtr = nullptr;
	std::shared_ptr<class ObjectManager> ObjectManagerPtr = nullptr;
	std::shared_ptr<class GameEventManager> EventManagerPtr = nullptr;
	std::shared_ptr<class ParticleManager> ParticleMgrPtr = nullptr;
};

