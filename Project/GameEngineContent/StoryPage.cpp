#include "PrecompileHeader.h"
#include "StoryPage.h"
#include <GameEnginePlatform/GameEngineInput.h>

bool StoryPage::PrevFrameAnykeyDown = false;

StoryPage::StoryPage()
{
	WalkHelpers.reserve(8);
}

StoryPage::~StoryPage()
{
}

void StoryPage::PageRead(FadeActor* FadePtr, StoryTextureView* _View, StoryFontActor* _Font, StorySound* _Sound)
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
		WalkHelpers[i].Walk(FadePtr, _View, _Font, _Sound);
	}

}

void StoryPage::SetFlip(FlipCondition _Condition, float _Time/*= 5.0f*/)
{
	FlipCheck = _Condition;
	FlipTime = _Time;
}

bool StoryPage::IsFlipCheck(std::shared_ptr<StorySound> _SoundActor)
{
	bool Result = false;
	int Check = static_cast<int>(FlipCheck);
	bool CurFrameAnyKey = GameEngineInput::IsAnyKey();


	if(Check & static_cast<int>(FlipCondition::UnCondition))
	{
		PrevFrameAnykeyDown = CurFrameAnyKey;
		return true;
	}

	if (Check & static_cast<int>(FlipCondition::VoiceEnd))
	{
		if (true == _SoundActor->IsVoiceEnd())
		{
			VoiceFlipTime += GameEngineTime::GlobalTime.GetDeltaTime();

			if (0.5f <= VoiceFlipTime)
			{
				Result = true;
			}
		}
		else
		{
			VoiceFlipTime = 0.0f;
		}
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
		if (true == CurFrameAnyKey && false == PrevFrameAnykeyDown)
		{
			Result = true;
		}
	}

	PrevFrameAnykeyDown = CurFrameAnyKey;
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

void StoryPage::Write_WriteText(std::vector<StoryFontParameter> _TextDatas)
{
	StoryUI::Helper Newhelper;
	Newhelper.Type = StoryUI::WalkType::WriteText;
	Newhelper.WriteTextDatas = _TextDatas;
	WalkHelpers.push_back(Newhelper);
}

void StoryPage::Write_ReadText()
{
	StoryUI::Helper Newhelper;
	Newhelper.Type = StoryUI::WalkType::ReadText;
	WalkHelpers.push_back(Newhelper);
}

void StoryPage::Write_ResetText()
{
	StoryUI::Helper Newhelper;
	Newhelper.Type = StoryUI::WalkType::RemoveText;
	WalkHelpers.push_back(Newhelper);
}

void StoryPage::Write_ReadVoice(const std::string_view& _VoiceName)
{
	StoryUI::Helper Newhelper;
	Newhelper.Type = StoryUI::WalkType::ReadVoice;
	Newhelper.SoundName = _VoiceName;
	WalkHelpers.push_back(Newhelper);
}

void StoryPage::Write_PlayBGM(const std::string_view& _SoundName)
{
	StoryUI::Helper Newhelper;
	Newhelper.Type = StoryUI::WalkType::PlayBGM;
	Newhelper.SoundName = _SoundName;
	WalkHelpers.push_back(Newhelper);
}

void StoryPage::Write_ResetBGM()
{
	StoryUI::Helper Newhelper;
	Newhelper.Type = StoryUI::WalkType::ResetBGM;
	WalkHelpers.push_back(Newhelper);
}
