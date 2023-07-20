#include "PrecompileHeader.h"
#include "Pigeon.h"

Pigeon::Pigeon()
{
}

Pigeon::~Pigeon()
{
}

void Pigeon::Start()
{
	BehaviorObject::Start();

	if (nullptr == GameEngineSprite::Find("WB_Idle.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("3_ForestOfHarmony");
		Path.Move("BehaviorObject");
		Path.Move("Pigeon");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("WB_Idle.png").GetFullPath(), 4, 4);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("WB_Ready.png").GetFullPath(), 2, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("WB_Fly.png").GetFullPath(), 2, 2);
	}

	Render->SetScaleRatio(2.0f);
	Render->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "WB_Idle.png", .Start = 0, .End = 12, .FrameInter = 0.13f, .Loop = true, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Ready", .SpriteName = "WB_Ready.png", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Fly", .SpriteName = "WB_Fly.png", .FrameInter = 0.07f, .Loop = true, .ScaleToTexture = true });

	Render->ChangeAnimation("Idle");

	EventCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Unknown);
	EventCol->SetColType(ColType::AABBBOX2D);
	EventCol->GetTransform()->SetLocalScale(float4(250, 250, 1));
}

void Pigeon::Update(float _DeltaTime)
{
	switch (State)
	{
	case Pigeon::PigeonState::Idle:

		if (nullptr != EventCol->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D))
		{
			Render->ChangeAnimation("Ready");
			State = PigeonState::Ready;
		}
		break;
	case Pigeon::PigeonState::Ready:
		if (true == Render->IsAnimationEnd())
		{
			Render->ChangeAnimation("Fly");
			State = PigeonState::Fly;
		}
	case Pigeon::PigeonState::Fly:
		MoveProgress += _DeltaTime * 0.4f;

		GetTransform()->SetWorldPosition(float4::LerpClamp(StartPos, EndPos, MoveProgress));

		if (1.0f <= MoveProgress)
		{
			Off();
			MoveProgress = 0.0f;
		}
		break;
	default:
		break;
	}

}

void Pigeon::Init()
{
	StartPos = GetTransform()->GetWorldPosition();
	EndPos = StartPos + float4(800, 1000);
}

void Pigeon::ResetBehavior()
{
	Render->ChangeAnimation("Idle");
	GetTransform()->SetWorldPosition(StartPos);
	State = PigeonState::Idle;
	MoveProgress = 0.0f;
	On();
}

void Pigeon::PlayBehavior()
{
	Render->ChangeAnimation("Idle");
	GetTransform()->SetWorldPosition(StartPos);
	State = PigeonState::Idle;
	MoveProgress = 0.0f;
	On();
}
