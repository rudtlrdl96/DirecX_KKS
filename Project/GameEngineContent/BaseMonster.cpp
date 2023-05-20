#include "PrecompileHeader.h"
#include "BaseMonster.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "CollisionDebugRender.h"

BaseMonster::BaseMonster()
{
}

BaseMonster::~BaseMonster()
{
}

void BaseMonster::Start()
{
	if (false == GameEngineInput::IsKey("MonsterDebugOn"))
	{
		GameEngineInput::CreateKey("MonsterDebugOn", VK_F3);
		GameEngineInput::CreateKey("MonsterDebugOff", VK_F4);
	}

	Render = CreateComponent<ContentSpriteRenderer>();
	Render->PipeSetting("2DTexture_ColorLight");
	Render->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	Render->GetTransform()->SetLocalPosition(float4::Zero);
	Render->SetScaleRatio(2.0f);

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
	GroundCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Unknown);
	WalkFallCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::Unknown);


	DataLoad();
	TextureLoad();
	LoadAnimation();
	AnimationAttackMetaDataLoad();
	SetColData();
	EffectLoadCheck();

	MonsterFsm.ChangeState("Idle");
}

void BaseMonster::Update(float _DeltaTime)
{
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

	TurnCoolTime -= _DeltaTime;

	MonsterFsm.Update(_DeltaTime);
	IsHit = false;
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
		LocalWalkFallColPos.x = -fabsf(LocalWalkFallColPos.x);
		LocalFindColPos.x = -fabsf(LocalFindColPos.x);
		LocalChasingColPos.x = -fabsf(LocalChasingColPos.x);

		WalkCol->GetTransform()->SetLocalPosition(LocalWalkColPos);
		WalkFallCol->GetTransform()->SetLocalPosition(LocalWalkFallColPos);
		FindCol->GetTransform()->SetLocalPosition(LocalFindColPos);
		ChasingCol->GetTransform()->SetLocalPosition(LocalChasingColPos);
	}
		break;
	case ActorViewDir::Right:
	{
		GetTransform()->SetLocalPositiveScaleX();

		LocalWalkColPos.x = fabsf(LocalWalkColPos.x);
		LocalWalkFallColPos.x = fabsf(LocalWalkFallColPos.x);
		LocalFindColPos.x = fabsf(LocalFindColPos.x);
		LocalChasingColPos.x = fabsf(LocalChasingColPos.x);

		WalkCol->GetTransform()->SetLocalPosition(LocalWalkColPos);
		WalkFallCol->GetTransform()->SetLocalPosition(LocalWalkFallColPos);
		FindCol->GetTransform()->SetLocalPosition(LocalFindColPos);
		ChasingCol->GetTransform()->SetLocalPosition(LocalChasingColPos);
	}
		break;
	default:
		break;
	}

	TurnCoolTime = 0.5f;
	HitRigidbody.SetMaxSpeed(300.0f);
	HitRigidbody.SetFricCoeff(1000.0f);
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
	
		EffectManager::CreateMetaData("FindPlayer", { 
			.SpriteName = "FindPlayerSightEffect.png",
			.AnimStart = 0,
			.AnimEnd = 14,
			.AnimIter = 0.025f,
			.ScaleRatio = 2.0f});

		Path.MoveParent();
		Path.Move("Particle");

		GameEngineTexture::Load(Path.GetPlusFileName("BaseHitParticle.png").GetFullPath());
	}
}

void BaseMonster::HitStiffen()
{
	GameEngineRandom& Rand = GameEngineRandom::MainRandom;

	switch (HitDir)
	{
	case ActorViewDir::Left:
		HitRigidbody.SetVelocity(float4::Left * 300.0f);

		EffectManager::PlayEffect({ .EffectName = "HitSkul",
			.Postion = GetTransform()->GetLocalPosition() + float4(Rand.RandomFloat(-50, 40), Rand.RandomFloat(25, 70), 0),
			.Scale = 0.6f,
			.FlipX = true });
		break;
	case ActorViewDir::Right:
		HitRigidbody.SetVelocity(float4::Right * 300.0f);

		EffectManager::PlayEffect({ .EffectName = "HitSkul",
			.Postion = GetTransform()->GetLocalPosition() + float4(Rand.RandomFloat(40, 50), Rand.RandomFloat(25, 70), 0),
			.Scale = 0.6f,
			.FlipX = false });
		break;
	default:
		break;
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