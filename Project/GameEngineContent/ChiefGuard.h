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
	void Start() override;

	void Skill_SlotA_Enter() override;
	void Skill_SlotA_Update(float _DeltaTime) override;
	void Skill_SlotA_End() override;

	void Skill_SlotB_Enter() override;
	void Skill_SlotB_Update(float _DeltaTime) override;

	void Switch_Enter() override;
	void Switch_Update(float _DeltaTime) override;

private:
	void DataLoad() override;
	void TextureLoad() override;
	void CreateAnimation() override;
	void AnimationColLoad() override;

	std::shared_ptr<class GameEngineCollision> FlashCol = nullptr;

	bool IsProjecTileShot = false;
	bool IsSkillAFlash = false;

	bool IsFlash = false;
	bool IsFlash_0 = false;
	bool IsFlash_1 = false;
	bool IsFlash_2 = false;

	float4 FlashStart = float4::Zero;
	float4 FlashEnd = float4::Zero;

	float FlashMoveX = 450.0f;

	float FlashProgress = 0.0f;
	float FlashSpeed = 20.0f;

	float4 GetFlashPosition(ActorViewDir _Dir);

};

