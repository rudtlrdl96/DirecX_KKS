#pragma once
#include "BaseContentActor.h"

class StorySound : public BaseContentActor
{
public:
	StorySound();
	~StorySound();

	StorySound(const StorySound& _Other) = delete;
	StorySound(StorySound&& _Other) noexcept = delete;
	StorySound& operator=(const StorySound& _Other) = delete;
	StorySound& operator=(StorySound&& _Other) noexcept = delete;

	void PlayVoice(const std::string_view& _VoiceName);
	void PlayBGM(const std::string_view& _SoundName);
	void ResetBGM();

	bool IsVoiceEnd() const;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineSoundPlayer VoicePlayer;
	GameEngineSoundPlayer BGMPlayer;

};

