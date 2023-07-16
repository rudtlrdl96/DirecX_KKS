#include "PrecompileHeader.h"
#include "ThornBush.h"
#include <GameEngineCore/GameEngineCollision.h>
#include "BaseMonster.h"
#include "Player.h"

ThornBush::ThornBush()
{
}

ThornBush::~ThornBush()
{
}

void ThornBush::Start()
{
	BehaviorObject::Start();

	AttackCol = CreateComponent<GameEngineCollision>();
	AttackCol->GetTransform()->SetLocalScale(float4(200, 80, 1));
	AttackCol->GetTransform()->SetLocalPosition(float4(0, 20, 1));

	if (nullptr == GameEngineSprite::Find("ThornBush_Idle.png"))
	{
		GameEngineDirectory Path;
		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("3_ForestOfHarmony");
		Path.Move("BehaviorObject");
		Path.Move("ThornBush");
		Path.Move("Sheet");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ThornBush_Idle.png").GetFullPath(), 11, 1);
	}

	Render->CreateAnimation({
		.AnimationName = "Idle",
		.SpriteName = "ThornBush_Idle.png",
		.FrameInter = 0.1f,
		.ScaleToTexture = true });

	Render->ChangeAnimation("Idle");
	Render->SetScaleRatio(2.0f);
}

void ThornBush::Update(float _DeltaTime)
{
	std::vector<std::shared_ptr<GameEngineCollision>> MonsterAllCol;

	AttackCol->CollisionAll((int)CollisionOrder::Monster, MonsterAllCol, ColType::OBBBOX2D, ColType::AABBBOX2D);

	for (size_t i = 0; i < MonsterAllCol.size(); i++)
	{
		std::shared_ptr<BaseMonster> CastingPtr = MonsterAllCol[i]->GetActor()->DynamicThis<BaseMonster>();

		if (nullptr == CastingPtr)
		{
			MsgAssert_Rtti<ThornBush>(" - BaseMonster를 상속 받은 클래스만 MonsterCol Order를 가질 수 있습니다");
		}

		if (0.0f < CastingPtr->GetThornHitCoolTime())
		{
			continue;
		}

		CastingPtr->SetThornHitCoolTime(1.5f);
		CastingPtr->HitMonster(30.0f, ActorViewDir::Right, false, false, false, HitEffectType::Normal);
		GameEngineSound::Play("Hit_Sword_Small.wav");
	}

	std::shared_ptr<GameEngineCollision> PlayerCol = AttackCol->Collision((int)CollisionOrder::Player, ColType::OBBBOX2D, ColType::AABBBOX2D);

	if (nullptr != PlayerCol)
	{
		std::shared_ptr<Player> CastingPtr = PlayerCol->GetActor()->DynamicThis<Player>();

		if (nullptr == CastingPtr)
		{
			MsgAssert_Rtti<ThornBush>(" - 플레이어 클래스만 Player Col Order를 가질 수 있습니다");
		}

		if (0.0f < CastingPtr->GetThornHitCoolTime())
		{
			return;
		}

		float4 Dir = CastingPtr->GetTransform()->GetWorldPosition() - GetTransform()->GetWorldPosition();
		Dir.y = 0;
		Dir.Normalize();
		Dir *= 100.0f;
		Dir.y = 400.0f;

		CastingPtr->SetThornHitCoolTime(1.5f);
		CastingPtr->HitPlayer(10.0f, Dir);
		GameEngineSound::Play("Hit_Sword_Small.wav");
	}
}

void ThornBush::ResetBehavior()
{
}

void ThornBush::PlayBehavior()
{
}
