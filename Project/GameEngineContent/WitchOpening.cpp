#include "PrecompileHeader.h"
#include "WitchOpening.h"

WitchOpening::WitchOpening()
{
}

WitchOpening::~WitchOpening()
{
}

void WitchOpening::Start()
{
	BaseNPC::Start();

	MainRender->CreateAnimation({
		.AnimationName = "CageIdle", .SpriteName = "Witch_OpeningCage.png", .ScaleToTexture = true });

	MainRender->CreateAnimation({
		.AnimationName = "HumanIdle", .SpriteName = "Witch_OpeningIdle.png", .ScaleToTexture = true });

	MainRender->CreateAnimation({
		.AnimationName = "CatPolymorp", .SpriteName = "Witch_CatPolymorp.png", .ScaleToTexture = true });

	MainRender->CreateAnimation({
		.AnimationName = "CatIdle", .SpriteName = "Witch_Cat_Idle.png", .ScaleToTexture = true });

	MainRender->CreateAnimation({
		.AnimationName = "CatWalk", .SpriteName = "Witch_Cat_Walk.png", .ScaleToTexture = true });

	GetTransform()->SetLocalNegativeScaleX();
	MainRender->ChangeAnimation("CageIdle");
}

void WitchOpening::Update(float _DeltaTime)
{
	BaseNPC::Update(_DeltaTime);
}

void WitchOpening::ResetBehavior()
{
}

void WitchOpening::PlayBehavior()
{
}

void WitchOpening::SpriteLoad()
{
	if (nullptr == GameEngineSprite::Find("Witch_OpeningCage.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("1_Opening");
		Path.Move("Npc");
		Path.Move("Witch");
		Path.Move("Sheet");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Witch_OpeningCage.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Witch_OpeningIdle.png").GetFullPath(), 6, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Witch_CatPolymorp.png").GetFullPath(), 21, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Witch_Cat_Idle.png").GetFullPath(), 6, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Witch_Cat_Walk.png").GetFullPath(), 6, 1);
	}
}