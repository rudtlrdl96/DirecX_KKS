#include "PrecompileHeader.h"
#include "StoryWalkHelper.h"

void StoryUI::Helper::Walk(FadeActor* _FadePtr, StoryTextureView* _ViewPtr, StoryFontActor* _Font)
{
	if (nullptr == _FadePtr)
	{
		MsgAssert_Rtti<Helper>(" - Nullptr FadeActor가 입력되었습니다");
		return;
	}

	if (nullptr == _ViewPtr)
	{
		MsgAssert_Rtti<Helper>(" - Nullptr StoryTextureView가 입력되었습니다");
		return;
	}

	switch (Type)
	{
	case StoryUI::WalkType::SetMainTex:
		_ViewPtr->SetMainTexture(TextureName, Vector);
		break;
	case StoryUI::WalkType::SetSubTex:
		_ViewPtr->SetSubTexture(TextureName, Vector);
		break;
	case StoryUI::WalkType::SetBackTex:
		_ViewPtr->SetBackgroundTexture(TextureName, Vector);
		break;
	case StoryUI::WalkType::SwapTex:
		_ViewPtr->SwapMainSubTexture();
		break;
	case StoryUI::WalkType::FadeIntro:
		_ViewPtr->FadeIntro(Speed);
		break;
	case StoryUI::WalkType::MoveMainTex:
		_ViewPtr->MoveMainTexture(Vector, Speed);
		break;
	case StoryUI::WalkType::FadeIn:
		_FadePtr->SetSpeed(Speed);
		_FadePtr->FadeIn();
		break;
	case StoryUI::WalkType::FadeOut:
		_FadePtr->SetSpeed(Speed);
		_FadePtr->FadeOut();
		break;
	case StoryUI::WalkType::SetFade:
		_FadePtr->SetFade();
		break;
	case StoryUI::WalkType::SetUnFade:
		_FadePtr->SetUnFade();
		break;
	case StoryUI::WalkType::WriteText:
		_Font->WriteText(WriteTextDatas);
		break;
	case StoryUI::WalkType::ReadText:
		_Font->ReadText();
		break;
	case StoryUI::WalkType::RemoveText:
		_Font->Reset();
		break;
	default:
		break;
	}


}
