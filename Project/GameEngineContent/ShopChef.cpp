#include "PrecompileHeader.h"
#include "ShopChef.h"
#include "NPC_TalkBox.h"
#include "FieldNoteActor.h"

ShopChef::ShopChef()
{
}

ShopChef::~ShopChef()
{
}

void ShopChef::CallUseEvent()
{
	NpcTalkBox->ButtonActive();
	NpcTalkBox->On();
}

void ShopChef::Start()
{
	BaseNPC::Start();

	MainRender->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Chef_Idle.png", .ScaleToTexture = true });
	PlayAnimation("Idle", false);
	NpcTalkBox = GetLevel()->CreateActor<NPC_TalkBox>();
	NpcTalkBox->GetTransform()->SetParent(GetTransform());
	NpcTalkBox->GetTransform()->SetWorldPosition(float4(0, -300, -110.0f));
	NpcTalkBox->SetButtonInterval(float4(0, 35));
	NpcTalkBox->AddButton("대화", [this]() {PlayNextScript(); });

	NpcTalkBox->SetTalkBoxName("쉐프", float4(3, 0));

	NpcTalkBox->AddMainText(L"이봐! 너무 삐쩍 말랐는데? 이러다 '뼈'만 남겠어! 하하!");
	NpcTalkBox->Off();

	TalkEventCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::UseEvent);
	TalkEventCol->SetColType(ColType::AABBBOX2D);
	TalkEventCol->GetTransform()->SetLocalScale(float4(200, 200, 1));
	TalkEventCol->GetTransform()->SetLocalPosition(float4(-101, 133));

	NoteActor = GetLevel()->CreateActor<FieldNoteActor>();
	NoteActor->GetTransform()->SetParent(GetTransform());
	NoteActor->GetTransform()->SetLocalPosition(float4(-100, 19, -100.0f));
	NoteActor->SetText("ㅁ 대화하기");
	NoteActor->AddKeyImage("KeyUI_F.png", float4(-35, 0, -1));
	NoteActor->Off();

	CreateTalkScript();
}


void ShopChef::Update(float _DeltaTime)
{
	if (true == NpcTalkBox->IsUpdate())
	{
		NoteActor->Off();
		return;
	}
	else
	{
		BubbleTalkTime += _DeltaTime;
	}

	if (false == IsFocus())
	{
		NoteActor->Off();
		return;
	}
	else
	{
		NoteActor->On();
	}
}

void ShopChef::SpriteLoad()
{
	if (nullptr == GameEngineSprite::Find("Chef_Idle.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("7_Shop");
		Path.Move("Npc");
		Path.Move("Chef");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Chef_Idle.png").GetFullPath(), 7, 1);
	}
}

void ShopChef::CreateTalkScript()
{
	TalkScripts.resize(5);

	TalkScripts[0] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};

		std::function<void()> Talk1 = [this, TalkEnd]()
		{
			NpcTalkBox->SetTalkMainText(L"다들 나를 검투사 출신으로 보던데, 너도 그렇게 생각해?", TalkEnd);
		};

		NpcTalkBox->SetTalkMainText(L"몸에 있는 타투는 신경 쓰지 마. 철없던 어린 시절 멋으로 했었지.", Talk1);
		NpcTalkBox->ButtonDisable();
	};

	TalkScripts[1] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};

		std::function<void()> Talk2 = [this, TalkEnd]()
		{
			NpcTalkBox->SetTalkMainText(L"와! 방금 먹은 거 어디 갔어?", TalkEnd);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"...", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"잠깐 기다려봐 해볼게 있어! 이거 먹어봐. 잠깐, 입은 있나?", Talk1);
		NpcTalkBox->ButtonDisable();
	};

	TalkScripts[2] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};

		std::function<void()> Talk1 = [this, TalkEnd]()
		{
			NpcTalkBox->SetTalkMainText(L"근데 넌 그러기엔 너무 구멍이 숭숭 나있는걸!", TalkEnd);
		};

		NpcTalkBox->SetTalkMainText(L"든-든하게 배를 채우라고. 속이 든든해야 싸움도 잘 할 수 있는 거야!", Talk1);
		NpcTalkBox->ButtonDisable();
	};

	TalkScripts[3] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};

		std::function<void()> Talk4 = [this, TalkEnd]()
		{
			NpcTalkBox->SetTalkMainText(L"빨간 망토와 잿빛 머리, 짙은 갑옷만이 기억에 남는구먼.", TalkEnd);
		};

		std::function<void()> Talk3 = [this, Talk4]()
		{
			NpcTalkBox->SetTalkMainText(L"잠깐 물 뜨러 간사이에 사라졌었는데, 맛있게 먹었나 몰라. 지금은 어떻게 지내려나?", Talk4);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"아무리 적이라지만... 밥 만드는 오크로서 굶어 죽는 꼴은 절대 못 보지 않겠어? 정성스레 간호해 준 뒤 인생 최고의 음식을 해줬지.", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"어느 날 드루이드 협곡을 지날 때였나? 바닥에 쓰러져 있는 인간을 발견했어. 꿈쩍도 않더라고. 조금 무서웠지만, 죽었나 싶어 가까이 가보니 살아있긴 하더라고? 극심한 영양실조였지.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"이십 년 전쯤인가... 요리 수행을 다니고 있었어. 작은 수레에 조리도구들을 잔뜩 싣고 유랑하며 요리를 하고 있었지.", Talk1);
		NpcTalkBox->ButtonDisable();
	};

	TalkScripts[4] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};

		std::function<void()> Talk2 = [this, TalkEnd]()
		{
			NpcTalkBox->SetTalkMainText(L"마왕님도 찾아와서 직접 드시고 갔어, 물론 그 빨간 머리도!", TalkEnd);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"다행히도 나는 수만 가지 레시피를 알고 있기에, 어떤 걸 가져다줘도 완벽하게 해낸다구!", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"음식을 하는 것보다 요새는 식재료를 구하는 게 더 힘들어.", Talk1);
		NpcTalkBox->ButtonDisable();
	};
}

void ShopChef::PlayNextScript()
{
	++TalkScriptNumber;

	if (TalkScripts.size() <= TalkScriptNumber)
	{
		TalkScriptNumber = 0;
	}

	TalkScripts[TalkScriptNumber]();
}

void ShopChef::TalkEndCallback()
{
	NpcTalkBox->Off();
	GetContentLevel()->CallEvent("PlayerInputUnlock");
	GetContentLevel()->CallEvent("StoryFadeOut");
	GetContentLevel()->CallEvent("PlayerFrameActive");
	GetContentLevel()->CallEvent("UseKeyOn");
}