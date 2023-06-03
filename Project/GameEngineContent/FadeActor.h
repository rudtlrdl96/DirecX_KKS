#pragma once
#include "BaseContentActor.h"

class FadeActor : public BaseContentActor
{
private:
	enum class FadeState
	{
		Wait,
		FadeIn,
		FadeOut,
	};
public:
	FadeActor();
	~FadeActor();

	FadeActor(const FadeActor& _Other) = delete;
	FadeActor(FadeActor&& _Other) noexcept = delete;
	FadeActor& operator=(const FadeActor& _Other) = delete;
	FadeActor& operator=(FadeActor&& _Other) noexcept = delete;

	void SetFade(const float4& _FadeColor = float4::Zero);
	void SetUnFade(const float4& _FadeColor = float4::Zero);

	void FadeIn(std::function<void()> _FadeEndCallback = nullptr, const float4& _FadeColor = float4::Zero);
	void FadeOut(std::function<void()> _FadeEndCallback = nullptr, const float4& _FadeColor = float4::Zero);

	void Reset();

	inline void SetSpeed(float _Speed)
	{
		FadeSpeed = _Speed;
	}

	inline void SetWaitTime(float _WaitTime)
	{
		WaitTime = _WaitTime;
	}

	inline bool IsFadeEnd() const
	{
		return IsFadeEndValue;
	}

protected:

	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class ContentFadeRender> MainRenderer = nullptr;

	bool IsFadeEndValue = false;

	FadeState State = FadeState::Wait;
	FadeBuffer Buffer;

	float FadeSpeed = 1.0f;
	float WaitTime = 0.0f;
	float CurWaitTime = 0.0f;

	std::function<void()> FadeEndCallback = nullptr;
};

