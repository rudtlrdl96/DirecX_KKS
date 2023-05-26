#include "PrecompileHeader.h"
#include "BaseMonster.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "CollisionDebugRender.h"
#include "HitParticle.h"
#include "HealthBar.h"
#include "DeadPartParticle.h"
#include "Player.h"

BaseMonster::BaseMonster()
{
}

BaseMonster::~BaseMonster()
{
}

void BaseMonster::HitMonster(float _Damage, ActorViewDir _HitDir, bool _IsStiffen, bool _IsPush)
{
	HP -= _Damage;

	HealthBarActiveTime = 3.0f;

	HitDir = _HitDir;
	IsHit = true;
	IsHitEffectOn = true;
	IsStiffen = _IsStiffen;
	IsPush = _IsPush;
	HitEffectProgress = 0.0f;
}

void BaseMonster::Start()
{
	HealthBarPtr = GetLevel()->CreateActor<HealthBar>();
	DeathEffectLocalPos = float4(0, 50, -5.0f);

	if (nullptr == GameEngineTexture::Find("EnemyHpBar.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("UI");

		GameEngineTexture::Load(Path.GetPlusFileName("EnemyHpBar.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("EnemySubBar.png").GetFullPath());
		GameEngineTexture::Load(Path.GetPlusFileName("EnemyHpFrame.png").GetFullPath());
	}

	HealthBarPtr->GetTransform()->SetParent(GetTransform());
	HealthBarPtr->GetTransform()->SetLocalPosition(float4(0, -15, -10));
	HealthBarPtr->SetTexture("EnemyHpFrame.png", "EnemyHpBar.png", "EnemySubBar.png");

	if (false == GameEngineInput::IsKey("MonsterDebugOn"))
	{
		GameEngineInput::CreateKey("MonsterDebugOn", VK_F3);
		GameEngineInput::CreateKey("MonsterDebugOff", VK_F4);
	}

	BattleActor::Start();
	
	MonsterFsm.Init(this);
	MonsterFsm.AddFSM("Idle", &BaseMonster::Idle_Enter, &BaseMonster::Idle_Update, &BaseMonster::Idle_End);
	MonsterFsm.AddFSM("Walk", &BaseMonster::Walk_Enter, &BaseMonster::Walk_Update, &BaseMonster::Walk_End);
	MonsterFsm.AddFSM("Chasing", &BaseMonster::Chasing_Enter, &BaseMonster::Chasing_Update, &BaseMonster::Chasing_End);
	MonsterFsm.AddFSM("Attack", &BaseMonster::Attack_Enter, &BaseMonster::Attack_Update, &BaseMonster::Attack_End);
	MonsterFsm.AddFSM("Hit", &BaseMonster::Hit_Enter, &BaseMonster::Hit_Update, &BaseMonster::Hit_End);
	
	BodyCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Monster);
	FindCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Unknown);
	ChasingCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Unknown);
	WalkCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Unknown);
	BackCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Unknown);
	GroundCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Unknown);
	WalkFallCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Unknown);

	HitRigidbody.SetMaxSpeed(300.0f);
	HitRigidbody.SetFricCoeff(1000.0f);

	DataLoad();
	TextureLoad();
	LoadAnimation();
	AnimationAttackMetaDataLoad();
	SetColData();
	EffectLoadCheck();
	DeathPartLoad();

	AttackCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Unknown);

	AttackCheck.SetCol(AttackCol, (UINT)CollisionOrder::Player);
	AttackCheck.SetRender(Render);
	AttackCheck.SetEvent([this](std::shared_ptr<BaseContentActor> _Ptr, const AttackColMetaData& _Data)
		{
			std::shared_ptr <Player> CastPtr = std::static_pointer_cast<Player>(_Ptr);

			if (nullptr == CastPtr)
			{
				MsgAssert_Rtti<BaseMonster>(" - 플레이어만 Player Col Order를 가질 수 있습니다.");
				return;
			}

			EffectManager::PlayEffect({
				.EffectName = "HitNormal",
				.Postion = CastPtr->GetTransform()->GetWorldPosition() + float4(0, 40, 0),
				.AddSetZ = -10.0f});

			switch (Dir)
			{
			case ActorViewDir::Left:
				CastPtr->HitPlayer(Data.Attack, float4(-300, 500) * AttakPushRatio);
				break;
			case ActorViewDir::Right:
				CastPtr->HitPlayer(Data.Attack, float4(300, 500) * AttakPushRatio);
				break;
			default:
				break;
			}
		});

	AttackCheck.SetColData(AnimColMeta_Attack);

	HP = Data.HP;
	MonsterFsm.ChangeState("Idle");
}

void BaseMonster::Update(float _DeltaTime)
{
	if (HP <= 0.0f)
	{
		MonsterDeath();
		return;
	}

	HealthBarActiveTime -= _DeltaTime;

	if (0.0f < HealthBarActiveTime)
	{
		HealthBarPtr->On();
	}
	else
	{
		HealthBarPtr->Off();
	}

	AttackWaitTime += _DeltaTime;
	TurnCoolTime -= _DeltaTime;
	HitParticleCoolTime += _DeltaTime;

	HealthBarPtr->UpdateBar(HP / Data.HP, _DeltaTime);


	if (true == GameEngineInput::IsDown("MonsterDebugOn"))
	{
		if (false == IsDebug())
		{
			DebugOn();
			CreateColDebugRender();
		}
	}
	else if (true == GameEngineInput::IsDown("MonsterDebugOff"))
	{
		DebugOff();
	}

	if (nullptr != PlayerActor && true == PlayerActor->IsDeath())
	{
		PlayerActor = nullptr;
	}

	MonsterFsm.Update(_DeltaTime);
	IsHit = false;

	if (true == IsHitEffectOn)
	{
		HitEffectProgress += _DeltaTime * HitEffectSpeed;

		if (0.5f >= HitEffectProgress)
		{
			Buffer.Color = float4::LerpClamp(float4(0, 0, 0, 1), float4(1, 1, 1, 1), HitEffectProgress * 2.0f);
		}
		else
		{
			Buffer.Color = float4::LerpClamp(float4(1, 1, 1, 1), float4(0, 0, 0, 1), (HitEffectProgress * 2.0f) - 1.0f);
		}
		
		if (1.0f <= HitEffectProgress)
		{
			IsHitEffectOn = false;
			HitEffectProgress = 0.0f;
		}
	}
}


void BaseMonster::SetViewDir(ActorViewDir _Dir, bool _Force /*= false*/)
{
	if (false == _Force && TurnCoolTime >= 0)
	{
		return;
	}

	Dir = _Dir;

	switch (_Dir)
	{
	case ActorViewDir::Left:
	{
		GetTransform()->SetLocalNegativeScaleX();

		LocalWalkColPos.x = -fabsf(LocalWalkColPos.x);
		LocalBackColPos.x = fabsf(LocalBackColPos.x);
		LocalWalkFallColPos.x = -fabsf(LocalWalkFallColPos.x);
		LocalFindColPos.x = -fabsf(LocalFindColPos.x);
		LocalChasingColPos.x = -fabsf(LocalChasingColPos.x);
	}
		break;
	case ActorViewDir::Right:
	{
		GetTransform()->SetLocalPositiveScaleX();

		LocalWalkColPos.x = fabsf(LocalWalkColPos.x);
		LocalBackColPos.x = -fabsf(LocalBackColPos.x);
		LocalWalkFallColPos.x = fabsf(LocalWalkFallColPos.x);
		LocalFindColPos.x = fabsf(LocalFindColPos.x);
		LocalChasingColPos.x = fabsf(LocalChasingColPos.x);
	}
		break;
	default:
		break;
	}

	WalkCol->GetTransform()->SetLocalPosition(LocalWalkColPos);
	BackCol->GetTransform()->SetLocalPosition(LocalBackColPos);
	WalkFallCol->GetTransform()->SetLocalPosition(LocalWalkFallColPos);
	FindCol->GetTransform()->SetLocalPosition(LocalFindColPos);
	ChasingCol->GetTransform()->SetLocalPosition(LocalChasingColPos);

	TurnCoolTime = 0.5f;
}


std::shared_ptr<class GameEngineCollision> BaseMonster::PlatformColCheck(const std::shared_ptr<class GameEngineCollision>& _Col, bool _IsHalf /*= false*/)
{
	std::shared_ptr<GameEngineCollision> ReslutCol = nullptr;

	ReslutCol = _Col->Collision(CollisionOrder::Platform_Normal, ColType::AABBBOX2D, ColType::AABBBOX2D);

	if (nullptr != ReslutCol)
	{
		return ReslutCol;
	}

	if (false == _IsHalf)
	{
		return ReslutCol;
	}

	ReslutCol = _Col->Collision(CollisionOrder::Platform_Half, ColType::AABBBOX2D, ColType::AABBBOX2D);

	if (nullptr != ReslutCol)
	{
		return ReslutCol;
	}

	return ReslutCol;
}

bool BaseMonster::Fall(float _DeltaTime)
{
	FallDir.y += _DeltaTime * ContentConst::Gravity_f;
	GetTransform()->AddLocalPosition(FallDir * _DeltaTime);

	std::shared_ptr<GameEngineCollision> ColPlatform = PlatformColCheck(GroundCol, true);

	if (nullptr != ColPlatform)
	{
		float4 CurPos = GetTransform()->GetWorldPosition();

		GameEngineTransform* ColTrans = ColPlatform->GetTransform();
		CurPos.y = ColTrans->GetWorldPosition().y + ColTrans->GetWorldScale().hy();

		GameEngineTransform* GroundTrans = GroundCol->GetTransform();
		CurPos.y -= GroundTrans->GetLocalPosition().y + GroundTrans->GetWorldScale().hy();

		GetTransform()->SetWorldPosition(CurPos);
		GetTransform()->SetLocalPosition(GetTransform()->GetLocalPosition());
		FallDir.y = 0;

		return false;
	}

	return true;
}

void BaseMonster::Turn(bool _Force /*= false*/)
{
	switch (Dir)
	{
	case ActorViewDir::Left:
		SetViewDir(ActorViewDir::Right, _Force);
		break;
	case ActorViewDir::Right:
		SetViewDir(ActorViewDir::Left, _Force);
		break;
	default:
		break;
	}
}

void BaseMonster::CreateColDebugRender()
{
	{
		std::shared_ptr<CollisionDebugRender> GroundDebugRender = GetLevel()->CreateActor<CollisionDebugRender>();
		GroundDebugRender->SetColor(CollisionDebugRender::DebugColor::Green);
		GroundDebugRender->SetTargetCollision(GroundCol);
		GroundDebugRender->GetTransform()->SetParent(GroundCol->GetTransform(), false);
		GroundDebugRender->GetTransform()->AddLocalPosition(float4(0, 0, -10));
	}

	{
		std::shared_ptr<CollisionDebugRender> WalkDebugRender = GetLevel()->CreateActor<CollisionDebugRender>();
		WalkDebugRender->SetColor(CollisionDebugRender::DebugColor::Green);
		WalkDebugRender->SetTargetCollision(WalkCol);
		WalkDebugRender->GetTransform()->SetParent(WalkCol->GetTransform(), false);
		WalkDebugRender->GetTransform()->AddLocalPosition(float4(0, 0, -10));
	}

	{
		std::shared_ptr<CollisionDebugRender> BodyDebugRender = GetLevel()->CreateActor<CollisionDebugRender>();
		BodyDebugRender->SetColor(CollisionDebugRender::DebugColor::Magenta);
		BodyDebugRender->SetTargetCollision(BodyCol);
		BodyDebugRender->GetTransform()->SetParent(BodyCol->GetTransform(), false);
		BodyDebugRender->GetTransform()->AddLocalPosition(float4(0, 0, -10));
	}

	{
		std::shared_ptr<CollisionDebugRender> FindDebugRender = GetLevel()->CreateActor<CollisionDebugRender>();
		FindDebugRender->SetColor(CollisionDebugRender::DebugColor::Black);
		FindDebugRender->SetTargetCollision(FindCol);
		FindDebugRender->GetTransform()->SetParent(FindCol->GetTransform(), false);
		FindDebugRender->GetTransform()->AddLocalPosition(float4(0, 0, -10));
	}

	{
		std::shared_ptr<CollisionDebugRender> ChasingDebugRender = GetLevel()->CreateActor<CollisionDebugRender>();
		ChasingDebugRender->SetColor(CollisionDebugRender::DebugColor::Red);
		ChasingDebugRender->SetTargetCollision(ChasingCol);
		ChasingDebugRender->GetTransform()->SetParent(ChasingCol->GetTransform(), false);
		ChasingDebugRender->GetTransform()->AddLocalPosition(float4(0, 0, -10));
	}
}

void BaseMonster::EffectLoadCheck()
{
	if (nullptr == GameEngineSprite::Find("FindPlayerSightEffect.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("Monster");
		Path.Move("Effect");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("FindPlayerSightEffect.png").GetFullPath(), 5, 3);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("MonsterDeathEffect.png").GetFullPath(), 3, 2);
	
		EffectManager::CreateMetaData("FindPlayer", { 
			.SpriteName = "FindPlayerSightEffect.png",
			.AnimStart = 0,
			.AnimEnd = 14,
			.AnimIter = 0.025f,
			.ScaleRatio = 2.0f});

		EffectManager::CreateMetaData("MonsterDeath", {
			.SpriteName = "MonsterDeathEffect.png",
			.AnimStart = 0,
			.AnimEnd = 5,
			.AnimIter = 0.04f,
			.ScaleRatio = 2.0f });

		Path.MoveParent();
		Path.Move("Particle");

		GameEngineTexture::Load(Path.GetPlusFileName("BaseHitParticle.png").GetFullPath());
	}
}

bool BaseMonster::HitCheck()
{
	if (true == IsHit)
	{
		HitEffect();

		if (false == IsSuperArmor && true == IsStiffen)
		{
			MonsterFsm.ChangeState("Hit");
			return true;
		}
	}

	return false;
}

void BaseMonster::MonsterDeath()
{
	Death();

	EffectManager::PlayEffect({
		.EffectName = "MonsterDeath",
		.Postion = GetTransform()->GetWorldPosition() + DeathEffectLocalPos });

	for (size_t i = 0; i < DeadPartNames.size(); i++)
	{
		std::shared_ptr<DeadPartParticle> DeadPart = GetLevel()->CreateActor<DeadPartParticle>();

		GameEngineTransform* PartTrans = DeadPart->GetTransform();

		GameEngineRandom& MainRand = GameEngineRandom::MainRandom;

		float4 Dir = float4::Up;
		Dir.RotaitonZDeg(MainRand.RandomFloat(-20, 20));
		DeadPart->Init(DeadPartNames[i], Dir, MainRand.RandomFloat(700.0f, 900.0f), 1.0f);
		PartTrans->SetWorldPosition(GetTransform()->GetWorldPosition() + DeathEffectLocalPos);

		PartTrans->SetWorldScale(PartTrans->GetWorldScale() * DeathPartScale);
	}

}

bool BaseMonster::Walk(float _DeltaTime)
{
	if (nullptr != WalkCol->Collision((int)CollisionOrder::Platform_Normal, ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		return false;
	}

	switch (Dir)
	{
	case ActorViewDir::Left:
		GetTransform()->AddLocalPosition(float4::Left * Data.MoveSpeed * _DeltaTime);
		break;
	case ActorViewDir::Right:
		GetTransform()->AddLocalPosition(float4::Right * Data.MoveSpeed * _DeltaTime);
		break;
	default:
		break;
	}
	
	return true;
}