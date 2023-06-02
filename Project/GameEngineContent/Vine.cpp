#include "PrecompileHeader.h"
#include "Vine.h"
#include <GameEngineCore/GameEngineCollision.h>
#include "Player.h"

Vine::Vine()
{
}

Vine::~Vine()
{
}

void Vine::Start()
{
	BehaviorObject::Start();

	if (nullptr == GameEngineSprite::Find("Vine_Idle.png"))
	{
		GameEngineDirectory Path;
		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("3_ForestOfHarmony");
		Path.Move("BehaviorObject");
		Path.Move("Vine");
		Path.Move("Sheet");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Vine_Idle.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Vine_BattleIdle.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Vine_AttackReady.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Vine_Attack.png").GetFullPath(), 9, 1);
	}

	Render->CreateAnimation({ 
		.AnimationName = "Idle",
		.SpriteName = "Vine_Idle.png",
		.FrameInter = 0.1f,
		.ScaleToTexture = true});

	Render->CreateAnimation({
	.AnimationName = "AttackReady",
	.SpriteName = "Vine_AttackReady.png",
	.FrameInter = 0.1f,
	.ScaleToTexture = true });

	Render->CreateAnimation({
		.AnimationName = "BattleIdle",
		.SpriteName = "Vine_BattleIdle.png",
		.FrameInter = 0.1f,
		.ScaleToTexture = true });

	Render->CreateAnimation({
		.AnimationName = "Attack",
		.SpriteName = "Vine_Attack.png",
		.FrameInter = 0.1f,
		.ScaleToTexture = true });

	Render->SetScaleRatio(2.0f);

	FindCol = CreateComponent<GameEngineCollision>();
	FindCol->GetTransform()->SetLocalScale(float4(300, 200, 1));
	FindCol->GetTransform()->SetLocalPosition(float4(0, 100, 0));

	AttackCol = CreateComponent<GameEngineCollision>();
	AttackCol->GetTransform()->SetLocalScale(float4(190, 140, 1));
	AttackCol->GetTransform()->SetLocalPosition(float4(0, 45, 0));
}

void Vine::Update(float _DeltaTime)
{
	AttackCoolTime -= _DeltaTime;

	switch (State)
	{
	case Vine::VineState::Idle:
	{
		if (nullptr != FindCol->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D))
		{
			State = Vine::VineState::AttackReady;
			Render->ChangeAnimation("AttackReady");
		}
	}
		break;
	case Vine::VineState::AttackReady:
	{
		if (true == Render->IsAnimationEnd())
		{
			State = Vine::VineState::BattleIdle;
			Render->ChangeAnimation("BattleIdle");

			AttackCoolTime = 1.5f;
		}
	}
	break;
	case Vine::VineState::BattleIdle:
	{
		if (0.0f < AttackCoolTime)
		{
			return;
		}

		if (nullptr != AttackCol->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D))
		{
			State = Vine::VineState::Attack;
			Render->ChangeAnimation("Attack");

			IsPlayerHit = false;
			AttackCoolTime = 3.0f;
		}
	}
		break;
	case Vine::VineState::Attack:
	{
		if (false == IsPlayerHit && 4 == Render->GetCurrentFrame())
		{
			std::shared_ptr<GameEngineCollision> PlayerCol = AttackCol->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D);

			if (nullptr != PlayerCol)
			{
				std::shared_ptr<Player> CastingPtr = PlayerCol->GetActor()->DynamicThis<Player>();

				if (nullptr == CastingPtr)
				{
					MsgAssert_Rtti<Vine>(" - 플레이어 클래스만 Player ColOrder를 가질 수 있습니다");
					return;
				}

				CastingPtr->HitPlayer(10, float4(200, 400));
				IsPlayerHit = true;
			}
		}

		if (true == Render->IsAnimationEnd())
		{
			State = Vine::VineState::BattleIdle;
			Render->ChangeAnimation("BattleIdle");
		}
	}
		break;
	default:
		break;
	}

}

void Vine::ResetBehavior()
{
	State = VineState::Idle;
	Render->ChangeAnimation("Idle");
}

void Vine::PlayBehavior()
{
	State = VineState::Idle;
	Render->ChangeAnimation("Idle");
}
