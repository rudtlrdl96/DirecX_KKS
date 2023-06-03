#pragma once
#include "BaseContentActor.h"

class StoryFade : public BaseContentActor
{
private:
	enum class StoryFadeState
	{
		None,
		FadeIn,
		FadeOut
	};

public:
	StoryFade();
	~StoryFade();

	StoryFade(const StoryFade& _Other) = delete;
	StoryFade(StoryFade&& _Other) noexcept = delete;
	StoryFade& operator=(const StoryFade& _Other) = delete;
	StoryFade& operator=(StoryFade&& _Other) noexcept = delete;

	void FadeIn();
	void FadeOut();
	void Reset();

	inline void SetSpeed(float _Speed)
	{
		FadeSpeed = _Speed;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class ContentUIRender> UpRenderer = nullptr;
	std::shared_ptr<class ContentUIRender> DownRenderer = nullptr;

	ColorBuffer UpRenderBuffer;
	ColorBuffer DownRenderBuffer;

	float4 UpStart = float4::Zero;
	float4 UpEnd = float4::Zero;

	float4 DownStart = float4::Zero;
	float4 DownEnd = float4::Zero;

	float FadeProgress = 0.0f;
	float FadeSpeed = 1.0f;

	StoryFadeState State = StoryFadeState::None;
};

