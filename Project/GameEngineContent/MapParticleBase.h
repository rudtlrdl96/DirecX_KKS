#pragma once
#include "BaseContentActor.h"
#include "Rigidbody2D.h"

class MapParticleBase : public BaseContentActor
{
public:
	MapParticleBase();
	~MapParticleBase();

	MapParticleBase(const MapParticleBase& _Other) = delete;
	MapParticleBase(MapParticleBase&& _Other) noexcept = delete;
	MapParticleBase& operator=(const MapParticleBase& _Other) = delete;
	MapParticleBase& operator=(MapParticleBase&& _Other) noexcept = delete;

	void Init(const float4& _RandRot);
	void AddForce(const float4& _Force);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	std::shared_ptr<GameEngineSpriteRenderer> ParticleRender = nullptr;

private:
	Rigidbody2D ParticleRigid;
	float4 RandRot = float4::Zero;

	virtual void SetTexture() = 0;
};

