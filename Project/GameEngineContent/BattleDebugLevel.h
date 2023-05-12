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

	void LevelChangeStart() override;
	void LevelChangeEnd() override;

private:
	std::shared_ptr<class MultiBackground> DebugBackground = nullptr;
	std::shared_ptr<class Tilemap> DebugTilemap = nullptr;
	std::shared_ptr<class BoneSkull> DebugSkull = nullptr;
	std::shared_ptr<class ObjectManager> DeubgObject = nullptr;

	std::shared_ptr<class GameEngineActorGUI> GameEngineActorGUIPtr = nullptr;

	float CameraSpeed = 300.0f;
};

