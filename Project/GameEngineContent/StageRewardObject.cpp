#include "PrecompileHeader.h"
#include "StageRewardObject.h"
#include "BaseGear.h"
#include "SkullGear.h"

StageRewardObject::StageRewardObject()
{
}

StageRewardObject::~StageRewardObject()
{
}

void StageRewardObject::SetReward(RewardType _Type)
{
	Type = _Type;

	if (Type == RewardType::MiddleBoss)
	{
		TableRender->ChangeAnimation("ChoiceTable");
	}
	else
	{
		TableRender->ChangeAnimation("SingleTable");

		AllPlatformCol.resize(1);

		AllPlatformCol[0] = CreateComponent<GameEngineCollision>((int)CollisionOrder::Platform_Half);
		AllPlatformCol[0]->SetColType(ColType::AABBBOX2D);
		AllPlatformCol[0]->GetTransform()->SetLocalPosition(TableRender->GetTransform()->GetLocalPosition() + float4(0, 22.5f, 0));
		AllPlatformCol[0]->GetTransform()->SetLocalScale(float4(156, 15, 1));
		AllPlatformCol[0]->Off();
	}


	switch (Type)
	{
	case RewardType::None:
	{
		IsRewardEndValue = true;

		Render->Off();
		RewardCol->Off();
		EnterCol->Off();
	}
		break;
	case RewardType::Normal:
	{
		GoldRewardInit();
	}
		break;
	case RewardType::Item:
	{
	
	}
		break;
	case RewardType::Skull:
	{
		SkullRewardInit();
	}
		break;
	case RewardType::MiddleBoss:
	{
		MiddleBossRewardInit();
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
	Render->GetTransform()->SetLocalPosition(float4(0, -90, -2));
	Render->SetScaleRatio(2.0f);
	Render->Off();

	TableRender = CreateComponent<GameEngineSpriteRenderer>();
	TableRender->GetTransform()->SetLocalPosition(float4(0, -120, -1));
	TableRender->SetScaleRatio(2.0f);
	TableRender->Off();

	TableRender->CreateAnimation({.AnimationName = "SingleTable", .SpriteName = "Gate_Table.png", .ScaleToTexture = true});
	TableRender->CreateAnimation({.AnimationName = "ChoiceTable", .SpriteName = "Gate_Table.png", .ScaleToTexture = true});


	RewardCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Unknown);
	RewardCol->GetTransform()->SetLocalScale(float4(150, 150));
	RewardCol->SetColType(ColType::AABBBOX2D);

	EnterCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Unknown);
	EnterCol->GetTransform()->SetLocalScale(float4(1100, 300));
	EnterCol->SetColType(ColType::AABBBOX2D);

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

	if (false == IsPlayerFirstEnter && nullptr != EnterCol->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		EffectManager::PlayEffect({
			.EffectName = "StageRewardEffect",
			.Position = GetTransform()->GetWorldPosition() + float4(0, 50)
			});

		IsPlayerFirstEnter = true;

		if (RewardType::MiddleBoss != Type)
		{
			Render->ChangeAnimation("Idle");
			Render->On();
		}

		TableRender->On();

		for (size_t i = 0; i < AllPlatformCol.size(); i++)
		{
			AllPlatformCol[i]->On();
		}

	}


	if (nullptr == RewardCol->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		return;
	}

	if (false == IsRewardEndValue && true == GameEngineInput::IsDown("UseKey"))
	{
		IsRewardEndValue = true;
		Render->ChangeAnimation("Open");

		switch (Type)
		{
		case RewardType::None:
			break;
		case RewardType::Normal:
			break;
		case RewardType::Skull:
			DropSkullReward();
			break;
		case RewardType::MiddleBoss:
			break;
		default:
			break;
		}

	}
}

void StageRewardObject::GoldRewardInit()
{	
	Render->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "GoldReward.png",
		.Start = 0, .End = 18, .FrameInter = 0.1f, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Open", .SpriteName = "EmptyAnimation.png",
		.Start = 0, .End = 0, .FrameInter = 0.08f, .Loop = false, .ScaleToTexture = true });
}

void StageRewardObject::SkullRewardInit()
{
	GameEngineRandom& Rand = GameEngineRandom::MainRandom;

	int RandValue = Rand.RandomInt(0, 100);

	if (10 > RandValue)
	{
		SkullRewardGrade = SkullGrade::Legendary;
	}
	else if (30 > RandValue)
	{
		SkullRewardGrade = SkullGrade::Unique;
	}
	else if (60 > RandValue)
	{
		SkullRewardGrade = SkullGrade::Rare;
	}
	else
	{
		SkullRewardGrade = SkullGrade::Normal;
	}

	switch (SkullRewardGrade)
	{
	case SkullGrade::Normal:
		Render->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Normal_SkullRewardIdle.png", .ScaleToTexture = true });
		Render->CreateAnimation({ .AnimationName = "Open", .SpriteName = "Normal_SkullRewardOpen.png",
			.Start = 0, .End = 10, .FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });
		break;
	case SkullGrade::Rare:
		Render->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Rare_SkullRewardIdle.png", .ScaleToTexture = true });
		Render->CreateAnimation({ .AnimationName = "Open", .SpriteName = "Rare_SkullRewardOpen.png",
			.Start = 0, .End = 10, .FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });
		break;
	case SkullGrade::Unique:
		Render->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Unique_SkullRewardIdle.png", .ScaleToTexture = true});
		Render->CreateAnimation({ .AnimationName = "Open", .SpriteName = "Unique_SkullRewardOpen.png",
			.Start = 0, .End = 12, .FrameInter = 0.08f, .Loop = false, .ScaleToTexture = true });
		break;
	case SkullGrade::Legendary:
		Render->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Legendary_SkullRewardIdle.png", .ScaleToTexture = true });
		Render->CreateAnimation({ .AnimationName = "Open", .SpriteName = "Legendary_SkullRewardOpen.png",
			.Start = 0, .End = 12, .FrameInter = 0.08f, .Loop = false, .ScaleToTexture = true });
		break;
	default:
		break;
	}
}

void StageRewardObject::MiddleBossRewardInit()
{
}

void StageRewardObject::DropSkullReward()
{
	std::vector<SkullData> RewardList;
	ContentDatabase<SkullData, SkullGrade>::CopyGradeDatas(SkullRewardGrade, RewardList);
		
	GameEngineRandom& Rand = GameEngineRandom::MainRandom;
	int RandIndex = Rand.RandomInt(0, static_cast<int>(RewardList.size() - 1));

	std::shared_ptr<SkullGear> Gear = GetLevel()->CreateActor<SkullGear>();
	Gear->Init(RewardList[RandIndex]);
	Gear->DropGear(GetTransform()->GetWorldPosition());

	if (SkullRewardGrade == SkullGrade::Legendary)
	{
		Gear->LegendaryGearEffectOn();
	}
}