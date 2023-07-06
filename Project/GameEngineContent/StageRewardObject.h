#pragma once
#include "BaseContentActor.h"

enum class RewardType
{
	None,
	Normal,
	Skull,
	MiddleBoss,
};

class StageRewardObject : public BaseContentActor
{
public:
	StageRewardObject();
	~StageRewardObject();

	StageRewardObject(const StageRewardObject& _Other) = delete;
	StageRewardObject(StageRewardObject&& _Other) noexcept = delete;
	StageRewardObject& operator=(const StageRewardObject& _Other) = delete;
	StageRewardObject& operator=(StageRewardObject&& _Other) noexcept = delete;

	inline bool IsRewardEnd() const
	{
		return IsRewardEndValue;
	}

	void SetReward(RewardType _Type);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> Render = nullptr;
	std::shared_ptr<GameEngineCollision> RewardCol = nullptr;

	RewardType Type = RewardType::None;

	bool IsRewardEndValue = false;

	void GoldRewardInit();
	void SkullRewardInit();

};