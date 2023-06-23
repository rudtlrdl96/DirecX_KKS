#include "PrecompileHeader.h"
#include "StorySound.h"

StorySound::StorySound()
{
}

StorySound::~StorySound()
{
}

void StorySound::PlayVoice(const std::string_view& _VoiceName)
{
	if (true == VoicePlayer.IsValid())
	{
		VoicePlayer.Stop();
	}

	VoicePlayer = GameEngineSound::Play(_VoiceName);
}

void StorySound::PlayBGM(const std::string_view& _SoundName)
{
	ResetBGM();
	BGMPlayer = GameEngineSound::Play(_SoundName);
	BGMPlayer.SetLoop(-1);
}

void StorySound::ResetBGM()
{
	if (true == BGMPlayer.IsValid())
	{
		BGMPlayer.Stop();
	}
}

bool StorySound::IsVoiceEnd() const
{
	if (false == VoicePlayer.IsValid())
	{
		return true;
	}

	bool IsPlaying = false;
	VoicePlayer.isPlaying(&IsPlaying);

	return !IsPlaying;
}

void StorySound::Start()
{
}

void StorySound::Update(float _DeltaTime)
{
}
