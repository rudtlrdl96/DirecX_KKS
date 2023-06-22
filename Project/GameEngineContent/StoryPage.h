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
	};
public:
	StoryPage();
	~StoryPage();

	void PageRead(FadeActor* FadePtr, StoryTextureView* _View, StoryFontActor* _Font);

	void SetFlip(FlipCondition _Condition, float _Time = 5.0f);
	bool IsFlipCheck();

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
	void Wirte_Text(std::vector<StoryFontParameter> _TextDatas);
	void Wirte_ResetText();

	inline void Reset()
	{
		ProgressTime = 0.0f;
	}

private:
	FlipCondition FlipCheck = FlipCondition::None;

	float FlipTime = 5.0f;
	float ProgressTime = 0.0f;

	std::vector<StoryUI::Helper> WalkHelpers;
};

