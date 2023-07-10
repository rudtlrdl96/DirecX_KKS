#pragma once
#include "BaseContentActor.h"
#include "ContentUIFontRenderer.h"

class VeteranHero_HealthBar : public BaseContentActor
{
public:
	VeteranHero_HealthBar();
	~VeteranHero_HealthBar();

	VeteranHero_HealthBar(const VeteranHero_HealthBar& _Other) = delete;
	VeteranHero_HealthBar(VeteranHero_HealthBar&& _Other) noexcept = delete;
	VeteranHero_HealthBar& operator=(const VeteranHero_HealthBar& _Other) = delete;
	VeteranHero_HealthBar& operator=(VeteranHero_HealthBar&& _Other) noexcept = delete;

	void UpdateBar(float _Progress, float _DeltaTime);
protected:
	void Start() override;

private:
	std::shared_ptr<class ContentUIRender> BarRedner = nullptr;
	std::shared_ptr<class ContentUIRender> SubBarRedner = nullptr;
	std::shared_ptr<class ContentUIRender> BarFrameRedner = nullptr;
	std::shared_ptr<class ContentUIRender> TopFrameRedner = nullptr;
	std::shared_ptr<class ContentUIRender> BottomFrameRedner = nullptr;

	std::shared_ptr<ContentUIFontRenderer> NameFontRender = nullptr;
	std::shared_ptr<ContentUIFontRenderer> SubFontRender = nullptr;

	ProgressBuffer BarBuffer = ProgressBuffer();
	ProgressBuffer SubBarBuffer = ProgressBuffer();

	ColorBuffer FrameBuffer = ColorBuffer();
	ColorBuffer PictureBuffer = ColorBuffer();

	bool IsSubUpdate = false;
	float ProgressTime = 0.0f;

	float4 StartProgress;
	float4 EndProgress;

};

