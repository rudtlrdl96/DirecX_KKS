#include "PrecompileHeader.h"
#include "LifeOrb.h"
#include "Player.h"

LifeOrb::LifeOrb()
{
}

LifeOrb::~LifeOrb()
{
}

void LifeOrb::DropOrb(const float4& _WorldPos)
{
	State = OrbState::Drop;

	DropRigid.SetVelocity(float4(0, 850));
	GetTransform()->SetWorldPosition(_WorldPos);
}

void LifeOrb::Start()
{
	if (nullptr == GameEngineSprite::Find("LifeorbSmall.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("Orb");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("LifeorbSmall.png").GetFullPath(), 9, 8);
	}

	GetContentLevel()->AddEvent("MoveStage", GetActorCode(), [this]()
		{
			Death();
		});

	OrbRender = CreateComponent<GameEngineSpriteRenderer>();
	OrbRender->CreateAnimation({.AnimationName = "Idle", .SpriteName = "LifeorbSmall.png", .Start = 0, .End = 68});
	OrbRender->ChangeAnimation("Idle");

	OrbGroundCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Unknown);
	OrbGroundCol->GetTransform()->SetLocalPosition(float4(0, -20, 0));
	OrbGroundCol->GetTransform()->SetLocalScale(float4(40, 40, 1));
	OrbGroundCol->SetColType(ColType::AABBBOX2D);

	OrbBodyCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::UseEvent);
	OrbBodyCol->GetTransform()->SetLocalScale(float4(40, 40, 1));
	OrbBodyCol->SetColType(ColType::AABBBOX2D);

	DropRigid.SetActiveGravity(true);
	DropRigid.SetGravity(-2000);
	DropRigid.SetMaxSpeed(2000);
}

void LifeOrb::Update(float _DeltaTime)
{
	switch (State)
	{
	case OrbState::None:
		break;
	case OrbState::Wave:
	{
		GetTransform()->SetWorldPosition(WaveCenter + float4(0, -sinf(GetLiveTime() * 3.0f) * 7.0f, 0));
	
		std::shared_ptr<GameEngineCollision> PlayerCol = OrbBodyCol->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D);

		if (nullptr != PlayerCol)
		{
			std::shared_ptr<Player> PlayerPtr = PlayerCol->GetActor()->DynamicThis<Player>();

			if (nullptr == PlayerPtr)
			{
				MsgAssert_Rtti<LifeOrb>(" - Player Class만 Player ColOrder를 가질 수 있습니다");
				return;
			}

			PlayerPtr->HealPlayer(10, float4::Up);
			Death();
		}
	}
		break;
	case OrbState::Drop:
	{
		DropRigid.UpdateForce(_DeltaTime);

		float4 DropVel = DropRigid.GetVelocity();

		GetTransform()->AddWorldPosition(DropVel * _DeltaTime);

		if (-300 < DropVel.y)
		{
			return;
		}

		std::shared_ptr<GameEngineCollision> PlatformCol = OrbGroundCol->Collision((int)CollisionOrder::Platform_Normal, ColType::AABBBOX2D, ColType::AABBBOX2D);

		if (nullptr != PlatformCol)
		{
			SetWaveState(PlatformCol);
		}

		PlatformCol = OrbGroundCol->Collision((int)CollisionOrder::Platform_Half, ColType::AABBBOX2D, ColType::AABBBOX2D);

		if (nullptr != PlatformCol)
		{
			SetWaveState(PlatformCol);
		}
	}		
		break;
	default:
		break;
	}

}

void LifeOrb::Destroy()
{
	GetContentLevel()->RemoveEvent("MoveStage", GetActorCode());
}

void LifeOrb::SetWaveState(std::shared_ptr<GameEngineCollision> _PlatformCol)
{
	State = OrbState::Wave;

	GameEngineTransform* ColTrans = _PlatformCol->GetTransform();

	float4 GreaPos = GetTransform()->GetWorldPosition();
	float PlatformUp = ColTrans->GetWorldPosition().y + ColTrans->GetWorldScale().hy() + OrbRender->GetTransform()->GetWorldScale().hy() + 20;

	GreaPos.y = PlatformUp;

	GetTransform()->SetWorldPosition(GreaPos);

	WaveCenter = GreaPos;
	ResetLiveTime();
}
