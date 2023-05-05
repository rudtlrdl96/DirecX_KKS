#include "PrecompileHeader.h"
#include "BackgroundToolLevel.h"
#include "MultiBackground.h"
#include "BackgroundToolGUI.h"
#include "ContentDatabase.h"

BackgroundToolLevel::BackgroundToolLevel()
{
}

BackgroundToolLevel::~BackgroundToolLevel()
{
}

void BackgroundToolLevel::Start()
{
	ContentLevel::Start();

	MultiBackgroundPtr = CreateActor<MultiBackground>();

	BackgroundToolGUIPtr = GameEngineGUI::FindGUIWindowConvert<BackgroundToolGUI>("BackgroundToolGUI");

	if (nullptr == BackgroundToolGUIPtr)
	{
		MsgAssert_Rtti<BackgroundToolLevel>(" - 백그라운드툴을 찾을 수 없습니다");
		return;
	}

	BackgroundToolGUIPtr->Pushback_OnGuiCallbackFunc(std::bind(&MultiBackground::ShowGUI, MultiBackgroundPtr));
}

void BackgroundToolLevel::Update(float _DeltaTime)
{
	ContentLevel::Update(_DeltaTime);

	if (true == BackgroundToolGUIPtr->CheckCreateTrigger())
	{
		int NewIndex = BackgroundToolGUIPtr->GetSelectBackgroundIndex();

		if (NewIndex >= 0)
		{
			BG_DESC NewDesc = ContentDatabase<BG_DESC, LevelArea>::GetData(static_cast<size_t>(NewIndex));
			MultiBackgroundPtr->CreateBackground(NewDesc);
		}
	}
}

void BackgroundToolLevel::LevelChangeStart()
{
	if (nullptr == BackgroundToolGUIPtr)
	{
		MsgAssert_Rtti<BackgroundToolLevel>(" - 백그라운드툴을 찾을 수 없습니다");
	}

	BackgroundToolGUIPtr->On();
}

void BackgroundToolLevel::LevelChangeEnd()
{
	if (nullptr == BackgroundToolGUIPtr)
	{
		MsgAssert_Rtti<BackgroundToolLevel>(" - 백그라운드툴을 찾을 수 없습니다");
	}

	BackgroundToolGUIPtr->Off();
}

void BackgroundToolLevel::Save()
{

}

void BackgroundToolLevel::Load()
{
}