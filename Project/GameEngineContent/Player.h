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

	void Death() override;

	void SetInventoryData();
	void InsertNewSkull(UINT _SkullIndex);
	void ForceSwapSkull();

	inline float GetMeleeAttack() const
	{
		return MeleeAttack;
	}

	inline float GetMagicAttack() const
	{
		return MagicAttack;
	}

	inline void AddJumpDir(const float4& _Dir)
	{
		MainSkull->JumpDir += _Dir;
	}

	void HitPlayer(float _Damage, const float4& _HitForce);

	void PushPlayer(const float4& _HitForce);

	bool CheckFall() const
	{
		return 0 > MainSkull->JumpDir.y;
	}

	inline float GetThornHitCoolTime() const
	{
		return MainSkull->ThornWaitTime;
	}

	inline void SetThornHitCoolTime(float _CoolTime)
	{
		MainSkull->ThornWaitTime = _CoolTime;
	}

	void InputLock();
	void InputUnlock();

	inline bool IsInputLock() const
	{
		return IsInputLockValue;
	}

	inline ActorViewDir GetViewDir() const
	{
		return MainSkull->GetViewDir();
	}

	void ActivePlayerFrame();
	void DisablePlayerFrame();

	void PlayStoryMove(const float4& _StoryMovePos, std::function<void()> _EndCallback);

protected:	
	void Start() override;
	void Update(float _DeltaTime);

	void LevelChangeEnd() override;

private:
	float SwitchCoolTime = 5.0f;
	float SwitchCoolEndTime = 5.0f;

	float MeleeAttack = 1000.0f;
	float MagicAttack = 1000.0f;
	float HP = 100.0f;
	
	float HitWaitTime = 0.0f;

	bool IsInputLockValue = false;

	std::shared_ptr<class PlayerHitFade> HitFade = nullptr;

	std::shared_ptr<class BaseQuintessence> Quintessence = nullptr;
	std::shared_ptr<class GameEngineCollision> PlayerBodyCol = nullptr;
	std::shared_ptr<class PlayerStateFrame> StateFrame = nullptr;

	std::shared_ptr<PlayerBaseSkull> MainSkull = nullptr;
	std::shared_ptr<PlayerBaseSkull> SubSkull = nullptr;

	std::shared_ptr<PlayerBaseSkull> CreateNewSkull(size_t _Index);

	void CreateColDebugRender();
};

