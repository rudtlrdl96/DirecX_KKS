#pragma once
#include "PlayerBaseSkull.h"

class BoneSkull : public PlayerBaseSkull
{
public:
	BoneSkull();
	~BoneSkull();

	BoneSkull(const BoneSkull& _Other) = delete;
	BoneSkull(BoneSkull&& _Other) noexcept = delete;
	BoneSkull& operator=(const BoneSkull& _Other) = delete;
	BoneSkull& operator=(BoneSkull&& _Other) noexcept = delete;

protected:

private:
	void TextureLoad() override;
	void CreateAnimation() override;
};

