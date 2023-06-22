#include "PrecompileHeader.h"
#include "StoryLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>

#include "FadeActor_UI.h"
#include "StoryFrontImage.h"
#include "StoryFontActor.h"
#include "StoryTextureView.h"
#include "StoryBackImage.h"

StoryLevel::StoryName StoryLevel::ChangeStoryName = StoryName::Opening;
std::string StoryLevel::StoryEndMoveLevel = "";

StoryLevel::StoryLevel()
{
}

StoryLevel::~StoryLevel()
{
}

#include "GameEngineActorGUI.h"

void StoryLevel::Start()
{
	UILevel::Start();

	GameEngineDirectory Path;
	Path.MoveParentToDirectory("Resources");
	Path.Move("Resources");
	Path.Move("Texture");
	Path.Move("9_Story");
	Path.Move("UI");

	{
		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (size_t i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> Tex = GameEngineTexture::Load(Files[i].GetFullPath());
		}
	}

	if (false == GameEngineInput::IsKey("Story_Opening"))
	{
		GameEngineInput::CreateKey("Story_Opening", '1');
		GameEngineInput::CreateKey("Story_ForestOfHarmony", '2');
		GameEngineInput::CreateKey("Story_GranHall", '3');
		GameEngineInput::CreateKey("Story_HolyCourtyard", '4');
		GameEngineInput::CreateKey("Story_Ending", '5');
	}

	FadeImage = CreateActor<FadeActor_UI>();
	FadeImage->GetTransform()->SetLocalPosition({ 0, 0, -1000 });
	FadeImage->SetSpeed(0.5f);

	BackImage = CreateActor<StoryBackImage>();
	StoryView = CreateActor<StoryTextureView>();
	FrontImage = CreateActor<StoryFrontImage>();

	StoryFont = CreateActor<StoryFontActor>();
	StoryFont->GetTransform()->SetLocalPosition({ 0, -270, -2000});
	
	SetOpeningBook();
	SetForestOfHarmonyBook();
	SetGrandHallBook();
	SetHolyCourtyard();
	SetEndingBook();
}

void StoryLevel::Update(float _DeltaTime)
{
	UILevel::Update(_DeltaTime);

	if (true == GameEngineInput::IsUp("Story_Opening"))
	{
		SetStoryName(StoryName::Opening);
	}
	else if (true == GameEngineInput::IsUp("Story_ForestOfHarmony"))
	{
		SetStoryName(StoryName::ForestOfHarmony);
	}
	else if (true == GameEngineInput::IsUp("Story_GranHall"))
	{
		SetStoryName(StoryName::GranHall);
	}
	else if (true == GameEngineInput::IsUp("Story_HolyCourtyard"))
	{
		SetStoryName(StoryName::HolyCourtyard);
	}
	else if (true == GameEngineInput::IsUp("Story_Ending"))
	{
		SetStoryName(StoryName::Ending);
	}

	StoryBookDatas[CurStoryName].Update(_DeltaTime);

	if (true == StoryBookDatas[CurStoryName].IsBookEnd() && true == FadeImage->IsFadeEnd())
	{
		if ("" != StoryEndMoveLevel)
		{
			GameEngineCore::ChangeLevel(StoryEndMoveLevel);
			StoryEndMoveLevel = "";
		}
	}
}

void StoryLevel::LevelChangeStart()
{
	std::shared_ptr<GameEngineActorGUI> Ptr = GameEngineGUI::FindGUIWindowConvert<GameEngineActorGUI>("GameEngineActorGUI");
	Ptr->SetTarget(StoryFont->GetTransform());
	Ptr->On();

	SetStoryName(ChangeStoryName);
	StoryReset();
}


void StoryLevel::StoryReset()
{
	FadeImage->SetUnFade();
	FadeImage->Reset();
	StoryView->Reset();
	StoryFont->Reset();

	std::map<StoryName, StoryBook>::iterator LoopIter = StoryBookDatas.begin();
	std::map<StoryName, StoryBook>::iterator EndIter = StoryBookDatas.end();

	while (LoopIter != EndIter)
	{
		LoopIter->second.Reset();
		++LoopIter;
	}
}