#pragma once
#include "PlayerBaseSkull.h"

class WolfSkull_Normal : public PlayerBaseSkull
{
public:
	WolfSkull_Normal();
	~WolfSkull_Normal();

	WolfSkull_Normal(const WolfSkull_Normal& _Other) = delete;
	WolfSkull_Normal(WolfSkull_Normal&& _Other) noexcept = delete;
	WolfSkull_Normal& operator=(const WolfSkull_Normal& _Other) = delete;
	WolfSkull_Normal& operator=(WolfSkull_Normal&& _Other) noexcept = delete;

protected:
	void Start() override;
	
	void Skill_SlotA_Enter() override;
	void Skill_SlotA_Update(float _DeltaTime) override;
	void Skill_SlotA_End() override;

	void Dash_Enter() override;
	void Dash_Update(float _DeltaTime) override;
	void Dash_End() override;

	void Switch_Enter() override;
	void Switch_Update(float _DeltaTime) override;

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

