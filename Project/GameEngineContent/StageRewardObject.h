#pragma once
#include "BaseContentActor.h"
#include "SkullData.h"
#include "ItemData.h"
#include "PointLightEffect.h"
#include "ContentMinimapRender.h"

enum class RewardType
{
	None,
	Normal,
	Skull,
	Item,
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

	void CallUseEvent() override;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Destroy() override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> Render = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> TableRender = nullptr;
	std::shared_ptr<ContentMinimapRender> MinimapImageRender = nullptr;

	std::shared_ptr<GameEngineCollision> RewardCol = nullptr;
	std::shared_ptr<GameEngineCollision> EnterCol = nullptr;

	std::shared_ptr<PointLightEffect> RewardLight = nullptr;
	std::shared_ptr<class FieldNoteActor> NoteActor = nullptr;

	std::vector<std::shared_ptr<GameEngineCollision>> AllPlatformCol;
	std::vector<std::shared_ptr<class BaseGear>> CreateGears;

	RewardType Type = RewardType::None;

	SkullGrade SkullRewardGrade = SkullGrade::Normal;
	ItemGrade ItemRewardGrade = ItemGrade::Normal;

	int ItemRewardIndex = 0;

	bool IsRewardEndValue = false;
	bool IsPlayerFirstEnter = false;
	bool IsLightStartEffect = false;

	float LightProgress = 0.0f;

	void GoldRewardInit();
	void SkullRewardInit();
	void ItemRewardInit();
	void MiddleBossRewardInit();

	std::shared_ptr<class SkullGear> DropSkullReward(const float4& _Pivot = float4::Zero, bool _GradeReset = false);
	std::shared_ptr<class ItemGear> DropItemReward(const float4& _Pivot = float4::Zero,  bool _GradeReset = false);
	std::shared_ptr<class ItemGear> BezierItemReward(const float4& _Start, const float4& _End,  bool _GradeReset = false);
	void DropGoldReward();

	void CreateLight();
	void ReleaseLight();

};