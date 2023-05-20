#include "PrecompileHeader.h"
#include "CarleonRecruit.h"
#include <GameEngineCore/GameEngineCollision.h>

CarleonRecruit::CarleonRecruit()
{
}

CarleonRecruit::~CarleonRecruit()
{
}

void CarleonRecruit::DataLoad()
{
}

void CarleonRecruit::TextureLoad()
{
}

void CarleonRecruit::LoadAnimation()
{
	Render->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "CarleonRecruit_Idle.png", .Start = 0, .End = 5, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Walk", .SpriteName = "CarleonRecruit_Walk.png", .Start = 0, .End = 7, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Hit1", .SpriteName = "CarleonRecruit_Hit1.png", .Start = 0, .End = 0, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Hit2", .SpriteName = "CarleonRecruit_Hit2.png", .Start = 0, .End = 0, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Death", .SpriteName = "CarleonRecruit_Dead.png", .Start = 0, .End = 0, .ScaleToTexture = true });		
}

void CarleonRecruit::AnimationAttackMetaDataLoad()
{
	AnimPauseTimes[0] = 0.3f;
	AnimPauseTimes[7] = 1.0f;

	AttackRigidbody.SetMaxSpeed(300.0f);
	AttackRigidbody.SetFricCoeff(1000.0f);

	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Data");
		Path.Move("1_Opening");
		Path.Move("Monster");

		AnimColMeta_Attack = ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("CarleonRecruit_Attack").GetFullPath());
	
		Render->CreateAnimation({
			.AnimationName = AnimColMeta_Attack.GetAnimationName().data(),
			.SpriteName = AnimColMeta_Attack.GetSpriteName().data(),
			.Start = AnimColMeta_Attack.GetStartFrame(),
			.End = AnimColMeta_Attack.GetEndFrame(),
			.Loop = false,
			.ScaleToTexture = true});
	}
}

void CarleonRecruit::SetColData()
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

void CarleonRecruit::Attack_Enter()
{
	BaseMonster::Attack_Enter();	
	IsAttackMove = false;
}

void CarleonRecruit::Attack_Update(float _DeltaTime)
{
	BaseMonster::Attack_Update(_DeltaTime);

	if (false == IsAttackMove && 1 == Render->GetCurrentFrame())
	{
		IsAttackMove = true;

		switch (Dir)
		{
		case ActorViewDir::Left:
			AttackRigidbody.SetVelocity(float4::Left * 500.0f);
			break;
		case ActorViewDir::Right:
			AttackRigidbody.SetVelocity(float4::Right * 500.0f);
			break;
		default:
			break;
		}
	}
}
