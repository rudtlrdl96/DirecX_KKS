#include "PrecompileHeader.h"
#include "RookieHero.h"
#include "HealthBar.h"
#include "RookieHero_HealthBar.h"
#include "MonsterDeadBodyActor.h"
#include "ContentLevel.h"
#include "ResultInfo.h"

RookieHero::RookieHero()
{
}

RookieHero::~RookieHero()
{
}

void RookieHero::Destroy()
{
	ContentLevel* LevelPtr = GetContentLevel();

	LevelPtr->RemoveEvent("RookieHero_IntroComboA", GetActorCode());
	LevelPtr->RemoveEvent("RookieHero_IntroComboB", GetActorCode());
	LevelPtr->RemoveEvent("RookieHero_IntroYeah", GetActorCode());
	LevelPtr->RemoveEvent("RookieHero_Introlol", GetActorCode());
	LevelPtr->RemoveEvent("RookieHero_Introlol_End", GetActorCode());
	LevelPtr->RemoveEvent("RookieHero_IntroWho", GetActorCode());
	LevelPtr->RemoveEvent("RookieHero_IntroPotion", GetActorCode());
	LevelPtr->RemoveEvent("RookieHero_Script00_End", GetActorCode());

	if (false == IsCustomSoundEnd)
	{
		LevelPtr->StopCustomBgm();
		GetContentLevel()->PlayBaseBGM();
	}
}

void RookieHero::HitMonster(float _Damage, float _CriDamage, ActorViewDir _HitDir, bool _IsStiffen, bool _IsPush, bool _IsMagicAttack, bool _IsCritical, HitEffectType _Type, std::function<void()> _KillEvent /*= nullptr*/)
{
	BossMonster::HitMonster(_Damage, _CriDamage, _HitDir, _IsStiffen, _IsPush, _IsMagicAttack, _IsCritical, _Type, _KillEvent);

	HealthBarActiveTime = 3.0f;
}

void RookieHero::Start()
{
	BossMonster::Start();
	SetViewDir(ActorViewDir::Right);
	BossRigidbody.SetFricCoeff(3000.0f);
	DashPower = 1450.0f;
	BackDashPower = 1050.0f;

	PatternWaitTime = 1.5f;

	PauseTimes["DeathIntro"][0] = 0.3f;

	BubblePivot = float4(0, 150, -100);

	HealthBarPtr = GetLevel()->CreateActor<HealthBar>();
	HealthBarPtr->GetTransform()->SetParent(GetTransform());
	HealthBarPtr->GetTransform()->SetLocalPosition(float4(0, -15, -10));
	HealthBarPtr->SetTexture("EnemyHpFrame.png", "EnemyHpBar.png", "EnemySubBar.png", HealthBarScale);
	HealthBarPtr->Off();

	HeroHealthBar = GetLevel()->CreateActor<RookieHero_HealthBar>();
	HeroHealthBar->GetTransform()->SetLocalPosition(float4(500, 300));
	HeroHealthBar->Off();

	BodyCol->GetTransform()->SetLocalPosition(float4(0, 60, 1));
	BodyCol->GetTransform()->SetLocalScale(float4(80, 120, 1));

	WalkCol->GetTransform()->SetLocalPosition(float4(47, 65, 1));
	WalkCol->GetTransform()->SetLocalScale(float4(7, 120, 1));

	BackCol->GetTransform()->SetLocalPosition(float4(-47, 65, 1));
	BackCol->GetTransform()->SetLocalScale(float4(7, 120, 1));

	GroundCol->GetTransform()->SetLocalPosition(float4(0, 3.0f, 1));
	GroundCol->GetTransform()->SetLocalScale(float4(20, 5.0f, 1));

	EventCol = CreateComponent<GameEngineCollision>();
	EventCol->GetTransform()->SetWorldPosition(float4(1888, 564, 1));
	EventCol->GetTransform()->SetLocalScale(float4(1220, 640, 1));
	EventCol->SetColType(ColType::AABBBOX2D);

	AttackCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::MonsterAttack);
	AttackCol->SetColType(ColType::AABBBOX2D);

	ExplosionCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::MonsterAttack);
	ExplosionCol->GetTransform()->SetLocalPosition(float4(0, 5, 0));
	ExplosionCol->GetTransform()->SetLocalScale(float4(325, 325, 1));

	Battle_Platform_Left = CreateComponent<GameEngineCollision>((int)CollisionOrder::Platform_Normal);
	Battle_Platform_Left->SetColType(ColType::AABBBOX2D);
	Battle_Platform_Left->GetTransform()->SetWorldPosition(float4(1216, 564, 1));
	Battle_Platform_Left->GetTransform()->SetWorldScale(float4(64, 640, 1));
	Battle_Platform_Left->GetTransform()->SetWorldRotation(float4::Zero);
	Battle_Platform_Left->Off();

	Battle_Platform_Right = CreateComponent<GameEngineCollision>((int)CollisionOrder::Platform_Normal);
	Battle_Platform_Right->SetColType(ColType::AABBBOX2D);
	Battle_Platform_Right->GetTransform()->SetWorldPosition(float4(2562, 564, 1));
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
	UltimateFade->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", UltimateColorBuffer);
	UltimateFade->SetTexture("FadeImage.png");
	UltimateFade->GetTransform()->SetWorldPosition(float4(0, 0, -999.0f));
	UltimateFade->GetTransform()->SetLocalScale(float4(100000, 100000, 1));
	UltimateFade->Off();

	AttackCheck.SetCol(AttackCol, (UINT)CollisionOrder::Player);
	AttackCheck.SetRender(Render);
	
	ContentLevel* LevelPtr = GetContentLevel();

	LevelPtr->AddEvent("RookieHero_IntroComboA", GetActorCode(), [this]()
		{
			IsBehaviorLoop = true;
			PlayBehaviorAnim = "Intro_ComboA";
			BossFsm.ChangeState("Behavior");
		});

	LevelPtr->AddEvent("RookieHero_IntroComboB", GetActorCode(), [this]()
		{
			IsBehaviorLoop = true;
			PlayBehaviorAnim = "Intro_ComboB";
			BossFsm.ChangeState("Behavior");
		});

	LevelPtr->AddEvent("RookieHero_IntroYeah", GetActorCode(), [this]()
		{
			IsBehaviorLoop = true;
			PlayBehaviorAnim = "Intro_Yeah";
			BossFsm.ChangeState("Behavior");
		});

	LevelPtr->AddEvent("RookieHero_Introlol", GetActorCode(), [this]()
		{
			IsBehaviorLoop = true;
			PlayBehaviorAnim = "Intro_lol";
			BossFsm.ChangeState("Behavior");
		});

	LevelPtr->AddEvent("RookieHero_Introlol_End", GetActorCode(), [this]()
		{
			IsBehaviorLoop = true;
			PlayBehaviorAnim = "Intro_lol_End";
			BossFsm.ChangeState("Behavior");
		});

	LevelPtr->AddEvent("RookieHero_IntroWho", GetActorCode(), [this]()
		{
			SetViewDir(ActorViewDir::Left);
			IsBehaviorLoop = true;
			PlayBehaviorAnim = "Intro_Who";
			GameEngineSound::Play("Atk_BluntWeapon_Small 1.wav");
			BossFsm.ChangeState("Behavior");
		});

	LevelPtr->AddEvent("RookieHero_IntroPotion", GetActorCode(), [this]()
		{
			IsBehaviorLoop = false;
			PlayBehaviorAnim = "Potion";
			BossFsm.ChangeState("Behavior");
		});	
	
	LevelPtr->AddEvent("RookieHero_Script00_End", GetActorCode(), [this]()
		{
			HeroHealthBar->On();
			IsBehaviorLoop = false;
			IsIntro = false;
			GetContentLevel()->PlayCustomBgm("Adventurer.wav");
		});
}

void RookieHero::Update(float _DeltaTime)
{
	BossMonster::Update(_DeltaTime);
	SpeechCoolTime += _DeltaTime;

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

		UltimateColorBuffer.Color = float4::LerpClamp(
			float4(1, 1, 1, 0.6f), float4(1, 1, 1, 0), Progress);

		if (1.0f <= Progress)
		{
			IsUltimateFadeOn = false;
			UltimateFade->Off();
		}
	}

	HealthBarPtr->UpdateBar(HP / Data.HP, _DeltaTime);
	HeroHealthBar->UpdateBar(HP / Data.HP, _DeltaTime);

	if (0.0f >= HP)
	{
		if (nullptr != Bubble)
		{
			Bubble->Death();
			Bubble = nullptr;
		}

		if (true == ChargeSound.IsValid())
		{
			ChargeSound.Stop();
		}

		if (false == IsDeathIntro)
		{
			GameEngineSound::Play("AdventurerHero_Voice_Dead.wav");
			ChargeSound = GameEngineSound::Play("Adventurer_Charge_Start.wav");

			if (true == UltimateLight->IsUpdate())
			{
				UltimateLightOff();
			}

			IsDeathIntro = true;
			HealthBarPtr->Off();
			HeroHealthBar->SetDeathPicture();
			PlayAnimation("DeathIntro", false);

			IsCustomSoundEnd = true;
			GetContentLevel()->StopCustomBgm();
			GetContentLevel()->PlayBaseBGM();
		}

		if (true == Render->IsAnimationEnd())
		{

			++ResultInfo::KillCount;
			GetContentLevel()->CallEvent("MinimapOn");
			GetContentLevel()->CallEvent("GoodsUIOn");
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
			GetContentLevel()->CallEvent("RookieHero_Intro");

			IsPlayerEnter = true;

			Battle_Platform_Left->On();
			Battle_Platform_Right->On();
			GetContentLevel()->StopBaseBGM();
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

void RookieHero::DataLoad()
{
	Data = ContentDatabase<MonsterData, LevelArea>::GetData(180); // 180 = �߽� ���
}

void RookieHero::CreateAnimation()
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

	Render->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "RookieHero_Idle.png", .Loop = true, .ScaleToTexture = true});
	Render->CreateAnimation({ .AnimationName = "Intro_ComboA", .SpriteName = "RookieHero_Intro_ComboA.png",
		.Start = 0, .End = 43, .Loop = true, .ScaleToTexture = true});
	Render->CreateAnimation({ .AnimationName = "Intro_ComboB", .SpriteName = "RookieHero_Intro_ComboB.png",
		.Start = 0, .End = 25, .Loop = false, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Intro_Yeah", .SpriteName = "RookieHero_Yeah.png", .Loop = true, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Intro_lol", .SpriteName = "RookieHero_lol.png", .Loop = true, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Intro_lol_End", .SpriteName = "RookieHero_lol_End.png", .Loop = true, .ScaleToTexture = true });
	Render->CreateAnimation({ .AnimationName = "Intro_Who", .SpriteName = "RookieHero_Who.png", .Loop = false, .ScaleToTexture = true });
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

	Render->SetAnimationStartEvent("Intro_ComboA", 1, []() {GameEngineSound::Play("Atk_Sword_Large (Slash Up).wav"); });
	Render->SetAnimationStartEvent("Intro_ComboA", 5, []() {GameEngineSound::Play("Atk_Sword_Large (Slash Down).wav");});
	Render->SetAnimationStartEvent("Intro_ComboA", 9, []() {GameEngineSound::Play("Atk_Flame_Very_Small.wav");});
	Render->SetAnimationStartEvent("Intro_ComboA", 31, []() {GameEngineSound::Play("Atk_Sword_Large (Slash Up).wav"); });
	Render->SetAnimationStartEvent("Intro_ComboA", 36, []() {GameEngineSound::Play("Atk_Sword_Large (Slash Down).wav");});
	Render->SetAnimationStartEvent("Intro_ComboA", 40, []() {GameEngineSound::Play("Atk_Flame_Very_Small.wav");});

	Render->SetAnimationStartEvent("Intro_ComboB", 1, []() {GameEngineSound::Play("Atk_Sword_Large (Slash Up).wav"); });
	Render->SetAnimationStartEvent("Intro_ComboB", 5, []() {GameEngineSound::Play("Atk_Sword_Large (Slash Down).wav"); });
	Render->SetAnimationStartEvent("Intro_ComboB", 9, []() {GameEngineSound::Play("Atk_Flame_Very_Small.wav"); });
	Render->SetAnimationStartEvent("Intro_ComboB", 13, []() {GameEngineSound::Play("Atk_Sword_Large (Slash Up).wav"); });
	Render->SetAnimationStartEvent("Intro_ComboB", 17, []() {GameEngineSound::Play("AdventurerHero_Voice_SpecialMove.wav"); GameEngineSound::Play("Hit_Sword_Large.wav"); });

	Render->SetAnimationStartEvent("AttackA", 5, []() {GameEngineSound::Play("AdventurerHero_ComboA.wav");});
	Render->SetAnimationStartEvent("AttackB", 1, []() {GameEngineSound::Play("AdventurerHero_ComboB.wav");});
	Render->SetAnimationStartEvent("AttackD", 1, []() {GameEngineSound::Play("AdventurerHero_ComboD.wav");});

	Render->SetAnimationStartEvent("BackDash", 1, []() {GameEngineSound::Play("AdventurerHero_BackDash.wav");});
	
}

void RookieHero::SelectPattern()
{
	GameEngineRandom& Rand = GameEngineRandom::MainRandom;

	float CurHpRatio = HP / Data.HP;

	// Ultimate
	if (0.5f >= CurHpRatio && 0.0f <= UltimateTime)
	{
		Cur_Pattern_Enter = std::bind(&RookieHero::Ultimate_Enter, this);
		Cur_Pattern_Update = std::bind(&RookieHero::Ultimate_Update, this, std::placeholders::_1);
		Cur_Pattern_End = std::bind(&RookieHero::Ultimate_End, this);

		AttackDistance = 600.0f;
		UltimateTime = -30.0f;
		return;
	}

	int RandPattern = Rand.RandomInt(0, 99);

	if (30 > RandPattern)
	{
		Cur_Pattern_Enter = std::bind(&RookieHero::ComboAttack_Enter, this);
		Cur_Pattern_Update = std::bind(&RookieHero::ComboAttack_Update, this, std::placeholders::_1);
		Cur_Pattern_End = std::bind(&RookieHero::ComboAttack_End, this);
		AttackDistance = 400.0f;
	}
	else if (60 > RandPattern)
	{
		Cur_Pattern_Enter = std::bind(&RookieHero::EnergyBall_Enter, this);
		Cur_Pattern_Update = std::bind(&RookieHero::EnergyBall_Update, this, std::placeholders::_1);
		Cur_Pattern_End = std::bind(&RookieHero::EnergyBall_End, this);
		AttackDistance = 1000.0f;
	}
	else if (90 > RandPattern)
	{
		Cur_Pattern_Enter = std::bind(&RookieHero::Explosion_Enter, this);
		Cur_Pattern_Update = std::bind(&RookieHero::Explosion_Update, this, std::placeholders::_1);
		Cur_Pattern_End = std::bind(&RookieHero::Explosion_End, this);
		AttackDistance = 200.0f;
	}
	else
	{
		Cur_Pattern_Enter = std::bind(&RookieHero::Potion_Enter, this);
		Cur_Pattern_Update = std::bind(&RookieHero::Potion_Update, this, std::placeholders::_1);
		Cur_Pattern_End = std::bind(&RookieHero::Potion_End, this);
		AttackDistance = 2000.0f;
	}
}


void RookieHero::UltimateLightOn()
{
	IsUltimateLightOn = true;
	IsUltimateLightOff = false;
	UltimateLightProgress = 0.0f;

	UltimateLight->On();
	UltimateLightBuffer.Color = float4(0.0f, 0.0f, 0.0f, 0.0f);
}


void RookieHero::UltimateLightOff()
{
	IsUltimateLightOn = false;
	IsUltimateLightOff = true;
	UltimateLightProgress = 0.0f;

	UltimateLight->On();
	UltimateLightBuffer.Color = float4(0.0f, 0.0f, 0.0f, 0.6f);
}


void RookieHero::UltimateFadeOn()
{
	IsUltimateFadeOn = true;
	UltimateFadeProgress = 0.0f;

	UltimateFade->On();
	UltimateColorBuffer.Color = float4(1.0f, 1.0f, 1.0f, 0.6f);
}