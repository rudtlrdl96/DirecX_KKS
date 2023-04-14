#include "PrecompileHeader.h"
#include "StudyActor.h"
#include <GameEngineCore/GameEngineRenderer.h>

StudyActor::StudyActor()
{
}

StudyActor::~StudyActor()
{
}

void StudyActor::Start()
{
	std::shared_ptr<GameEngineRenderer> RenderPtr = CreateComponent<GameEngineRenderer>();
	RenderPtr->SetPipeLine("2DTexture");
}
