#include "PrecompileHeader.h"
#include "GiantEnt.h"
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "Projectile.h"
#include "Player.h"
#include "MonsterDeadBodyActor.h"

GiantEnt::GiantEnt()
{
}

GiantEnt::~GiantEnt()
{
}

void GiantEnt::Start()
{
	StunPivot = float4(0, 150);
	HealthBarScale = float4(1.3f, 1.3f, 1.5f, 1.0f);
	NormalMonster::Start();

	if (nullptr != MinimapImageRender)
	{
		MinimapImageRender->GetTransform()->SetLocalPosition(float4(0, 70, 0));
		MinimapImageRender->GetTransform()->SetLocalScale(float4(120, 140, 1));
	}

	OrbPer = 20.0f;

	HitEvent = []()
	{
		GameEngineSound::Play("Legacy_Hit (Unused).wav");
	};
}

void GiantEnt::DataLoad()
{
	Data = ContentDatabase<MonsterData, LevelArea>::GetData(103); // 103 = 숲지기(자이언트 엔트)

	IsSuperArmor = true;
	IsUnPushArmor = true;
	AttackWaitEndTime = 2.0f;

	RangeAttackPauseTimes[1] = 0.5f;
	RangeAttackPauseTimes[3] = 0.5f;

	RewardGold = 7;
	RewardManaStone = 7;
}

void GiantEnt::TextureLoad()
{
	if (nullptr == GameEngineSprite::Find("GaintEntStampEffect.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("3_ForestOfHarmony");
		Path.Move("Monster");

		{
			Path.Move("GiganticEnt");
			Path.Move("Effect");

			GameEngineSprite::LoadSheet(Path.GetPlusFileName("GaintEntStampEffect.png").GetFullPath(), 11, 2);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("GiantEntProjectile.png").GetFullPath(), 1, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("GiantEntProjectileEffect.png").GetFullPath(), 7, 1);
			Path.MoveParent();


			Path.Move("GiganticEnt_DeadRoot");
			GameEngineTexture::Load(Path.GetPlusFileName("GiganticEnt_DeadRoot.png").GetFullPath());

			Path.MoveParent();
			Path.MoveParent();
		}


	}

	if (false == EffectManager::IsCreate("GaintEntStampEffect"))
	{
		EffectManager::CreateMetaData("GaintEntStampEffect", {
			.SpriteName = "GaintEntStampEffect.png",
			.AnimStart = 0,
			.AnimEnd = 21,
			.AnimInter = 0.02f,
			.ScaleRatio = 1.5f,
			});

		EffectManager::CreateMetaData("GiantEntProjectile", {
			.SpriteName = "GiantEntProjectile.png",
			.AnimStart = 0,
			.AnimEnd = 0,
			.AnimInter = 0.1f,
			.ScaleRatio = 2.0f,
			});

		EffectManager::CreateMetaData("GiantEntProjectileEffect", {
			.SpriteName = "GiantEntProjectileEffect.png",
			.AnimStart = 0,
			.AnimEnd = 6,
			.AnimInter = 0.05f,
			.ScaleRatio = 2.0f,
			});
	}
}

void GiantEnt::LoadAnimation()
{
	Render->CreateAnimation({ .AnimationName = "Idle",  .SpriteName = "GiganticEnt_Idle.png", .Start = 0, .End = 4, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Walk",  .SpriteName = "GiganticEnt_Idle.png", .Start = 0, .End = 0, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Hit1",  .SpriteName = "GiganticEnt_Idle.png", .Start = 0, .End = 0, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Hit2",  .SpriteName = "GiganticEnt_Idle.png", .Start = 0, .End = 0, .ScaleToTexture = true }); 
	Render->CreateAnimation({ .AnimationName = "Death", .SpriteName = "GiganticEnt_Idle.png", .Start = 0, .End = 0, .ScaleToTexture = true });

	std::vector<float> RangeAnimFrame = {0.1f, 1.2f, 0.1f, 0.1f};

	Render->CreateAnimation({ .AnimationName = "RangeAttack", .SpriteName = "GiganticEnt_RangeAttack.png", .Start = 0, .End = 3, .ScaleToTexture = true, .FrameTime = RangeAnimFrame});
}

void GiantEnt::AnimationAttackMetaDataLoad()
{
	AnimPauseTimes[3] = 0.5f;
	AnimPauseTimes[6] = 0.75f;

	AttackRigidbody.SetMaxSpeed(1000.0f);
	AttackRigidbody.SetFricCoeff(2000.0f);

	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Data");
		Path.Move("3_ForestOfHarmony");
		Path.Move("Monster");

		AnimColMeta_Attack = ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("GiganticEnt_MeleeAttack").GetFullPath());

		Render->CreateAnimation({
			.AnimationName = AnimColMeta_Attack.GetAnimationName().data(),
			.SpriteName = AnimColMeta_Attack.GetSpriteName().data(),
			.Start = AnimColMeta_Attack.GetStartFrame(),
			.End = AnimColMeta_Attack.GetEndFrame(),
			.FrameInter = 0.15f,
			.Loop = false,
			.ScaleToTexture = true });
	}

	Render->SetAnimationStartEvent("Attack", 1, []()
		{
			GameEngineSound::Play("GiganticEnt_MeleeAttackReady.wav");
		});

	Render->SetAnimationStartEvent("Attack", 4, []()
		{
			GameEngineSound::Play("Atk_Stomp_Large.wav");
		});

}

void GiantEnt::SetColData()
{
	DeathEffectLocalPos = float4(0, 80, -0.1f);

	{
		GameEngineTransform* ColTrans = GroundCol->GetTransform();

		ColTrans->SetLocalPosition(float4(0, 10, 0));
		ColTrans->SetWorldScale(float4(80, 6, 1));
	}

	{
		GameEngineTransform* ColTrans = BodyCol->GetTransform();

		ColTrans->SetLocalPosition(float4(0, 100, 0));
		ColTrans->SetWorldScale(float4(100, 180, 1));
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

		float4 LocalFindColPos = float4(0, 80, 0);

		ColTrans->SetLocalPosition(LocalFindColPos);
		ColTrans->SetWorldScale(float4(700, 150, 1));
	}

	{
		GameEngineTransform* ColTrans = ChasingCol->GetTransform();

		float4 LocalChasingColPos = float4(0, 80, 0);

		ColTrans->SetLocalPosition(LocalChasingColPos);
		ColTrans->SetWorldScale(float4(1100, 900, 1));
	}

	LoadFindEffectPos = float4(0, 150, 0);
}

void GiantEnt::DeathPartLoad()
{
	DeathPartScale = 2.0f;

	DeadPartNames.reserve(11);
	DeadPartNames.push_back("Parts_GiganticEnt01.png");
	DeadPartNames.push_back("Parts_GiganticEnt02.png");
	DeadPartNames.push_back("Parts_GiganticEnt03.png");
	DeadPartNames.push_back("Parts_GiganticEnt04.png");
	DeadPartNames.push_back("Parts_GiganticEnt05.png");
	DeadPartNames.push_back("Parts_GiganticEnt06.png");
	DeadPartNames.push_back("Parts_GiganticEnt07.png");
	DeadPartNames.push_back("Parts_GiganticEnt08.png");
	DeadPartNames.push_back("Parts_GiganticEnt09.png");
	DeadPartNames.push_back("Parts_GiganticEnt10.png");
	DeadPartNames.push_back("Parts_GiganticEnt11.png");

	if (nullptr == GameEngineTexture::Find("Parts_GiganticEnt01.png"))
	{
		GameEngineDirectory Path;
		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("3_ForestOfHarmony");
		Path.Move("Monster");
		Path.Move("GiganticEnt");
		Path.Move("DeadPart");

		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (size_t i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> LoadTex = GameEngineTexture::Load(Files[i].GetFullPath());

			if (nullptr == LoadTex)
			{
				MsgAssert_Rtti<GiantEnt>(" - 알 수 없는 이유로 DeadPart 텍스쳐 로드를 실패했습니다");
			}
		}
	}

}


void GiantEnt::ShotProjectile(float _Deg)
{
	float4 ProjectileDir = float4::Right;

	for (size_t i = 0; i < 6; i++)
	{
		ProjectileDir = float4::Right;
		ProjectileDir.RotaitonZDeg(_Deg);

		std::shared_ptr<Projectile> NewProjectile = GetLevel()->CreateActor<Projectile>();

		NewProjectile->ShotProjectile({
			.EffectName = "GiantEntProjectile",
			.Pos = GetTransform()->GetWorldPosition() + float4(0, 45, 0),
			.Dir = ProjectileDir,
			.ColScale = float4(50, 50, 1),
			.ColOrder = (int)CollisionOrder::Player,
			.IsColDeath = true,
			.Damage = Data.Attack,
			.Speed = 700.0f,
			.LiveTime = 1.0f,
			.EnterEvent = PlayerHit,
			.DeathEvent = ProjectileEndEffect,
			});
	}
}

void GiantEnt::MonsterDeath()
{
	NormalMonster::MonsterDeath();

	std::shared_ptr<MonsterDeadBodyActor> DeadBody = GetLevel()->CreateActor<MonsterDeadBodyActor>();

	DeadBody->SetTexture("GiganticEnt_DeadRoot.png", 2.0f);
	DeadBody->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition() + float4(0, 47, -1.0f));
}

void GiantEnt::ProjectileEndEffect(const float4& _EndPos)
{
	EffectManager::PlayEffect({
	.EffectName = "GiantEntProjectileEffect",
	.Position = _EndPos,
		});
}

void GiantEnt::PlayerHit(std::shared_ptr<class BaseContentActor> _HitActor, const ProjectileHitParameter& _Parameter)
{
	ProjectileEndEffect(_Parameter.ProjectilePos);

	SoundDoubleCheck::Play("Hit_Energy_Medium.wav");

	std::shared_ptr<Player> CastringPtr = _HitActor->DynamicThis<Player>();

	if (nullptr == CastringPtr)
	{
		return;
	}

	CastringPtr->HitPlayer(_Parameter.Attack, _Parameter.AttackDir * 300.0f);
}