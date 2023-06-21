#include "PrecompileHeader.h"
#include "StoryPage.h"
#include <GameEnginePlatform/GameEngineInput.h>

StoryPage::StoryPage()
{
	WalkHelpers.reserve(8);
}

StoryPage::~StoryPage()
{
}

void StoryPage::PageRead(FadeActor* FadePtr, StoryTextureView* _View, RectFontActor* _Font)
{
	if (nullptr == FadePtr)
	{
		MsgAssert_Rtti<StoryPage>("nullptr FadePtr이 입력되었습니다");
	}

	if (nullptr == _View)
	{
		MsgAssert_Rtti<StoryPage>("nullptr ViewPtr이 입력되었습니다");
	}

	for (size_t i = 0; i < WalkHelpers.size(); i++)
	{
		WalkHelpers[i].Walk(FadePtr, _View, _Font);
	}

}

void StoryPage::SetFlip(FlipCondition _Condition, float _Time/*= 5.0f*/)
{
	FlipCheck = _Condition;
	FlipTime = _Time;
}

bool StoryPage::IsFlipCheck()
{
	bool Result = false;
	int Check = static_cast<int>(FlipCheck);

	if(Check & static_cast<int>(FlipCondition::UnCondition))
	{
		return true;
	}

	if (Check & static_cast<int>(FlipCondition::Time))
	{
		if (ProgressTime >= FlipTime)
		{
			Result = true;
		}
	}

	if (Check & static_cast<int>(FlipCondition::AnyKey))
	{
		if (true == GameEngineInput::IsAnyKey())
		{
			Result = true;
		}
	}

	return Result;
}

void StoryPage::Update(float _DeltaTime)
{
	ProgressTime += _DeltaTime;
}

void StoryPage::Write_SetMainTex(const std::string_view& _Name, const float4& _Pos)
{
	StoryUI::Helper Newhelper;

	Newhelper.Type = StoryUI::WalkType::SetMainTex;
	Newhelper.TextureName = _Name;
	Newhelper.Vector = _Pos;

	WalkHelpers.push_back(Newhelper);
}

void StoryPage::Write_SetSubTex(const std::string_view& _Name, const float4& _Pos)
{
	StoryUI::Helper Newhelper;

	Newhelper.Type = StoryUI::WalkType::SetSubTex;
	Newhelper.TextureName = _Name;
	Newhelper.Vector = _Pos;

	WalkHelpers.push_back(Newhelper);
}

void StoryPage::Write_SetBackTex(const std::string_view& _Name, const float4& _Pos)
{
	StoryUI::Helper Newhelper;

	Newhelper.Type = StoryUI::WalkType::SetBackTex;
	Newhelper.TextureName = _Name;
	Newhelper.Vector = _Pos;

	WalkHelpers.push_back(Newhelper);
}

void StoryPage::Write_SwapTex()
{
	StoryUI::Helper Newhelper;
	Newhelper.Type = StoryUI::WalkType::SwapTex;
	WalkHelpers.push_back(Newhelper);
}

void StoryPage::Write_FadeIntro(float _FadeSpeed)
{
	StoryUI::Helper Newhelper;
	Newhelper.Type = StoryUI::WalkType::FadeIntro;
	Newhelper.Speed = _FadeSpeed;
	WalkHelpers.push_back(Newhelper);
}

void StoryPage::Write_MoveMainTex(const float4& _MoveDir, float _MoveSpeed)
{
	StoryUI::Helper Newhelper;
	Newhelper.Type = StoryUI::WalkType::MoveMainTex;
	Newhelper.Vector = _MoveDir;
	Newhelper.Speed = _MoveSpeed;
	WalkHelpers.push_back(Newhelper);
}

void StoryPage::Write_FadeIn(float _FadeSpeed)
{
	StoryUI::Helper Newhelper;
	Newhelper.Type = StoryUI::WalkType::FadeIn;
	Newhelper.Speed = _FadeSpeed;
	WalkHelpers.push_back(Newhelper);
}

void StoryPage::Write_FadeOut(float _FadeSpeed)
{
	StoryUI::Helper Newhelper;
	Newhelper.Type = StoryUI::WalkType::FadeOut;
	Newhelper.Speed = _FadeSpeed;
	WalkHelpers.push_back(Newhelper);
}

void StoryPage::Write_SetFade()
{
	StoryUI::Helper Newhelper;
	Newhelper.Type = StoryUI::WalkType::SetFade;
	WalkHelpers.push_back(Newhelper);
}

void StoryPage::Write_SetUnFade()
{
	StoryUI::Helper Newhelper;
	Newhelper.Type = StoryUI::WalkType::SetUnFade;
	WalkHelpers.push_back(Newhelper);
}

void StoryPage::Wirte_Text(const std::string_view _Text)
{
	StoryUI::Helper Newhelper;
	Newhelper.Type = StoryUI::WalkType::WriteText;
	WalkHelpers.push_back(Newhelper);
}
