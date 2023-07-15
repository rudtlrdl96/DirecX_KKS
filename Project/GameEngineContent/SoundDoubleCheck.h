#pragma once


class SoundDoubleCheck
{
public:
	static void Play(const std::string_view& _SoundName);
	static bool IsPlay(const std::string_view& _SoundName);
	static void SoundListReset();

protected:
	
private:
	static std::map<std::string, bool> CurFramePlayEffectSound;

	SoundDoubleCheck();
	~SoundDoubleCheck();

	SoundDoubleCheck(const SoundDoubleCheck& _Other) = delete;
	SoundDoubleCheck(SoundDoubleCheck&& _Other) noexcept = delete;
	SoundDoubleCheck& operator=(const SoundDoubleCheck& _Other) = delete;
	SoundDoubleCheck& operator=(SoundDoubleCheck&& _Other) noexcept = delete;

};

