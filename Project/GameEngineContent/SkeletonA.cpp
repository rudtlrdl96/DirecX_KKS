#include "PrecompileHeader.h"
#include "SkeletonA.h"

SkeletonA::SkeletonA()
{
}

SkeletonA::~SkeletonA()
{
}

void SkeletonA::Start()
{
	BaseNPC::Start();

	MainRender->CreateAnimation({
		.AnimationName = "Idle", .SpriteName = "SkeletonA_Idle.png", .ScaleToTexture = true});

	MainRender->CreateAnimation({
		.AnimationName = "Dead", .SpriteName = "SkeletonA_Dead.png", .ScaleToTexture = true });

	PlayAnimation("Idle", true);

	GetContentLevel()->AddEvent("WitchCageOut", GetActorCode(), [this]()
		{
			PlayAnimation("Dead", true);

			if (nullptr != Bubble)
			{
				Bubble->Death();
				Bubble = nullptr;
			}

			Bubble = GetLevel()->CreateActor<SpeechBubble>();

			Bubble->PlayBubble({
				.Target = DynamicThis<GameEngineActor>(),
				.Text = "¥Ÿ«‡¿Ãæﬂ",
				.Pivot = float4(0, 105, 0),
				.IsLoop = false,
				.LiveTime = 3.0f,
				.LoopInter = 3.0f,
				.IsAutoScale = true
				});
		});
}

void SkeletonA::Update(float _DeltaTime)
{
	if (nullptr != Bubble && true == Bubble->IsDeath())
	{
		Bubble = nullptr;
	}

	BaseNPC::Update(_DeltaTime);
}

void SkeletonA::ResetBehavior()
{
	if (nullptr != Bubble)
	{
		Bubble->Death();
		Bubble = nullptr;
	}

	PlayAnimation("Idle", true);
}

void SkeletonA::PlayBehavior()
{
	PlayAnimation("Idle", true);

	Bubble = GetLevel()->CreateActor<SpeechBubble>();

	Bubble->PlayBubble({
		.Target = DynamicThis<GameEngineActor>(),
		.Text = "æÓº≠ ∏∂≥‡¥‘¿ª ±∏«ÿ¡‡",
		.Pivot = float4(0, 105, 0),
		.IsLoop = true,
		.LiveTime = 3.0f,
		.LoopInter = 3.0f,
		.IsAutoScale = true
		});
}

void SkeletonA::SpriteLoad()
{
	if (nullptr == GameEngineSprite::Find("SkeletonA_Idle.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("1_Opening");
		Path.Move("Npc");
		Path.Move("SkeletonA");
		Path.Move("Sheet");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("SkeletonA_Idle.png").GetFullPath(), 13, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("SkeletonA_Dead.png").GetFullPath(), 1, 1);
	}
}
