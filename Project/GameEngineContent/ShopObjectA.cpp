#include "PrecompileHeader.h"
#include "ShopObjectA.h"

ShopObjectA::ShopObjectA()
{
}

ShopObjectA::~ShopObjectA()
{
}

void ShopObjectA::Start()
{
	BehaviorObject::Start();

	if (nullptr == GameEngineSprite::Find("ShopObjectA.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("7_Shop");
		Path.Move("BehaviorObject");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ShopObjectA.png").GetFullPath(), 4, 2);
	}

	Render->SetScaleRatio(2.0f);
	Render->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "ShopObjectA.png", .Loop = true, .ScaleToTexture = true });
	Render->ChangeAnimation("Idle");
}

void ShopObjectA::Update(float _DeltaTime)
{
}

void ShopObjectA::ResetBehavior()
{
}

void ShopObjectA::PlayBehavior()
{
}