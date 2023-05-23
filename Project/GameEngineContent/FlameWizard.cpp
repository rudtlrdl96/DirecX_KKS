#include "PrecompileHeader.h"
#include "FlameWizard.h"
#include <GameEngineCore/GameEngineCollision.h>

FlameWizard::FlameWizard()
{
}

FlameWizard::~FlameWizard()
{
}

void FlameWizard::Start()
{
	BaseMonster::Start();

	TeleportCol = CreateComponent<GameEngineCollision>();

	GameEngineTransform* ColTrans = TeleportCol->GetTransform();

	ColTrans->SetLocalPosition(float4(0, -500, 0));
	ColTrans->SetWorldScale(float4(10, 1000, 1));
	ColTrans->SetWorldRotation(float4::Zero);

	PlatformCols.reserve(8);
}

void FlameWizard::Update(float _DeltaTime)
{
	BaseMonster::Update(_DeltaTime);

	if (nullptr != SignEffectActor && true == SignEffectActor->IsDeath())
	{
		SignEffectActor = nullptr;
	}
}

void FlameWizard::DataLoad()
{
	Data = ContentDatabase<MonsterData, MonsterArea>::GetData(108); // 108 = È­¿° ¸¶¹ý»ç

	AttackWaitEndTime = 2.0f;
}

void FlameWizard::TextureLoad()
{
	//if (nullptr == GameEngineSprite::Find("RootEntAttackSign.png"))
	//{
	//	GameEngineDirectory Path;
	//
	//	Path.MoveParentToDirectory("Resources");
	//	Path.Move("Resources");
	//	Path.Move("Texture");
	//	Path.Move("3_ForestOfHarmony");
	//	Path.Move("Monster");
	//
	//	{
	//		Path.Move("RootEnt");
	//		Path.Move("Effect");
	//
	//		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RootEntAttackSign.png").GetFullPath(), 8, 3);
	//		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RootEntAttackEffect.png").GetFullPath(), 9, 1);
	//
	//		Path.MoveParent();
	//		Path.MoveParent();
	//	}
	//
	//	EffectManager::CreateMetaData("RootEntAttackSign", {
	//		.SpriteName = "RootEntAttackSign.png",
	//		.AnimStart = 0,
	//		.AnimEnd = 22,
	//		.AnimIter = 0.045f,
	//		.ScaleRatio = 2.0f,
	//		});
	//
	//	EffectManager::CreateMetaData("RootEntAttackEffect", {
	//		.SpriteName = "RootEntAttackEffect.png",
	//		.AnimStart = 0,
	//		.AnimEnd = 8,
	//		.AnimIter = 0.03f,
	//		.ScaleRatio = 2.0f,
	//		});
	//}
}

void FlameWizard::LoadAnimation()
{
	Render->CreateAnimation({ .AnimationName = "Idle",  .SpriteName = "RootEnt_Idle.png", .Start = 0, .End = 4, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Walk",  .SpriteName = "RootEnt_Walk.png", .Start = 0, .End = 5, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Hit1",  .SpriteName = "RootEnt_Hit1.png", .Start = 0, .End = 0, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Hit2",  .SpriteName = "RootEnt_Hit2.png", .Start = 0, .End = 0, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Death", .SpriteName = "RootEnt_Dead.png", .Start = 0, .End = 0, .ScaleToTexture = true });
}

void FlameWizard::AnimationAttackMetaDataLoad()
{
	AnimPauseTimes[2] = 0.5f;
	AnimPauseTimes[7] = 0.5f;

	AttackRigidbody.SetMaxSpeed(300.0f);
	AttackRigidbody.SetFricCoeff(1000.0f);

	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Data");
		Path.Move("3_ForestOfHarmony");
		Path.Move("Monster");

		AnimColMeta_Attack = ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("RootEnt_Attack").GetFullPath());

		Render->CreateAnimation({
			.AnimationName = AnimColMeta_Attack.GetAnimationName().data(),
			.SpriteName = AnimColMeta_Attack.GetSpriteName().data(),
			.Start = AnimColMeta_Attack.GetStartFrame(),
			.End = AnimColMeta_Attack.GetEndFrame(),
			.Loop = false,
			.ScaleToTexture = true });
	}
}

void FlameWizard::SetColData()
{
	{
		GameEngineTransform* ColTrans = GroundCol->GetTransform();

		ColTrans->SetLocalPosition(float4(0, -3, 0));
		ColTrans->SetWorldScale(float4(45, 6, 1));
	}

	{
		GameEngineTransform* ColTrans = BodyCol->GetTransform();

		ColTrans->SetLocalPosition(float4(0, 45, 0));
		ColTrans->SetWorldScale(float4(50, 90, 1));
	}

	{
		GameEngineTransform* ColTrans = WalkCol->GetTransform();

		LocalWalkColPos = float4(32, 42, 0);

		ColTrans->SetLocalPosition(LocalWalkColPos);
		ColTrans->SetWorldScale(float4(10, 80, 1));
	}
	{
		GameEngineTransform* ColTrans = BackCol->GetTransform();

		LocalBackColPos = float4(-32, 42, 0);

		ColTrans->SetLocalPosition(LocalBackColPos);
		ColTrans->SetWorldScale(float4(10, 80, 1));
	}
	{
		GameEngineTransform* ColTrans = WalkFallCol->GetTransform();

		LocalWalkFallColPos = float4(32, 32, 0);

		ColTrans->SetLocalPosition(LocalWalkFallColPos);
		ColTrans->SetWorldScale(float4(10, 100, 1));
	}

	{
		GameEngineTransform* ColTrans = FindCol->GetTransform();

		LocalFindColPos = float4(200, 50, 0);

		ColTrans->SetLocalPosition(LocalFindColPos);
		ColTrans->SetWorldScale(float4(400, 100, 1));
	}

	{
		GameEngineTransform* ColTrans = ChasingCol->GetTransform();

		LocalChasingColPos = float4(0, 50, 0);

		ColTrans->SetLocalPosition(LocalChasingColPos);
		ColTrans->SetWorldScale(float4(1000, 300, 1));
	}

	LoadFindEffectPos = float4(0, 100, 0);
}

void FlameWizard::Hit_Enter()
{
	BaseMonster::Hit_Enter();

	if (nullptr != SignEffectActor)
	{
		SignEffectActor->Death();
	}
}

void FlameWizard::Hit_End()
{
	AttackWaitTime = 1.5f;
	BaseMonster::Hit_End();
}

void FlameWizard::Attack_Enter()
{
	BaseMonster::Attack_Enter();

	IsAttackSign = false;
	IsAttackEffect = false;

	AttackPos = PlayerActor->GetTransform()->GetWorldPosition() + float4(0, 0, -10.0f);

	float HighY = -100000.0f;

	GameEngineTransform* FloorColTrans = TeleportCol->GetTransform();

	FloorColTrans->SetWorldPosition(AttackPos + float4(0, -FloorColTrans->GetWorldScale().hy()));

	PlatformCols.clear();

	if (true == TeleportCol->CollisionAll((int)CollisionOrder::Platform_Normal, PlatformCols, ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		for (size_t i = 0; i < PlatformCols.size(); i++)
		{
			GameEngineTransform* ColTrans = PlatformCols[i]->GetTransform();

			float ColY = ColTrans->GetWorldPosition().y + ColTrans->GetWorldScale().hy();

			if (HighY < ColY)
			{
				HighY = ColY;
				AttackPos.y = HighY;
			}
		}
	}

	PlatformCols.clear();

	if (true == TeleportCol->CollisionAll((int)CollisionOrder::Platform_Half, PlatformCols, ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		for (size_t i = 0; i < PlatformCols.size(); i++)
		{
			GameEngineTransform* ColTrans = PlatformCols[i]->GetTransform();

			float ColY = ColTrans->GetWorldPosition().y + ColTrans->GetWorldScale().hy();

			if (HighY < ColY)
			{
				HighY = ColY;
				AttackPos.y = HighY;
			}
		}
	}

	PlatformCols.clear();
}

void FlameWizard::Attack_Update(float _DeltaTime)
{
	BaseMonster::Attack_Update(_DeltaTime);

	if (false == IsAttackSign && 0 == Render->GetCurrentFrame())
	{
		IsAttackSign = true;

		SignEffectActor = EffectManager::PlayEffect({
			.EffectName = "RootEntAttackSign",
			.Postion = AttackPos,
			});
	}

	if (false == IsAttackEffect && 3 == Render->GetCurrentFrame())
	{
		IsAttackEffect = true;

		EffectManager::PlayEffect({
			.EffectName = "RootEntAttackEffect",
			.Postion = AttackPos + float4(0, -15, 0),
			});
	}
}