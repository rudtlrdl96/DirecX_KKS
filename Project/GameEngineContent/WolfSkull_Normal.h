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
	
private:
	void DataLoad() override;
	void TextureLoad() override;
	void CreateAnimation() override;
	void AnimationColLoad() override;

};

