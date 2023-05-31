#pragma once
#include "BaseContentActor.h"
#include "BaseDoor.h"

class GameEventManager : public BaseContentActor
{
	enum class ClearDoorType
	{
		SingleDoor,
		DoubleDoor,
	};

public:
	GameEventManager();
	~GameEventManager();

	GameEventManager(const GameEventManager& _Other) = delete;
	GameEventManager(GameEventManager&& _Other) noexcept = delete;
	GameEventManager& operator=(const GameEventManager& _Other) = delete;
	GameEventManager& operator=(GameEventManager&& _Other) noexcept = delete;

	void SaveBin(GameEngineSerializer& _SaveSerializer);
	void LoadBin(GameEngineSerializer& _LoadSerializer);

	void ShowGUI() override;

	inline float4 GetSpawnPoint() const
	{
		return SpawnPoint;
	}

	void DoorActive();
	void DoorDisable();

	void SetDoorLevel(std::shared_ptr<class BattleLevel> _Level);

protected:
	void Start() override;
	
private:
	float4 SpawnPoint = float4::Zero;
	float4 DoorPoint = float4::Zero;
		
	LevelArea DoorArea = LevelArea::None;
	ClearDoorType DType = ClearDoorType::SingleDoor;

	std::shared_ptr<class BaseDoor> FirstDoorActor = nullptr;
	std::shared_ptr<class BaseDoor> SecondDoorActor = nullptr;

	std::shared_ptr<ContentSpriteRenderer> ClearBackRender = nullptr;
	ColorBuffer ClearBackBuffer;

	// ImGui
	const char* DoorComboText[2] = { "Single" ,"Double" };
	const char* AreaComboText[7] = { "None" ,"Opening", "Castle", "ForestOfHarmony", "GrandHall", "HolyCourtyard", "Shop" };

	void SetClearDoorType(ClearDoorType _Type);
	void SetDoorType(DoorType _FirstType, DoorType _SecondType);
};

