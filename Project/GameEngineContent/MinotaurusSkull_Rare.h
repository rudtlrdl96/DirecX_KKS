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
	
private:
	void DataLoad() override;
	void TextureLoad() override;
	void CreateAnimation() override;
	void AnimationColLoad() override;

};

