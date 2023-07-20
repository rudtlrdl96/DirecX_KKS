#include "PrecompileHeader.h"
#include "Bug.h"

Bug::Bug()
{
}

Bug::~Bug()
{
}

void Bug::Start()
{
	BehaviorObject::Start();

	if (nullptr == GameEngineSprite::Find("BugWalk.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("3_ForestOfHarmony");
		Path.Move("BehaviorObject");
		Path.Move("Bug");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("BugWalk.png").GetFullPath(), 2, 2);
	}

	Render->SetScaleRatio(2.0f);
	Render->CreateAnimation({ .AnimationName = "Walk", .SpriteName = "BugWalk.png", .Loop = true, .ScaleToTexture = true });
	Render->ChangeAnimation("Walk");
}

void Bug::Update(float _DeltaTime)
{
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
		WalkTime = GameEngineRandom::MainRandom.RandomFloat(-10, -6);

		float DirX = GetTransform()->GetWorldPosition().x - CenterPos.x;

		if (-250 > DirX)
		{
			SetViewDir(ActorViewDir::Right);
		}
		else if (250 < DirX)
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
	}
}

void Bug::Init()
{
	CenterPos = GetTransform()->GetWorldPosition();
}

void Bug::ResetBehavior()
{
	GetTransform()->SetWorldPosition(CenterPos);
}

void Bug::PlayBehavior()
{
	GetTransform()->SetWorldPosition(CenterPos);
}

void Bug::SetViewDir(ActorViewDir _Dir)
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
