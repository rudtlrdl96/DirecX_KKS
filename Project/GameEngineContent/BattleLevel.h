#pragma once
#include "ContentLevel.h"

class BattleLevel : public ContentLevel
{
public:
	BattleLevel();
	~BattleLevel();

	BattleLevel(const BattleLevel& _Other) = delete;
	BattleLevel(BattleLevel&& _Other) noexcept = delete;
	BattleLevel& operator=(const BattleLevel& _Other) = delete;
	BattleLevel& operator=(BattleLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	std::shared_ptr<class DebugSpriteActor> DebugActor = nullptr;

	std::shared_ptr<class MultiBackground> MBackgroundPtr;
	std::shared_ptr<class Tilemap> TilemapPtr = nullptr;
	std::shared_ptr<class ObjectManager> ObjectManagerPtr = nullptr;
private:


};

