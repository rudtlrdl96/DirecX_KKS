#include "PrecompileHeader.h"
#include "SoundDoubleCheck.h"

std::map<std::string, bool> SoundDoubleCheck::CurFramePlayEffectSound;

void SoundDoubleCheck::Play(const std::string_view& _SoundName)
{
	if (true == IsPlay(_SoundName))
	{
		return;
	}

	GameEngineSound::Play(_SoundName);
	CurFramePlayEffectSound[_SoundName.data()] = true;
}

bool SoundDoubleCheck::IsPlay(const std::string_view& _SoundName)
{
	return CurFramePlayEffectSound[_SoundName.data()];
}

void SoundDoubleCheck::SoundListReset()
{
	CurFramePlayEffectSound.clear();
}

SoundDoubleCheck::SoundDoubleCheck()
{
}

SoundDoubleCheck::~SoundDoubleCheck()
{
}
