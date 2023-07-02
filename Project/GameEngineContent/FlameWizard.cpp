#include "PrecompileHeader.h"
#include "FlameWizard.h"
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "Projectile.h"
#include "Player.h"

FlameWizard::FlameWizard()
{
}

FlameWizard::~FlameWizard()
{
}


void TeleportIn_Enter(NormalMonster* _this)
{
	_this->GetRender()->ChangeAnimation("TeleportIn");

	EffectManager::PlayEffect({
	.EffectName = "WizardEffectTeleportIn",
	.Position = _this->GetTransform()->GetWorldPosition() + float4(0, 60, -5.0f),
		});
}

void TeleportIn_Update(NormalMonster* _this, float _DeltaTime)
{
	std::shared_ptr<ContentSpriteRenderer> Render = _this->GetRender();

	if (2 == Render->GetCurrentFrame())
	{
		_this->FadeOn();
	}

	if (true == Render->IsAnimationEnd())
	{
		_this->ChangeFSM("TeleportOut");
	}
}

void TeleportIn_End(NormalMonster* _this)
{
}

void TeleportOut_Enter(NormalMonster* _this)
{
	std::shared_ptr<FlameWizard> CastingPtr = _this->DynamicThis<FlameWizard>();

	CastingPtr->GetRender()->ChangeAnimation("TeleportOut");

	if (nullptr == CastingPtr)
	{
		MsgAssert_Rtti<FlameWizard>("해당 함수는 FlameWizard만 사용할 수 있습니다");
		return;
	}

	std::shared_ptr<GameEngineActor> PlayerActor = CastingPtr->PlayerActor;

	if (nullptr == PlayerActor)
	{
		return;
	}


	GameEngineTransform* PlayerTrans = PlayerActor->GetTransform();
	GameEngineTransform* MonsterTrans = CastingPtr->GetTransform();

	float4 PlayerPos = PlayerTrans->GetWorldPosition();
	float4 MonsterPos = MonsterTrans->GetWorldPosition();

	float HighY = -100000.0f;

	GameEngineTransform* FloorColTrans = CastingPtr->FloorCheckCol->GetTransform();

	FloorColTrans->SetWorldPosition(PlayerPos + float4(0, -FloorColTrans->GetWorldScale().hy()));

	CastingPtr->PlatformCols.clear();

	if (true == CastingPtr->FloorCheckCol->CollisionAll((int)CollisionOrder::Platform_Normal, CastingPtr->PlatformCols, ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		for (size_t i = 0; i < CastingPtr->PlatformCols.size(); i++)
		{
			GameEngineTransform* ColTrans = CastingPtr->PlatformCols[i]->GetTransform();

			float ColY = ColTrans->GetWorldPosition().y + ColTrans->GetWorldScale().hy();

			if (HighY < ColY)
			{
				HighY = ColY;
				PlayerPos.y = HighY;
			}
		}
	}

	CastingPtr->PlatformCols.clear();

	for (size_t i = 0; i < 5; i++)
	{
		float4 TeleportPos = PlayerPos + float4(GameEngineRandom::MainRandom.RandomFloat(-200.0f, 200.0f), 0, 0);
		TeleportPos.z = MonsterPos.z;
		MonsterTrans->SetWorldPosition(TeleportPos);

		std::shared_ptr<GameEngineCollision> GroundCol = ContentFunc::PlatformColCheck(CastingPtr->GroundCol, true);
		std::shared_ptr<GameEngineCollision> BodyCol = ContentFunc::PlatformColCheck(CastingPtr->BodyCol, true);

		if (nullptr == GroundCol || nullptr != BodyCol)
		{
			MonsterTrans->SetWorldPosition(MonsterPos);
		}
		else
		{
			break;
		}
	}

	EffectManager::PlayEffect({
	.EffectName = "WizardEffectTeleportOut",
	.Position = CastingPtr->GetTransform()->GetWorldPosition() + float4(0, 60, -5.0f),
		});

	CastingPtr->FadeOff();
}

void TeleportOut_Update(NormalMonster* _this, float _DeltaTime)
{
	std::shared_ptr<ContentSpriteRenderer> Render = _this->GetRender();

	if (true == Render->IsAnimationEnd())
	{
		_this->ChangeFSM("Idle");
	}
}

void TeleportOut_End(NormalMonster* _this)
{

}

void FlameWizard::Start()
{
	NormalMonster::Start();

	MonsterFsm.AddFSM("TeleportIn", &TeleportIn_Enter, &TeleportIn_Update, &TeleportIn_End);
	MonsterFsm.AddFSM("TeleportOut", &TeleportOut_Enter, &TeleportOut_Update, &TeleportOut_End);

	FloorCheckCol = CreateComponent<GameEngineCollision>();

	GameEngineTransform* ColTrans = FloorCheckCol->GetTransform();

	ColTrans->SetLocalPosition(float4(0, -150, 0));
	ColTrans->SetWorldScale(float4(10, 300, 1));
	ColTrans->SetWorldRotation(float4::Zero);

	PlatformCols.reserve(8);
}

void FlameWizard::Update(float _DeltaTime)
{
	NormalMonster::Update(_DeltaTime);

	if (nullptr != ShotProjectile)
	{
		if (true == ShotProjectile->IsWaitEnd() || true == ShotProjectile->IsDeath())
		{
			ShotProjectile = nullptr;
		}
	}

	TeleportCoolTime -= _DeltaTime;
}

void FlameWizard::DataLoad()
{
	Data = ContentDatabase<MonsterData, LevelArea>::GetData(108); // 108 = 화염 마법사

	AttackWaitEndTime = 2.0f;
}

void FlameWizard::TextureLoad()
{
	if (nullptr == GameEngineSprite::Find("FireHitEffect.png"))
	{
		GameEngineDirectory Path;
	
		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("3_ForestOfHarmony");
		Path.Move("Monster");
	
		{
			Path.Move("FlameWizard");
			Path.Move("Effect");
	
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("FireHitEffect.png").GetFullPath(), 4, 3);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("FlameWizardProjcetile.png").GetFullPath(), 4, 6);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("WizardEffectTeleportIn.png").GetFullPath(), 3, 1);
			GameEngineSprite::LoadSheet(Path.GetPlusFileName("WizardEffectTeleportOut.png").GetFullPath(), 5, 1);
	
			Path.MoveParent();
			Path.MoveParent();
		}
	
		EffectManager::CreateMetaData("FireHitEffect", {
			.SpriteName = "FireHitEffect.png",
			.AnimStart = 0,
			.AnimEnd = 11,
			.AnimIter = 0.05f,
			.ScaleRatio = 2.0f,
			});
	
		EffectManager::CreateMetaData("FlameWizardProjcetile", {
			.SpriteName = "FlameWizardProjcetile.png",
			.AnimStart = 0,
			.AnimEnd = 23,
			.AnimIter = 0.03f,
			.ScaleRatio = 2.0f,
			});

		EffectManager::CreateMetaData("WizardEffectTeleportIn", {
			.SpriteName = "WizardEffectTeleportIn.png",
			.AnimStart = 0,
			.AnimEnd = 2,
			.AnimIter = 0.05f,
			.ScaleRatio = 2.0f,
			});

		EffectManager::CreateMetaData("WizardEffectTeleportOut", {
			.SpriteName = "WizardEffectTeleportOut.png",
			.AnimStart = 0,
			.AnimEnd = 4,
			.AnimIter = 0.05f,
			.ScaleRatio = 2.0f,
			});
	}
}

void FlameWizard::LoadAnimation()
{
	Render->CreateAnimation({ .AnimationName = "Idle",  .SpriteName = "FlameWizard_Idle.png", .Start = 0, .End = 4, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "TeleportIn",  .SpriteName = "FlameWizard_TeleportIn.png", .Start = 0, .End = 7, .FrameInter = 0.05f, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "TeleportOut",  .SpriteName = "FlameWizard_TeleportOut.png", .Start = 0, .End = 4, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Hit1",  .SpriteName = "FlameWizard_Hit1.png", .Start = 0, .End = 0, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Hit2",  .SpriteName = "FlameWizard_Hit2.png", .Start = 0, .End = 0, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Death", .SpriteName = "FlameWizard_Hit1.png", .Start = 0, .End = 0, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "AttackEnter", .SpriteName = "FlameWizard_AttackEnter.png", .Start = 0, .End = 2, .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "AttackLoop", .SpriteName = "FlameWizard_AttackLoop.png", .Start = 0, .End = 4, .ScaleToTexture = true });
}

void FlameWizard::AnimationAttackMetaDataLoad()
{
	AttackRigidbody.SetMaxSpeed(300.0f);
	AttackRigidbody.SetFricCoeff(1000.0f);
}

void FlameWizard::SetColData()
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

		float4 LocalWalkColPos = float4(32, 42, 0);

		ColTrans->SetLocalPosition(LocalWalkColPos);
		ColTrans->SetWorldScale(float4(10, 80, 1));
	}
	{
		GameEngineTransform* ColTrans = BackCol->GetTransform();

		float4 LocalBackColPos = float4(-32, 42, 0);

		ColTrans->SetLocalPosition(LocalBackColPos);
		ColTrans->SetWorldScale(float4(10, 80, 1));
	}
	{
		GameEngineTransform* ColTrans = WalkFallCol->GetTransform();

		float4 LocalWalkFallColPos = float4(32, 32, 0);

		ColTrans->SetLocalPosition(LocalWalkFallColPos);
		ColTrans->SetWorldScale(float4(10, 100, 1));
	}

	{
		GameEngineTransform* ColTrans = FindCol->GetTransform();

		float4 LocalFindColPos = float4(0, 50, 0);

		ColTrans->SetLocalPosition(LocalFindColPos);
		ColTrans->SetWorldScale(float4(600, 600, 1));
	}

	{
		GameEngineTransform* ColTrans = ChasingCol->GetTransform();

		float4 LocalChasingColPos = float4(0, 50, 0);

		ColTrans->SetLocalPosition(LocalChasingColPos);
		ColTrans->SetWorldScale(float4(1000, 600, 1));
	}

	LoadFindEffectPos = float4(0, 100, 0);
}

void FlameWizard::DeathPartLoad()
{
	DeathPartScale = 2.0f;

	DeadPartNames.reserve(8);
	DeadPartNames.push_back("Parts_FlameWizard01.png");
	DeadPartNames.push_back("Parts_FlameWizard02.png");
	DeadPartNames.push_back("Parts_FlameWizard03.png");
	DeadPartNames.push_back("Parts_FlameWizard04.png");
	DeadPartNames.push_back("Parts_FlameWizard05.png");
	DeadPartNames.push_back("Parts_FlameWizard06.png");
	DeadPartNames.push_back("Parts_FlameWizard07.png");
	DeadPartNames.push_back("Parts_FlameWizard08.png");

	if (nullptr == GameEngineTexture::Find("Parts_FlameWizard01.png"))
	{
		GameEngineDirectory Path;
		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("3_ForestOfHarmony");
		Path.Move("Monster");
		Path.Move("FlameWizard");
		Path.Move("DeadPart");

		std::vector<GameEngineFile> Files = Path.GetAllFile({ ".png" });

		for (size_t i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> LoadTex = GameEngineTexture::Load(Files[i].GetFullPath());

			if (nullptr == LoadTex)
			{
				MsgAssert_Rtti<FlameWizard>(" - 알 수 없는 이유로 DeadPart 텍스쳐 로드를 실패했습니다");
			}
		}
	}
}

void FlameWizard::Idle_Update(float _DeltaTime)
{
	if (true == HitCheck())
	{
		return;
	}

	if (true == Fall(_DeltaTime))
	{
		return;
	}

	if (true == IsStun)
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
			.Position = GetTransform()->GetWorldPosition() + LoadFindEffectPos });

		PlayerActor = ResultCol->GetActor()->DynamicThis<GameEngineActor>();
		return;
	}
}

void FlameWizard::Chasing_Enter()
{

}

void FlameWizard::Chasing_Update(float _DeltaTime)
{
	if(true == HitCheck())
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
	else
	{
		if (TeleportCoolTime <= 0.0f)
		{
			MonsterFsm.ChangeState("TeleportIn");
			TeleportCoolTime = 5.0f;
		}

		return;
	}
}

void FlameWizard::Chasing_End()
{

}

void FlameWizard::Hit_Enter()
{
	NormalMonster::Hit_Enter();
	
	if (nullptr != ShotProjectile)
	{
		ShotProjectile->Death();
		ShotProjectile = nullptr;
	}
}

void FlameWizard::Hit_End()
{
	NormalMonster::Hit_End();
	AttackWaitTime = 1.5f;
}

void FlameWizard::Attack_Enter()
{
	Render->ChangeAnimation("AttackEnter");

	IsAttackLoop = false;
	AttackCount = 0;
	AttackCoolTime = 0.0f;
	
}

void FlameWizard::Attack_Update(float _DeltaTime)
{
	if (true == HitCheck())
	{
		MonsterFsm.ChangeState("Hit");
		return;
	}

	if (nullptr == PlayerActor || true == PlayerActor->IsDeath())
	{
		MonsterFsm.ChangeState("Idle");
		return;
	}

	if (false == IsAttackLoop && true == Render->IsAnimationEnd())
	{
		IsAttackLoop = true;
		CreateProjectile(1.5f);
		Render->ChangeAnimation("AttackLoop");
		return;
	}

	if (true == IsAttackLoop && nullptr == ShotProjectile)
	{
		++AttackCount;
		CreateProjectile(0.5f);

		if (2 <= AttackCount)
		{
			MonsterFsm.ChangeState("Idle");
			return;
		}
	}

}

void FlameWizard::CreateProjectile(float _WaitTime)
{
	ShotProjectile = GetLevel()->CreateActor<Projectile>();
	float4 ShotPos = GetTransform()->GetWorldPosition();

	switch (Dir)
	{
	case ActorViewDir::Left:
		ShotPos += float4(-50, 70.0f, 0.0f);
		break;
	case ActorViewDir::Right:
		ShotPos += float4(50, 70.0f, 0.0f);
		break;
	default:
		break;
	}


	float4 PlayerPos = PlayerActor->GetTransform()->GetWorldPosition() + float4(0, 70.0f, 0.0f);
	float4 ShotDir = PlayerPos - ShotPos;
	ShotDir.z = 0;
	ShotDir.Normalize();

	ShotProjectile->ShotProjectile({
		.EffectName = "FlameWizardProjcetile",
		.Pos = ShotPos,
		.Dir = ShotDir,
		.ColScale = float4(50, 50, 1),
		.ColOrder = (int)CollisionOrder::Player,
		.IsColDeath = true,
		.Damage = Data.Attack,
		.Speed = 500.0f,
		.LiveTime = 2.0f + _WaitTime,
		.WaitTime = _WaitTime,
		.EnterEvent = &PlayerHit,
		.DeathEvent = &ProjectileEndEffect,
		});
}


void FlameWizard::ProjectileEndEffect(const float4& _EndPos)
{
	EffectManager::PlayEffect({
	.EffectName = "FireHitEffect",
	.Position = _EndPos,
		});
}

void FlameWizard::PlayerHit(std::shared_ptr<class BaseContentActor> _HitActor, const ProjectileHitParameter& _Parameter)
{
	ProjectileEndEffect(_Parameter.ProjectilePos);

	std::shared_ptr<Player> CastringPtr = _HitActor->DynamicThis<Player>();

	if (nullptr == CastringPtr)
	{
		return;
	}

	CastringPtr->HitPlayer(_Parameter.Attack, _Parameter.AttackDir * 200.0f);
}