#include "PrecompileHeader.h"
#include "SkeletonB.h"

SkeletonB::SkeletonB()
{
}

SkeletonB::~SkeletonB()
{
}

void SkeletonB::Destroy()
{
	GetContentLevel()->RemoveEvent("WitchCageOut", GetActorCode());
}

void SkeletonB::Start()
{
	BaseNPC::Start();

	MainRender->CreateAnimation({
		.AnimationName = "Idle", .SpriteName = "SkeletonB_Idle.png", .ScaleToTexture = true });

	MainRender->CreateAnimation({
		.AnimationName = "Dead", .SpriteName = "SkeletonB_Dead.png", .ScaleToTexture = true });

	PlayAnimation("Idle", true);
}

void SkeletonB::Update(float _DeltaTime)
{
	BaseNPC::Update(_DeltaTime);

	if (nullptr != Bubble && true == Bubble->IsDeath())
	{
		Bubble = nullptr;
	}	
}

void SkeletonB::PlayBehavior()
{
	Bubble = GetLevel()->CreateActor<SpeechBubble>();
	Bubble->PlayBubble({
		.Target = DynamicThis<GameEngineActor>(),
		.Text = "�Ʒ� ����Ű�� C�� ������ �� �־�. � �ΰ����� �Ѿư�",
		.Pivot = float4(0, 105, 0),
		.IsLarge = true,
		.IsLoop = true,
		.LiveTime = 3.0f,
		});
}

void SkeletonB::ResetBehavior()
{
	Bubble->Death();
	Bubble = nullptr;
}

void SkeletonB::SpriteLoad()
{
	if (nullptr == GameEngineSprite::Find("SkeletonB_Idle.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("1_Opening");
		Path.Move("Npc");
		Path.Move("SkeletonB");
		Path.Move("Sheet");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("SkeletonB_Idle.png").GetFullPath(), 4, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("SkeletonB_Dead.png").GetFullPath(), 1, 1);
	}
}
