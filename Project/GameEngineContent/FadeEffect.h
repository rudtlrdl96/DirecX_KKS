#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>

enum class FadeState
{
	None,
	FadeIn,
	FadeOut,
};

// Ό³Έν :
class FadeEffect : public GameEnginePostProcess
{
public:
	// constrcuter destructer
	FadeEffect();
	~FadeEffect();

	// delete Function
	FadeEffect(const FadeEffect& _Other) = delete;
	FadeEffect(FadeEffect&& _Other) noexcept = delete;
	FadeEffect& operator=(const FadeEffect& _Other) = delete;
	FadeEffect& operator=(FadeEffect&& _Other) noexcept = delete;

	inline void FadeIn(std::function<void()> _FadeEndCallback = nullptr, const float4& _FadeColor = float4::Zero)
	{
		State = FadeState::FadeIn;
		FadeData = _FadeColor;
		FadeData.a = 1.0f;
		Callback = _FadeEndCallback;
	}

	inline void FadeOut(std::function<void()> _FadeEndCallback = nullptr, const float4& _FadeColor = float4::Zero)
	{
		State = FadeState::FadeOut;
		FadeData = _FadeColor;
		FadeData.a = 0.0f;
		Callback = _FadeEndCallback;
	}

	inline void SetSpeed(float _Speed)
	{
		Speed = _Speed;
	}

protected:
	void Start(GameEngineRenderTarget* _Target) override;
	void Effect(GameEngineRenderTarget* _Target, float _DeltaTime) override;

private:
	float4 FadeData = { 0.0f, 0.0f, 0.0f, 1.0f };
	float Speed = 1.0f;

	FadeState State = FadeState::None;

	std::shared_ptr<GameEngineRenderUnit> FadeUnit;
	std::function<void()> Callback = nullptr;

};

