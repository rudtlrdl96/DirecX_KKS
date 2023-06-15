#include "PrecompileHeader.h"
#include "VeteranHero.h"
#include "HealthBar.h"
#include "VeteranHero_HealthBar.h"
#include "MonsterDeadBodyActor.h"

VeteranHero::VeteranHero()
{
}

VeteranHero::~VeteranHero()
{
}

void VeteranHero::Destroy()
{
	ContentLevel* LevelPtr = GetContentLevel();

	LevelPtr->RemoveEvent("VeteranHero_Script02_End", GetActorCode());
	LevelPtr->RemoveEvent("VeteranHero_Script01_End", GetActorCode());
	LevelPtr->RemoveEvent("VeteranHero_Script00_End", GetActorCode());
}

void VeteranHero::HitMonster(float _Damage, ActorViewDir _HitDir, bool _IsStiffen, bool _IsPush)
{
	BossMonster::HitMonster(_Damage, _HitDir, _IsStiffen, _IsPush);

	HealthBarActiveTime = 3.0f;
}

void VeteranHero::Start()
{
	BossMonster::Start();
	SetViewDir(ActorViewDir::Right);
	BossRigidbody.SetGravity(ContentConst::Gravity_f - 1000.0f);
	BossRigidbody.SetActiveGravity(true);
	BossRigidbody.SetFricCoeff(3000.0f);
	DashPower = 1450.0f;
	BackDashPower = 1050.0f;

	PatternWaitTime = 1.5f;

	PauseTimes["DeathIntro"][0] = 0.3f;

	HealthBarPtr = GetLevel()->CreateActor<HealthBar>();
	HealthBarPtr->GetTransform()->SetParent(GetTransform());
	HealthBarPtr->GetTransform()->SetLocalPosition(float4(0, -15, -10));
	HealthBarPtr->SetTexture("EnemyHpFrame.png", "EnemyHpBar.png", "EnemySubBar.png", HealthBarScale);
	HealthBarPtr->Off();

	HeroHealthBar = GetLevel()->CreateActor<VeteranHero_HealthBar>();
	HeroHealthBar->GetTransform()->SetLocalPosition(float4(0, 290));
	HeroHealthBar->Off();

	BodyCol->GetTransform()->SetLocalPosition(float4(0, 60, 1));
	BodyCol->GetTransform()->SetLocalScale(float4(80, 120, 1));

	WalkCol->GetTransform()->SetLocalPosition(float4(47, 65, 1));
	WalkCol->GetTransform()->SetLocalScale(float4(7, 120, 1));

	BackCol->GetTransform()->SetLocalPosition(float4(-47, 65, 1));
	BackCol->GetTransform()->SetLocalScale(float4(7, 120, 1));

	GroundCol->GetTransform()->SetLocalPosition(float4(0, 3.0f, 1));
	GroundCol->GetTransform()->SetLocalScale(float4(76, 5.0f, 1));

	EventCol = CreateComponent<GameEngineCollision>();
	EventCol->GetTransform()->SetWorldPosition(float4(1248, 564, 1));
	EventCol->GetTransform()->SetLocalScale(float4(1220, 640, 1));

	AttackCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::MonsterAttack);
	AttackCol->SetColType(ColType::AABBBOX2D);

	ExplosionCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::MonsterAttack);
	ExplosionCol->GetTransform()->SetLocalPosition(float4(0, 5, 0));
	ExplosionCol->GetTransform()->SetLocalScale(float4(420, 420, 1));

	ExplosionChargeCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::MonsterAttack);
	ExplosionChargeCol->GetTransform()->SetLocalPosition(float4(0, 0, 0));
	ExplosionChargeCol->GetTransform()->SetLocalScale(float4(1, 1, 1));


	SwordRender = CreateComponent<ContentSpriteRenderer>();
	SwordRender->PipeSetting("2DTexture_Color");
	SwordRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", SwordBuffer);
	SwordRender->SetScaleToTexture("AdventurerHero_Sword.png");
	float4 TextureSclae = SwordRender->GetTransform()->GetLocalScale();
	SwordRender->GetTransform()->SetLocalScale(TextureSclae * 2.0f);
	SwordRender->Off();


	Battle_Platform_Left = CreateComponent<GameEngineCollision>((int)CollisionOrder::Platform_Normal);
	Battle_Platform_Left->SetColType(ColType::AABBBOX2D);
	Battle_Platform_Left->GetTransform()->SetWorldPosition(float4(705, 565, 1));
	Battle_Platform_Left->GetTransform()->SetWorldScale(float4(64, 640, 1));
	Battle_Platform_Left->GetTransform()->SetWorldRotation(float4::Zero);
	Battle_Platform_Left->Off();

	Battle_Platform_Right = CreateComponent<GameEngineCollision>((int)CollisionOrder::Platform_Normal);
	Battle_Platform_Right->SetColType(ColType::AABBBOX2D);
	Battle_Platform_Right->GetTransform()->SetWorldPosition(float4(2050, 565, 1));
	Battle_Platform_Right->GetTransform()->SetWorldScale(float4(64, 640, 1));
	Battle_Platform_Right->GetTransform()->SetWorldRotation(float4::Zero);
	Battle_Platform_Right->Off();

	UltimateLight = CreateComponent<ContentSpriteRenderer>();
	UltimateLight->PipeSetting("2DTexture_Color");
	UltimateLight->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", UltimateLightBuffer);
	UltimateLight->SetTexture("FadeImage.png");
	UltimateLight->GetTransform()->SetWorldPosition(float4(0, 0, -4.5f));
	UltimateLight->GetTransform()->SetLocalScale(float4(100000, 100000, 1));
	UltimateLight->Off();

	UltimateFade = CreateComponent<ContentSpriteRenderer>();
	UltimateFade->PipeSetting("2DTexture_Color");
	UltimateFade->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", UltimateFadeBuffer);
	UltimateFade->SetTexture("FadeImage.png");
	UltimateFade->GetTransform()->SetWorldPosition(float4(0, 0, -999.0f));
	UltimateFade->GetTransform()->SetLocalScale(float4(100000, 100000, 1));
	UltimateFade->Off();

	AttackCheck.SetCol(AttackCol, (UINT)CollisionOrder::Player);
	AttackCheck.SetRender(Render);

	SwordRigidbody.SetMaxSpeed(2000.0f);
	SwordRigidbody.SetFricCoeff(500.0f);

	ContentLevel* LevelPtr = GetContentLevel();
	//

	LevelPtr->AddEvent("VeteranHero_Script02_End", GetActorCode(), [this]()
		{
			IsIntro = false;
			HeroHealthBar->On();
		});

	LevelPtr->AddEvent("VeteranHero_Script01_End", GetActorCode(), [this]()
		{
			IsBehaviorLoop = true;
			PlayBehaviorAnim = "Intro_Throwing";
			BossFsm.ChangeState("Behavior");

			SwordRigidbody.SetActiveGravity(true);
			SwordRigidbody.SetVelocity(float4(0, 700, 0));
			SwordRigidbody.SetGravity(-900.0f);

			SwordRender->GetTransform()->SetLocalRotation(float4(0, 0, 180));
			SwordRender->GetTransform()->SetLocalPosition(float4(20, 170, 0));
			SwordRender->On();
			IsSwordThrowing = true;
		});

	LevelPtr->AddEvent("VeteranHero_Script00_End", GetActorCode(), [this]()
		{
			IsIntroJump = true;
			PlayAnimation("Intro_LandReady");

			GetTransform()->SetWorldPosition(float4(1970, 800));
			BossRigidbody.SetVelocity(float4(-1000, -500, 0));
			BossRigidbody.SetGravity(ContentConst::Gravity_f - 1000.0f);
			IsGroundUp = false;

			SetViewDir(ActorViewDir::Left);
		});

	GetTransform()->AddLocalPosition(float4(-100, -200));
	IsIntro = false;
	IsPlayerEnter = true;
	Battle_Platform_Left->On();
	Battle_Platform_Right->On();
}

void VeteranHero::Update(float _DeltaTime)
{
	if (true == IsSwordThrowing)
	{
		SwordRigidbody.UpdateForce(_DeltaTime);

		float4 Vel = SwordRigidbody.GetVelocity();
		float4 CurFrameVel = Vel * _DeltaTime;

		SwordRender->GetTransform()->AddLocalPosition(CurFrameVel);
		SwordRender->GetTransform()->AddLocalRotation(float4(0, 0, _DeltaTime * 1200.0f));

		if (170.0f > SwordRender->GetTransform()->GetLocalPosition().y)
		{
			SwordRender->Off();
			SwordRigidbody.SetActiveGravity(false);
			SwordRigidbody.SetVelocity(float4::Zero);
			IsSwordThrowing = false;

			IsBehaviorLoop = false;
			PlayBehaviorAnim = "Intro_LandEnd";
			BossFsm.ChangeState("Behavior");

			BehaviorEndCallback = [this]()
			{
				GetContentLevel()->CallEvent("VeteranHero_Script02");
				PlayAnimation("Intro_LandEndWait");
			};
		}
	}

	if (true == IsIntroJump)
	{
		BossRigidbody.UpdateForce(_DeltaTime);
		float4 IntroVel =  BossRigidbody.GetVelocity();

		if (true == IsGroundUp)
		{
			BossRigidbody.SetVelocity(float4::Zero);

			IsBehaviorLoop = false;
			PlayBehaviorAnim = "Intro_Land";
			BossFsm.ChangeState("Behavior");

			BehaviorEndCallback = [this]()
			{
				GetContentLevel()->CallEvent("VeteranHero_Script01");
				PlayAnimation("Intro_Land", true, 26);
			};

			IsGroundUp = false;
			IsIntroJump = false;
		}

		GetTransform()->AddLocalPosition(IntroVel * _DeltaTime);
		BossMonster::Update(_DeltaTime);
		return;
	}
	BossMonster::Update(_DeltaTime);
	if (true == IsUltimateLightOn)
	{
		UltimateLightProgress += _DeltaTime * 2.0f;

		UltimateLightBuffer.Color = float4::LerpClamp(
			float4(0, 0, 0, 0), float4(0, 0, 0, 0.6f), UltimateLightProgress);

		if (1.0f <= UltimateLightProgress)
		{
			IsUltimateLightOn = false;
		}
	}

	if (true == IsUltimateLightOff)
	{
		UltimateLightProgress += _DeltaTime * 2.0f;

		UltimateLightBuffer.Color = float4::LerpClamp(
			float4(0, 0, 0, 0.6f), float4(0, 0, 0, 0), UltimateLightProgress);

		if (1.0f <= UltimateLightProgress)
		{
			IsUltimateLightOff = false;
			UltimateLight->Off();
		}
	}

	if (true == IsUltimateFadeOn)
	{
		UltimateFadeProgress += _DeltaTime * 1.5f;

		float Progress = UltimateFadeProgress - 0.2f;

		UltimateFadeBuffer.Color = float4::LerpClamp(
			float4(1, 1, 1, 0.6f), float4(1, 1, 1, 0), Progress);

		if (1.0f <= Progress)
		{
			IsUltimateFadeOn = false;
			UltimateFade->Off();
		}
	}

	HealthBarPtr->UpdateBar(HP / Data.HP, _DeltaTime);

	if (nullptr != HeroHealthBar)
	{
		HeroHealthBar->UpdateBar(HP / Data.HP, _DeltaTime);
	}

	if (0.0f >= HP)
	{
		if (false == IsDeathIntro)
		{
			if (true == UltimateLight->IsUpdate())
			{
				UltimateLightOff();
			}

			IsDeathIntro = true;
			HealthBarPtr->Off();
			HeroHealthBar->Death();
			HeroHealthBar = nullptr;

			PlayAnimation("DeathIntro", false);
		}

		if (true == Render->IsAnimationEnd())
		{
			GetContentLevel()->CallEvent("MinimapOn");
			GetContentLevel()->CallEvent("RookieHero_Death");
			Death();

			std::shared_ptr<MonsterDeadBodyActor> DeadBody = GetLevel()->CreateActor<MonsterDeadBodyActor>();

			DeadBody->SetTexture("RookieHero_DeadBody.png", 2.0f);
			DeadBody->GetTransform()->SetWorldPosition(GetTransform()->GetWorldPosition() + float4(0, -2, -1.0f));

			if (ActorViewDir::Left == Dir)
			{
				DeadBody->GetTransform()->SetLocalNegativeScaleX();
			}
		}

		return;
	}

	UltimateTime += _DeltaTime;

	if (false == IsPlayerEnter)
	{
		std::shared_ptr<GameEngineCollision> PlayerCol =
			EventCol->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D);

		if (nullptr != PlayerCol)
		{
			GetContentLevel()->CallEvent("MinimapOff");
			GetContentLevel()->CallEvent("VeteranHero_Intro");

			IsPlayerEnter = true;

			Battle_Platform_Left->On();
			Battle_Platform_Right->On();
		}
	}


	if (nullptr != ExplosionEffect && ExplosionEffect->IsDeath())
	{
		ExplosionEffect = nullptr;
	}

	if (nullptr != UltimateSmokeEffect && UltimateSmokeEffect->IsDeath())
	{
		UltimateSmokeEffect = nullptr;
	}

	if (nullptr != UltimateAuraEffect && UltimateAuraEffect->IsDeath())
	{
		UltimateAuraEffect = nullptr;
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
}

void VeteranHero::DataLoad()
{
	Data = ContentDatabase<MonsterData, LevelArea>::GetData(190); // 180 = 각성 용사
}

void VeteranHero::CreateAnimation()
{
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Data");
		Path.Move("3_ForestOfHarmony");
		Path.Move("Boss");

		AttackA_Data = ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("RookieHero_AttackA").GetFullPath());
		AttackB_Data = ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("RookieHero_AttackB").GetFullPath());
		AttackD_Data = ContentFunc::LoadAnimAttackMetaData(Path.GetPlusFileName("RookieHero_AttackD").GetFullPath());

		Render->CreateAnimation({
			.AnimationName = AttackA_Data.GetAnimationName().data(),
			.SpriteName = AttackA_Data.GetSpriteName().data(),
			.Start = AttackA_Data.GetStartFrame(),
			.End = AttackA_Data.GetEndFrame(),
			.FrameInter = 0.11f,
			.Loop = false,
			.ScaleToTexture = true });

		Render->CreateAnimation({
			.AnimationName = AttackB_Data.GetAnimationName().data(),
			.SpriteName = AttackB_Data.GetSpriteName().data(),
			.Start = AttackB_Data.GetStartFrame(),
			.End = AttackB_Data.GetEndFrame(),
			.FrameInter = 0.11f,
			.Loop = false,
			.ScaleToTexture = true });

		Render->CreateAnimation({
			.AnimationName = AttackD_Data.GetAnimationName().data(),
			.SpriteName = AttackD_Data.GetSpriteName().data(),
			.Start = AttackD_Data.GetStartFrame(),
			.End = AttackD_Data.GetEndFrame(),
			.FrameInter = 0.11f,
			.Loop = false,
			.ScaleToTexture = true });
	}

	Render->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "RookieHero_Idle.png", .Loop = true, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Intro_ComboA", .SpriteName = "RookieHero_Intro_ComboA.png",
		.Start = 0, .End = 43, .Loop = true, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Intro_ComboB", .SpriteName = "RookieHero_Intro_ComboB.png",
		.Start = 0, .End = 25, .Loop = false, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Intro_Yeah", .SpriteName = "RookieHero_Yeah.png", .Loop = true, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Intro_lol", .SpriteName = "RookieHero_lol.png", .Loop = true, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Intro_lol_End", .SpriteName = "RookieHero_lol_End.png", .Loop = true, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Intro_Who", .SpriteName = "RookieHero_Who.png", .Loop = false, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Intro_LandReady", .SpriteName = "RookieHero_LandingReady.png", .FrameInter = 0.05f, .Loop = true, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Intro_Land", .SpriteName = "RookieHero_LandingIntro.png", .FrameInter = 0.035f, .Loop = false, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Intro_LandEnd", .SpriteName = "RookieHero_LandingEnd.png", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Intro_LandEndWait", .SpriteName = "RookieHero_LandingEndWait.png", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Intro_Throwing", .SpriteName = "RookieHero_Throwing.png", .FrameInter = 0.05f, .Loop = false, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Potion", .SpriteName = "RookieHero_Potion.png", .Loop = true, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Hit", .SpriteName = "RookieHero_Hit.png", .Loop = false, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Dash", .SpriteName = "RookieHero_Dash.png", .Loop = true, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "BackDash", .SpriteName = "RookieHero_BackDash.png", .Loop = true, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Groggy", .SpriteName = "RookieHero_Groggy.png",.FrameInter = 0.15f, .Loop = true, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "EnergyBallReady", .SpriteName = "RookieHero_EnergyBallReady.png", .FrameInter = 0.06666f, .Loop = false, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "EnergyBall", .SpriteName = "RookieHero_EnergyBall.png", .Loop = false, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "ExplosionReady", .SpriteName = "RookieHero_ExplosionReady.png", .Loop = false, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Explosion", .SpriteName = "RookieHero_ExplosionLoop.png", .Loop = true, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "AttackA_Ready", .SpriteName = "RookieHero_AttackAReady.png", .Loop = false, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "AttackC", .SpriteName = "RookieHero_AttackC.png", .Loop = true, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "AttackE", .SpriteName = "RookieHero_AttackE.png", .Loop = true, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "SwordEnergyReady", .SpriteName = "RookieHero_SwordEnergyReady.png", .Loop = true, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "SwordEnergy", .SpriteName = "RookieHero_SwordEnergy.png", .Loop = true, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "DeathIntro", .SpriteName = "RookieHero_DeadIntro.png", .Loop = true, .ScaleToTexture = true });
}

void VeteranHero::SelectPattern()
{
	Cur_Pattern_Enter = std::bind(&VeteranHero::Explosion_Enter, this);
	Cur_Pattern_Update = std::bind(&VeteranHero::Explosion_Update, this, std::placeholders::_1);
	Cur_Pattern_End = std::bind(&VeteranHero::Explosion_End, this);
	AttackDistance = 230.0f;

	return;

	GameEngineRandom& Rand = GameEngineRandom::MainRandom;

	float CurHpRatio = HP / Data.HP;

	// Ultimate
	if (0.5f >= CurHpRatio && 0.0f <= UltimateTime)
	{
		Cur_Pattern_Enter = std::bind(&VeteranHero::Ultimate_Enter, this);
		Cur_Pattern_Update = std::bind(&VeteranHero::Ultimate_Update, this, std::placeholders::_1);
		Cur_Pattern_End = std::bind(&VeteranHero::Ultimate_End, this);

		AttackDistance = 600.0f;
		UltimateTime = -30.0f;
		return;
	}

	switch (Rand.RandomInt(0, 3))
	{
	case 0: // ComboAttack
	{
		Cur_Pattern_Enter = std::bind(&VeteranHero::ComboAttack_Enter, this);
		Cur_Pattern_Update = std::bind(&VeteranHero::ComboAttack_Update, this, std::placeholders::_1);
		Cur_Pattern_End = std::bind(&VeteranHero::ComboAttack_End, this);
		AttackDistance = 400.0f;
	}
	break;
	case 1: // EnergyBall
	{
		Cur_Pattern_Enter = std::bind(&VeteranHero::EnergyBall_Enter, this);
		Cur_Pattern_Update = std::bind(&VeteranHero::EnergyBall_Update, this, std::placeholders::_1);
		Cur_Pattern_End = std::bind(&VeteranHero::EnergyBall_End, this);
		AttackDistance = 1000.0f;
	}
	break;
	case 2: // Explosion
	{
		Cur_Pattern_Enter = std::bind(&VeteranHero::Explosion_Enter, this);
		Cur_Pattern_Update = std::bind(&VeteranHero::Explosion_Update, this, std::placeholders::_1);
		Cur_Pattern_End = std::bind(&VeteranHero::Explosion_End, this);
		AttackDistance = 230.0f;
	}
	break;
	default:
		MsgAssert_Rtti<VeteranHero>(" - 존재하지 않는 패턴으로 설정하려 했습니다");
		break;
	}

	// 신규 패턴 -> 돌진 공격, 검기 웨이브, 내려찍기, 랜딩어택
	// 발악 패턴 -> 신규 궁극기

	// 변경 패턴
	// 에너지볼 : 에너지볼 이펙트 변경 에너지볼의 속도, 추적능력변경, 3개 동시에 발사 [완료]
	// 콤보어택 : 마지막 공격이 검기 발사 [완료]

	// 필살기 : 더 이상 그로기상태가 없음, 즉시발사, 연기 후속타
	// 폭발 : 이펙트 변경, 차징시 지속 데미지

}


void VeteranHero::UltimateLightOn()
{
	IsUltimateLightOn = true;
	IsUltimateLightOff = false;
	UltimateLightProgress = 0.0f;

	UltimateLight->On();
	UltimateLightBuffer.Color = float4(0.0f, 0.0f, 0.0f, 0.0f);
}


void VeteranHero::UltimateLightOff()
{
	IsUltimateLightOn = false;
	IsUltimateLightOff = true;
	UltimateLightProgress = 0.0f;

	UltimateLight->On();
	UltimateLightBuffer.Color = float4(0.0f, 0.0f, 0.0f, 0.6f);
}


void VeteranHero::UltimateFadeOn()
{
	IsUltimateFadeOn = true;
	UltimateFadeProgress = 0.0f;

	UltimateFade->On();
	UltimateFadeBuffer.Color = float4(1.0f, 1.0f, 1.0f, 0.6f);
}