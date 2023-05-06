#include "PrecompileHeader.h"
#include "BackgroundToolLevel.h"
#include "MultiBackground.h"
#include "BackgroundToolGUI.h"
#include "ContentDatabase.h"
#include "DebugSpriteActor.h"

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

	DebugActor = CreateActor<DebugSpriteActor>();

	MainCamCtrl.SetLookatTarget(DebugActor);
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

	MultiBackgroundPtr->UpdateTargetPos(_DeltaTime, MainCamCtrl.GetCameraPos());

	if (true == BackgroundToolGUIPtr->CheckSaveTrigger())
	{
		Save();
	}
	else if (true == BackgroundToolGUIPtr->CheckLoadTrigger())
	{
		Load();
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
	std::string Path = ContentFunc::GetSaveFilePath();

	if ("" == Path)
	{
		return;
	}

	GameEngineSerializer SaveSerializer;
	SaveSerializer.BufferResize(2048);

	MultiBackgroundPtr->SaveBin(SaveSerializer);

	GameEngineFile SaveFile = GameEngineFile(Path);
	SaveFile.SaveBin(SaveSerializer);

}

void BackgroundToolLevel::Load()
{
	std::string Path = ContentFunc::GetOpenFilePath();

	if ("" == Path)
	{
		return;
	}

	GameEngineFile LoadFile = GameEngineFile(Path);

	GameEngineSerializer SaveSerializer;
	SaveSerializer.BufferResize(2048);
	LoadFile.LoadBin(SaveSerializer);

	MultiBackgroundPtr->LoadBin(SaveSerializer);
}