#include "PrecompileHeader.h"
#include "RookieHero.h"

RookieHero::RookieHero()
{
}

RookieHero::~RookieHero()
{
}

void RookieHero::Death()
{
	BossMonster::Death();

	ContentLevel* LevelPtr = GetContentLevel();

	LevelPtr->RemoveEvent("RookieHero_IntroComboA", GetActorCode());
	LevelPtr->RemoveEvent("RookieHero_IntroComboB", GetActorCode());
	LevelPtr->RemoveEvent("RookieHero_IntroYeah", GetActorCode());
	LevelPtr->RemoveEvent("RookieHero_Introlol", GetActorCode());
	LevelPtr->RemoveEvent("RookieHero_Introlol_End", GetActorCode());
	LevelPtr->RemoveEvent("RookieHero_IntroWho", GetActorCode());
	LevelPtr->RemoveEvent("RookieHero_IntroPotion", GetActorCode());
	LevelPtr->RemoveEvent("RookieHero_Script00_End", GetActorCode());
}

void RookieHero::Start()
{
	BossMonster::Start();
	SetViewDir(ActorViewDir::Right);

	EventCol = CreateComponent<GameEngineCollision>();
	EventCol->GetTransform()->SetWorldPosition(float4(1248, 564, 1));
	EventCol->GetTransform()->SetLocalScale(float4(1220, 640, 1));

	Battle_Platform_Left = CreateComponent<GameEngineCollision>((int)CollisionOrder::Platform_Normal);
	Battle_Platform_Left->GetTransform()->SetWorldPosition(float4(576, 564, 1));
	Battle_Platform_Left->GetTransform()->SetLocalScale(float4(64, 640, 1));
	Battle_Platform_Left->Off();

	Battle_Platform_Right = CreateComponent<GameEngineCollision>((int)CollisionOrder::Platform_Normal);
	Battle_Platform_Right->GetTransform()->SetWorldPosition(float4(1922, 564, 1));
	Battle_Platform_Right->GetTransform()->SetLocalScale(float4(64, 640, 1));
	Battle_Platform_Right->Off();

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
			IsBehaviorLoop = false;
		});

}

void RookieHero::Update(float _DeltaTime)
{
	BossMonster::Update(_DeltaTime);

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
		}
	}
}

void RookieHero::DataLoad()
{
	Data = ContentDatabase<MonsterData, LevelArea>::GetData(180); // 180 = 견습 용사
}

void RookieHero::SpriteLoad()
{
	if (nullptr == GameEngineSprite::Find("RookieHero_Idle.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("3_ForestOfHarmony");
		Path.Move("Boss");
		Path.Move("RookieHero");
		Path.Move("Sheet");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_Idle.png").GetFullPath(), 6, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_Intro_ComboA.png").GetFullPath(), 8, 6);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_Intro_ComboB.png").GetFullPath(), 7, 4);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_Yeah.png").GetFullPath(), 7, 3);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_lol.png").GetFullPath(), 5, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_lol_End.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_Who.png").GetFullPath(), 6, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_Potion.png").GetFullPath(), 6, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_Hit.png").GetFullPath(), 3, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("RookieHero_Dash.png").GetFullPath(), 3, 1);
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
	Render->CreateAnimation({ .AnimationName = "Dash", .SpriteName = "RookieHero_Dash.png", .Loop = false, .ScaleToTexture = true });
}

void RookieHero::SelectPattern()
{
	Cur_Pattern_Enter = std::bind(&RookieHero::TempPattern_Enter, this);
	Cur_Pattern_Update = std::bind(&RookieHero::TempPattern_Update, this, std::placeholders::_1);
	Cur_Pattern_End = std::bind(&RookieHero::TempPattern_End, this);
}