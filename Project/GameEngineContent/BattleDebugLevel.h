#pragma once
#include "ContentLevel.h"

class BattleDebugLevel : public ContentLevel
{
public:
	BattleDebugLevel();
	~BattleDebugLevel();

	BattleDebugLevel(const BattleDebugLevel& _Other) = delete;
	BattleDebugLevel(BattleDebugLevel&& _Other) noexcept = delete;
	BattleDebugLevel& operator=(const BattleDebugLevel& _Other) = delete;
	BattleDebugLevel& operator=(BattleDebugLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class MultiBackground> DebugBackground = nullptr;
	std::shared_ptr<class Tilemap> DebugTilemap = nullptr;
	std::shared_ptr<class DebugSpriteActor> DeubgActor = nullptr;

	float CameraSpeed = 300.0f;
};

