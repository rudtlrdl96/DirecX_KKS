#include "PrecompileHeader.h"
#include "SkeleTong.h"

SkeleTong::SkeleTong()
{
}

SkeleTong::~SkeleTong()
{
}

void SkeleTong::Start()
{
	BaseNPC::Start();

	MainRender->CreateAnimation({
		.AnimationName = "Idle", .SpriteName = "SkeleTong_Idle.png", .FrameInter = 0.2f, .ScaleToTexture = true });

	MainRender->CreateAnimation({
		.AnimationName = "Dead", .SpriteName = "SkeleTong_Dead.png", .ScaleToTexture = true });

	MainRender->CreateAnimation({
		.AnimationName = "Wow", .SpriteName = "SkeleTong_Wow.png", .ScaleToTexture = true });

	MainRender->CreateAnimation({
		.AnimationName = "Surqrise", .SpriteName = "SkeleTong_Surqrise.png", .ScaleToTexture = true });

	MainRender->CreateAnimation({
		.AnimationName = "Talk", .SpriteName = "SkeleTong_Talk.png", .ScaleToTexture = true });

	MainRender->CreateAnimation({
		.AnimationName = "Walk", .SpriteName = "SkeleTong_Walk.png", .ScaleToTexture = true });

	MainRender->ChangeAnimation("Idle");
}

void SkeleTong::SpriteLoad()
{
	if (nullptr == GameEngineSprite::Find("SkeleTong_Idle.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("1_Opening");
		Path.Move("Npc");
		Path.Move("SkeleTong");
		Path.Move("Sheet");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("SkeleTong_Idle.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("SkeleTong_Dead.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("SkeleTong_Wow.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("SkeleTong_Surqrise.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("SkeleTong_Talk.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("SkeleTong_Walk.png").GetFullPath(), 13, 1);
	}
}