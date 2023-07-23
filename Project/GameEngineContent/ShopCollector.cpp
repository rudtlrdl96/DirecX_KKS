#include "PrecompileHeader.h"
#include "ShopCollector.h"
#include "NPC_TalkBox.h"
#include "FieldNoteActor.h"
#include "MapPlatform.h"

ShopCollector::ShopCollector()
{
}

ShopCollector::~ShopCollector()
{
}

void ShopCollector::CallUseEvent()
{
	NpcTalkBox->ButtonActive();
	NpcTalkBox->On();
}

void ShopCollector::Start()
{
	BaseNPC::Start();

	MainRender->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Collector_Idle.png", .ScaleToTexture = true });
	PlayAnimation("Idle", false);
	NpcTalkBox = GetLevel()->CreateActor<NPC_TalkBox>();
	NpcTalkBox->GetTransform()->SetParent(GetTransform());
	NpcTalkBox->GetTransform()->SetWorldPosition(float4(0, -300, -110.0f));
	NpcTalkBox->SetButtonInterval(float4(0, 35));
	NpcTalkBox->AddButton("대화", [this]() {PlayNextScript(); });

	NpcTalkBox->SetTalkBoxName("수집가", float4(2, 0), float4(130, 34));

	NpcTalkBox->AddMainText(L"반갑습니다. 스켈레톤 소년.");
	NpcTalkBox->Off();

	TalkEventCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::UseEvent);
	TalkEventCol->SetColType(ColType::AABBBOX2D);
	TalkEventCol->GetTransform()->SetLocalScale(float4(165, 165, 1));
	TalkEventCol->GetTransform()->SetLocalPosition(float4(366, 87));

	NoteActor = GetLevel()->CreateActor<FieldNoteActor>();
	NoteActor->GetTransform()->SetParent(GetTransform());
	NoteActor->GetTransform()->SetLocalPosition(float4(375, -12, -100.0f));
	NoteActor->SetText("ㅁ 대화하기");
	NoteActor->AddKeyImage("KeyUI_F.png", float4(-35, 0, -1));
	NoteActor->Off();

	{
		ItemPlatform0 = CreateComponent<GameEngineCollision>((int)CollisionOrder::Platform_Half);
		ItemPlatform0->GetTransform()->SetLocalPosition(float4(-402, 78, 0));
		ItemPlatform0->GetTransform()->SetLocalScale(float4(70, 15, 1));
		ItemPlatform0->SetColType(ColType::AABBBOX2D);
	
		ItemPlatform1 = CreateComponent<GameEngineCollision>((int)CollisionOrder::Platform_Half);
		ItemPlatform1->GetTransform()->SetLocalPosition(float4(-233, 78, 0));
		ItemPlatform1->GetTransform()->SetLocalScale(float4(70, 15, 1));
		ItemPlatform1->SetColType(ColType::AABBBOX2D);

		ItemPlatform2 = CreateComponent<GameEngineCollision>((int)CollisionOrder::Platform_Half);
		ItemPlatform2->GetTransform()->SetLocalPosition(float4(-65, 78, 0));
		ItemPlatform2->GetTransform()->SetLocalScale(float4(70, 15, 1));
		ItemPlatform2->SetColType(ColType::AABBBOX2D);

		ItemPlatform3 = CreateComponent<GameEngineCollision>((int)CollisionOrder::Platform_Half);
		ItemPlatform3->GetTransform()->SetLocalPosition(float4(105, 78, 0));
		ItemPlatform3->GetTransform()->SetLocalScale(float4(70, 15, 1));
		ItemPlatform3->SetColType(ColType::AABBBOX2D);
	}

	CreateTalkScript();
}

//#include "GameEngineActorGUI.h"

void ShopCollector::Update(float _DeltaTime)
{
	//std::shared_ptr<GameEngineActorGUI> Ptr = GameEngineGUI::FindGUIWindowConvert<GameEngineActorGUI>("GameEngineActorGUI");
	//Ptr->SetTarget(ItemPlatform0->GetTransform());
	//Ptr->On();

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

void ShopCollector::SpriteLoad()
{
	if (nullptr == GameEngineSprite::Find("Collector_Idle.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("7_Shop");
		Path.Move("Npc");
		Path.Move("Collector");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Collector_Idle.png").GetFullPath(), 5, 1);
	}
}

void ShopCollector::CreateTalkScript()
{
	TalkScripts.resize(4);

	TalkScripts[0] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};

		std::function<void()> Talk2 = [this, TalkEnd]()
		{
			NpcTalkBox->SetTalkMainText(L"당신 역시 굉장히 특별한 영혼을 지닌 모양이에요.", TalkEnd);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"이 장소는 특별해서 아무나 올 수 있는 곳이 아니에요.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"여기 오는 손님은 오랜만이네요. 환영해요. 아름다운 장소죠?", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"가는 김에... 그 오우거 녀석도 한번 봐야겠군요.", TalkEnd);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"혹시 또 아나요. 새로운 연줄을 소개해 줘서 장물의 퀄리티가 더 올라갈지.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"바깥이 조금 잠잠해진다면, 마녀를 한번 보러 가야겠어요. 그녀와의 대화는 얻어 가는 게 정말 많거든요.", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"같은 스켈레톤이라서 뭔가 통하는 게 있을 줄 알았는데요.", TalkEnd);
		};

		NpcTalkBox->SetTalkMainText(L"머리가 없는 스켈레톤과 이야기는 나눠보셨나요?", Talk1);
		NpcTalkBox->ButtonDisable();
	};

	TalkScripts[3] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};

		std::function<void()> Talk2 = [this, TalkEnd]()
		{
			NpcTalkBox->SetTalkMainText(L"구매를 원하시나요? 골드로만 받습니다.", TalkEnd);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"이곳에서는 약탈당할 위험도 없으니, 천천히 구경하시죠", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"제 수집품들은 하모니아 대륙 최고의 물건들만 이루어져 있습니다.", Talk1);
		NpcTalkBox->ButtonDisable();
	};
}

void ShopCollector::PlayNextScript()
{
	++TalkScriptNumber;

	if (TalkScripts.size() <= TalkScriptNumber)
	{
		TalkScriptNumber = 0;
	}

	TalkScripts[TalkScriptNumber]();
}

void ShopCollector::TalkEndCallback()
{
	NpcTalkBox->Off();
	GetContentLevel()->CallEvent("PlayerInputUnlock");
	GetContentLevel()->CallEvent("StoryFadeOut");
	GetContentLevel()->CallEvent("PlayerFrameActive");
	GetContentLevel()->CallEvent("UseKeyOn");
}