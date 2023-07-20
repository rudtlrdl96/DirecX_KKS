#include "PrecompileHeader.h"
#include "Bat.h"

Bat::Bat()
{
}

Bat::~Bat()
{
}

void Bat::Start()
{
	if (nullptr == GameEngineSprite::Find("BatFly.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("2_Castle");
		Path.Move("BehaviorObject");
		Path.Move("Bat");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BatFly.png").GetFullPath(), 5, 1);
	}

	BehaviorObject::Start();
	Render->Off();

	EventCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Unknown);
	EventCol->GetTransform()->SetLocalScale(float4(600, 720, 1));
	EventCol->SetColType(ColType::AABBBOX2D);

	BatRenders.reserve(4);

	for (size_t i = 0; i < BatRenders.capacity(); i++)
	{
		CreateBat();
	}

	FlyEventFuncs.reserve(1);

	FlyEventFuncs.push_back([this]()
		{	
			float4 StartPos = float4(900, 0);

			GameEngineRandom& Rand = GameEngineRandom::MainRandom;

			RandBatCount = Rand.RandomInt(2, static_cast<int>(BatRenders.size()));

			for (size_t i = 0; i < RandBatCount; i++)
			{
				float4 MoveDir = float4::Left;

				GameEngineTransform* RenderTrans = BatRenders[i].BatRender->GetTransform();
			
				BatRenders[i].StartPos = StartPos + float4(Rand.RandomFloat(-20, 20), Rand.RandomFloat(-100, 100));
				RenderTrans->SetLocalPosition(BatRenders[i].StartPos);
				MoveDir.RotaitonZDeg(Rand.RandomFloat(-5, 5));

				BatRenders[i].EndPos = BatRenders[i].StartPos + MoveDir * 1800.0f;

				BatRenders[i].BatRender->SetNegativeFlipX();
				BatRenders[i].BatRender->On();
			}

			MoveSpeed = 0.4f;
		});

	FlyEventFuncs.push_back([this]()
		{
			float4 StartPos = float4(-300, 450);

			GameEngineRandom& Rand = GameEngineRandom::MainRandom;

			RandBatCount = Rand.RandomInt(2, static_cast<int>(BatRenders.size()));

			for (size_t i = 0; i < RandBatCount; i++)
			{
				float4 MoveDir = float4::Down;

				GameEngineTransform* RenderTrans = BatRenders[i].BatRender->GetTransform();

				BatRenders[i].StartPos = StartPos + float4(Rand.RandomFloat(-200, 200), Rand.RandomFloat(-20, 20));
				RenderTrans->SetLocalPosition(BatRenders[i].StartPos);
				MoveDir.RotaitonZDeg(Rand.RandomFloat(40, 50));

				BatRenders[i].EndPos = BatRenders[i].StartPos + MoveDir * 1500.0f;

				BatRenders[i].BatRender->SetPositiveFlipX();
				BatRenders[i].BatRender->On();
			}

			MoveSpeed = 0.4f;
		});
	
	FlyEventFuncs.push_back([this]()
		{	
			float4 StartPos = float4(-150, -450);

			GameEngineRandom& Rand = GameEngineRandom::MainRandom;

			RandBatCount = Rand.RandomInt(2, static_cast<int>(BatRenders.size()));

			for (size_t i = 0; i < RandBatCount; i++)
			{
				float4 MoveDir = float4::Up;

				GameEngineTransform* RenderTrans = BatRenders[i].BatRender->GetTransform();

				BatRenders[i].StartPos = StartPos + float4(Rand.RandomFloat(-200, 200), Rand.RandomFloat(-20, 20));
				RenderTrans->SetLocalPosition(BatRenders[i].StartPos);
				MoveDir.RotaitonZDeg(Rand.RandomFloat(-35, -25));

				BatRenders[i].EndPos = BatRenders[i].StartPos + MoveDir * 1500.0f;

				BatRenders[i].BatRender->SetPositiveFlipX();
				BatRenders[i].BatRender->On();
			}

			MoveSpeed = 0.4f;

		});
	
}

void Bat::Update(float _DeltaTime)
{
	BatFlyCoolTime += _DeltaTime;

	if (true == IsFly)
	{
		MoveProgress += _DeltaTime * MoveSpeed;

		for (size_t i = 0; i < RandBatCount; i++)
		{
			BatRenders[i].BatRender->On();
			float4 BatRenderPos = float4::LerpClamp(BatRenders[i].StartPos, BatRenders[i].EndPos, MoveProgress);
			BatRenders[i].BatRender->GetTransform()->SetLocalPosition(BatRenderPos);
		}

		if (1.0f <= MoveProgress)
		{
			MoveProgress = 0.0f;
			IsFly = false;

			for (size_t i = 0; i < BatRenders.size(); i++)
			{
				BatRenders[i].BatRender->Off();
			}
		}
	}

	if (0.0f > BatFlyCoolTime)
	{
		return;
	}


	if (false == IsFly && nullptr != EventCol->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		BatFlyCoolTime = -10.0f;
		FlyEventFuncs[EventIndex]();
		++EventIndex;

		IsFly = true;
		MoveProgress = 0.0f;

		if (EventIndex >= FlyEventFuncs.size())
		{
			EventIndex = 0;
		}
	}	
}

void Bat::ResetBehavior()
{
}

void Bat::PlayBehavior()
{
}

void Bat::CreateBat()
{
	std::shared_ptr<GameEngineSpriteRenderer> NewRender = CreateComponent<GameEngineSpriteRenderer>();

	NewRender->SetScaleRatio(2.0f);
	NewRender->CreateAnimation({.AnimationName = "Fly", .SpriteName = "BatFly.png", .FrameInter = 0.1f, .Loop = true, .ScaleToTexture = true});
	NewRender->ChangeAnimation("Fly");

	NewRender->GetTransform()->SetWorldRotation(float4::Zero);
	NewRender->Off();

	BatRenders.push_back(BatlInfo(NewRender, float4::Zero, float4::Zero));
}
