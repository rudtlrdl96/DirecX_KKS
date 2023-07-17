#include "PrecompileHeader.h"
#include "StageRewardObject.h"
#include "BaseGear.h"
#include "SkullGear.h"
#include "FieldNoteActor.h"
#include "Inventory.h"
#include "AnimationPartParticle.h"

StageRewardObject::StageRewardObject()
{
}

StageRewardObject::~StageRewardObject()
{
	ReleaseLight();
}

void StageRewardObject::SetReward(RewardType _Type)
{
	Type = _Type;

	if (Type == RewardType::MiddleBoss)
	{
		TableRender->ChangeAnimation("ChoiceTable");

		AllPlatformCol.resize(3);

		AllPlatformCol[0] = CreateComponent<GameEngineCollision>((int)CollisionOrder::Platform_Half);
		AllPlatformCol[0]->SetColType(ColType::AABBBOX2D);
		AllPlatformCol[0]->GetTransform()->SetLocalPosition(TableRender->GetTransform()->GetLocalPosition() + float4(-88, 58.5f, 0));
		AllPlatformCol[0]->GetTransform()->SetLocalScale(float4(56, 15, 1));
		AllPlatformCol[0]->Off();


		AllPlatformCol[1] = CreateComponent<GameEngineCollision>((int)CollisionOrder::Platform_Half);
		AllPlatformCol[1]->SetColType(ColType::AABBBOX2D);
		AllPlatformCol[1]->GetTransform()->SetLocalPosition(TableRender->GetTransform()->GetLocalPosition() + float4(0, 58.5f, 0));
		AllPlatformCol[1]->GetTransform()->SetLocalScale(float4(120, 15, 1));
		AllPlatformCol[1]->Off();

		
		AllPlatformCol[2] = CreateComponent<GameEngineCollision>((int)CollisionOrder::Platform_Half);
		AllPlatformCol[2]->SetColType(ColType::AABBBOX2D);
		AllPlatformCol[2]->GetTransform()->SetLocalPosition(TableRender->GetTransform()->GetLocalPosition() + float4(88, 58.5f, 0));
		AllPlatformCol[2]->GetTransform()->SetLocalScale(float4(56, 15, 1));
		AllPlatformCol[2]->Off();
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

void StageRewardObject::CallUseEvent()
{
	MinimapImageRender->Off();

	if (RewardType::MiddleBoss != Type && false == IsRewardEndValue)
	{
		NoteActor->Off();
		IsRewardEndValue = true;
		Render->ChangeAnimation("Open");

		switch (Type)
		{
		case RewardType::None:
			break;
		case RewardType::Normal:
			DropGoldReward();
			break;
		case RewardType::Skull:
			DropSkullReward();
			break;
		case RewardType::MiddleBoss:

			break;
		default:
			break;
		}

		GetContentLevel()->CallEvent("RewardWorldLightOff");
		ReleaseLight();
	}
}

void StageRewardObject::Start()
{
	Render = CreateComponent<GameEngineSpriteRenderer>();
	Render->GetTransform()->SetLocalPosition(float4(0, -90, -11));
	Render->SetScaleRatio(2.0f);
	Render->Off();

	TableRender = CreateComponent<GameEngineSpriteRenderer>();
	TableRender->GetTransform()->SetLocalPosition(float4(0, -120, -10));
	TableRender->SetScaleRatio(2.0f);
	TableRender->Off();

	TableRender->CreateAnimation({.AnimationName = "SingleTable", .SpriteName = "Gate_Table.png", .ScaleToTexture = true});
	TableRender->CreateAnimation({.AnimationName = "ChoiceTable", .SpriteName = "Gate_ChoiceTable.png", .ScaleToTexture = true});

	NoteActor = GetLevel()->CreateActor<FieldNoteActor>();
	NoteActor->GetTransform()->SetParent(GetTransform());
	NoteActor->GetTransform()->SetLocalPosition(float4(0, -140, -100.0f));
	NoteActor->SetText("ㅁ 살펴보기");
	NoteActor->AddKeyImage("KeyUI_F.png", float4(-35, 0, -1));
	NoteActor->Off();

	RewardCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::UseEvent);
	RewardCol->GetTransform()->SetLocalScale(float4(150, 150));
	RewardCol->SetColType(ColType::AABBBOX2D);

	EnterCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Unknown);
	EnterCol->GetTransform()->SetLocalScale(float4(1100, 300));
	EnterCol->SetColType(ColType::AABBBOX2D);

	if (nullptr != GetLevel()->GetCamera((int)CameraOrder::MiniMap))
	{
		MinimapImageRender = CreateComponent<ContentMinimapRender>();
		MinimapImageRender->SetTexture("MinimapImage.png");
		MinimapImageRender->ColorOptionValue.PlusColor = float4(0, 0.8f, 0, 0.0f);
		MinimapImageRender->Off();
	}

}

void StageRewardObject::Update(float _DeltaTime)
{
	if (nullptr != RewardLight)
	{
		ContentLevel* Level = GetContentLevel();
		std::shared_ptr<GameEngineCamera> MainCam = Level->GetMainCamera();

		float4 Result = GetTransform()->GetWorldPosition();

		Result *= MainCam->GetView();
		Result *= MainCam->GetProjection();
		Result *= MainCam->GetViewPort();

		RewardLight->LightBuffer.LightPos = Result - float4(0, 800);

		if (true == IsLightStartEffect)
		{
			LightProgress += _DeltaTime;

			RewardLight->LightBuffer.LightOption.z = ContentFunc::Lerp<float>(175.0f, 170.0f, LightProgress) * GameEngineMath::DegToRad;
			RewardLight->LightBuffer.LightOption.w = ContentFunc::Lerp<float>(185.0f, 190.0f, LightProgress) * GameEngineMath::DegToRad;

			if (1.0f <= LightProgress)
			{
				IsLightStartEffect = false;
			}
		}
	}

	if (RewardType::None == Type)
	{
		return;
	}

	if (false == IsPlayerFirstEnter && nullptr != EnterCol->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		GetContentLevel()->CallEvent("RewardWorldLightOn");
		CreateLight();

		EffectManager::PlayEffect({
			.EffectName = "StageRewardEffect",
			.Position = GetTransform()->GetWorldPosition() + float4(0, 50)
			});

		IsPlayerFirstEnter = true;

		if (RewardType::MiddleBoss != Type)
		{
			Render->ChangeAnimation("Idle");
			Render->On();

			if (nullptr != MinimapImageRender)
			{
				MinimapImageRender->GetTransform()->SetWorldPosition(TableRender->GetTransform()->GetWorldPosition() + float4(0, 50));
				MinimapImageRender->GetTransform()->SetWorldScale(float4(80, 100, 1));

				MinimapImageRender->On();
			}
		}
		else
		{
			std::shared_ptr<SkullGear> FirstGear = DropSkullReward(float4(-88, 0), true);
			std::shared_ptr<GameEngineCollision> FirstCol = FirstGear->GetBodyCol();
			FirstCol->GetTransform()->AddLocalPosition(float4(0, -25));
			FirstCol->GetTransform()->AddLocalScale(float4(0, 50));

			std::shared_ptr<SkullGear> SecondGear = DropSkullReward(float4(0, 0), true);
			std::shared_ptr<GameEngineCollision> SecondCol = SecondGear->GetBodyCol();
			SecondCol->GetTransform()->AddLocalPosition(float4(0, -25));
			SecondCol->GetTransform()->AddLocalScale(float4(0, 50));


			std::shared_ptr<SkullGear> ThirdGear = DropSkullReward(float4(88, 0), true);
			std::shared_ptr<GameEngineCollision> ThirdCol = ThirdGear->GetBodyCol();
			ThirdCol->GetTransform()->AddLocalPosition(float4(0, -25));
			ThirdCol->GetTransform()->AddLocalScale(float4(0, 50));
		}

		TableRender->On();

		for (size_t i = 0; i < AllPlatformCol.size(); i++)
		{
			AllPlatformCol[i]->On();
		}

	}


	if (RewardType::MiddleBoss == Type)
	{
		bool IsSelectGear = false;

		for (size_t i = 0; i < CreateGears.size(); i++)
		{
			if (true == CreateGears[i]->IsDeath())
			{
				IsSelectGear = true;
			}
		}

		if (true == IsSelectGear)
		{
			IsRewardEndValue = true;

			for (size_t i = 0; i < CreateGears.size(); i++)
			{
				CreateGears[i]->IsUseOn();
				CreateGears[i]->Death();
				CreateGears[i] = nullptr;
			}

			CreateGears.clear();
			GetContentLevel()->CallEvent("RewardWorldLightOff");
			ReleaseLight();
		}
	}

	for (size_t i = 0; i < CreateGears.size(); i++)
	{
		if (true == CreateGears[i]->IsDeath())
		{
			CreateGears.clear();
			break;
		}
	}

	if (nullptr == RewardCol->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		NoteActor->Off();
		return;
	}
	else if (true == Render->IsUpdate() && false == IsRewardEndValue)
	{
		NoteActor->On();
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

	std::vector<float> Per = {40.0f, 30.0f, 20.0f, 10.0f };
		 
	SkullRewardGrade = ContentFunc::RandEnum<SkullGrade>(Per);

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

std::shared_ptr<SkullGear> StageRewardObject::DropSkullReward(float4 _Pivot /*= float4::Zero*/, bool _GradeReset /*= false*/)
{
	if (true == _GradeReset)
	{
		std::vector<float> Per = { 40.0f, 30.0f, 20.0f, 10.0f };
		SkullRewardGrade = ContentFunc::RandEnum<SkullGrade>(Per);
	}

	std::vector<SkullData> RewardList;
	ContentDatabase<SkullData, SkullGrade>::CopyGradeDatas(SkullRewardGrade, RewardList);
		
	GameEngineRandom& Rand = GameEngineRandom::MainRandom;
	int RandIndex = Rand.RandomInt(0, static_cast<int>(RewardList.size() - 1));

	std::shared_ptr<SkullGear> Gear = GetLevel()->CreateActor<SkullGear>();
	Gear->Init(RewardList[RandIndex]);
	Gear->DropGear(Render->GetTransform()->GetWorldPosition() + _Pivot);

	if (SkullRewardGrade == SkullGrade::Legendary)
	{
		Gear->LegendaryGearEffectOn();
	}

	CreateGears.push_back(Gear);

	return Gear;
}

void StageRewardObject::DropGoldReward()
{
	Inventory::AddGoods_Gold(100);

	for (size_t i = 0; i < 50; i++)
	{
		std::shared_ptr<AnimationPartParticle> DeadPart = GetLevel()->CreateActor<AnimationPartParticle>();

		GameEngineTransform* PartTrans = DeadPart->GetTransform();

		GameEngineRandom& MainRand = GameEngineRandom::MainRandom;

		int RandLiveTime = MainRand.RandomInt(0, 2);

		float4 Dir = float4::Up;
		Dir.RotaitonZDeg(MainRand.RandomFloat(-15, 15));
		DeadPart->Init(
			{ .AnimationName = "Idle", .SpriteName = "Goods_Gold.png", .FrameInter = 0.1f, .Loop = true, .ScaleToTexture = true }, 2.0f, Dir, MainRand.RandomFloat(700.0f, 900.0f), 0.7f + (0.05f * RandLiveTime));

		DeadPart->RotOff();

		AnimationPartParticle* GetPtr = DeadPart.get();
		DeadPart->SetEndCallback([GetPtr]()
			{
				float4 DeathPos = GetPtr->GetTransform()->GetWorldPosition();

				EffectManager::PlayEffect({ .EffectName = "GoldGoodsEffect", .Position = DeathPos });
				SoundDoubleCheck::Play("Object_GainGold.wav");
			});

		PartTrans->SetWorldPosition(Render->GetTransform()->GetWorldPosition() + float4(0, 40));
	}
}

void StageRewardObject::CreateLight()
{
	if (nullptr == RewardLight)
	{
		RewardLight = GetContentLevel()->CreatePointLight(PointLightType::CircleAngle);

		RewardLight->LightBuffer.LightColor = float4(0.5f, 0.5f, 0.5f, 1.0f);
		RewardLight->LightBuffer.LightOption.x = 0.6f;
		RewardLight->LightBuffer.LightOption.y = 955.0f;

		RewardLight->LightBuffer.LightOption.z = 175.0f * GameEngineMath::DegToRad;
		RewardLight->LightBuffer.LightOption.w = 185.0f * GameEngineMath::DegToRad;

		IsLightStartEffect = true;
		LightProgress = 0.0f;
	}
}

void StageRewardObject::ReleaseLight()
{
	if (nullptr != RewardLight)
	{
		GetContentLevel()->ReleasePointLight(RewardLight);
		RewardLight = nullptr;
	}

}