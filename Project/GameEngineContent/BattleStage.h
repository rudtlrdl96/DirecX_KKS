#pragma once
#include "BaseContentActor.h"
#include "StageRewardObject.h"

class BattleStage : public BaseContentActor
{
public:
	static void SetNextReward(RewardType _Reward)
	{
		NextRewardType = _Reward;
	}

private:
	static RewardType NextRewardType;


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

	void StageReset();
	void StagePlay();

	void Destroy() override;

	inline void SetFiretDoorType(DoorType _Type)
	{
		EventManagerPtr->SetFiretDoorType(_Type);
	}

	inline void SetSecondDoorType(DoorType _Type)
	{
		EventManagerPtr->SetSecondDoorType(_Type);
	}

	inline void StageRewardOn()
	{
		IsNoneReward = false;
	}

	inline void StageRewardOff()
	{
		IsNoneReward = true;
	}


protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	
private:
	std::shared_ptr<class Tilemap> TilemapPtr = nullptr;
	std::shared_ptr<class ObjectManager> ObjectManagerPtr = nullptr;
	std::shared_ptr<class GameEventManager> EventManagerPtr = nullptr;
	std::shared_ptr<class ParticleManager> ParticleMgrPtr = nullptr;
	std::shared_ptr<class MonsterManager> MonsterMgrPtr = nullptr;
	std::shared_ptr<class NPCManager> NPCMgrPtr = nullptr;
	std::shared_ptr<class StageRewardObject> RewardObject = nullptr;

	int LockCount = 0;

	bool IsNoneReward = true;
	bool IsStageReward = false;
	bool IsRewardEnd = false;
};

