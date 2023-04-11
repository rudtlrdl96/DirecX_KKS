#include "PrecompileHeader.h"
#include "ContentCore.h"
#include <GameEngineCore/GameEngineCore.h>
#include "LogoLevel.h"

ContentCore::ContentCore()
{
}

ContentCore::~ContentCore()
{
}

void ContentCore::CoreLoading()
{
	GameEngineCore::CreateLevel<LogoLevel>("Logo");
	GameEngineCore::ChangeLevel("Logo");
}

void ContentCore::CoreEnd()
{

}