#include "PrecompileHeader.h"
#include "ShopHeadless.h"
#include "NPC_TalkBox.h"
#include "FieldNoteActor.h"


ShopHeadless::ShopHeadless()
{
}

ShopHeadless::~ShopHeadless()
{
}


void ShopHeadless::CallUseEvent()
{
	NpcTalkBox->ButtonActive();
	NpcTalkBox->On();
}

void ShopHeadless::Start()
{
	BaseNPC::Start();

	if (nullptr != GetLevel()->GetCamera((int)CameraOrder::MiniMap))
	{
		MinimapImageRender = CreateComponent<ContentMinimapRender>();
		MinimapImageRender->SetTexture("MinimapImage.png");
		MinimapImageRender->ColorOptionValue.PlusColor = float4(0.0f, 0.784f, 0.0f, 0.0f);
		MinimapImageRender->GetTransform()->SetLocalPosition(float4(34, 52, 0));
		MinimapImageRender->GetTransform()->SetLocalScale(float4(65, 90, 1));
	}

	MainRender->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Headless_Idle.png", .ScaleToTexture = true });
	MainRender->CreateAnimation({ .AnimationName = "WithHead", .SpriteName = "Headless_WithHead.png", .ScaleToTexture = true });
	PlayAnimation("Idle", false);
	NpcTalkBox = GetLevel()->CreateActor<NPC_TalkBox>();
	NpcTalkBox->GetTransform()->SetParent(GetTransform());
	NpcTalkBox->GetTransform()->SetWorldPosition(float4(0, -300, -110.0f));
	NpcTalkBox->SetButtonInterval(float4(0, 35));
	NpcTalkBox->AddButton("��ȭ", [this]() {PlayNextScript(); });

	NpcTalkBox->SetTalkBoxName("��帮��", float4(2, 0));

	NpcTalkBox->AddMainText(L"�ȳ� ģ��! �� �̾߱� �� �� ��� ����?");
	NpcTalkBox->Off();

	TalkEventCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::UseEvent);
	TalkEventCol->SetColType(ColType::AABBBOX2D);
	TalkEventCol->GetTransform()->SetLocalScale(float4(165, 165, 1));
	TalkEventCol->GetTransform()->SetLocalPosition(float4(50, 93));

	NoteActor = GetLevel()->CreateActor<FieldNoteActor>();
	NoteActor->GetTransform()->SetParent(GetTransform());
	NoteActor->GetTransform()->SetLocalPosition(float4(46, 0, -100.0f));
	NoteActor->SetText("�� ��ȭ�ϱ�");
	NoteActor->AddKeyImage("KeyUI_F.png", float4(-35, 0, -1));
	NoteActor->Off();

	CreateTalkScript();
}

//#include "GameEngineActorGUI.h"

void ShopHeadless::Update(float _DeltaTime)
{
	//std::shared_ptr<GameEngineActorGUI> Ptr = GameEngineGUI::FindGUIWindowConvert<GameEngineActorGUI>("GameEngineActorGUI");
	//Ptr->SetTarget(NoteActor->GetTransform());
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

void ShopHeadless::SpriteLoad()
{
	if (nullptr == GameEngineSprite::Find("Headless_Idle.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("7_Shop");
		Path.Move("Npc");
		Path.Move("Headless");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Headless_Idle.png").GetFullPath(), 8, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Headless_WithHead.png").GetFullPath(), 8, 1);
	}
}

void ShopHeadless::CreateTalkScript()
{
	TalkScripts.resize(8);

	TalkScripts[0] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};

		std::function<void()> Talk3 = [this, TalkEnd]()
		{
			NpcTalkBox->SetTalkMainText(L"���� �ڴ� ���߿� �ϰ� ���� ���� �Ѵٴ� ���� �����. ���� ���� �� ���� �� �Ȱ� ������, �׷��� �� ���� �� �ð� �ƴϴ�?", TalkEnd);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"������ �̺ұ��� ���� �ִ���ϱ�? ���� ������ �ʾ�? �ϰ� ���� ���� �� �ϸ鼭 ����� �ڴ°ž�!", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"�� ��°�δ� ��𼱰� ������ ������..��� �ߴ���? ������ �����ϰ� �ִ��. ������ �� �𸣰����� ��� �����Ѵ� �ϴ����. �ٵ� ���� �׷��� �ϰ� �ִµ� �༮�� ���� �ڰ� �ִ� �� �ƴϰھ�?", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"����. ���� ��鼭 ���� �����ٰ� ������ ���̷����� �� �־�. ù ��°�δ� ���� ���ռ��� �ִ� �������̾�. ���� ����԰� ������ Į �ؾ��� ���ع��ȴޱ�? �Ӹ� ��絵 ���ְ� ���̾�.", Talk1);
		NpcTalkBox->ButtonDisable();
	};

	TalkScripts[1] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};

		std::function<void()> Talk4 = [this, TalkEnd]()
		{
			NpcTalkBox->SetTalkMainText(L"ȭ���� �� ����� ������? �׷��� ���� �� ���쵵 Ȱ�� ��µ�, �༮���� �Ⱥ� ������!", TalkEnd);
		};

		std::function<void()> Talk3 = [this, Talk4]()
		{
			NpcTalkBox->SetTalkMainText(L"���� ���ݰ� ȭ����� ����ġ�� ���忡�� �޴� �� ����. ���� �Ӹ��� �־��� ���� �ص� ȭ���� �� �Ӹ��� �������ߴٴϱ�.", Talk4);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"�׷��� ���� ���� ������ �󸶳� �������? �ƴϴ�. ������� �ϸ� ���忡�� �޴� ������ ������ �ϰھ�.", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"��ġ������ ����, �Ƿ��� ü���� �ؾ� �ǳ�? �׷��� ���� ��ġ�����ε� �� ���� �ֳ�. �� ��� ��Ұ������� �ְŵ�.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"�� ����, �� ���� ���ռ��� ������ ���� �ɰ��� ������ �ִٰ� ������. ��. ���� ������ ���ռ����� ���� ���� ��ġ�� ����?", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"���� �� ������ ���� ���� ���� ������ ������ �����ؾ� �ϰŵ�. ���� �� ���̷����̶� �� ���� ������! �׸��� ������ �Ӹ����� ������!", TalkEnd);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"������ ���̶�... ���� ����� �ڵ��� ���� ���� ���Ҵµ� ��°�� ���� �� ���� ���� ���� �ɱ�? ���� ���� ������ Ȯ���� �ڵ��� �ִٸ� �׵�� �̾߱⸦ ���� ���� �;�!", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"���� ������� �ʾ�? �� �� �ο�⵵ ���� ������ �� ���� �й�ۿ� ���ٴ�. ������ ���� ���� �����Ѵٸ� ���� �ƴұ�?", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"���� ������ �̾߱⸦ �� �ٰ�. ���� ���̷����� ������ ���� �� ���� ������ ����. �� ���� ���� �� �й��� ���� �� �� ����.", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"�� ��ġ���� ��� �ǳ� ģ��?", TalkEnd);
		};

		std::function<void()> Talk3 = [this, Talk4]()
		{
			NpcTalkBox->SetTalkMainText(L"�����ϱ� �� �����غ��� �� ��ũ �༮ �����ǵ� ���������� ��. ��ü �丮�� � ��ġ���� ������ �ִ��� �𸣰ڳ�.", Talk4);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"��� ���� ������ �� �� ��� ���� �� ���� Į������ �����糪 ������̶����. �׵� ������ �����ϱ�� �����ϰŵ�.", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"�Ӹ��� �� �������ĸ� �� �׳�� ������ �ο���. �׳��� ������ ����? �� Į���¿��� ���� �����ϴٴ� ��� ���ݾ�.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"����, �� �и��� �������� �Ӹ��� �־��� ģ��.", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"����� ������ �Ļ� �ڸ��� ���� ���� �ߴµ�, �׷��� �ʿ��� �� ������ �� �ؾ߰ڴ�. ��� �Ծ�� ���� �� ������?", TalkEnd);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"�����Դ´ٶ�... �׷��� ���� �� ������ �༮�� �Ļ��Ϸ� ����� �ߴµ�, ������ ����������� �ϴ����. �� �̹� �����Ծ��µ� ���̾�.", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"���� �� �Ծ�� �ϳİ�? �װ� �����̶�� �ϴ°ǰ�. �� �ӻ� �� �����ݾ�! �����ϱ��. �� ��. �Ӹ��� ���� ������ ���� �����Ծ���.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"����! ���� �װ� ���̶�� �� ������ �׷��� �� ������ �� �ؾ߰ڴ�. ���� ���� ���� ���� �԰� ������ �ϴ� �ž� �� �ٺ���!", Talk1);
		NpcTalkBox->ButtonDisable();
	};

	TalkScripts[5] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};

		std::function<void()> Talk4 = [this, TalkEnd]()
		{
			NpcTalkBox->SetTalkMainText(L"�ٸ��ٴ� �� Ʋ���ٴ� �Ͱ� ���̰� �ִµ�, �� ��� ������?", TalkEnd);
		};

		std::function<void()> Talk3 = [this, Talk4]()
		{
			NpcTalkBox->SetTalkMainText(L"���డ ������ ������ŵ�. ��ī���̿��� ���� ���������� �ִٰ�. ���������� ������ �� ���鲨��. ��ǻ� �ΰ��ε�� �ٸ� �ٰ� �����ϱ�.", Talk4);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"����� ��� �˱Ⱑ ���ƿ��µ� ������ ���� �� �����̶���? �༮�� ������ ��𼱰� ���Ű���. Į���¿��� ������ ���� ��ī���̰� �ִٴ� �ҹ��� �־�.", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"�ٵ� ���� Į���� �༮��� �´ڶ߸��� ���� �Ŀ��� �� ��������, �ο�� ���� ������ ����á��. �׸��� ��縦 ������.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"���� ����. ���� ���� �����ϱ� ���� �и��� ��ũ �༮�� �� ���ö��� �ΰ����� ���ٱ�.", Talk1);
		NpcTalkBox->ButtonDisable();
	};

	TalkScripts[6] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};

		std::function<void()> Talk4 = [this, TalkEnd]()
		{
			NpcTalkBox->SetTalkMainText(L"���� ����. � �� �����ӿ� ���� ���� �ڷḦ ��ǥ�ؾ߰ھ�.", TalkEnd);
		};

		std::function<void()> Talk3 = [this, Talk4]()
		{
			NpcTalkBox->SetTalkMainText(L"�� ������ ���� �˾�? �����ӵ��� ���� ����! �׷����� ���� ���� ���. �����ӵ��� ���� ��� ������ �� �ִٴ� �ž�!", Talk4);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"���� �ִ� ����鸸 ���̷����� �ȴٴ� �� ���� ����� �ʾ�? ���� �� �� ���� �� �־�. �����ӵ��� ���̷����� ���� �ʴ´ٴ� ���!", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"���̷������ ��°�� ���̷����� �Ǵ��� �˾�? ���� �˾Ƴ���. ������ ���� �����߾�. �츮�� ���� �ֱ� �����̾�.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"���� ����. �� ���̷��濡 ���� ������ ��ǥ�� �����̾�.", Talk1);
		NpcTalkBox->ButtonDisable();
	};

	TalkScripts[7] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};

		std::function<void()> Talk4 = [this, TalkEnd]()
		{
			NpcTalkBox->SetTalkMainText(L"�׸��� ���� ���ƿԴµ� �׳డ �׷�����. �� �Ӹ� �����?", TalkEnd);
		};

		std::function<void()> Talk3 = [this, Talk4]()
		{
			NpcTalkBox->SetTalkMainText(L"�׶� ������� ������ ���� ������� ������. �� �� �ü����� ȭ�� ���ʸ� ���߳��� �����ϰ� ���߾�.", Talk4);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"�׳డ �� �ŷ� �ִ� �� ������. �׷����� �׷��� ���� ������ �� ����. �� ���� ���� �ʾ�. Į���� ���� ���� ���� �ѷ��׿������� ������� ���� �ʾҾ�.", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"�αٴ�ٴ� �� �������� ����� ������ ���� ���� �Ҹ���µ�, Ȥ�� ���� ��������? �� �ؿ� �ִ� ������ �༮�� �ƴϰ���?", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"�����? �����Լ� ���� ����ڵ� �Ҹ�. ���� �и��� ���̷����̰�, ������ ���� �ٵ� ��𼱰� ��� �αٴ�� �Ҹ��� ����.", Talk1);
		NpcTalkBox->ButtonDisable();
	};
}

void ShopHeadless::PlayNextScript()
{
	++TalkScriptNumber;

	if (TalkScripts.size() <= TalkScriptNumber)
	{
		TalkScriptNumber = 0;
	}

	TalkScripts[TalkScriptNumber]();
}

void ShopHeadless::TalkEndCallback()
{
	NpcTalkBox->Off();
	GetContentLevel()->CallEvent("PlayerInputUnlock");
	GetContentLevel()->CallEvent("StoryFadeOut");
	GetContentLevel()->CallEvent("PlayerFrameActive");
	GetContentLevel()->CallEvent("UseKeyOn");
}