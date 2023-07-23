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
	NpcTalkBox->AddButton("��ȭ", [this]() {PlayNextScript(); });

	NpcTalkBox->SetTalkBoxName("������", float4(2, 0), float4(130, 34));

	NpcTalkBox->AddMainText(L"�ݰ����ϴ�. ���̷��� �ҳ�.");
	NpcTalkBox->Off();

	TalkEventCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::UseEvent);
	TalkEventCol->SetColType(ColType::AABBBOX2D);
	TalkEventCol->GetTransform()->SetLocalScale(float4(165, 165, 1));
	TalkEventCol->GetTransform()->SetLocalPosition(float4(366, 87));

	NoteActor = GetLevel()->CreateActor<FieldNoteActor>();
	NoteActor->GetTransform()->SetParent(GetTransform());
	NoteActor->GetTransform()->SetLocalPosition(float4(375, -12, -100.0f));
	NoteActor->SetText("�� ��ȭ�ϱ�");
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
			NpcTalkBox->SetTalkMainText(L"��� ���� ������ Ư���� ��ȥ�� ���� ����̿���.", TalkEnd);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"�� ��Ҵ� Ư���ؼ� �ƹ��� �� �� �ִ� ���� �ƴϿ���.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"���� ���� �մ��� �������̳׿�. ȯ���ؿ�. �Ƹ��ٿ� �����?", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"���� �迡... �� ����� �༮�� �ѹ� ���߰ڱ���.", TalkEnd);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"Ȥ�� �� �Ƴ���. ���ο� ������ �Ұ��� �༭ �幰�� ����Ƽ�� �� �ö���.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"�ٱ��� ���� ���������ٸ�, ���ฦ �ѹ� ���� ���߰ھ��. �׳���� ��ȭ�� ��� ���� �� ���� ���ŵ��.", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"���� ���̷����̶� ���� ���ϴ� �� ���� �� �˾Ҵµ���.", TalkEnd);
		};

		NpcTalkBox->SetTalkMainText(L"�Ӹ��� ���� ���̷���� �̾߱�� �������̳���?", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"���Ÿ� ���Ͻó���? ���θ� �޽��ϴ�.", TalkEnd);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"�̰������� ��Ż���� ���赵 ������, õõ�� �����Ͻ���", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"�� ����ǰ���� �ϸ�Ͼ� ��� �ְ��� ���ǵ鸸 �̷���� �ֽ��ϴ�.", Talk1);
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