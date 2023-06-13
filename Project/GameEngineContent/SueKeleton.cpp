#include "PrecompileHeader.h"
#include "SueKeleton.h"

SueKeleton::SueKeleton()
{
}

SueKeleton::~SueKeleton()
{
}

void SueKeleton::Destroy()
{
	BaseNPC::Destroy();
	ContentLevel* LevelPtr = GetContentLevel();
	LevelPtr->RemoveEvent("Suekeleton_Script01_End", GetActorCode());
}

void SueKeleton::Start()
{
	BaseNPC::Start();

	MainRender->CreateAnimation({
		.AnimationName = "Idle", .SpriteName = "SueKeleton_Idle.png", .ScaleToTexture = true });

	MainRender->CreateAnimation({
		.AnimationName = "Dead", .SpriteName = "SueKeleton_Dead.png", 
		.FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });

	MainRender->CreateAnimation({
		.AnimationName = "GiveWeapon", .SpriteName = "SueKeleton_GiveWeapon.png",
		.FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });

	MainRender->ChangeAnimation("Idle");

	FirstScriptCol = CreateComponent<GameEngineCollision>();
	FirstScriptCol->GetTransform()->SetLocalPosition(float4(-340, -100, 0));
	FirstScriptCol->GetTransform()->SetLocalScale(float4(400, 600, 1));

	SecondScriptCol = CreateComponent<GameEngineCollision>();
	SecondScriptCol->GetTransform()->SetLocalScale(float4(140, 1000, 1));

	GetContentLevel()->AddEvent("Suekeleton_Script01_End", GetActorCode(), [this]()
		{
			PlayAnimation("GiveWeapon", true);
			IsGiveWeapon = true;
		});
}

void SueKeleton::Update(float _DeltaTime)
{
	BaseNPC::Update(_DeltaTime);

	if (false == IsFirstScriptPlay &&
		nullptr != FirstScriptCol->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		IsFirstScriptPlay = true;
		FirstScriptCol->Off();

		GetContentLevel()->CallEvent("Suekeleton_Script00");

	}

	if (false == IsSecondScriptPlay &&
		nullptr != SecondScriptCol->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		IsSecondScriptPlay = true;
		SecondScriptCol->Off();

		GetContentLevel()->CallEvent("PlayerMove_Suekeleton");
	}	


	if (true == IsGiveWeapon && true == MainRender->IsAnimationEnd())
	{
		IsGiveWeapon = false;
		PlayAnimation("Dead", true);
		GetContentLevel()->CallEvent("Suekeleton_Script02");
	}
}

void SueKeleton::ResetBehavior()
{
	IsFirstScriptPlay = false;
	IsSecondScriptPlay = false;

	FirstScriptCol->On();
	SecondScriptCol->On();
}

void SueKeleton::PlayBehavior()
{
	IsFirstScriptPlay = false;
	IsSecondScriptPlay = false;

	FirstScriptCol->On();
	SecondScriptCol->On();
}

void SueKeleton::SpriteLoad()
{
	if (nullptr == GameEngineSprite::Find("SueKeleton_Idle.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("1_Opening");
		Path.Move("Npc");
		Path.Move("SueKeleton");
		Path.Move("Sheet");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("SueKeleton_Idle.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("SueKeleton_GiveWeapon.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("SueKeleton_Dead.png").GetFullPath(), 9, 1);
	}
}
