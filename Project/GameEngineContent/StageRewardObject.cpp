#include "PrecompileHeader.h"
#include "StageRewardObject.h"

StageRewardObject::StageRewardObject()
{
}

StageRewardObject::~StageRewardObject()
{
}

void StageRewardObject::SetReward(RewardType _Type)
{
	switch (Type)
	{
	case RewardType::Normal:
	{
		GoldRewardInit();
	}
		break;
	case RewardType::Skull:
	{
		SkullRewardInit();
	}
		break;
	case RewardType::MiddleBoss:
	{
	
	}
		break;
	default:
		MsgAssert_Rtti<StageRewardObject>(" - 잘못된 리워드 타입입니다");
		break;
	}

}

void StageRewardObject::Start()
{
	Render = CreateComponent<GameEngineSpriteRenderer>();
	Render->GetTransform()->SetLocalScale(float4(150, 150));

	RewardCol = CreateComponent<GameEngineCollision>();
	RewardCol->GetTransform()->SetLocalScale(float4(150, 150));

	if (false == GameEngineInput::IsKey("UseKey"))
	{
		GameEngineInput::CreateKey("UseKey", 'F');
	}
}

void StageRewardObject::Update(float _DeltaTime)
{
	if (RewardType::None == Type)
	{
		return;
	}

	if (nullptr == RewardCol->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		return;
	}

	if (true == GameEngineInput::IsDown("UseKey"))
	{
		IsRewardEndValue = true;
	}
}

void StageRewardObject::GoldRewardInit()
{
}

void StageRewardObject::SkullRewardInit()
{
	if (nullptr == GameEngineSprite::Find("Normal_SkullRewardIdle.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("Reward");
		Path.Move("Skull");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Normal_SkullRewardIdle.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Normal_SkullRewardOpen.png").GetFullPath(), 3, 4);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Rare_SkullRewardIdle.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Rare_SkullRewardOpen.png").GetFullPath(), 3, 4);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Unique_SkullRewardIdle.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Unique_SkullRewardOpen.png").GetFullPath(), 4, 4);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Legendary_SkullRewardIdle.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Legendary_SkullRewardOpen.png").GetFullPath(), 5, 3);
	}

	Render->CreateAnimation({ .AnimationName = "Skull_Normal_Idle", .SpriteName = "Normal_SkullRewardIdle.png" });
	Render->CreateAnimation({ .AnimationName = "Skull_Normal_Open", .SpriteName = "Normal_SkullRewardOpen.png",
		.Start = 0, .End = 10, .FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });

	Render->CreateAnimation({ .AnimationName = "Skull_Rare_Idle", .SpriteName = "Rare_SkullRewardIdle.png" });
	Render->CreateAnimation({ .AnimationName = "Skull_Rare_Open", .SpriteName = "Rare_SkullRewardOpen.png",
		.Start = 0, .End = 10, .FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });

	Render->CreateAnimation({ .AnimationName = "Skull_Unique_Idle", .SpriteName = "Unique_SkullRewardIdle.png" });
	Render->CreateAnimation({ .AnimationName = "Skull_Unique_Open", .SpriteName = "Unique_SkullRewardOpen.png",
		.Start = 0, .End = 12, .FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });

	Render->CreateAnimation({ .AnimationName = "Skull_Legendary_Idle", .SpriteName = "Legendary_SkullRewardIdle.png" });
	Render->CreateAnimation({ .AnimationName = "Skull_Legendary_Open", .SpriteName = "Legendary_SkullRewardOpen.png",
		.Start = 0, .End = 12, .FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });
}