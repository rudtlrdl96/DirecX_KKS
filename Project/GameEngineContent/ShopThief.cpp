#include "PrecompileHeader.h"
#include "ShopThief.h"
#include "NPC_TalkBox.h"
#include "FieldNoteActor.h"

ShopThief::ShopThief()
{
}

ShopThief::~ShopThief()
{
}

void ShopThief::CallUseEvent()
{
	NpcTalkBox->ButtonActive();
	NpcTalkBox->On();
}

void ShopThief::Start()
{
	BaseNPC::Start();

	MainRender->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "ShopThiefIdle.png", .ScaleToTexture = true });

	PlayAnimation("Idle", false);
	NpcTalkBox = GetLevel()->CreateActor<NPC_TalkBox>();
	NpcTalkBox->GetTransform()->SetParent(GetTransform());
	NpcTalkBox->GetTransform()->SetWorldPosition(float4(0, -300, -110.0f));
	NpcTalkBox->SetButtonInterval(float4(0, 35));
	NpcTalkBox->AddButton("대화", [this]() {PlayNextScript(); });

	NpcTalkBox->SetTalkBoxName("도굴꾼", float4(2, 0), float4(130, 34));

	NpcTalkBox->AddMainText(L"어디에서도 못 본 물건들일 거야! 그 검은 보석 몇 개와 교환한다니까!");
	NpcTalkBox->Off();

	TalkEventCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::UseEvent);
	TalkEventCol->SetColType(ColType::AABBBOX2D);
	TalkEventCol->GetTransform()->SetLocalScale(float4(160, 160, 1));
	TalkEventCol->GetTransform()->SetLocalPosition(float4(3, -80));

	NoteActor = GetLevel()->CreateActor<FieldNoteActor>();
	NoteActor->GetTransform()->SetParent(GetTransform());
	NoteActor->GetTransform()->SetLocalPosition(float4(0, -171, -100.0f));
	NoteActor->SetText("ㅁ 대화하기");
	NoteActor->AddKeyImage("KeyUI_F.png", float4(-35, 0, -1));
	NoteActor->Off();

	CreateTalkScript();
}

void ShopThief::Update(float _DeltaTime)
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

void ShopThief::SpriteLoad()
{
	if (nullptr == GameEngineSprite::Find("ShopThiefIdle.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("7_Shop");
		Path.Move("Npc");
		Path.Move("ShopThief");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("ShopThiefIdle.png").GetFullPath(), 4, 6);
	}
}

void ShopThief::CreateTalkScript()
{
	TalkScripts.resize(6);

	TalkScripts[0] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};

		std::function<void()> Talk3 = [this, TalkEnd]()
		{
			NpcTalkBox->SetTalkMainText(L"참고로 밥은 정말 맛없다.", TalkEnd);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"정신없이 도망치다 보니 우연찮게 이곳으로 들어왔는데, 다들 친절하게 대해주네. 참 다행이야.", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"처음에는 내가 나뭇가지로 불 좀 피웠다고 그런 줄 알았는데, 나중에는 가시덩굴로 위협하더라고.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"처음엔 급하게 성에서 도망 나와서 숲에 숨었어. 근데 엔트들이 계속 날 쫓아내려 하는 거야.", Talk1);
		NpcTalkBox->ButtonDisable();
	};

	TalkScripts[1] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};

		std::function<void()> Talk3 = [this, TalkEnd]()
		{
			NpcTalkBox->SetTalkMainText(L"아무도 기억 못 해... 아무도...", TalkEnd);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"다 죽어나갔지만, 걔네들 누가 챙겨주지?", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"걔네도 큰 꿈을 품고 성 밖으로 나서서 마족들을 막 공격하지? 지금 그래서 초대 용사만큼의 유명세를 떨친 이가 몇이나 있어?", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"그 모험가들 있잖아? 진짜 불쌍한 놈들이다. 나라가 만들어낸 용사 전설에 세뇌당해 머리가 이상해진 거야.", Talk1);
		NpcTalkBox->ButtonDisable();
	};

	TalkScripts[2] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};

		std::function<void()> Talk3 = [this, TalkEnd]()
		{
			NpcTalkBox->SetTalkMainText(L"그녀는 조심히 다루라던데, 왜 그러는지는 잘 모르겠네.", TalkEnd);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"물론 꽁짜로 받아가진 않아. 굉장히 비싼 값에 쳐주더라고. 나야 좋지! 뭔지도 모르는 괴상한 보석인데 말이야. 그녀 외에는 아무도 사려 하지 않는데.", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"가끔씩 그 마녀처럼 생긴 녀석이 몰래 이곳에 오곤 해. 그리고 나에게서 검은 보석들을 받아가.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"보석을 모으는 이유? 아주 중요한 이유가 있지.", Talk1);
		NpcTalkBox->ButtonDisable();
	};

	TalkScripts[3] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};

		std::function<void()> Talk5 = [this, TalkEnd]()
		{
			NpcTalkBox->SetTalkMainText(L"그래도 종종 나갔다 올 꺼야.", TalkEnd);
		};

		std::function<void()> Talk4 = [this, Talk5]()
		{
			NpcTalkBox->SetTalkMainText(L"조금이라기엔... 좀 많지?", Talk5);
		};

		std::function<void()> Talk3 = [this, Talk4]()
		{
			NpcTalkBox->SetTalkMainText(L"...", Talk4);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"조금 가져왔지.", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"녀석들이 대놓고 전시하면서 봐라! 이것이 칼레온의 보물이다! 하고 자랑하는데, 그걸 어떻게 보고만 있어?", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"그... 맞아. 내가 조금 칼레온에서 보물을 좀 훔쳤어. 그래도 놈들 참 너무한다.", Talk1);
		NpcTalkBox->ButtonDisable();
	};

	TalkScripts[4] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};

		std::function<void()> Talk3 = [this, TalkEnd]()
		{
			NpcTalkBox->SetTalkMainText(L"혹시 무슨 이유 때문에 그러는지 넌 알 수 있겠니?", TalkEnd);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"인간 주제에 여기 머무를 수 있어서 그런 건가? 아니면 도굴꾼 주제에 뻔뻔하게 여기 머무르는 게 우습나?", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"내가 봤을 때는 저 친구들이 훨씬 이상해 보이는 것 같단 말이지.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"여기 있는 친구들이 그러는데, 내가 조금 이상하다네.", Talk1);
		NpcTalkBox->ButtonDisable();
	};

	TalkScripts[5] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};

		std::function<void()> Talk3 = [this, TalkEnd]()
		{
			NpcTalkBox->SetTalkMainText(L"대체 그녀는 언제쯤 다시 오려나...", TalkEnd);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"이제 그냥 골드 주머니로 보여... 내가 돈에 미쳐 버린 걸까.", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"이 검은 보석은 원래 가까이하면 위험하다는 말을 하던데. 난 아무렇지도 않아. 아무것도 느껴지지 않는다고.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"그녀가 나보고 굉장히 특이한 힘을 가졌다고 하더라.", Talk1);
		NpcTalkBox->ButtonDisable();
	};
}

void ShopThief::PlayNextScript()
{
	++TalkScriptNumber;

	if (TalkScripts.size() <= TalkScriptNumber)
	{
		TalkScriptNumber = 0;
	}

	TalkScripts[TalkScriptNumber]();
}

void ShopThief::TalkEndCallback()
{
	NpcTalkBox->Off();
	GetContentLevel()->CallEvent("PlayerInputUnlock");
	GetContentLevel()->CallEvent("StoryFadeOut");
	GetContentLevel()->CallEvent("PlayerFrameActive");
	GetContentLevel()->CallEvent("UseKeyOn");
}