#include "PrecompileHeader.h"
#include "LifeOrb.h"
#include "Player.h"
#include "PlayerState.h"
#include "CaptureAnimation.h"
#include "Inventory.h"

LifeOrb::LifeOrb()
{
}

LifeOrb::~LifeOrb()
{
}

void LifeOrb::DropOrb(const float4& _WorldPos)
{
	float4 OrbPos = _WorldPos;
	OrbPos.z = GameEngineRandom::MainRandom.RandomFloat(-40, -31);

	DropStartY = OrbPos.y;

	State = OrbState::Drop;

	DropRigid.SetVelocity(float4(0, 850));
	GetTransform()->SetWorldPosition(OrbPos);
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
	OrbRender->CreateAnimation({.AnimationName = "Idle", .SpriteName = "LifeorbSmall.png", .Start = 0, .End = 68, .Loop = true, .ScaleToTexture = true});
	OrbRender->ChangeAnimation("Idle");
	OrbRender->SetScaleRatio(2.0f);

	OrbGroundCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Unknown);
	OrbGroundCol->GetTransform()->SetLocalPosition(float4(0, -20, 0));
	OrbGroundCol->GetTransform()->SetLocalScale(float4(40, 20, 1));
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
		GetTransform()->SetWorldPosition(WaveCenter + float4(0, -sinf(GetLiveTime() * 3.0f) * 5.0f, 0));
	
		if (PlayerState::GetHP() >= PlayerState::GetMaxHP() + Inventory::GetMaxHP())
		{
			return;
		}

		std::shared_ptr<GameEngineCollision> PlayerCol = OrbBodyCol->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D);


		if (nullptr != PlayerCol)
		{
			std::shared_ptr<Player> PlayerPtr = PlayerCol->GetActor()->DynamicThis<Player>();

			if (nullptr == PlayerPtr)
			{
				MsgAssert_Rtti<LifeOrb>(" - Player Class만 Player ColOrder를 가질 수 있습니다");
				return;
			}

			EffectManager::PlayEffect({
				.EffectName = "PlayerHeal",
				.Position = GetTransform()->GetWorldPosition() + float4(0, 40),
				});

			PlayerPtr->GetMainSkull()->EffectCaptureAnimation({
					.SpriteRender = PlayerPtr->GetMainSkull()->GetMainRender(),
					.StartColor = float4(0.6f, 0.035f, 0.82f, 0.8f), .EndColor = float4(0.6f, 0.035f, 0.82f, 0.0f),
					.Speed = 3.0f,
					.WaitTime = 0.0f
					});

			PlayerPtr->HealPlayer(10, float4::Up);
			Death();
		}
	}
		break;
	case OrbState::Drop:
	{
		DropRigid.UpdateForce(_DeltaTime);

		float4 CurFramePos = GetTransform()->GetWorldPosition();
		float4 DropVel = DropRigid.GetVelocity();

		GetTransform()->AddWorldPosition(DropVel * _DeltaTime);

		if (-300 < DropVel.y)
		{
			return;
		}

		if (CurFramePos.y > DropStartY + 100)
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
	float PlatformUp = ColTrans->GetWorldPosition().y + ColTrans->GetWorldScale().hy() + OrbRender->GetTransform()->GetWorldScale().hy();

	GreaPos.y = PlatformUp;

	GetTransform()->SetWorldPosition(GreaPos);

	WaveCenter = GreaPos;
	ResetLiveTime();
}
