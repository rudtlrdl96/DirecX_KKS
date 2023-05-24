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

	void SetFade();
	void SetUnFade();

	void FadeIn(std::function<void()> _FadeEndCallback = nullptr);
	void FadeOut(std::function<void()> _FadeEndCallback = nullptr);

	void Reset();

	inline void SetSpeed(float _Speed)
	{
		FadeSpeed = _Speed;
	}

protected:

	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::shared_ptr<class ContentUIRender> MainRenderer = nullptr;

	FadeState State = FadeState::Wait;
	FadeBuffer Buffer;

	float FadeSpeed = 1.0f;

	std::function<void()> FadeEndCallback = nullptr;
};

