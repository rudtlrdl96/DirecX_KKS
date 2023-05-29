#include "PrecompileHeader.h"
#include "CarleonArcher.h"

#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "Projectile.h"
#include "Player.h"

CarleonArcher::CarleonArcher()
{
}

CarleonArcher::~CarleonArcher()
{
}
void CarleonArcher::Update(float _DeltaTime)
{
	if (nullptr != SignEffectActor && SignEffectActor->IsDeath())
	{
		SignEffectActor = nullptr;
	}

	BaseMonster::Update(_DeltaTime);
}
void CarleonArcher::DataLoad()
{
	Data = ContentDatabase<MonsterData, LevelArea>::GetData(1); // 1 = 칼레온 아쳐
	AttackWaitEndTime = 2.0f;
}

void CarleonArcher::TextureLoad()
{
	if (nullptr == GameEngineSprite::Find("CaerleonArcher_Projectile.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("1_Opening");

		Path.Move("Monster");
		{
			Path.Move("CarleonArcher");
			Path.Move("Effect");

			GameEngineSprite::LoadSheet(Path.GetPlusFileName("CaerleonArcher_Projectile.png").GetFullPath(), 1, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("AttackSign_Archer.png").GetFullPath(), 1, 19);

			Path.MoveParent();
			Path.MoveParent();
		}

		EffectManager::CreateMetaData("CaerleonArcher_Projectile", {
			.SpriteName = "CaerleonArcher_Projectile.png",
			.AnimStart = 0,
			.AnimEnd = 0,
			.ScaleRatio = 2.0f,
			});

		EffectManager::CreateMetaData("AttackSign_Archer", {
			.SpriteName = "AttackSign_Archer.png",
			.AnimStart = 0,
			.AnimEnd = 18,
			.AnimIter = 0.025f,
			.ScaleRatio = 2.0f,
			});
	}
}

void CarleonArcher::LoadAnimation()
{
	Render->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "CarleonArcher_Idle.png", .Start = 0, .End = 4, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Walk", .SpriteName = "CarleonArcher_Walk.png", .Start = 0, .End = 5, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Hit1", .SpriteName = "CarleonArcher_Hit1.png", .Start = 0, .End = 0, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Hit2", .SpriteName = "CarleonArcher_Hit2.png", .Start = 0, .End = 0, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Death", .SpriteName = "CarleonArcher_Dead.png", .Start = 0, .End = 0, .ScaleToTexture = true });
}

void CarleonArcher::AnimationAttackMetaDataLoad()
{
	AnimPauseTimes[2] = 0.5f;
	AnimPauseTimes[3] = 1.0f;

	AttackRigidbody.SetMaxSpeed(300.0f);
	AttackRigidbody.SetFricCoeff(1000.0f);

	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Data");
		Path.Move("1_Opening");
		Path.Move("Monster");

		AnimColMeta_Attack = ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("CarleonArcher_Attack").GetFullPath());

		Render->CreateAnimation({
			.AnimationName = AnimColMeta_Attack.GetAnimationName().data(),
			.SpriteName = AnimColMeta_Attack.GetSpriteName().data(),
			.Start = AnimColMeta_Attack.GetStartFrame(),
			.End = AnimColMeta_Attack.GetEndFrame(),
			.Loop = false,
			.ScaleToTexture = true });
	}
}

void CarleonArcher::SetColData()
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

		LocalChasingColPos = float4(150, 50, 0);

		ColTrans->SetLocalPosition(LocalChasingColPos);
		ColTrans->SetWorldScale(float4(300, 100, 1));
	}

	LoadFindEffectPos = float4(0, 100, 0);
}

void CarleonArcher::DeathPartLoad()
{
	DeadPartNames.reserve(5);
	DeadPartNames.push_back("Parts_CaerleonArcher01.png");
	DeadPartNames.push_back("Parts_CaerleonArcher02.png");
	DeadPartNames.push_back("Parts_CaerleonArcher03.png");
	DeadPartNames.push_back("Parts_CaerleonArcher04.png");
	DeadPartNames.push_back("Parts_CaerleonArcher05.png");

	if (nullptr == GameEngineTexture::Find("Parts_CaerleonArcher01.png"))
	{
		GameEngineDirectory Path;
		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("1_Opening");
		Path.Move("Monster");
		Path.Move("CarleonArcher");
		Path.Move("DeadPart");

		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (size_t i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> LoadTex = GameEngineTexture::Load(Files[i].GetFullPath());

			if (nullptr == LoadTex)
			{
				MsgAssert_Rtti<CarleonArcher>(" - 알 수 없는 이유로 DeadPart 텍스쳐 로드를 실패했습니다");
			}
		}
	}
}

void CarleonArcher::Hit_Enter()
{
	BaseMonster::Hit_Enter();

	if (nullptr != SignEffectActor)
	{
		SignEffectActor->Death();
	}
}

void CarleonArcher::Attack_Enter()
{
	BaseMonster::Attack_Enter();
	IsAttackShot = false;
	IsAttackSign = false;
}

void CarleonArcher::Attack_Update(float _DeltaTime)
{
	BaseMonster::Attack_Update(_DeltaTime);

	if (false == IsAttackSign && 2 == Render->GetCurrentFrame())
	{
		IsAttackSign = true;

		float4 EffectPos = GetTransform()->GetWorldPosition();

		switch (Dir)
		{
		case ActorViewDir::Left:
			EffectPos += float4(-500, 53, -0.1f);
			break;
		case ActorViewDir::Right:
			EffectPos += float4(500, 53, -0.1f);
			break;
		default:
			break;
		}

		SignEffectActor = EffectManager::PlayEffect({
			.EffectName = "AttackSign_Archer",
			.Postion = EffectPos});

		// Projectile Shot
	}

	if (false == IsAttackShot && 3 == Render->GetCurrentFrame())
	{
		IsAttackShot = true;

		std::shared_ptr<Projectile> ShotArrow = GetLevel()->CreateActor<Projectile>();
		float4 EffectPos = GetTransform()->GetWorldPosition();

		float4 ShotDir;

		switch (Dir)
		{
		case ActorViewDir::Left:
			EffectPos += float4(-60, 53, -0.1f);
			ShotDir = float4::Left;
			break;
		case ActorViewDir::Right:
			ShotDir = float4::Right;
			EffectPos += float4(60, 53, -0.1f);
			break;
		default:
			break;
		}

		ShotArrow->ShotProjectile({
			.EffectName = "CaerleonArcher_Projectile",
			.Pos = EffectPos,
			.Dir = ShotDir,
			.ColScale = float4(40, 20),
			.ColOrder = (int)CollisionOrder::Player,
			.IsColDeath = true,
			.Damage = Data.Attack,
			.Speed = 1000.0f,
			.LiveTime = 2.0f,
			.EnterEvent = &PlayerHit,
			.DeathEvent = &ProjectileEndEffect
			});
	}
}

void CarleonArcher::ProjectileEndEffect(const float4& _EndPos)
{
	EffectManager::PlayEffect({
	.EffectName = "HitSkeletonSword",
	.Postion = _EndPos,
		});
}

void CarleonArcher::PlayerHit(std::shared_ptr<BaseContentActor> _HitActor, const ProjectileHitParameter& _Parameter)
{
	ProjectileEndEffect(_Parameter.ProjectilePos);

	std::shared_ptr<Player> CastringPtr = _HitActor->DynamicThis<Player>();

	if (nullptr == CastringPtr)
	{
		return;
	}

	CastringPtr->HitPlayer(_Parameter.Attack, _Parameter.AttackDir * 300.0f + float4(0, 300, 0));
}