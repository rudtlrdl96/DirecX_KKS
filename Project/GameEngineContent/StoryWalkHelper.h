#pragma once
#include "FadeActor.h"
#include "StoryTextureView.h"

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
		SetUnFade
	};

	class Helper
	{

	public:
		Helper() {}
		virtual ~Helper() {}

		std::string TextureName = "";
		float4 Vector = float4::Zero;
		float Speed = 0.0f;

		WalkType Type = WalkType::SetFade;

		void Walk(FadeActor* _FadePtr, StoryTextureView* _ViewPtr);
	};

}


