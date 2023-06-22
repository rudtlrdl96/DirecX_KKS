#pragma once
#include "BaseContentActor.h"

class StoryFontParameter
{
public:
	std::string StoryText = "";

	float Line = 0.0f;
	float PosX = 0.0f;
	float WaitTime = 0.0f;
};

class StoryFontActor : public BaseContentActor
{
public:
	StoryFontActor();
	~StoryFontActor();

	StoryFontActor(const StoryFontActor& _Other) = delete;
	StoryFontActor(StoryFontActor&& _Other) noexcept = delete;
	StoryFontActor& operator=(const StoryFontActor& _Other) = delete;
	StoryFontActor& operator=(StoryFontActor&& _Other) noexcept = delete;

	void WriteText(std::vector<StoryFontParameter> _TextParameter);
	void ReadText();

	void Reset();
	void SkipText();

	inline void SetFadeSpeed(float _Speed)
	{
		FadeSpeed = _Speed;
	}

protected:
	void Update(float _DeltaTime) override;

private:
	std::vector<std::shared_ptr<GameEngineFontRenderer>> TextRender;
	std::vector<float> WaitTimes;

	float ReadProgress = 0.0f;
	float FadeSpeed = 1.5f;
	float FontSize = 19.0f;

	bool IsRead = false;

	size_t Index = 0;

	float4 FontColorFadeStart = float4(0.63921f, 0.53333f, 0.38431f, 0.0f);
	float4 FontColorFadeEnd = float4(0.63921f, 0.53333f, 0.38431f, 1.0f);
};