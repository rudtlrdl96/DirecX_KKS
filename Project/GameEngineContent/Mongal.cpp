#include "PrecompileHeader.h"
#include "Mongal.h"

Mongal::Mongal()
{
}

Mongal::~Mongal()
{
}

void Mongal::DataLoad()
{
	Data = ContentDatabase<MonsterData, LevelArea>::GetData(90); // 90 = ¸ó°¥
}

void Mongal::TextureLoad()
{
}

void Mongal::LoadAnimation()
{
	Render->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Mongal_BattleIdle.png", .Start = 0, .End = 5, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Walk", .SpriteName = "Mongal_BattleWalk.png", .Start = 0, .End = 7, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Hit1", .SpriteName = "Mongal_BattleHit1.png", .Start = 0, .End = 0, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Hit2", .SpriteName = "Mongal_BattleHit2.png", .Start = 0, .End = 0, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Death", .SpriteName = "Mongal_BattleDead.png", .Start = 0, .End = 13, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Idle_NoBattle", .SpriteName = "Mongal_Idle.png", .Start = 0, .End = 5, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Walk_NoBattle", .SpriteName = "Mongal_Walk.png", .Start = 0, .End = 7, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Wakeup", .SpriteName = "Mongal_WakeUp.png", .Start = 0, .End = 20, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Laugh", .SpriteName = "Mongal_Laugh.png", .Start = 0, .End = 2, .ScaleToTexture = true });
}

void Mongal::AnimationAttackMetaDataLoad()
{
	AnimPauseTimes[6] = 0.2f;

	AttackRigidbody.SetMaxSpeed(300.0f);
	AttackRigidbody.SetFricCoeff(1000.0f);

	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Data");
		Path.Move("1_Opening");
		Path.Move("Monster");

		AnimColMeta_Attack = ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("Mongal_Attack").GetFullPath());

		Render->CreateAnimation({
			.AnimationName = AnimColMeta_Attack.GetAnimationName().data(),
			.SpriteName = AnimColMeta_Attack.GetSpriteName().data(),
			.Start = AnimColMeta_Attack.GetStartFrame(),
			.End = AnimColMeta_Attack.GetEndFrame(),
			.Loop = false,
			.ScaleToTexture = true });
	}
}

void Mongal::SetColData()
{
	{
		GameEngineTransform* ColTrans = GroundCol->GetTransform();

		ColTrans->SetLocalPosition(float4(0, -3, 0));
		ColTrans->SetWorldScale(float4(70, 6, 1));
	}

	{
		GameEngineTransform* ColTrans = BodyCol->GetTransform();

		ColTrans->SetLocalPosition(float4(0, 70, 0));
		ColTrans->SetWorldScale(float4(80, 140, 1));
	}

	{
		GameEngineTransform* ColTrans = WalkCol->GetTransform();

		LocalWalkColPos = float4(45, 72, 0);

		ColTrans->SetLocalPosition(LocalWalkColPos);
		ColTrans->SetWorldScale(float4(10, 140, 1));
	}
	{
		GameEngineTransform* ColTrans = BackCol->GetTransform();

		LocalBackColPos = float4(-45, 72, 0);

		ColTrans->SetLocalPosition(LocalBackColPos);
		ColTrans->SetWorldScale(float4(10, 140, 1));
	}
	{
		GameEngineTransform* ColTrans = WalkFallCol->GetTransform();

		LocalWalkFallColPos = float4(45, 55, 0);

		ColTrans->SetLocalPosition(LocalWalkFallColPos);
		ColTrans->SetWorldScale(float4(10, 170, 1));
	}

	{
		GameEngineTransform* ColTrans = FindCol->GetTransform();

		LocalFindColPos = float4(200, 50, 0);

		ColTrans->SetLocalPosition(LocalFindColPos);
		ColTrans->SetWorldScale(float4(400, 100, 1));
	}

	{
		GameEngineTransform* ColTrans = ChasingCol->GetTransform();

		LocalChasingColPos = float4(50, 50, 0);

		ColTrans->SetLocalPosition(LocalChasingColPos);
		ColTrans->SetWorldScale(float4(100, 100, 1));
	}

	LoadFindEffectPos = float4(0, 150, 0);
}

void Mongal::DeathPartLoad()
{
}

void Mongal::MonsterDeath()
{
	Render->ChangeAnimation("Death", 0, false);
}
