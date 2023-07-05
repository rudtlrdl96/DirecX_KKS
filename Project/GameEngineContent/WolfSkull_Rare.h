#pragma once
#include "PlayerBaseSkull.h"

class WolfSkull_Rare : public PlayerBaseSkull
{
public:
	WolfSkull_Rare();
	~WolfSkull_Rare();

	WolfSkull_Rare(const WolfSkull_Rare& _Other) = delete;
	WolfSkull_Rare(WolfSkull_Rare&& _Other) noexcept = delete;
	WolfSkull_Rare& operator=(const WolfSkull_Rare& _Other) = delete;
	WolfSkull_Rare& operator=(WolfSkull_Rare&& _Other) noexcept = delete;

protected:
	void Start() override;

	void Attack_Enter() override;
	void JumpAttack_Enter() override;

	void Skill_SlotA_Enter() override;
	void Skill_SlotA_Update(float _DeltaTime) override;
	void Skill_SlotA_End() override;

	void Dash_Enter() override;
	void Dash_Update(float _DeltaTime) override;
	void Dash_End() override;

	void Switch_Enter() override;
	void Switch_Update(float _DeltaTime) override;
	void Switch_End() override;

private:
	bool IsSkillMove = false;
	bool IsSwitchMove = false;

	float4 SwitchMoveStart = float4::Zero;
	float4 SwitchMoveEnd = float4::Zero;

	std::shared_ptr<GameEngineCollision> SwitchCol = nullptr;

	float SwitchMoveProgress = 0.0f;

	void DataLoad() override;
	void TextureLoad() override;
	void CreateAnimation() override;
	void AnimationColLoad() override;

	void Dash() override;


};

