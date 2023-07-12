#pragma once
#include "BaseContentActor.h"
#include "Rigidbody2D.h"

class TexturePartParticle : public BaseContentActor
{
public:
	TexturePartParticle();
	~TexturePartParticle();

	TexturePartParticle(const TexturePartParticle& _Other) = delete;
	TexturePartParticle(TexturePartParticle&& _Other) noexcept = delete;
	TexturePartParticle& operator=(const TexturePartParticle& _Other) = delete;
	TexturePartParticle& operator=(TexturePartParticle&& _Other) noexcept = delete;

	void Init(const std::string_view& _TexName, const float4& _Dir, float _Power, float _LiveTime);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeEnd() override;

private:
	Rigidbody2D ParticleRigid;

	float LiveTime = 1.0f;

	float4 RandRot = float4::Zero;

	std::shared_ptr<ContentSpriteRenderer> Render = nullptr;
	ColorBuffer Buffer;
};

