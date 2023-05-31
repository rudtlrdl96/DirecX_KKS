#pragma once
#include "BaseContentActor.h"

enum class DoorType
{
	Broken,
	Normal,
	Equip,
	Skull,
	Shop,
	MiddleBoss,
	BossInter,
	MainBoss,
};

class BaseDoor : public BaseContentActor
{
public:
	BaseDoor();
	~BaseDoor();

	BaseDoor(const BaseDoor& _Other) = delete;
	BaseDoor(BaseDoor&& _Other) noexcept = delete;
	BaseDoor& operator=(const BaseDoor& _Other) = delete;
	BaseDoor& operator=(BaseDoor&& _Other) noexcept = delete;

	inline void SetBattleLevel(std::shared_ptr<class BattleLevel> _LevelPtr)
	{
		LevelPtr = _LevelPtr;
	}

	void SetSprite(const std::string_view& _ActiveSprite, const std::string_view& _DisableSprite);
	void SetDoorType(LevelArea _Area, DoorType _Type);

	void ActiveOn();
	void ActiveOff();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
		
private:
	std::shared_ptr<ContentSpriteRenderer> DoorRender = nullptr;
	ColorBuffer Buffer;

	LevelArea Area = LevelArea::None;
	DoorType Type = DoorType::Broken;

	std::shared_ptr<class BattleLevel> LevelPtr = nullptr;
	std::shared_ptr<class GameEngineCollision> DoorCollision = nullptr;

	std::string ActiveSpriteName = "";
	std::string DisableSpriteName = "";

	bool IsActiveDoor = false;
};

