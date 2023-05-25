#include "PrecompileHeader.h"
#include "GiantEnt.h"
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "Projectile.h"

GiantEnt::GiantEnt()
{
}

GiantEnt::~GiantEnt()
{
}

void GiantEnt::DataLoad()
{
	Data = ContentDatabase<MonsterData, MonsterArea>::GetData(103); // 103 = 숲지기(자이언트 엔트)

	IsSuperArmor = true;
	AttackWaitEndTime = 2.0f;

	RangeAttackPauseTimes[1] = 0.5f;
	RangeAttackPauseTimes[3] = 0.5f;
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
			Path.MoveParent();
		}

		EffectManager::CreateMetaData("GaintEntStampEffect", {
			.SpriteName = "GaintEntStampEffect.png",
			.AnimStart = 0,
			.AnimEnd = 21,
			.AnimIter = 0.02f,
			.ScaleRatio = 1.5f,
			});

		EffectManager::CreateMetaData("GiantEntProjectile", {
			.SpriteName = "GiantEntProjectile.png",
			.AnimStart = 0,
			.AnimEnd = 0,
			.AnimIter = 0.1f,
			.ScaleRatio = 2.0f,
			});

		EffectManager::CreateMetaData("GiantEntProjectileEffect", {
			.SpriteName = "GiantEntProjectileEffect.png",
			.AnimStart = 0,
			.AnimEnd = 6,
			.AnimIter = 0.05f,
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
	Render->CreateAnimation({ .AnimationName = "RangeAttack", .SpriteName = "GiganticEnt_RangeAttack.png", .Start = 0, .End = 3, .ScaleToTexture = true });
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

		LocalFindColPos = float4(0, 80, 0);

		ColTrans->SetLocalPosition(LocalFindColPos);
		ColTrans->SetWorldScale(float4(700, 150, 1));
	}

	{
		GameEngineTransform* ColTrans = ChasingCol->GetTransform();

		LocalChasingColPos = float4(0, 80, 0);

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
			.Speed = 700.0f,
			.LiveTime = 1.0f,
			.EnterEvent = PlayerHit,
			.DeathEvent = ProjectileEndEffect,
			});
	}
}

void GiantEnt::ProjectileEndEffect(const float4& _EndPos)
{
	EffectManager::PlayEffect({
	.EffectName = "GiantEntProjectileEffect",
	.Postion = _EndPos,
		});
}

void GiantEnt::PlayerHit(std::shared_ptr<class BaseContentActor> _HitActor, const ProjectileHitParameter& _Parameter)
{
	ProjectileEndEffect(_Parameter.ProjectilePos);
}