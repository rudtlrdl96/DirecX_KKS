#pragma once
#include "BaseContentActor.h"

class TalkArrow : public BaseContentActor
{
public:
	enum class ArrowState
	{
		FadeIn,
		FadeOut,
	};
public:
	TalkArrow();
	~TalkArrow();

	TalkArrow(const TalkArrow& _Other) = delete;
	TalkArrow(TalkArrow&& _Other) noexcept = delete;
	TalkArrow& operator=(const TalkArrow& _Other) = delete;
	TalkArrow& operator=(TalkArrow&& _Other) noexcept = delete;

	inline void SetState(ArrowState _State)
	{
		State = _State;
		ArrowProgress = 0.0f;
	}

	inline void SetSpeed(float _Speed)
	{
		ArrowSpeed = _Speed;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
		 
private:
	std::shared_ptr<class ContentUIRender> ArrowRender = nullptr;
	ColorBuffer ArrowBuffer;

	ArrowState State = ArrowState::FadeIn;
	float ArrowProgress = 0.0f;
	float ArrowSpeed = 1.0f;
};

