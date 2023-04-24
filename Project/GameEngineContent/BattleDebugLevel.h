#pragma once
#include "BaseDebugLevel.h"

class BattleDebugLevel : public BaseDebugLevel
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
	std::shared_ptr<class Tilemap> DebugTilemap = nullptr;

	float CameraSpeed = 300.0f;
};

