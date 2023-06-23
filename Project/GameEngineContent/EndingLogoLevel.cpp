#include "PrecompileHeader.h"
#include "EndingLogoLevel.h"
#include "BlackBackground.h"
#include "SkulLogo.h"

EndingLogoLevel::EndingLogoLevel()
{
}

EndingLogoLevel::~EndingLogoLevel()
{
}

void EndingLogoLevel::Start()
{
	UILevel::Start();

	GameEngineDirectory Path;
	Path.MoveParentToDirectory("Resources");
	Path.Move("Resources");
	Path.Move("Texture");
	Path.Move("10_EndingLogo");
	Path.Move("UI");

	{
		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineTexture::Load(Files[i].GetFullPath());
		}
	}

	BackPtr = CreateActor<BlackBackground>();
	LogoPtr = CreateActor<SkulLogo>();

}

void EndingLogoLevel::Update(float _DeltaTime)
{
	UILevel::Update(_DeltaTime);


	if (false == LogoPtr->IsUpdate())
	{
		LogoWaitTime += _DeltaTime;

		if (1.0f <= LogoWaitTime)
		{
			LogoPtr->On();
		}
	}
}

void EndingLogoLevel::LevelChangeStart()
{
	UILevel::LevelChangeStart();

	LogoWaitTime = 0.0f;
	LogoPtr->Off();
}
