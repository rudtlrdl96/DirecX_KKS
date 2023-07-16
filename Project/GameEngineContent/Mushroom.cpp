#include "PrecompileHeader.h"
#include "Mushroom.h"
#include <GameEngineCore/GameEngineCollision.h>
#include "Player.h"

Mushroom::Mushroom()
{
}

Mushroom::~Mushroom()
{
}

void Mushroom::Start()
{
	BehaviorObject::Start();

	if (nullptr == GameEngineSprite::Find("Mushroom_Idle.png"))
	{
		GameEngineDirectory Path;
		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("3_ForestOfHarmony");
		Path.Move("BehaviorObject");
		Path.Move("Mushroom");
		Path.Move("Sheet");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Mushroom_Idle.png").GetFullPath(), 2, 2);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Mushroom_Active.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Mushroom_Return.png").GetFullPath(), 5, 1);
	}

	Render->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Mushroom_Idle.png", .FrameInter = 0.15f, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Active", .SpriteName = "Mushroom_Active.png", .FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Return", .SpriteName = "Mushroom_Return.png", .FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });

	Render->SetScaleRatio(2.0f);
	Render->ChangeAnimation("Idle");

	Col = CreateComponent<GameEngineCollision>();
	Col->GetTransform()->SetLocalScale(float4( 64, 64, 1 ));
	Col->GetTransform()->SetLocalPosition(float4(0, 32, 0));
}

void Mushroom::Update(float _DeltaTime)
{
	switch (State)
	{
	case Mushroom::MushroomState::Idle:
	{
		std::shared_ptr<GameEngineCollision> PlayerCol = Col->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D);

		if (nullptr != PlayerCol)
		{
			std::shared_ptr<Player> CastingPlayerPtr = PlayerCol->GetActor()->DynamicThis<Player>();

			if (nullptr == CastingPlayerPtr)
			{
				MsgAssert_Rtti<Player>(" - Player Class만 Player ColOreder를 가질 수 있습니다");
				return;
			}

			if (true == CastingPlayerPtr->CheckFall())
			{
				Render->ChangeAnimation("Active");
				State = MushroomState::Active;

				EffectManager::PlayEffect({
					.EffectName = "Appearance_Impact",
					.Position = GetTransform()->GetWorldPosition() + float4(-5, 45, 100),
					.Scale = 1.2f,
					.Color = float4(-0.1f, 0.3f, 0.3f, 1.0f)});

				float4 Vel = CastingPlayerPtr->GetBattleRigidVelocity();
				Vel.y = 2800.0f;
				CastingPlayerPtr->SetPushPlayer(Vel);

				int RandSound = GameEngineRandom::MainRandom.RandomInt(0, 3);

				if (0 == RandSound)
				{
					GameEngineSound::Play("Trap_Jump 1.wav");
				}
				else if (1 == RandSound)
				{
					GameEngineSound::Play("Trap_Jump 2.wav");
				}
				else if (2 == RandSound)
				{
					GameEngineSound::Play("Trap_Jump 3.wav");
				}
				else if (3 == RandSound)
				{
					GameEngineSound::Play("Trap_Jump 4.wav");
				}

			}
		}

		break;
	}
	case Mushroom::MushroomState::Active:
	{
		if (true == Render->IsAnimationEnd())
		{
			Render->ChangeAnimation("Return");
			State = MushroomState::Return;
		}
		break;
	}
	case Mushroom::MushroomState::Return:
	{
		if (true == Render->IsAnimationEnd())
		{
			Render->ChangeAnimation("Idle");
			State = MushroomState::Idle;
		}
		break;	
	}
	default:
		break;
	}

}

void Mushroom::ResetBehavior()
{
	State = MushroomState::Idle;
	Render->ChangeAnimation("Idle");
}

void Mushroom::PlayBehavior()
{
	State = MushroomState::Idle;
	Render->ChangeAnimation("Idle");
}
