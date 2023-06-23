#pragma once
#include "StoryWalkHelper.h"

class StoryPage
{
public:
	enum class FlipCondition
	{
		None   = 0,      
		UnCondition = 1 << 0, // 조건 없이 바로 실행
		AnyKey		= 1 << 1, // 키를 누르면
		Time		= 1 << 2, // 일정 시간을 기다리면
		VoiceEnd	= 1 << 3, // 보이스 실행이 End 상태일때
	};
public:
	StoryPage();
	~StoryPage();

	void PageRead(FadeActor* FadePtr, StoryTextureView* _View, StoryFontActor* _Font, StorySound* _Sound);

	void SetFlip(FlipCondition _Condition, float _Time = 5.0f);
	bool IsFlipCheck(std::shared_ptr<StorySound> _SoundActor);

	void Update(float _DeltaTime);

	void Write_SetMainTex(const std::string_view& _Name, const float4& _Pos);
	void Write_SetSubTex(const std::string_view& _Name, const float4& _Pos);
	void Write_SetBackTex(const std::string_view& _Name, const float4& _Pos);
	void Write_SwapTex();
	void Write_FadeIntro(float _FadeSpeed);
	void Write_MoveMainTex(const float4& _MoveDir, float _MoveSpeed);
	void Write_FadeIn(float _FadeSpeed);
	void Write_FadeOut(float _FadeSpeed);
	void Write_SetFade();
	void Write_SetUnFade();
	void Write_WriteText(std::vector<StoryFontParameter> _TextDatas);
	void Write_ReadText();
	void Write_ResetText();
	void Write_ReadVoice(const std::string_view& _VoiceName);
	void Write_PlayBGM(const std::string_view& _SoundName);
	void Write_ResetBGM();

	inline void Reset()
	{
		ProgressTime = 0.0f;
	}

private:
	FlipCondition FlipCheck = FlipCondition::None;

	float FlipTime = 5.0f;
	float ProgressTime = 0.0f;

	float VoiceFlipTime = 0.0f;

	std::vector<StoryUI::Helper> WalkHelpers;
};

