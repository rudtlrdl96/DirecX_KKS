#pragma once
#include "BaseContentActor.h"

class TitleLogo : public BaseContentActor
{
public:
	TitleLogo();
	~TitleLogo();

	TitleLogo(const TitleLogo& _Other) = delete;
	TitleLogo(TitleLogo&& _Other) noexcept = delete;
	TitleLogo& operator=(const TitleLogo& _Other) = delete;
	TitleLogo& operator=(TitleLogo&& _Other) noexcept = delete;

	void SetLogo(const std::string_view& _TexName, float _IntroTime, float _OutroTime, float _WaitTime, float _Scale);

	bool IsLogoEnd() const
	{
		return LogoEndValue;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> LogoRender = nullptr;

	bool LogoEndValue = false;

	float4 LogoColor = float4::Zero;
	float ProgressTime = 0.0f;

	float IntroStartTime = 1.0f;
	float IntroEndTime = 1.0f;
	float OutroStartTime = 1.0f;
	float OutroEndTime = 1.0f;
	float WaitStartTime  = 1.0f;
	float WaitEndTime  = 1.0f;

	float ProgressCheck(float _StartTime, float _EndTime, float _TotalProgressTime);
};

