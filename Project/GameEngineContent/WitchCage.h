#pragma once
#include "BattleActor.h"

class WitchCage : public BattleActor
{
public:
	WitchCage();
	~WitchCage();

	WitchCage(const WitchCage& _Other) = delete;
	WitchCage(WitchCage&& _Other) noexcept = delete;
	WitchCage& operator=(const WitchCage& _Other) = delete;
	WitchCage& operator=(WitchCage&& _Other) noexcept = delete;

	void Reset();

	inline bool IsBroken() const
	{
		return IsBrokenValue;
	}

	inline void SetBrokenCallback(std::function<void()> _Callback)
	{
		BrokenCallback = _Callback;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineCollision> CageCol = nullptr;
	std::shared_ptr<ContentSpriteRenderer> BackCageRender = nullptr;

	ColorBuffer CageRenderBuffer;

	bool IsAllMonsterDeath = false;
	bool IsBrokenValue = false;
	int HitCount = 0;
	float HitCoolTime = 0.0f;

	std::function<void()> BrokenCallback = nullptr;
	std::vector<std::string> DeadPartNames;

	void PlayBrokenParticle();


};

