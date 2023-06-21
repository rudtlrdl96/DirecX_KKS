#include "PrecompileHeader.h"
#include "SkeleTong.h"

SkeleTong::SkeleTong()
{
}

SkeleTong::~SkeleTong()
{
}

void SkeleTong::Start()
{
	if (nullptr == GameEngineTexture::Find("FadeImage.png"))
	{
		GameEngineDirectory Path;
		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("0_Common");
		Path.Move("UI");

		GameEngineTexture::Load(Path.GetPlusFileName("FadeImage.png").GetFullPath());
	}

	BaseNPC::Start();

	MainRender->CreateAnimation({
		.AnimationName = "Idle", .SpriteName = "SkeleTong_Idle.png", .FrameInter = 0.2f, .ScaleToTexture = true});

	MainRender->CreateAnimation({
		.AnimationName = "Dead", .SpriteName = "SkeleTong_Dead.png", .FrameInter = 0.2f, .ScaleToTexture = true });

	MainRender->CreateAnimation({
		.AnimationName = "Wow", .SpriteName = "SkeleTong_Wow.png", .FrameInter = 0.2f, .ScaleToTexture = true });

	MainRender->CreateAnimation({
		.AnimationName = "Surqrise", .SpriteName = "SkeleTong_Surqrise.png", .FrameInter = 0.15f, .Loop = false, .ScaleToTexture = true });

	MainRender->CreateAnimation({
		.AnimationName = "Talk", .SpriteName = "SkeleTong_Talk.png", .FrameInter = 0.15f, .ScaleToTexture = true });

	MainRender->CreateAnimation({
		.AnimationName = "Walk", .SpriteName = "SkeleTong_Walk.png",
		.Start = 0, .End = 12, .FrameInter = 0.15f, .Loop = false, .ScaleToTexture = true });

	AnimFramePause["Idle"][0] = 1.5f;
	PlayAnimation("Idle", true);

	AnimFramePause["Talk"][0] = 0.2f;

	FadeRender = CreateComponent<ContentUIRender>();
	FadeRender->PipeSetting("2DTexture_Color");
	FadeRender->GetShaderResHelper().SetConstantBufferLink("ColorBuffer", Buffer);
	FadeRender->SetTexture("FadeImage.png");
	FadeRender->GetTransform()->SetWorldPosition(float4(0, 0, -105.0f));
	FadeRender->GetTransform()->SetLocalScale(GameEngineWindow::GetScreenSize());
	FadeRender->Off();

	ContentLevel* LevelPtr = GetContentLevel();

	LevelPtr->AddEvent("SkeleTong_Script00_End", GetActorCode(), [this]()
		{
			IsFadeEnd = true;
		});

	LevelPtr->AddEvent("SkeleTong_Script01_End", GetActorCode(), [this]()
		{
			PlayAnimation("Walk", true, 12);
		});	

	LevelPtr->AddEvent("SkeleTong_Script02", GetActorCode(), [this]()
		{
			PlayAnimation("Wow", true);
		});

	LevelPtr->AddEvent("SkeleTong_Script02_End", GetActorCode(), [this]()
		{
			PlayAnimation("Walk", true, 12);
			IsScript3Active = true;
		});	

	LevelPtr->AddEvent("SkeleTong_Script03_End", GetActorCode(), [this]()
		{
			PlayAnimation("Walk", true, 12);

			if (nullptr != Bubble)
			{
				Bubble->Death();
				Bubble = nullptr;
			}

			Bubble = GetLevel()->CreateActor<SpeechBubble>();

			Bubble->PlayBubble({
				.Target = DynamicThis<GameEngineActor>(),
				.Text = "ºÎÅ¹ÇÑ´Ù...",
				.Pivot = float4(-45, 105, 0),
				.IsLoop = false,
				.FontSize = 20,
				.LiveTime = 3.0f,
				});

		});
}


void SkeleTong::Update(float _DeltaTime)
{
	if (nullptr != Bubble && Bubble->IsDeath())
	{
		Bubble = nullptr;
	}

	BaseNPC::Update(_DeltaTime);

	if (true == IsFadeEnd)
	{
		FadeProgress += _DeltaTime;

		if (1.0f < FadeProgress)
		{
			FadeProgress = 1.0f;
			IsMove = true;
			IsFadeEnd = false;
		}

		Buffer.Color.a = 1.0f - FadeProgress;
	}

	if (true == IsMove)
	{
		MoveWaitTime += _DeltaTime;

		if (3.0f <= MoveWaitTime)
		{
			PlayAnimation("Walk", false);

			MainRender->ChangeAnimation("Walk", false);

			if (true == MainRender->IsAnimationEnd())
			{
				IsMove = false;
				IsSurqrise = true;
				GetContentLevel()->CallEvent("SkeleTongWalkEnd");
			}
		}
	}

	if (true == IsSurqrise)
	{
		SurqriseTime += _DeltaTime;

		if (0.1f <= SurqriseTime)
		{
			PlayAnimation("Surqrise", false);
		}

		if (1.0f <= SurqriseTime)
		{
			IsSurqrise = false;
			GetContentLevel()->CallEvent("SkeleTong_Script01");
			PlayAnimation("Talk", true);
		}
	}

	if (true == IsScript3Active)
	{
		Script3WaitTime +=	_DeltaTime;

		if (1.0f <= Script3WaitTime)
		{
			PlayAnimation("Talk", true);
			IsScript3Active = false;
		}
	}
}

void SkeleTong::PlayBehavior()
{
	if (nullptr != Bubble)
	{
		Bubble->Death();
		Bubble = nullptr;
	}

	FadeProgress = 0.0f;
	Buffer.Color.a = 1.0f;
	FadeRender->On();

	GetContentLevel()->CallEvent("SkeleTong_Script00");
}

void SkeleTong::Destroy()
{
	if (nullptr != Bubble)
	{
		Bubble->Death();
		Bubble = nullptr;
	}

	ContentLevel* LevelPtr = GetContentLevel();

	LevelPtr->RemoveEvent("SkeleTong_Script00_End", GetActorCode());
	LevelPtr->RemoveEvent("SkeleTong_Script01_End", GetActorCode());
	LevelPtr->RemoveEvent("SkeleTong_Script02", GetActorCode());
	LevelPtr->RemoveEvent("SkeleTong_Script02_End", GetActorCode());
	LevelPtr->RemoveEvent("SkeleTong_Script03_End", GetActorCode());
}

void SkeleTong::SpriteLoad()
{
	if (nullptr == GameEngineSprite::Find("SkeleTong_Idle.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("1_Opening");
		Path.Move("Npc");
		Path.Move("SkeleTong");
		Path.Move("Sheet");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("SkeleTong_Idle.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("SkeleTong_Dead.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("SkeleTong_Wow.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("SkeleTong_Surqrise.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("SkeleTong_Talk.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("SkeleTong_Walk.png").GetFullPath(), 7, 2);
	}
}