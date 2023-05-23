#pragma once
#include "BaseMonster.h"

class FlameWizard : public BaseMonster
{
public:
	FlameWizard();
	~FlameWizard();

	FlameWizard(const FlameWizard& _Other) = delete;
	FlameWizard(FlameWizard&& _Other) noexcept = delete;
	FlameWizard& operator=(const FlameWizard& _Other) = delete;
	FlameWizard& operator=(FlameWizard&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void DataLoad() override;
	void TextureLoad() override;
	void LoadAnimation() override;
	void AnimationAttackMetaDataLoad() override;
	void SetColData() override;

	void Hit_Enter() override;
	void Hit_End() override;

	void Attack_Enter() override;
	void Attack_Update(float _DeltaTime) override;

private:
	bool IsAttackSign = false;
	bool IsAttackEffect = false;

	float4 AttackPos = float4::Zero;

	std::vector<std::shared_ptr<GameEngineCollision>> PlatformCols;

	std::shared_ptr<class GameEngineCollision> TeleportCol = nullptr;
	std::shared_ptr<EffectActor> SignEffectActor = nullptr;

};

