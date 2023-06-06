#include "PrecompileHeader.h"
#include "SueKeleton.h"

SueKeleton::SueKeleton()
{
}

SueKeleton::~SueKeleton()
{
}

void SueKeleton::Start()
{
	BaseNPC::Start();

	MainRender->CreateAnimation({
		.AnimationName = "Idle", .SpriteName = "SueKeleton_Idle.png", .ScaleToTexture = true });

	MainRender->CreateAnimation({
		.AnimationName = "Dead", .SpriteName = "SueKeleton_Dead.png", .Loop = false, .ScaleToTexture = true });

	MainRender->CreateAnimation({
		.AnimationName = "Wow", .SpriteName = "SueKeleton_GiveWeapon.png", .ScaleToTexture = true });

	MainRender->ChangeAnimation("Idle");
}

void SueKeleton::SpriteLoad()
{
	if (nullptr == GameEngineSprite::Find("SueKeleton_Idle.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("1_Opening");
		Path.Move("Npc");
		Path.Move("SueKeleton");
		Path.Move("Sheet");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("SueKeleton_Idle.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("SueKeleton_GiveWeapon.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("SueKeleton_Dead.png").GetFullPath(), 9, 1);
	}
}
