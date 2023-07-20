#include "PrecompileHeader.h"
#include "FlagA.h"

FlagA::FlagA()
{
}

FlagA::~FlagA()
{
}

void FlagA::Start()
{
	BehaviorObject::Start();

	if (nullptr == GameEngineSprite::Find("ForestFlagA.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("3_ForestOfHarmony");
		Path.Move("BehaviorObject");
		Path.Move("FlagA");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ForestFlagA.png").GetFullPath(), 6, 1);
	}

	Render->SetScaleRatio(2.0f);
	Render->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "ForestFlagA.png", .Loop = true, .ScaleToTexture = true });
	Render->ChangeAnimation("Idle");
}

void FlagA::Update(float _DeltaTime)
{
}

void FlagA::ResetBehavior()
{
}

void FlagA::PlayBehavior()
{
}
