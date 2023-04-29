#include "PrecompileHeader.h"
#include "StoryLevel.h"

#include <GameEnginePlatform/GameEngineInput.h>

#include "FadeActor.h"
#include "StoryFrontImage.h"
#include "StoryTextureView.h"
#include "StoryBackImage.h"

StoryLevel::StoryLevel()
{
}

StoryLevel::~StoryLevel()
{
}

void StoryLevel::Start()
{
	UILevel::Start();

	GameEngineDirectory Path;
	Path.MoveParentToDirectory("Resources");
	Path.Move("Resources");
	Path.Move("Texture");
	Path.Move("UI");
	Path.Move("Story");

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

	//BackImage = CreateActor<StoryBackImage>();
	StoryView = CreateActor<StoryTextureView>();
	FrontImage = CreateActor<StoryFrontImage>();

	FadeImage = CreateActor<FadeActor>();
	FadeImage->SetSpeed(0.5f);

	SetOpeningBook();
	SetForestOfHarmonyBook();
	SetGrandHallBook();
	SetHolyCourtyard();
	SetEndingBook();
}

void StoryLevel::Update(float _DeltaTime)
{
	UILevel::Update(_DeltaTime);

	if (true == GameEngineInput::IsDown("Story_Opening"))
	{
		SetSotoryName(StoryName::Opening);
	}
	else if (true == GameEngineInput::IsDown("Story_ForestOfHarmony"))
	{
		SetSotoryName(StoryName::ForestOfHarmony);
	}
	else if (true == GameEngineInput::IsDown("Story_GranHall"))
	{
		SetSotoryName(StoryName::GranHall);
	}
	else if (true == GameEngineInput::IsDown("Story_HolyCourtyard"))
	{
		SetSotoryName(StoryName::HolyCourtyard);
	}
	else if (true == GameEngineInput::IsDown("Story_Ending"))
	{
		SetSotoryName(StoryName::Ending);
	}

	StoryBookDatas[CurStoryName].Update(_DeltaTime);
}

void StoryLevel::LevelChangeStart()
{
	StoryReset();	
}


void StoryLevel::StoryReset()
{
	FadeImage->SetUnFade();

	FadeImage->Reset();
	StoryView->Reset();

	std::map<StoryName, StoryBook>::iterator LoopIter = StoryBookDatas.begin();
	std::map<StoryName, StoryBook>::iterator EndIter = StoryBookDatas.end();

	while (LoopIter != EndIter)
	{
		LoopIter->second.Reset();
		++LoopIter;
	}
}