#pragma once
#include "BaseContentActor.h"
#include "ContentSlice9Renderer.h"

class SpeechBubbleParameter
{
public:
	std::shared_ptr<GameEngineActor> Target = nullptr;
	
	const std::string_view& Text = "";
	const float4& Pivot = float4::Zero;

	bool IsLarge = false;
	bool IsLoop = false;
	
	float FontSize = 0.0f;
	float LiveTime = 0.0f;
	float LoopInter = 0.0f;

	bool IsAutoScale = false;
};

class SpeechBubble : public BaseContentActor
{
public:
	SpeechBubble();
	~SpeechBubble();

	SpeechBubble(const SpeechBubble& _Other) = delete;
	SpeechBubble(SpeechBubble&& _Other) noexcept = delete;
	SpeechBubble& operator=(const SpeechBubble& _Other) = delete;
	SpeechBubble& operator=(SpeechBubble&& _Other) noexcept = delete;

	void PlayBubble(const SpeechBubbleParameter& _BubbleParameter);
	void SetBubbleScale(const float4& _Scale);

	inline float4 GetBubbleScale() const
	{
		return BubbleRender->GetTransform()->GetLocalScale();
	}

	void On() override;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	
private:
	std::shared_ptr<ContentSlice9Renderer> BubbleRender = nullptr;
	std::shared_ptr<GameEngineFontRenderer> FontRender = nullptr;
	ColorBuffer Buffer = ColorBuffer();

	std::weak_ptr<GameEngineActor> Target;
	float4 Pivot = float4::Zero;

	std::string TalkText = "";

	float LiveTime = 0.0f;
	float LoopInter = 0.0f;
	float OffTime = 0.0f;

	bool IsLoop = false;


};

