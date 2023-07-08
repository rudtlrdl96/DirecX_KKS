#pragma once
#include "BaseContentActor.h"

class PlayerHitFade : public BaseContentActor
{
public:
	PlayerHitFade();
	~PlayerHitFade();

	PlayerHitFade(const PlayerHitFade& _Other) = delete;
	PlayerHitFade(PlayerHitFade&& _Other) noexcept = delete;
	PlayerHitFade& operator=(const PlayerHitFade& _Other) = delete;
	PlayerHitFade& operator=(PlayerHitFade&& _Other) noexcept = delete;

	void Active();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class ContentUIRender> FadeRender = nullptr;

	float4 StartColor = float4::Zero;
	float4 EndColor = float4::Zero;

	ColorBuffer Buffer;

	bool IsFadeActive = false;
	float Progress = 0.0f;
	float Speed = 2.0f;
};

