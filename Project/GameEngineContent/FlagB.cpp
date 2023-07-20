#include "PrecompileHeader.h"
#include "FlagB.h"

FlagB::FlagB()
{
}

FlagB::~FlagB()
{
}

void FlagB::Start()
{
	BehaviorObject::Start();

	if (nullptr == GameEngineSprite::Find("ForestFlagB.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("3_ForestOfHarmony");
		Path.Move("BehaviorObject");
		Path.Move("FlagB");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ForestFlagB.png").GetFullPath(), 4, 2);
	}

	Render->SetScaleRatio(2.0f);
	Render->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "ForestFlagB.png", .Start = 0, .End = 6, .Loop = true, .ScaleToTexture = true });
	Render->ChangeAnimation("Idle");
}

void FlagB::Update(float _DeltaTime)
{
}

void FlagB::ResetBehavior()
{
}

void FlagB::PlayBehavior()
{
}
