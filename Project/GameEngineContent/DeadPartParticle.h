#pragma once
#include "BaseContentActor.h"
#include "Rigidbody2D.h"

class DeadPartParticle : public BaseContentActor
{
public:
	DeadPartParticle();
	~DeadPartParticle();

	DeadPartParticle(const DeadPartParticle& _Other) = delete;
	DeadPartParticle(DeadPartParticle&& _Other) noexcept = delete;
	DeadPartParticle& operator=(const DeadPartParticle& _Other) = delete;
	DeadPartParticle& operator=(DeadPartParticle&& _Other) noexcept = delete;

	void Init(const std::string_view& _TexName, const float4& _Dir, float _Power, float _LiveTime);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	Rigidbody2D ParticleRigid;

	float LiveTime = 1.0f;

	float4 RandRot = float4::Zero;

	std::shared_ptr<ContentSpriteRenderer> Render = nullptr;
	ColorBuffer Buffer;
};

