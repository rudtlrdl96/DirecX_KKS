#include "PrecompileHeader.h"
#include "Mouse.h"

Mouse::Mouse()
{
}

Mouse::~Mouse()
{
}

void Mouse::Start()
{
	BehaviorObject::Start();

	if (nullptr == GameEngineSprite::Find("MouseIdle.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("2_Castle");
		Path.Move("BehaviorObject");
		Path.Move("Mouse");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("MouseIdle.png").GetFullPath(), 2, 3);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("MouseWalk.png").GetFullPath(), 2, 3);
	}

	Render->SetScaleRatio(2.0f);
	Render->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "MouseIdle.png", .Loop = true, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Walk", .SpriteName = "MouseWalk.png", .Loop = true, .ScaleToTexture = true });
	Render->ChangeAnimation("Idle");
}

void Mouse::Update(float _DeltaTime)
{
	switch (State)
	{
	case Mouse::MouseState::Idle:
		IdleTime += _DeltaTime;

		if (0.0f <= IdleTime)
		{
			float DirX = GetTransform()->GetWorldPosition().x - CenterPos.x;

			if (-300 > DirX)
			{
				SetViewDir(ActorViewDir::Right);
			}
			else if (300 < DirX)
			{
				SetViewDir(ActorViewDir::Left);
			}
			else
			{
				int RandInt = GameEngineRandom::MainRandom.RandomInt(0, 1);

				if (0 == RandInt)
				{
					SetViewDir(ActorViewDir::Right);
				}
				else
				{
					SetViewDir(ActorViewDir::Left);
				}
			}

			WalkTime = GameEngineRandom::MainRandom.RandomFloat(-6, -3);
			State = MouseState::Walk;
			Render->ChangeAnimation("Walk");
		}

		break;
	case Mouse::MouseState::Walk:
		WalkTime += _DeltaTime;

		switch (Dir)
		{
		case ActorViewDir::Left:
			GetTransform()->AddWorldPosition(float4::Left * _DeltaTime * 30.0f);
			break;
		case ActorViewDir::Right:
			GetTransform()->AddWorldPosition(float4::Right * _DeltaTime * 30.0f);
			break;
		default:
			break;
		}
		
		if (0.0f <= WalkTime)
		{
			IdleTime = GameEngineRandom::MainRandom.RandomFloat(-10, -4);
			State = MouseState::Idle;
			Render->ChangeAnimation("Idle");
		}
		break;
	default:
		break;
	}
}

void Mouse::Init()
{
	CenterPos = GetTransform()->GetWorldPosition();
}

void Mouse::ResetBehavior()
{
	GetTransform()->SetWorldPosition(CenterPos);
}

void Mouse::PlayBehavior()
{
	GetTransform()->SetWorldPosition(CenterPos);
}

void Mouse::SetViewDir(ActorViewDir _Dir)
{
	Dir = _Dir;

	switch (Dir)
	{
	case ActorViewDir::Left:
	{
		GetTransform()->SetLocalNegativeScaleX();
	}
	break;
	case ActorViewDir::Right:
	{
		GetTransform()->SetLocalPositiveScaleX();
	}
	break;
	default:
		break;
	}

}
