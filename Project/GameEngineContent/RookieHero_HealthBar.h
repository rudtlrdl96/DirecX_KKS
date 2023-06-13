#pragma once
#include "BaseContentActor.h"

class RookieHero_HealthBar : public BaseContentActor
{
public:
	RookieHero_HealthBar();
	~RookieHero_HealthBar();

	RookieHero_HealthBar(const RookieHero_HealthBar& _Other) = delete;
	RookieHero_HealthBar(RookieHero_HealthBar&& _Other) noexcept = delete;
	RookieHero_HealthBar& operator=(const RookieHero_HealthBar& _Other) = delete;
	RookieHero_HealthBar& operator=(RookieHero_HealthBar&& _Other) noexcept = delete;

	void SetDeathPicture();
	void UpdateBar(float _Progress, float _DeltaTime);
	void Destroy() override;

protected:
	std::shared_ptr<class ContentUIRender> BarRedner = nullptr;
	std::shared_ptr<class ContentUIRender> SubBarRedner = nullptr;
	std::shared_ptr<class ContentUIRender> FrameRedner = nullptr;
	std::shared_ptr<class ContentUIRender> PictureRedner = nullptr;

	ProgressBuffer BarBuffer = ProgressBuffer();
	ProgressBuffer SubBarBuffer = ProgressBuffer();

	ColorBuffer FrameBuffer = ColorBuffer();
	ColorBuffer PictureBuffer = ColorBuffer();

	bool IsSubUpdate = false;
	float ProgressTime = 0.0f;

	float4 StartProgress;
	float4 EndProgress;

	void Start() override;

};

