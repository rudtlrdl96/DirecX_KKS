#pragma once
#include "BaseContentActor.h"
#include "Rigidbody2D.h"

enum class OrbState
{
	None,
	Wave,
	Drop,
};

class LifeOrb : public BaseContentActor
{
public:
	LifeOrb();
	~LifeOrb();

	LifeOrb(const LifeOrb& _Other) = delete;
	LifeOrb(LifeOrb&& _Other) noexcept = delete;
	LifeOrb& operator=(const LifeOrb& _Other) = delete;
	LifeOrb& operator=(LifeOrb&& _Other) noexcept = delete;

	void DropOrb(const float4& _WorldPos);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Destroy() override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> OrbRender = nullptr;
	std::shared_ptr<GameEngineCollision> OrbBodyCol = nullptr;
	std::shared_ptr<GameEngineCollision> OrbGroundCol = nullptr;

	Rigidbody2D DropRigid;

	OrbState State = OrbState::None;

	float4 WaveCenter = float4::Zero;

	void SetWaveState(std::shared_ptr<GameEngineCollision> _PlatformCol);
};

