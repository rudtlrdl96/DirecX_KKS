#pragma once
#include "BaseContentActor.h"
#include "Rigidbody2D.h"

class AnimationPartParticle : public BaseContentActor
{
public:
	AnimationPartParticle();
	~AnimationPartParticle();

	AnimationPartParticle(const AnimationPartParticle& _Other) = delete;
	AnimationPartParticle(AnimationPartParticle&& _Other) noexcept = delete;
	AnimationPartParticle& operator=(const AnimationPartParticle& _Other) = delete;
	AnimationPartParticle& operator=(AnimationPartParticle&& _Other) noexcept = delete;

	void Init(const ContentAnimationParameter& _Parameter, float _ScaleRatio, const float4& _Dir, float _Power, float _LiveTime);

	inline void SetEndCallback(std::function<void()> _EndCallback)
	{
		EndCallback = _EndCallback;
	}

	inline void RotOff()
	{
		IsRot = false;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeEnd() override;

private:
	Rigidbody2D ParticleRigid;

	float LiveTime = 1.0f;

	float4 RandRot = float4::Zero;

	bool IsRot = true;

	std::shared_ptr<ContentSpriteRenderer> Render = nullptr;
	ColorBuffer Buffer;

	std::function<void()> EndCallback = nullptr;
};

