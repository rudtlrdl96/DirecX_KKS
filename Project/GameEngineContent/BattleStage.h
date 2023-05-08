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

protected:
	void Start() override;
	
private:
	std::shared_ptr<class Tilemap> TilemapPtr = nullptr;
	std::shared_ptr<class ObjectManager> ObjectManagerPtr = nullptr;
};

