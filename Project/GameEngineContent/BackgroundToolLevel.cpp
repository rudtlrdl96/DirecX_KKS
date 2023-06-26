#include "PrecompileHeader.h"
#include "BackgroundToolLevel.h"

#include "BackgroundToolGUI.h"
#include "GameEngineActorGUI.h"

#include "MultiBackground.h"
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

	//MainCamCtrl.SetMinWidth(128);
	//MainCamCtrl.SetMinHeight(128);

	MultiBackgroundPtr = CreateActor<MultiBackground>();

	BackgroundToolGUIPtr = GameEngineGUI::FindGUIWindowConvert<BackgroundToolGUI>("BackgroundToolGUI");

	if (nullptr == BackgroundToolGUIPtr)
	{
		MsgAssert_Rtti<BackgroundToolLevel>(" - 백그라운드툴을 찾을 수 없습니다");
		return;
	}

	BackgroundToolGUIPtr->Pushback_OnGuiCallbackFunc(std::bind(&MultiBackground::ShowGUI, MultiBackgroundPtr));


	ActorGUIPtr = GameEngineGUI::FindGUIWindowConvert<GameEngineActorGUI>("GameEngineActorGUI");

	if (nullptr == ActorGUIPtr)
	{
		MsgAssert_Rtti<BackgroundToolLevel>(" - GameEngineActor Gui가 생성되지 않았습니다.");
	}

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
			BackgroundMetaData NewMetaData = ContentDatabase<BackgroundMetaData, LevelArea>::GetData(static_cast<size_t>(NewIndex));
			MultiBackgroundPtr->CreateBackground(NewMetaData);
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
	ContentLevel::LevelChangeStart();

	if (nullptr == BackgroundToolGUIPtr)
	{
		MsgAssert_Rtti<BackgroundToolLevel>(" - 백그라운드툴을 찾을 수 없습니다");
	}

	BackgroundToolGUIPtr->On();

	if (nullptr == ActorGUIPtr)
	{
		MsgAssert_Rtti<BackgroundToolLevel>(" - GameEngineActor Gui를 찾을 수 없습니다");
		return;
	}

	ActorGUIPtr->SetTarget(DebugActor->GetTransform());
	ActorGUIPtr->On();
}

void BackgroundToolLevel::LevelChangeEnd()
{
	ContentLevel::LevelChangeEnd();

	if (nullptr == BackgroundToolGUIPtr)
	{
		MsgAssert_Rtti<BackgroundToolLevel>(" - 백그라운드툴을 찾을 수 없습니다");
	}

	BackgroundToolGUIPtr->Off();

	if (nullptr == ActorGUIPtr)
	{
		MsgAssert_Rtti<BackgroundToolLevel>(" - GameEngineActor Gui를 찾을 수 없습니다");
		return;
	}

	ActorGUIPtr->SetTarget(nullptr);
	ActorGUIPtr->Off();
}



void BackgroundToolLevel::Save()
{
	std::string Path = ContentFunc::GetSaveFilePath();

	if ("" == Path)
	{
		return;
	}

	GameEngineSerializer SaveSerializer;
	SaveSerializer.BufferResize(4096);

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
	SaveSerializer.BufferResize(4096);
	LoadFile.LoadBin(SaveSerializer);

	MultiBackgroundPtr->LoadBin(SaveSerializer);
}