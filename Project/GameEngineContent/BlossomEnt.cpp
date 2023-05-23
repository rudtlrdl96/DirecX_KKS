#include "PrecompileHeader.h"
#include "BlossomEnt.h"
#include <GameEngineCore/GameEngineCollision.h>

BlossomEnt::BlossomEnt()
{
}

BlossomEnt::~BlossomEnt()
{
}

void BlossomEnt::DataLoad()
{
	Data = ContentDatabase<MonsterData, MonsterArea>::GetData(101); // 101 = ²É ¿£Æ®

	AttackWaitEndTime = 2.0f;
}

void BlossomEnt::TextureLoad()
{
	if (nullptr == GameEngineSprite::Find("BlossomEntAttackEffect.png"))
	{
		GameEngineDirectory Path;
	
		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("3_ForestOfHarmony");
		Path.Move("Monster");
	
		{
			Path.Move("BlossomEnt");
			Path.Move("Effect");
	
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("BlossomEntAttackEffect.png").GetFullPath(), 4, 7);
	
			Path.MoveParent();
			Path.MoveParent();
		}
	
		EffectManager::CreateMetaData("BlossomEntAttackEffect", {
			.SpriteName = "BlossomEntAttackEffect.png",
			.AnimStart = 0,
			.AnimEnd = 27,
			.AnimIter = 0.05f,
			.ScaleRatio = 1.5f,
			});
	}
}

void BlossomEnt::LoadAnimation()
{
	Render->CreateAnimation({ .AnimationName = "Idle",  .SpriteName = "BlossomEnt_Idle.png", .Start = 0, .End = 4, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Walk",  .SpriteName = "BlossomEnt_Walk.png", .Start = 0, .End = 5, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Hit1",  .SpriteName = "BlossomEnt_Hit1.png", .Start = 0, .End = 0, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Hit2",  .SpriteName = "BlossomEnt_Hit2.png", .Start = 0, .End = 0, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Death", .SpriteName = "BlossomEnt_Idle.png", .Start = 0, .End = 0, .ScaleToTexture = true });
}

void BlossomEnt::AnimationAttackMetaDataLoad()
{
	AnimPauseTimes[9] = 1.5f;

	AttackRigidbody.SetMaxSpeed(300.0f);
	AttackRigidbody.SetFricCoeff(1000.0f);

	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Data");
		Path.Move("3_ForestOfHarmony");
		Path.Move("Monster");

		AnimColMeta_Attack = ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("BlossomEnt_Attack").GetFullPath());

		Render->CreateAnimation({
			.AnimationName = AnimColMeta_Attack.GetAnimationName().data(),
			.SpriteName = AnimColMeta_Attack.GetSpriteName().data(),
			.Start = AnimColMeta_Attack.GetStartFrame(),
			.End = AnimColMeta_Attack.GetEndFrame(),
			.Loop = false,
			.ScaleToTexture = true });
	}
}

void BlossomEnt::SetColData()
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

		LocalChasingColPos = float4(25, 50, 0);

		ColTrans->SetLocalPosition(LocalChasingColPos);
		ColTrans->SetWorldScale(float4(50, 100, 1));
	}

	LoadFindEffectPos = float4(0, 100, 0);
}

void BlossomEnt::Attack_Enter()
{
	BaseMonster::Attack_Enter();
	IsAttackStart = false;

	IsSuperArmor = true;

	Buffer.OutlineColor = float4(1.0f, 1.0f, -1.0f, 1.0f);
}

void BlossomEnt::Attack_Update(float _DeltaTime)
{
	BaseMonster::Attack_Update(_DeltaTime);

	if (false == IsAttackStart && 9 == Render->GetCurrentFrame())
	{
		IsAttackStart = true;

		EffectManager::PlayEffect({
			.EffectName = "BlossomEntAttackEffect",
			.Postion = GetTransform()->GetWorldPosition() + float4(0, 45, -0.1f)
			});
	}
}

void BlossomEnt::Attack_End()
{
	IsSuperArmor = false;
	BaseMonster::Attack_End();
	Buffer.OutlineColor = float4::Null;
}
