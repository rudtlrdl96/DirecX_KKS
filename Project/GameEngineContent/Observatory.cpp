#include "PrecompileHeader.h"
#include "Observatory.h"

Observatory::Observatory()
{
}

Observatory::~Observatory()
{
}

void Observatory::Start()
{
	BehaviorObject::Start();

	if (nullptr == GameEngineSprite::Find("Observatory.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("3_ForestOfHarmony");
		Path.Move("BehaviorObject");
		Path.Move("Observatory");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Observatory.png").GetFullPath(), 4, 2);
	}

	Render->SetScaleRatio(2.0f);
	Render->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Observatory.png", .Start = 0, .End = 6, .Loop = true, .ScaleToTexture = true });
	Render->ChangeAnimation("Idle");
}

void Observatory::Update(float _DeltaTime)
{
}

void Observatory::ResetBehavior()
{
}

void Observatory::PlayBehavior()
{
}
