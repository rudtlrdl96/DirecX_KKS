#pragma once
#include "BaseContentActor.h"
#include "ContentUIFontRenderer.h"

class PlayerHealthBar : public BaseContentActor
{
public:
	PlayerHealthBar();
	~PlayerHealthBar();

	PlayerHealthBar(const PlayerHealthBar& _Other) = delete;
	PlayerHealthBar(PlayerHealthBar&& _Other) noexcept = delete;
	PlayerHealthBar& operator=(const PlayerHealthBar& _Other) = delete;
	PlayerHealthBar& operator=(PlayerHealthBar&& _Other) noexcept = delete;

	void SetTexture(const std::string_view& _BarName, const std::string_view& _SubBarName);
	void SetScale(float _Scale);

	void UpdateBar(float _CurHP, float _MaxHP, float _DeltaTime);

protected:
	void Start() override;

private:
	std::shared_ptr<class ContentUIRender> BarRedner = nullptr;
	std::shared_ptr<class ContentUIRender> SubBarRedner = nullptr;
	std::shared_ptr<ContentUIFontRenderer> HpFontRender = nullptr;

	ProgressBuffer BarBuffer = ProgressBuffer();
	ProgressBuffer SubBarBuffer = ProgressBuffer();

	bool IsSubUpdate = false;
	float ProgressTime = 0.0f;

	float4 StartProgress;
	float4 EndProgress;
};

