#pragma once
#include "BaseContentActor.h"
#include "Rigidbody2D.h"

class HitParticle : public BaseContentActor
{
public:
	HitParticle();
	~HitParticle();

	HitParticle(const HitParticle& _Other) = delete;
	HitParticle(HitParticle&& _Other) noexcept = delete;
	HitParticle& operator=(const HitParticle& _Other) = delete;
	HitParticle& operator=(HitParticle&& _Other) noexcept = delete;

	void Init(const float4& _Dir, float _Power, float _LiveTime);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	
private:
	Rigidbody2D ParticleRigid;

	float LiveTime = 1.0f;

	std::shared_ptr<ContentSpriteRenderer> Render = nullptr;
	ColorBuffer Buffer;
};

