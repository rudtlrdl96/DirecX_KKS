#include "PrecompileHeader.h"
#include "ShopObjectB.h"

ShopObjectB::ShopObjectB()
{
}

ShopObjectB::~ShopObjectB()
{
}

void ShopObjectB::Start()
{
	BehaviorObject::Start();

	if (nullptr == GameEngineSprite::Find("ShopObjectB.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("7_Shop");
		Path.Move("BehaviorObject");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ShopObjectB.png").GetFullPath(), 4, 2);
	}

	Render->SetScaleRatio(2.0f);
	Render->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "ShopObjectB.png", .Loop = true, .ScaleToTexture = true });
	Render->ChangeAnimation("Idle");
}

void ShopObjectB::Update(float _DeltaTime)
{
}

void ShopObjectB::ResetBehavior()
{
}

void ShopObjectB::PlayBehavior()
{
}