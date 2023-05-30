#include "PrecompileHeader.h"
#include "TitleLevel.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineCore/GameEngineCamera.h>

#include "BlackBackground.h"
#include "FadeActor.h"
#include "TitleLogo.h"
#include "TitleActor.h"

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Start()
{
	UILevel::Start();

	GameEngineDirectory Path;
	Path.MoveParentToDirectory("Resources");
	Path.Move("Resources");
	Path.Move("Texture");
	Path.Move("8_Title");
	Path.Move("UI");

	{
		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineTexture::Load(Files[i].GetFullPath());
		}
	}

	BlackBG = CreateActor<BlackBackground>();
	
	Logo = CreateActor<TitleLogo>();
	Logo->SetLogo("Logo_SouthPAW.png", 1.0f, 2.0f, 1.0f, 0.25f);

	Title = CreateActor<TitleActor>();

	Fade = CreateActor<FadeActor>();
	Fade->SetUnFade();
}

void TitleLevel::Update(float _DeltaTime)
{
	UILevel::Update(_DeltaTime);

	switch (State)
	{
	case TitleLevel::TitleState::DevLogo:
		if (true == Logo->IsLogoEnd())
		{
			Logo->SetLogo("Logo_Neowiz.png", 1.0f, 2.0f, 1.0f, 0.4f);
			State = TitleLevel::TitleState::PublishingLogo;
		}
		break;
	case TitleLevel::TitleState::PublishingLogo:
		if (true == Logo->IsLogoEnd())
		{
			Logo->Off();
			Fade->SetSpeed(0.5f);
			Fade->FadeOut();
			Title->TitleOn(2.0f, 1.5f);
			State = TitleLevel::TitleState::Intro;
		}
		break;
	case TitleLevel::TitleState::Intro:
		if(true == Title->IsLogoFadeEnd())
		{
			State = TitleLevel::TitleState::InputWait;
		}
		break;
	case TitleLevel::TitleState::InputWait:

		if (false == IsInputWait)
		{
			return;
		}
		
		if (true == GameEngineInput::IsAnyKey())
		{
			IsInputWait = false;

			Fade->FadeIn([]()
				{
					GameEngineCore::ChangeLevel("Opening");
				});

		}
		break;
	default:
		break;
	}
}

void TitleLevel::LevelChangeStart()
{
	IsInputWait = true;
}
