#pragma once
#include "BaseContentActor.h"

class TitleActor : public BaseContentActor
{
public:
	TitleActor();
	~TitleActor();

	TitleActor(const TitleActor& _Other) = delete;
	TitleActor(TitleActor&& _Other) noexcept = delete;
	TitleActor& operator=(const TitleActor& _Other) = delete;
	TitleActor& operator=(TitleActor&& _Other) noexcept = delete;

	void TitleOn(float _LogoWaitTime, float _LogoFadeSpeed);

	bool IsLogoFadeEnd() const
	{
		return IsLogoFadeValue;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class ContentUIRender> TextureRender = nullptr;
	std::shared_ptr<class ContentUIRender> LogoRender = nullptr;

	float WaitTime = 1.0f;
	float ProgressTime = 0.0f;
	float LogoFadeProgress = 0.0f;
	float LogoFadeSpeed = 1.0f;

	bool IsLogoFadeValue = false;

	ColorBuffer BackTexBuffer;
	ColorBuffer LogoBuffer;
};

