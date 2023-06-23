#pragma once
#include "FadeActor_UI.h"
#include "StoryTextureView.h"
#include "StoryFontActor.h"
#include "StorySound.h"

namespace StoryUI
{
	enum class WalkType
	{
		SetMainTex,
		SetSubTex,
		SetBackTex,
		SwapTex,
		FadeIntro,
		MoveMainTex,
		FadeIn,
		FadeOut,
		SetFade,
		SetUnFade,
		WriteText,
		ReadText,
		RemoveText,
		ReadVoice,
		PlayBGM,
		ResetBGM,
	};

	class Helper
	{

	public:
		Helper() {}
		virtual ~Helper() {}

		std::string TextureName = "";
		std::string SoundName = "";
		std::vector<StoryFontParameter> WriteTextDatas;

		float4 Vector = float4::Zero;
		float Speed = 0.0f;

		WalkType Type = WalkType::SetFade;

		void Walk(FadeActor* _FadePtr, StoryTextureView* _ViewPtr, class StoryFontActor* _Font, class StorySound* _Sound);
	};

}


