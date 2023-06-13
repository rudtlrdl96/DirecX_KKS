#pragma once
#include "BaseContentActor.h"

class StoryHero_FirstHero_Opening : public BaseContentActor
{
private:
	enum class HeroState
	{
		Landing,
		Idle,
		CastingIntro,
		CastingLoop
	};

public:
	StoryHero_FirstHero_Opening();
	~StoryHero_FirstHero_Opening();

	StoryHero_FirstHero_Opening(const StoryHero_FirstHero_Opening& _Other) = delete;
	StoryHero_FirstHero_Opening(StoryHero_FirstHero_Opening&& _Other) noexcept = delete;
	StoryHero_FirstHero_Opening& operator=(const StoryHero_FirstHero_Opening& _Other) = delete;
	StoryHero_FirstHero_Opening& operator=(StoryHero_FirstHero_Opening&& _Other) noexcept = delete;

	void PlayLandingEffect();
	void Destroy() override;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<ContentSpriteRenderer> MainRender = nullptr;
	ColorBuffer Buffer;

	HeroState State = HeroState::Landing;

	float Landing_IntroWaitTime = 0.0f;

	float IdleProgress = 0.0f;
	float IdleUpSpeed = 3.0f;

	float4 IdleStart = float4::Zero;
	float4 IdleEnd = float4::Zero;

	bool IsTalkStart = false;

	std::shared_ptr<EffectActor> BigbangReadyEffect = nullptr;

	std::shared_ptr<EffectActor> OrbStartEffect = nullptr;
	std::shared_ptr<EffectActor> OrbLoopEffect = nullptr;
	std::shared_ptr<EffectActor> OrbTrailEffect = nullptr;

	bool IsBigbangStart = false;
	bool IsBigbangEnd = false;
	bool IsLevelEnd = false;

	float BigbangTime = 0.0f;
	float FadeTime = 0.0f;
	float LevelEndTime = 0.0f;
};

