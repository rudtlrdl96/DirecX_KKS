#pragma once
#include "PlayerBaseSkull.h"

class ChiefGuard : public PlayerBaseSkull
{
public:
	ChiefGuard();
	~ChiefGuard();

	ChiefGuard(const ChiefGuard& _Other) = delete;
	ChiefGuard(ChiefGuard&& _Other) noexcept = delete;
	ChiefGuard& operator=(const ChiefGuard& _Other) = delete;
	ChiefGuard& operator=(ChiefGuard&& _Other) noexcept = delete;

protected:
	
private:
	void TextureLoad() override;
	void CreateAnimation() override;
	void AnimationColLoad() override;

};

