#include "PrecompileHeader.h"
#include "SkeletonA.h"

SkeletonA::SkeletonA()
{
}

SkeletonA::~SkeletonA()
{
}

void SkeletonA::Start()
{
	BaseNPC::Start();

	MainRender->CreateAnimation({
		.AnimationName = "Idle", .SpriteName = "SkeletonA_Idle.png", .ScaleToTexture = true});

	MainRender->CreateAnimation({
		.AnimationName = "Dead", .SpriteName = "SkeletonA_Dead.png", .ScaleToTexture = true });

	MainRender->ChangeAnimation("Idle");
}

void SkeletonA::SpriteLoad()
{
	if (nullptr == GameEngineSprite::Find("SkeletonA_Idle.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("1_Opening");
		Path.Move("Npc");
		Path.Move("SkeletonA");
		Path.Move("Sheet");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("SkeletonA_Idle.png").GetFullPath(), 13, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("SkeletonA_Dead.png").GetFullPath(), 1, 1);
	}
}
