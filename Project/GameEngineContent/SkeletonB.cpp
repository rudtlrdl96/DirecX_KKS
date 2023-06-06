#include "PrecompileHeader.h"
#include "SkeletonB.h"

SkeletonB::SkeletonB()
{
}

SkeletonB::~SkeletonB()
{
}

void SkeletonB::Start()
{
	BaseNPC::Start();

	MainRender->CreateAnimation({
		.AnimationName = "Idle", .SpriteName = "SkeletonB_Idle.png", .ScaleToTexture = true });

	MainRender->CreateAnimation({
		.AnimationName = "Dead", .SpriteName = "SkeletonB_Dead.png", .ScaleToTexture = true });

	MainRender->ChangeAnimation("Idle");
}

void SkeletonB::SpriteLoad()
{
	if (nullptr == GameEngineSprite::Find("SkeletonB_Idle.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("1_Opening");
		Path.Move("Npc");
		Path.Move("SkeletonB");
		Path.Move("Sheet");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("SkeletonB_Idle.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("SkeletonB_Dead.png").GetFullPath(), 1, 1);
	}
}
