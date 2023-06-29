#pragma once
#include "PlayerBaseSkull.h"

class MinotaurusSkull_Rare : public PlayerBaseSkull
{
public:
	MinotaurusSkull_Rare();
	~MinotaurusSkull_Rare();

	MinotaurusSkull_Rare(const MinotaurusSkull_Rare& _Other) = delete;
	MinotaurusSkull_Rare(MinotaurusSkull_Rare&& _Other) noexcept = delete;
	MinotaurusSkull_Rare& operator=(const MinotaurusSkull_Rare& _Other) = delete;
	MinotaurusSkull_Rare& operator=(MinotaurusSkull_Rare&& _Other) noexcept = delete;

protected:
	void Start() override;
	
	void Attack_Enter() override;
	void Attack_End() override;

	void JumpAttack_Enter() override;
	void JumpAttack_Update(float _DeltaTime) override;
	void JumpAttack_End() override;

private:
	std::shared_ptr<GameEngineCollision> JumpAttackCol = nullptr;
	std::map<UINT, std::shared_ptr <class BaseMonster>> JumpAttackDoubleCheck;

	float JumpAttackTime = 0.0f;
	float JumpAttackLandTime = 0.0f;

	bool IsJumpAttackLand = false;

	void DataLoad() override;
	void TextureLoad() override;
	void CreateAnimation() override;
	void AnimationColLoad() override;
};

