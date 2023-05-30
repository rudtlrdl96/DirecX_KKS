#include "PrecompileHeader.h"
#include "GlacialWizard.h"
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "RigidProjectile.h"
#include "Player.h"

GlacialWizard::GlacialWizard()
{
}

GlacialWizard::~GlacialWizard()
{
}

void GlacialWizard::DataLoad()
{
	Data = ContentDatabase<MonsterData, LevelArea>::GetData(109); // 109 = 빙결 마법사

	AttackWaitEndTime = 2.0f;
}

void GlacialWizard::TextureLoad()
{
	if (nullptr == GameEngineSprite::Find("IcicleSpawnEffect.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("3_ForestOfHarmony");
		Path.Move("Monster");

		{
			Path.Move("GlacialWizard");
			Path.Move("Effect");

			GameEngineSprite::LoadSheet(Path.GetPlusFileName("Icicle.png").GetFullPath(), 1, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("HitSlashEffect.png").GetFullPath(), 5, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("IcicleSpawnEffect.png").GetFullPath(), 5, 4);

			Path.MoveParent();
			Path.MoveParent();
		}

		EffectManager::CreateMetaData("Icicle", {
			.SpriteName = "Icicle.png",
			.AnimStart = 0,
			.AnimEnd = 0,
			.AnimIter = 0.1f,
			.ScaleRatio = 2.0f,
			});

		EffectManager::CreateMetaData("HitSlashEffect", {
			.SpriteName = "HitSlashEffect.png",
			.AnimStart = 0,
			.AnimEnd = 4,
			.AnimIter = 0.025f,
			.ScaleRatio = 2.0f,
			});

		EffectManager::CreateMetaData("IcicleSpawnEffect", {
			.SpriteName = "IcicleSpawnEffect.png",
			.AnimStart = 0,
			.AnimEnd = 18,
			.AnimIter = 0.03f,
			.ScaleRatio = 2.0f,
			});
	}
}

void GlacialWizard::LoadAnimation()
{
	Render->CreateAnimation({ .AnimationName = "Idle",  .SpriteName = "GlacialWizard_Idle.png", .Start = 0, .End = 4, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Hit1",  .SpriteName = "GlacialWizard_Hit1.png", .Start = 0, .End = 0, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Hit2",  .SpriteName = "GlacialWizard_Hit2.png", .Start = 0, .End = 0, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Death", .SpriteName = "GlacialWizard_Hit1.png", .Start = 0, .End = 0, .ScaleToTexture = true });
}

void GlacialWizard::AnimationAttackMetaDataLoad()
{
	AnimPauseTimes[3] = 0.35f;
	AnimPauseTimes[7] = 0.75f;

	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Data");
		Path.Move("3_ForestOfHarmony");
		Path.Move("Monster");

		AnimColMeta_Attack = ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("GlacialWizard_Attack").GetFullPath());

		Render->CreateAnimation({
			.AnimationName = AnimColMeta_Attack.GetAnimationName().data(),
			.SpriteName = AnimColMeta_Attack.GetSpriteName().data(),
			.Start = AnimColMeta_Attack.GetStartFrame(),
			.End = AnimColMeta_Attack.GetEndFrame(),
			.FrameInter = 0.1f,
			.Loop = false,
			.ScaleToTexture = true });
	}
}

void GlacialWizard::SetColData()
{
	{
		GameEngineTransform* ColTrans = GroundCol->GetTransform();

		ColTrans->SetLocalPosition(float4(0, -3, 0));
		ColTrans->SetWorldScale(float4(45, 7, 1));
	}

	{
		GameEngineTransform* ColTrans = BodyCol->GetTransform();

		ColTrans->SetLocalPosition(float4(0, 47, 0));
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

		LocalFindColPos = float4(0, 50, 0);

		ColTrans->SetLocalPosition(LocalFindColPos);
		ColTrans->SetWorldScale(float4(600, 600, 1));
	}

	{
		GameEngineTransform* ColTrans = ChasingCol->GetTransform();

		LocalChasingColPos = float4(0, 50, 0);

		ColTrans->SetLocalPosition(LocalChasingColPos);
		ColTrans->SetWorldScale(float4(1000, 600, 1));
	}

	LoadFindEffectPos = float4(0, 100, 0);
}

void GlacialWizard::DeathPartLoad()
{
	DeathPartScale = 2.0f;

	DeadPartNames.reserve(8);
	DeadPartNames.push_back("Parts_CaerleonLowClassWizard01.png");
	DeadPartNames.push_back("Parts_CaerleonLowClassWizard02.png");
	DeadPartNames.push_back("Parts_CaerleonLowClassWizard03.png");
	DeadPartNames.push_back("Parts_CaerleonLowClassWizard04.png");
	DeadPartNames.push_back("Parts_CaerleonLowClassWizard05.png");
	DeadPartNames.push_back("Parts_CaerleonLowClassWizard06.png");
	DeadPartNames.push_back("Parts_CaerleonLowClassWizard07.png");
	DeadPartNames.push_back("Parts_CaerleonLowClassWizard08.png");

	if (nullptr == GameEngineTexture::Find("Parts_CaerleonLowClassWizard01.png"))
	{
		GameEngineDirectory Path;
		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("3_ForestOfHarmony");
		Path.Move("Monster");
		Path.Move("GlacialWizard");
		Path.Move("DeadPart");

		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (size_t i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> LoadTex = GameEngineTexture::Load(Files[i].GetFullPath());

			if (nullptr == LoadTex)
			{
				MsgAssert_Rtti<GlacialWizard>(" - 알 수 없는 이유로 DeadPart 텍스쳐 로드를 실패했습니다");
			}
		}
	}

}

void GlacialWizard::Idle_Update(float _DeltaTime)
{

	if (true == Fall(_DeltaTime))
	{
		return;
	}

	if (true == HitCheck())
	{
		return;
	}

	if (AttackWaitTime < AttackWaitEndTime)
	{
		return;
	}

	if (true == IsChasingWait)
	{
		ChasingWaitTime += _DeltaTime;


		if (ChasingWaitTime >= 0.5f)
		{
			MonsterFsm.ChangeState("Chasing");
		}

		return;
	}

	if (nullptr != PlayerActor)
	{
		MonsterFsm.ChangeState("Chasing");
		return;
	}

	std::shared_ptr<GameEngineCollision> ResultCol = nullptr;

	ResultCol = FindCol->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D);

	if (nullptr != ResultCol)
	{
		IsChasingWait = true;

		EffectManager::PlayEffect({
			.EffectName = "FindPlayer",
			.Postion = GetTransform()->GetWorldPosition() + LoadFindEffectPos });

		PlayerActor = ResultCol->GetActor()->DynamicThis<GameEngineActor>();
		return;
	}
}

void GlacialWizard::Chasing_Enter()
{

}

void GlacialWizard::Chasing_Update(float _DeltaTime)
{
	if (true == HitCheck())
	{
		return;
	}

	Fall(_DeltaTime);

	if (nullptr == PlayerActor)
	{
		MonsterFsm.ChangeState("Idle");
		return;
	}

	GameEngineTransform* PlayerTrans = PlayerActor->GetTransform();
	GameEngineTransform* MonsterTrans = GetTransform();

	float4 ChasingDir = PlayerTrans->GetWorldPosition() - MonsterTrans->GetWorldPosition();
	ChasingDir.y = 0;
	ChasingDir.Normalize();

	if (ChasingDir.x < 0)
	{
		SetViewDir(ActorViewDir::Left);
	}
	else
	{
		SetViewDir(ActorViewDir::Right);
	}

	std::shared_ptr<GameEngineCollision> ResultCol = nullptr;

	ResultCol = ChasingCol->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D);

	if (nullptr != ResultCol)
	{
		PlayerActor = ResultCol->GetActor()->DynamicThis<GameEngineActor>();
		MonsterFsm.ChangeState("Attack");
		return;
	}
}

void GlacialWizard::Chasing_End()
{

}

void GlacialWizard::Hit_End()
{
	BaseMonster::Hit_End();
	AttackWaitTime = 1.5f;
}

void GlacialWizard::Attack_Enter()
{
	BaseMonster::Attack_Enter();
	IsProjectileShot = false;
}

void GlacialWizard::Attack_Update(float _DeltaTime)
{
	BaseMonster::Attack_Update(_DeltaTime);

	if (nullptr == PlayerActor || true == PlayerActor->IsDeath())
	{
		return;
	}

	if (false == IsProjectileShot && 4 == Render->GetCurrentFrame())
	{
		IsProjectileShot = true;
		
		std::shared_ptr<RigidProjectile> ShotProjectile = GetLevel()->CreateActor<RigidProjectile>();

		float4 PlayerPos = PlayerActor->GetTransform()->GetWorldPosition();
		float4 ShotPos = PlayerPos + float4(0, 300.0f, -5.0f);
		float4 ShotDir = PlayerPos - ShotPos;
		ShotDir.z = 0;
		ShotDir.Normalize();

		ShotProjectile->InitRigd(2000.0f, 500.0f);

		ShotProjectile->ShotProjectile({
			.EffectName = "Icicle",
			.Pos = ShotPos,
			.Dir = ShotDir,
			.ColScale = float4(30, 80, 1),
			.ColOrder = (int)CollisionOrder::Player,
			.IsColDeath = true,
			.Damage = Data.Attack,
			.Speed = 3000.0f,
			.LiveTime = 2.0f,
			.WaitTime = 0.3f,
			.EnterEvent = &PlayerHit,
			.DeathEvent = &ProjectileEndEffect,
			});

		EffectManager::PlayEffect({
			.EffectName = "IcicleSpawnEffect",
			.Postion = ShotPos + float4(0, -50, -0.1f)});
	}
}

void GlacialWizard::ProjectileEndEffect(const float4& _EndPos)
{
	EffectManager::PlayEffect({
	.EffectName = "HitSlashEffect",
	.Postion = _EndPos,
		});
}

void GlacialWizard::PlayerHit(std::shared_ptr<class BaseContentActor> _HitActor, const ProjectileHitParameter& _Parameter)
{
	ProjectileEndEffect(_Parameter.ProjectilePos);

	std::shared_ptr<Player> CastringPtr = _HitActor->DynamicThis<Player>();

	if (nullptr == CastringPtr)
	{
		return;
	}

	CastringPtr->HitPlayer(_Parameter.Attack, float4(_Parameter.AttackDir.x, 1.0f) * 300.0f);
}