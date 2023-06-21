#include "PrecompileHeader.h"
#include "Mongal.h"
#include <GameEngineCore/GameEngineLevel.h>

#include "HealthBar.h"
#include "BattleLevel.h"

#include "StoryHero_FirstHero_Opening.h"

Mongal::Mongal()
{
}

Mongal::~Mongal()
{
}

void Mongal::Destroy()
{
	ContentLevel* LevelPtr = GetContentLevel();
	LevelPtr->RemoveEvent("Mongal_Laugh", GetActorCode());
}

void Mongal::Start()
{
	NormalMonster::Start();
	SetViewDir(ActorViewDir::Left, true);
	IsUnWalkable = true;
	AttackWaitEndTime = 2.0f;

	GetContentLevel()->AddEvent("Mongal_Laugh", GetActorCode(), [this]()
		{
			State = DeathState::Laugh;
			Render->ChangeAnimation("Laugh");
		});
}

void Mongal::Update(float _DeltaTime)
{
	if (true == IsMongalDeath)
	{
		StoryUpdate(_DeltaTime);
		return;
	}

	NormalMonster::Update(_DeltaTime);
}

void Mongal::DataLoad()
{
	Data = ContentDatabase<MonsterData, LevelArea>::GetData(90); // 90 = 몬갈
}

void Mongal::TextureLoad()
{
	if (nullptr == GameEngineSprite::Find("MongalDeathEffect.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("1_Opening");
		Path.Move("Monster");
		Path.Move("Mongal");
		Path.Move("Effect");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("MongalDeathEffect.png").GetFullPath(), 5, 5);
	
		EffectManager::CreateMetaData("MongalDeathEffect", {
			.SpriteName = "MongalDeathEffect.png",
			.AnimStart = 0,
			.AnimEnd = 22,
			.AnimIter = 0.05f,
			.ScaleRatio = 2.0f,
			});
	}
}

void Mongal::LoadAnimation()
{
	Render->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Mongal_BattleIdle.png", .Start = 0, .End = 5, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Walk", .SpriteName = "Mongal_BattleWalk.png", .Start = 0, .End = 7, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Hit1", .SpriteName = "Mongal_BattleHit1.png", .Start = 0, .End = 0, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Hit2", .SpriteName = "Mongal_BattleHit2.png", .Start = 0, .End = 0, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Death", .SpriteName = "Mongal_BattleDead.png", .Start = 0, .End = 13, .FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Death_NoBattle", .SpriteName = "Mongal_Death.png", .Start = 0, .End = 0, .FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Idle_NoBattle", .SpriteName = "Mongal_Idle.png", .Start = 0, .End = 5, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Walk_NoBattle", .SpriteName = "Mongal_Walk.png", .Start = 0, .End = 7, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Wakeup", .SpriteName = "Mongal_WakeUp.png", .Start = 0, .End = 20, .FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Laugh", .SpriteName = "Mongal_Laugh.png", .Start = 0, .End = 2, .ScaleToTexture = true });
}

void Mongal::AnimationAttackMetaDataLoad()
{
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
			.FrameInter = 0.15f,
			.Loop = false,
			.ScaleToTexture = true });
	}
}

void Mongal::SetColData()
{
	DeathEffectLocalPos = float4(0, 80, -0.1f);

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

		float4 LocalWalkColPos = float4(45, 72, 0);

		ColTrans->SetLocalPosition(LocalWalkColPos);
		ColTrans->SetWorldScale(float4(10, 140, 1));
	}
	{
		GameEngineTransform* ColTrans = BackCol->GetTransform();

		float4 LocalBackColPos = float4(-45, 72, 0);

		ColTrans->SetLocalPosition(LocalBackColPos);
		ColTrans->SetWorldScale(float4(10, 140, 1));
	}
	{
		GameEngineTransform* ColTrans = WalkFallCol->GetTransform();

		float4 LocalWalkFallColPos = float4(45, 55, 0);

		ColTrans->SetLocalPosition(LocalWalkFallColPos);
		ColTrans->SetWorldScale(float4(10, 170, 1));
	}

	{
		GameEngineTransform* ColTrans = FindCol->GetTransform();

		float4 LocalFindColPos = float4(200, 50, 0);

		ColTrans->SetLocalPosition(LocalFindColPos);
		ColTrans->SetWorldScale(float4(400, 100, 1));
	}

	{
		GameEngineTransform* ColTrans = ChasingCol->GetTransform();

		float4 LocalChasingColPos = float4(50, 50, 0);

		ColTrans->SetLocalPosition(LocalChasingColPos);
		ColTrans->SetWorldScale(float4(100, 100, 1));
	}

	LoadFindEffectPos = float4(0, 150, 0);
}

void Mongal::DeathPartLoad()
{
}

void Mongal::Hit_Enter()
{
	NormalMonster::Hit_Enter();

	ForceEscapeTime = 0.0f;
}

void Mongal::Hit_Update(float _DeltaTime)
{
	NormalMonster::Hit_Update(_DeltaTime);

	ForceEscapeTime += _DeltaTime;

	if (2.0f <= ForceEscapeTime)
	{
		if (nullptr != PlayerActor)
		{
			MonsterFsm.ChangeState("Attack");
		}
	}
}

void Mongal::Attack_Enter()
{
	if ("" == AnimColMeta_Attack.GetAnimationName())
	{
		MsgAssert_Rtti<BaseMonster>(" - 몬스터의 공격 정보가 존재하지 않습니다");
	}

	if (nullptr != PlayerActor)
	{
		float4 Dir = PlayerActor->GetTransform()->GetWorldPosition() - GetTransform()->GetWorldPosition();

		if (0 >  Dir.x)
		{
			SetViewDir(ActorViewDir::Left);
		}
		else
		{
			SetViewDir(ActorViewDir::Right);
		}

	}

	Render->ChangeAnimation(AnimColMeta_Attack.GetAnimationName());
	AttackRigidbody.SetVelocity(float4::Zero);

	AttackCheckFrame = 0;
	CurPauseTime = 0.0f;

	AttackCheck.Reset();

	IsSuperArmor = true;
	IsUnPushArmor = true;
	IsAttackMove = false;
}

void Mongal::Attack_Update(float _DeltaTime)
{
	AttackCheck.Update();

	if (true == HitCheck())
	{
		return;
	}

	Fall(_DeltaTime);
	AttackRigidbody.UpdateForce(_DeltaTime);

	size_t CurFrame = Render->GetCurrentFrame();

	if (false == IsAttackMove && 3 == CurFrame)
	{
		IsAttackMove = true;

		switch (Dir)
		{
		case ActorViewDir::Left:
			AttackRigidbody.AddVelocity(float4::Left * 300.0f);
			break;
		case ActorViewDir::Right:
			AttackRigidbody.AddVelocity(float4::Right * 300.0f);
			break;
		default:
			break;
		}
	}

	if (AttackCheckFrame != CurFrame)
	{
		AttackCheckFrame = CurFrame;
		CurPauseTime = 0.0f;
	}

	CurPauseTime += _DeltaTime;

	if (AnimPauseTimes[AttackCheckFrame] > CurPauseTime)
	{
		Render->SetAnimPauseOn();
	}
	else
	{
		Render->SetAnimPauseOff();
	}

	if (nullptr == ContentFunc::PlatformColCheck(WalkCol))
	{
		float4 Velocity = AttackRigidbody.GetVelocity() * _DeltaTime;
		GetTransform()->AddLocalPosition(Velocity);
	}

	if (true == Render->IsAnimationEnd())
	{
		++AttackLoopCount;

		if (3 <= AttackLoopCount)
		{
			MonsterFsm.ChangeState("Idle");
			AttackLoopCount = 0;
			IsUnPushArmor = false;
			IsSuperArmor = false;
		}
		else
		{
			MonsterFsm.ChangeState("Attack");
		}

		return;
	}
}

void Mongal::Attack_End()
{
	AttackWaitTime = 0.0f;
}

void Mongal::MonsterDeath()
{
	IsMongalDeath = true;
	State = DeathState::BattleDeath;
	DeathTimeCheck = 0.0f;

	HealthBarPtr->Off();

	EffectManager::PlayEffect({
		.EffectName = "MonsterDeath",
		.Position = GetTransform()->GetWorldPosition() + DeathEffectLocalPos });

	Render->ChangeAnimation("Death", 0, false);
	GetContentLevel()->CallEvent("MongalDeath");
}


