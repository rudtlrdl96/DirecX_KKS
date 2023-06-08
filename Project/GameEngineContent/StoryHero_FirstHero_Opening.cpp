#include "PrecompileHeader.h"
#include "StoryHero_FirstHero_Opening.h"
#include "StoryLevel.h"

StoryHero_FirstHero_Opening::StoryHero_FirstHero_Opening()
{
}

StoryHero_FirstHero_Opening::~StoryHero_FirstHero_Opening()
{
}

void StoryHero_FirstHero_Opening::PlayLandingEffect()
{
	EffectManager::PlayEffect({
		.EffectName = "FirstHero_Landing",
		.Position = GetTransform()->GetWorldPosition() + float4(-10, 300, 0)});
}

void StoryHero_FirstHero_Opening::Death()
{
	BaseContentActor::Death();

	ContentLevel* LevelPtr = GetContentLevel();

	LevelPtr->RemoveEvent("NextLevelMove", GetActorCode());
	LevelPtr->RemoveEvent("Story_FirstHeroTalk0_End", GetActorCode());
}

void StoryHero_FirstHero_Opening::Start()
{
	if (nullptr == GameEngineSprite::Find("FirstHero_Story_Landing.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("1_Opening");
		Path.Move("Npc");
		Path.Move("FirstHero");
		Path.Move("Sheet");

		
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("FirstHero_Story_Landing.png").GetFullPath(), 10, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("FirstHero_Story_FlyIdle.png").GetFullPath(), 9, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("FirstHero_Story_CastingIntro.png").GetFullPath(), 6, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("FirstHero_Story_CastingLoop.png").GetFullPath(), 6, 1);

		Path.MoveParent();
		Path.Move("Effect");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("FirstHero_BigbangReady_Effect.png").GetFullPath(), 5, 5);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("FirstHero_Landing_Effect.png").GetFullPath(), 7, 7);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("FirstHero_OrbLoop_Effect.png").GetFullPath(), 7, 6);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("FirstHero_OrbStart_Effect.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("FirstHero_OrbTrail_Effect.png").GetFullPath(), 5, 5);

		EffectManager::CreateMetaData("FirstHero_BigbangReady", {
			.SpriteName = "FirstHero_BigbangReady_Effect.png",
			.AnimStart = 0,
			.AnimEnd = 22,
			.AnimIter = 0.05f,
			.ScaleRatio = 2.0f});

		EffectManager::CreateMetaData("FirstHero_Landing", {
			.SpriteName = "FirstHero_Landing_Effect.png",
			.AnimStart = 0,
			.AnimEnd = 42,
			.AnimIter = 0.04f,
			.ScaleRatio = 2.0f });

		EffectManager::CreateMetaData("FirstHero_OrbLoop", {
			.SpriteName = "FirstHero_OrbLoop_Effect.png",
			.AnimStart = 0,
			.AnimEnd = 37,
			.AnimIter = 0.05f,
			.ScaleRatio = 2.0f });

		EffectManager::CreateMetaData("FirstHero_OrbStart", {
			.SpriteName = "FirstHero_OrbStart_Effect.png",
			.AnimStart = 0,
			.AnimEnd = 4,
			.AnimIter = 0.05f,
			.ScaleRatio = 3.0f });

		EffectManager::CreateMetaData("FirstHero_OrbTrail", {
			.SpriteName = "FirstHero_OrbTrail_Effect.png",
			.AnimStart = 0,
			.AnimEnd = 21,
			.AnimIter = 0.05f,
			.ScaleRatio = 2.0f });

	}

	MainRender = CreateComponent<ContentSpriteRenderer>();
	MainRender->PipeSetting("2DTexture_ColorLight");
	MainRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	MainRender->SetScaleRatio(2.0f);

	MainRender->CreateAnimation({
	.AnimationName = "Landing", .SpriteName = "FirstHero_Story_Landing.png", .FrameInter = 0.15f, .Loop = false, .ScaleToTexture = true});

	MainRender->CreateAnimation({
	.AnimationName = "Idle", .SpriteName = "FirstHero_Story_FlyIdle.png",.FrameInter = 0.13f, .Loop = true, .ScaleToTexture = true });

	MainRender->CreateAnimation({
	.AnimationName = "CastingIntro", .SpriteName = "FirstHero_Story_CastingIntro.png",.FrameInter = 0.13f, .Loop = false, .ScaleToTexture = true });

	MainRender->CreateAnimation({
	.AnimationName = "CastingLoop", .SpriteName = "FirstHero_Story_CastingLoop.png",.FrameInter = 0.13f, .Loop = true, .ScaleToTexture = true });

	GetContentLevel()->AddEvent("NextLevelMove", GetActorCode(), [this]()
		{
			Death();
		});

	GetContentLevel()->AddEvent("Story_FirstHeroTalk0_End", GetActorCode(), [this]()
		{
			State = HeroState::CastingIntro;
			MainRender->ChangeAnimation("CastingIntro");
		});

	GetTransform()->SetLocalNegativeScaleX();
	MainRender->ChangeAnimation("Landing");
	GetContentLevel()->GetCamCtrl().CameraShake(30, 20.0f, 15);

}

void StoryHero_FirstHero_Opening::Update(float _DeltaTime)
{
	switch (State)
	{
	case StoryHero_FirstHero_Opening::HeroState::Landing:
	{
		Landing_IntroWaitTime += _DeltaTime;

		if (2.0f > Landing_IntroWaitTime && 0 == MainRender->GetCurrentFrame())
		{
			MainRender->SetAnimPauseOn();
		}
		else
		{
			MainRender->SetAnimPauseOff();
		}

		if (true == MainRender->IsAnimationEnd())
		{
			State = HeroState::Idle;
			IdleStart = GetTransform()->GetLocalPosition();
			IdleEnd = IdleStart + float4(0, 30, 0);
		}
	}
		break;
	case StoryHero_FirstHero_Opening::HeroState::Idle:
		MainRender->ChangeAnimation("Idle", 0, false);

		if (0 < MainRender->GetCurrentFrame())
		{
			IdleProgress += _DeltaTime * IdleUpSpeed;
			GetTransform()->SetLocalPosition(float4::LerpClamp(IdleStart, IdleEnd, IdleProgress));
		}

		if (false == IsTalkStart && 1.0f <= IdleProgress)
		{
			IsTalkStart = true;
			GetContentLevel()->CallEvent("Story_FirstHeroTalk0");
		}

		break;
	case StoryHero_FirstHero_Opening::HeroState::CastingIntro:
		if (true == MainRender->IsAnimationEnd())
		{
			State = HeroState::CastingLoop;
			MainRender->ChangeAnimation("CastingLoop");

			BigbangReadyEffect = EffectManager::PlayEffect({
				.EffectName = "FirstHero_BigbangReady",
				.Position = GetTransform()->GetWorldPosition() + float4(-70, 250, 0) });

			GetContentLevel()->GetCamCtrl().CameraShake(25, 20.0f, 100);
		}
		break;
	case StoryHero_FirstHero_Opening::HeroState::CastingLoop:

		if (nullptr != BigbangReadyEffect && true == BigbangReadyEffect->IsAnimationEnd())
		{
			BigbangReadyEffect->Death();
			BigbangReadyEffect = nullptr;

			GetContentLevel()->CallEvent("FadeOut_White");

			OrbStartEffect = EffectManager::PlayEffect({
				.EffectName = "FirstHero_OrbStart",
				.Position = GetTransform()->GetWorldPosition() + float4(-70, 250, 0) });
		}

		if (nullptr != OrbStartEffect && true == OrbStartEffect->IsAnimationEnd())
		{
			OrbStartEffect->Death();
			OrbStartEffect = nullptr;

			OrbLoopEffect = EffectManager::PlayEffect({
				.EffectName = "FirstHero_OrbLoop",
				.Position = GetTransform()->GetWorldPosition() + float4(-70, 250, 0),
				.Triger = EffectDeathTrigger::Time,
				.Time = 3.0f });

			OrbTrailEffect = EffectManager::PlayEffect({
				.EffectName = "FirstHero_OrbTrail",
				.Position = GetTransform()->GetWorldPosition() + float4(-80, 250, 0),
				.AddSetZ = -50.0f,
				.Triger = EffectDeathTrigger::Time,
				.Time = 3.0f});

			IsBigbangStart = true;
		}

		if (true == IsBigbangStart)
		{
			BigbangTime += _DeltaTime;

			if (false == IsBigbangEnd && 1.5f < BigbangTime)
			{
				GetContentLevel()->CallEvent("FadeIn_White");
				IsBigbangEnd = true;
			}
		}

		if (true == IsBigbangEnd)
		{
			FadeTime += _DeltaTime;

			if (false == IsLevelEnd && 2.0f <= FadeTime)
			{
				GetContentLevel()->CallEvent("FadeIn");
				IsLevelEnd = true;
			}
		}

		if (true == IsLevelEnd)
		{
			LevelEndTime += _DeltaTime;

			if (2.0f <= LevelEndTime)
			{
				OrbLoopEffect = nullptr;
				OrbTrailEffect = nullptr;

				Death();
				StoryLevel::SetLevelEnterStoryName(StoryLevel::StoryName::Opening);
				StoryLevel::SetStoryEndMoveLevel("Castle");
				GameEngineCore::ChangeLevel("Story");
			}
		}
		break;
	default:
		break;
	}

}
