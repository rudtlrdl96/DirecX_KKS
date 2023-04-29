#pragma once
#include "UILevel.h"

class TitleLevel : public UILevel
{	
private:
	enum class TitleState
	{
		DevLogo,
		PublishingLogo,
		Intro,
		InputWait
	};

public:
	TitleLevel();
	~TitleLevel();

	TitleLevel(const TitleLevel& _Other) = delete;
	TitleLevel(TitleLevel&& _Other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _Other) = delete;
	TitleLevel& operator=(TitleLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime);

	void LevelChangeStart() override;
private:
	std::shared_ptr<class BlackBackground> BlackBG = nullptr;
	std::shared_ptr<class FadeActor> Fade = nullptr;
	std::shared_ptr<class TitleLogo> Logo = nullptr;
	std::shared_ptr<class TitleActor> Title = nullptr;

	bool IsInputWait = true;
	
	TitleState State = TitleState::DevLogo;
};