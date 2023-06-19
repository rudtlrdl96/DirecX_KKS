#pragma once
#include "UILevel.h"

class EndingLogoLevel : public UILevel
{
public:
	EndingLogoLevel();
	~EndingLogoLevel();

	EndingLogoLevel(const EndingLogoLevel& _Other) = delete;
	EndingLogoLevel(EndingLogoLevel&& _Other) noexcept = delete;
	EndingLogoLevel& operator=(const EndingLogoLevel& _Other) = delete;
	EndingLogoLevel& operator=(EndingLogoLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;

private:
	std::shared_ptr<class BlackBackground> BackPtr = nullptr;
	std::shared_ptr<class SkulLogo> LogoPtr = nullptr;

	float LogoWaitTime = 0.0f;
};

