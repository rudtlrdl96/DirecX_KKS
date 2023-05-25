#pragma once
#include "BaseContentActor.h"
#include "PlayerBaseSkull.h"


class Player : public BaseContentActor
{
	friend class PlayerStateFrame;
public:
	Player();
	~Player();

	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	void SetInventoryData();

	inline float GetMeleeAttack() const
	{
		return MeleeAttack;
	}

	inline float GetMagicAttack() const
	{
		return MagicAttack;
	}

protected:	
	void Start() override;
	void Update(float _DeltaTime);

private:
	float SwitchCoolTime = 5.0f;
	float SwitchCoolEndTime = 5.0f;

	float MeleeAttack = 10.0f;
	float MagicAttack = 10.0f;
	float HP = 100.0f;

	std::shared_ptr<class BaseQuintessence> Quintessence = nullptr;
	std::shared_ptr<class GameEngineCollision> PlayerBodyCol = nullptr;
	std::shared_ptr<class PlayerStateFrame> StateFrame = nullptr;

	std::shared_ptr<PlayerBaseSkull> MainSkull = nullptr;
	std::shared_ptr<PlayerBaseSkull> SubSkull = nullptr;

	std::shared_ptr<PlayerBaseSkull> CreateNewSkull(size_t _Index);

	void CreateColDebugRender();
};

