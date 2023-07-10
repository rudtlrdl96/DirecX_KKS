#pragma once
#include "BaseContentActor.h"
#include "ContentUIFontRenderer.h"
#include "Rigidbody2D.h"

class VeteranHero_HealthBar : public BaseContentActor
{
public:
	VeteranHero_HealthBar();
	~VeteranHero_HealthBar();

	VeteranHero_HealthBar(const VeteranHero_HealthBar& _Other) = delete;
	VeteranHero_HealthBar(VeteranHero_HealthBar&& _Other) noexcept = delete;
	VeteranHero_HealthBar& operator=(const VeteranHero_HealthBar& _Other) = delete;
	VeteranHero_HealthBar& operator=(VeteranHero_HealthBar&& _Other) noexcept = delete;

	void DropFrame();
	void UpFrame();

	void UpdateBar(float _Progress, float _DeltaTime);
protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class ContentUIRender> BarRedner = nullptr;
	std::shared_ptr<class ContentUIRender> SubBarRedner = nullptr;
	std::shared_ptr<class ContentUIRender> BarFrameRedner = nullptr;
	std::shared_ptr<class ContentUIRender> TopFrameRedner = nullptr;
	std::shared_ptr<class ContentUIRender> BottomFrameRedner = nullptr;

	std::shared_ptr<ContentUIFontRenderer> NameFontRender = nullptr;
	std::shared_ptr<ContentUIFontRenderer> SubFontRender = nullptr;

	Rigidbody2D Rigid;

	ProgressBuffer BarBuffer = ProgressBuffer();
	ProgressBuffer SubBarBuffer = ProgressBuffer();

	ColorBuffer FrameBuffer = ColorBuffer();
	ColorBuffer PictureBuffer = ColorBuffer();

	int GroundColCount = 0;
	
	float ProgressTime = 0.0f;
	
	bool IsDrop = false;
	bool IsSubUpdate = false;


	float4 StartProgress;
	float4 EndProgress;
	float4 StartPos = float4::Zero;
	float4 EndPos = float4::Zero;



};

