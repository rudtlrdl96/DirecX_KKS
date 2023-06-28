#pragma once
#include "PlayerBaseSkull.h"

class WolfSkull_Unique : public PlayerBaseSkull
{
public:
	WolfSkull_Unique();
	~WolfSkull_Unique();

	WolfSkull_Unique(const WolfSkull_Unique& _Other) = delete;
	WolfSkull_Unique(WolfSkull_Unique&& _Other) noexcept = delete;
	WolfSkull_Unique& operator=(const WolfSkull_Unique& _Other) = delete;
	WolfSkull_Unique& operator=(WolfSkull_Unique&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void Attack_Enter() override;
	void JumpAttack_Enter() override;

	void Skill_SlotA_Enter() override;
	void Skill_SlotA_Update(float _DeltaTime) override;
	void Skill_SlotA_End() override;

	void Skill_SlotB_Enter() override;
	void Skill_SlotB_Update(float _DeltaTime) override;
	void Skill_SlotB_End() override;

	void Dash_Enter() override;
	void Dash_Update(float _DeltaTime) override;
	void Dash_End() override;

	void Switch_Enter() override;
	void Switch_Update(float _DeltaTime) override;

private:
	bool IsSkillMove = false;
	bool IsSwitchMove = false;
	bool IsSwitchTrailAttack = false;

	float4 SwitchMoveStart = float4::Zero;
	float4 SwitchMoveEnd = float4::Zero;

	std::shared_ptr<GameEngineCollision> SwitchCol = nullptr;

	float SwitchMoveProgress = 0.0f;
	float TrailAttackProgress = 0.0f;

	int TrailAttackCount = 0;

	void DataLoad() override;
	void TextureLoad() override;
	void CreateAnimation() override;
	void AnimationColLoad() override;

	void Dash() override;
};

