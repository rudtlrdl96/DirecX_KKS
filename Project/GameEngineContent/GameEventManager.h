#pragma once
#include "BaseContentActor.h"
#include "BaseDoor.h"

class GameEventManager : public BaseContentActor
{
private:
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

	inline float4 GetDoorPoint() const
	{
		return DoorPoint;
	}

	void DoorActive();
	void DoorDisable();

	void SetDoorLevel(std::shared_ptr<class BattleLevel> _Level);

	inline void SetFiretDoorType(DoorType _Type)
	{
		FirestDoorType = _Type;
		FirstDoorActor->SetDoorType(DoorArea, FirestDoorType);
	}

	inline void SetSecondDoorType(DoorType _Type)
	{
		SecondDoorType = _Type;
		SecondDoorActor->SetDoorType(DoorArea, SecondDoorType);
	}

protected:
	void Start() override;
	
private:	
	// Player
	float4 SpawnPoint = float4::Zero;
	
	// Door
	float4 DoorPoint = float4::Zero;
		
	LevelArea DoorArea = LevelArea::None;
	ClearDoorType DType = ClearDoorType::SingleDoor;

	DoorType FirestDoorType = DoorType::Normal;
	DoorType SecondDoorType = DoorType::Normal;

	std::shared_ptr<class BaseDoor> FirstDoorActor = nullptr;
	std::shared_ptr<class BaseDoor> SecondDoorActor = nullptr;

	std::shared_ptr<ContentSpriteRenderer> ClearBackRender = nullptr;
	ColorBuffer ClearBackBuffer;

	// Event

	std::vector<std::shared_ptr<class EventActor>> EventActors;

	// ImGui
	const char* DoorComboText[2] = { "Single" ,"Double" };
	const char* AreaComboText[7] = { "None" ,"Opening", "Castle", "ForestOfHarmony", "GrandHall", "HolyCourtyard", "Shop" };

	std::shared_ptr<class ScaleDebugRender> GUI_EventColRender = nullptr;

	int GUI_SelectEvent = 0;

	void SetClearDoorType(ClearDoorType _Type);
	void SetDoorType(DoorType _FirstType, DoorType _SecondType);
};

