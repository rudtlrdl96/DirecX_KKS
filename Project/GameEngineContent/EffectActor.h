#pragma once
#include "BaseContentActor.h"


enum class EffectDeathTrigger
{
	Time,
	AnimEnd,
	None,
};

class EffectMetaData
{
public:
	std::string SpriteName = "";

	float4 RenderPivot = float4::Zero;

	UINT AnimStart = 0;
	UINT AnimEnd = 0;

	float AnimInter = 0.1f;
	float ScaleRatio = 1.0f;

	float4 Color = float4::Zero;
};

class EffectActor : public BaseContentActor
{
private:
	friend class EffectManager;
	
public:
	EffectActor();
	~EffectActor();

	EffectActor(const EffectActor& _Other) = delete;
	EffectActor(EffectActor&& _Other) noexcept = delete;
	EffectActor& operator=(const EffectActor& _Other) = delete;
	EffectActor& operator=(EffectActor&& _Other) noexcept = delete;

	void PauseOn();
	void PauseOff();

	inline size_t GetCurrentFrame() const
	{
		return EffectRender->GetCurrentFrame();
	}

	inline bool IsAnimationEnd() const
	{
		return EffectRender->IsAnimationEnd();
	}

	inline void IsFadeDeathOn(float _DeathFadeSpeed)
	{
		IsFadeDeathValue = true;
		DeathFadeSpeed = _DeathFadeSpeed;
	}

protected:
	std::shared_ptr<ContentSpriteRenderer> EffectRender = nullptr;

	ColorBuffer Buffer;

	EffectDeathTrigger DeathTrigger = EffectDeathTrigger::Time;
	float DeathTime = 0.0f;
	float WaitTime = 0.0f;

	float DeathProgress = 0.0f;
	float DeathFadeSpeed = 1.0f;
	float IntroProgress = 0.0f;
	float IntroFadeSpeed = 1.0f;

	float EffectAlpha = 1.0f;

	bool IsFadeDeathValue = false;
	bool IsFadeIntroValue = false;

	void Init(const EffectMetaData& _MetaData, const class EffectParameter& _Parameter);

	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool IsFadeDeath = false;

};

