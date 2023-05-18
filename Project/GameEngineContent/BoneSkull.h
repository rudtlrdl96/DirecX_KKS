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
	void Start() override;

	void Skill_SlotA_Update(float _DeltaTime) override;
	void Skill_SlotB_Enter() override;
private:
	void TextureLoad() override;
	void CreateAnimation() override;
	void AnimationColLoad() override;

	std::shared_ptr<class BoneHead> HeadActor = nullptr;

};

