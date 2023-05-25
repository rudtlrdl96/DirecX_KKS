#pragma once
#include "BaseContentActor.h"

class HealthBar : public BaseContentActor
{
public:
	HealthBar();
	~HealthBar();

	HealthBar(const HealthBar& _Other) = delete;
	HealthBar(HealthBar&& _Other) noexcept = delete;
	HealthBar& operator=(const HealthBar& _Other) = delete;
	HealthBar& operator=(HealthBar&& _Other) noexcept = delete;

	void SetTexture(const std::string_view& _FrameName, const std::string_view& _BarName, const std::string_view& _SubBarName);
	void UpdateBar(float _Progress, float _DeltaTime);

protected:
	void Start() override;

private:
	std::shared_ptr<ContentSpriteRenderer> BarRedner = nullptr;
	std::shared_ptr<ContentSpriteRenderer> SubBarRedner = nullptr;
	std::shared_ptr<ContentSpriteRenderer> FrameRedner = nullptr;

	ProgressBuffer BarBuffer = ProgressBuffer();
	ProgressBuffer SubBarBuffer = ProgressBuffer();

	ColorBuffer FrameBuffer = ColorBuffer();

	bool IsSubUpdate = false;
	float ProgressTime = 0.0f;

	float4 StartProgress;
	float4 EndProgress;

};


