#include "PrecompileHeader.h"
#include "Spider.h"

Spider::Spider()
{
}

Spider::~Spider()
{
}

void Spider::Start()
{
	BehaviorObject::Start();

	if (nullptr == GameEngineSprite::Find("SpiderIdle.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("2_Castle");
		Path.Move("BehaviorObject");
		Path.Move("Spider");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("SpiderIdle.png").GetFullPath(), 9, 1);
	}

	Render->SetScaleRatio(2.0f);
	Render->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "SpiderIdle.png", .Loop = true, .ScaleToTexture = true });
	Render->ChangeAnimation("Idle");
}

void Spider::Update(float _DeltaTime)
{
}

void Spider::ResetBehavior()
{
}

void Spider::PlayBehavior()
{
}
