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

	void HitPlayer(float _Damage, const float4& _HitForce);

protected:	
	void Start() override;
	void Update(float _DeltaTime);

	void LevelChangeEnd() override;

private:
	float SwitchCoolTime = 5.0f;
	float SwitchCoolEndTime = 5.0f;

	float MeleeAttack = 25.0f;
	float MagicAttack = 25.0f;
	float HP = 100.0f;
	
	float HitWaitTime = 0.0f;

	std::shared_ptr<class PlayerHitFade> HitFade = nullptr;

	std::shared_ptr<class BaseQuintessence> Quintessence = nullptr;
	std::shared_ptr<class GameEngineCollision> PlayerBodyCol = nullptr;
	std::shared_ptr<class PlayerStateFrame> StateFrame = nullptr;

	std::shared_ptr<PlayerBaseSkull> MainSkull = nullptr;
	std::shared_ptr<PlayerBaseSkull> SubSkull = nullptr;

	std::shared_ptr<PlayerBaseSkull> CreateNewSkull(size_t _Index);

	void CreateColDebugRender();
};

