#include "LogoLevel.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include "VertexActor.h"

LogoLevel::LogoLevel()
{
}

LogoLevel::~LogoLevel()
{
}

void LogoLevel::Loading()
{
	CreateActor<VertexActor>();

	GameEngineInput::CreateKey("ScaleUp", VK_RIGHT);
	GameEngineInput::CreateKey("ScaleDown", VK_LEFT);
	GameEngineInput::CreateKey("AngleUp", VK_UP);
	GameEngineInput::CreateKey("AngleDown", VK_DOWN);

	GameEngineInput::CreateKey("MoveLeft", 'a');
	GameEngineInput::CreateKey("MoveRight", 'd');
	GameEngineInput::CreateKey("MoveUp", 'w');
	GameEngineInput::CreateKey("MoveDown", 's');

	GameEngineInput::CreateKey("ChildAnlgeUp", 'q');
	GameEngineInput::CreateKey("ChildAnlgeDown", 'e');
}
