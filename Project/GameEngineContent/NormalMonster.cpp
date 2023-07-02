#include "PrecompileHeader.h"
#include "NormalMonster.h"
#include <GameEngineCore/GameEngineLevel.h>

#include "HealthBar.h"
#include "Player.h"
#include "DeadPartParticle.h"

NormalMonster::NormalMonster()
{
}

NormalMonster::~NormalMonster()
{
}

void NormalMonster::HitMonster(float _Damage, ActorViewDir _HitDir, bool _IsStiffen, bool _IsPush, bool _IsMagicAttack, HitEffectType _Type, std::function<void()> _KillEvent /*= nullptr*/)
{
	BaseMonster::HitMonster(_Damage, _HitDir, _IsStiffen, _IsPush, _IsMagicAttack, _Type, _KillEvent);

	if (nullptr == PlayerActor)
	{
		std::shared_ptr<GameEngineCollision> ColPtr = HitFindCol->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D);

		if (nullptr != ColPtr)
		{
			PlayerActor = ColPtr->GetActor()->DynamicThis<GameEngineActor>();
		}
	}

	HealthBarActiveTime = 3.0f;
}

void NormalMonster::Stun(float _Time)
{
	BaseMonster::Stun(_Time);
	MonsterFsm.ChangeState("Idle");
}

void NormalMonster::Start()
{
	BaseMonster::Start();

	DeathEffectLocalPos = float4(0, 50, -5.0f);

	if (false == GameEngineInput::IsKey("MonsterDebugOn"))
	{
		GameEngineInput::CreateKey("MonsterDebugOn", VK_F3);
		GameEngineInput::CreateKey("MonsterDebugOff", VK_F4);
	}

	MonsterFsm.Init(this);
	MonsterFsm.AddFSM("Idle", &NormalMonster::Idle_Enter, &NormalMonster::Idle_Update, &NormalMonster::Idle_End);
	MonsterFsm.AddFSM("Walk", &NormalMonster::Walk_Enter, &NormalMonster::Walk_Update, &NormalMonster::Walk_End);
	MonsterFsm.AddFSM("Chasing", &NormalMonster::Chasing_Enter, &NormalMonster::Chasing_Update, &NormalMonster::Chasing_End);
	MonsterFsm.AddFSM("Attack", &NormalMonster::Attack_Enter, &NormalMonster::Attack_Update, &NormalMonster::Attack_End);
	MonsterFsm.AddFSM("Hit", &NormalMonster::Hit_Enter, &NormalMonster::Hit_Update, &NormalMonster::Hit_End);

	HitFindCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Unknown);
	HitFindCol->SetColType(ColType::AABBBOX2D);
	BodyCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Monster);
	BodyCol->SetColType(ColType::AABBBOX2D);
	FindCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Unknown);
	FindCol->SetColType(ColType::AABBBOX2D);
	ChasingCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Unknown);
	ChasingCol->SetColType(ColType::AABBBOX2D);
	WalkCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Unknown);
	WalkCol->SetColType(ColType::AABBBOX2D);
	BackCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Unknown);
	BackCol->SetColType(ColType::AABBBOX2D);
	GroundCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Unknown);
	GroundCol->SetColType(ColType::AABBBOX2D);
	WalkFallCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Unknown);
	WalkFallCol->SetColType(ColType::AABBBOX2D);

	HitFindCol->GetTransform()->SetLocalScale(float4(400, 300, 1));
		
	BattleActorRigidbody.SetMaxSpeed(300.0f);
	BattleActorRigidbody.SetFricCoeff(1000.0f);

	TextureLoad();
	LoadAnimation();
	AnimationAttackMetaDataLoad();
	SetColData();
	DeathPartLoad();

	AttackCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Unknown);
	AttackCol->SetColType(ColType::AABBBOX2D);

	AttackCheck.SetCol(AttackCol, (UINT)CollisionOrder::Player);
	AttackCheck.SetRender(Render);
	AttackCheck.SetEvent([this](std::shared_ptr<BaseContentActor> _Ptr, const AttackColMetaData& _Data)
		{
			std::shared_ptr <Player> CastPtr = std::static_pointer_cast<Player>(_Ptr);

			if (nullptr == CastPtr)
			{
				MsgAssert_Rtti<NormalMonster>(" - 플레이어만 Player Col Order를 가질 수 있습니다.");
				return;
			}

			EffectManager::PlayEffect({
				.EffectName = "HitNormal",
				.Position = CastPtr->GetTransform()->GetWorldPosition() + float4(0, 40, 0),
				.AddSetZ = -10.0f });

			switch (Dir)
			{
			case ActorViewDir::Left:
				CastPtr->HitPlayer(Data.Attack, float4(-250, 400) * AttakPushRatio);
				break;
			case ActorViewDir::Right:
				CastPtr->HitPlayer(Data.Attack, float4(250, 400) * AttakPushRatio);
				break;
			default:
				break;
			}
		});

	AttackCheck.SetColData(AnimColMeta_Attack);
	MonsterFsm.ChangeState("Idle");

	HealthBarPtr = GetLevel()->CreateActor<HealthBar>();
	HealthBarPtr->GetTransform()->SetParent(GetTransform());
	HealthBarPtr->GetTransform()->SetLocalPosition(float4(0, -15, -10));
	HealthBarPtr->SetTexture("EnemyHpFrame.png", "EnemyHpBar.png", "EnemySubBar.png", HealthBarScale);
	HealthBarPtr->Off();

	IsAppear = true;

	Render->Off();
	BodyCol->Off();
}

void NormalMonster::Update(float _DeltaTime)
{
	if (HP <= 0.0f)
	{
		MonsterDeath();
		return;
	}

	AttackWaitTime += _DeltaTime;
	TurnCoolTime -= _DeltaTime;

	BattleActorRigidbody.UpdateForce(_DeltaTime);

	if (nullptr == ContentFunc::PlatformColCheck(WalkCol) && nullptr == ContentFunc::PlatformColCheck(BackCol))
	{
		GetTransform()->AddLocalPosition(BattleActorRigidbody.GetVelocity() * _DeltaTime);
	}

	if (true == GameEngineInput::IsDown("MonsterDebugOn"))
	{
		CreateColDebugRender(true);
	}
	else if (true == GameEngineInput::IsDown("MonsterDebugOff"))
	{
		CreateColDebugRender(false);
	}

	if (nullptr != PlayerActor && true == PlayerActor->IsDeath())
	{
		PlayerActor = nullptr;
	}

	MonsterFsm.Update(_DeltaTime);

	BaseMonster::Update(_DeltaTime);

	if (true == IsAppear)
	{
		if (nullptr == AppearEffect)
		{
			AppearEffect = EffectManager::PlayEffect({
				.EffectName = "MonsterAppear",
				.Position = GetTransform()->GetWorldPosition() + float4(0, 50, 0) });
		}

		if (5 == AppearEffect->GetCurrentFrame())
		{
			AppearEffect = nullptr;
			IsAppear = false;
			Render->On();
			BodyCol->On();
		}

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

	HealthBarPtr->UpdateBar(HP / Data.HP, _DeltaTime);  
}

void NormalMonster::SetViewDir(ActorViewDir _Dir, bool _Force /*= false*/)
{
	if (false == _Force && TurnCoolTime >= 0)
	{
		return;
	}

	BaseMonster::SetViewDir(_Dir, _Force);

	TurnCoolTime = 0.5f;
}

bool NormalMonster::Fall(float _DeltaTime)
{
	FallDir.y += _DeltaTime * ContentConst::Gravity_f;
	GetTransform()->AddLocalPosition(FallDir * _DeltaTime);

	std::shared_ptr<GameEngineCollision> ColPlatform = ContentFunc::PlatformColCheck(GroundCol, true);

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

void NormalMonster::Turn(bool _Force /*= false*/)
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

void NormalMonster::CreateColDebugRender(bool _IsActive)
{
	if (true == _IsActive)
	{
		HitFindCol->DebugOn();
		BodyCol->DebugOn();
		WalkCol->DebugOn();
		BackCol->DebugOn();
		WalkFallCol->DebugOn();
		GroundCol->DebugOn();
		FindCol->DebugOn();
		ChasingCol->DebugOn();
		AttackCol->DebugOn();
	}
	else
	{
		HitFindCol->DebugOff();
		BodyCol->DebugOff();
		WalkCol->DebugOff();
		BackCol->DebugOff();
		WalkFallCol->DebugOff();
		GroundCol->DebugOff();
		FindCol->DebugOff();
		ChasingCol->DebugOff();
		AttackCol->DebugOff();
	}
}

bool NormalMonster::HitCheck()
{
	if (true == IsHit)
	{
		if (true == IsPush)
		{
			HitPush();
		}

		if (false == IsSuperArmor && true == IsStiffen)
		{
			MonsterFsm.ChangeState("Hit");
			return true;
		}
	}

	return false;
}

void NormalMonster::MonsterDeath()
{
	Death();

	EffectManager::PlayEffect({
		.EffectName = "MonsterDeath",
		.Position = GetTransform()->GetWorldPosition() + DeathEffectLocalPos });

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

bool NormalMonster::Walk(float _DeltaTime)
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