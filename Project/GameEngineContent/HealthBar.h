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

	void SetTexture(const std::string_view& _FrameName, const std::string_view& _BarName);

protected:
	void Start() override;
	
private:
	std::shared_ptr<class ContentUIRender> BarRedner = nullptr;
	std::shared_ptr<class ContentUIRender> FrameRedner = nullptr;

	ProgressBuffer BarBuffer = ProgressBuffer();
	ColorBuffer FrameBuffer = ColorBuffer();

};


