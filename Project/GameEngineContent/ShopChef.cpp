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
	NpcTalkBox->AddButton("��ȭ", [this]() {PlayNextScript(); });

	NpcTalkBox->SetTalkBoxName("����", float4(3, 0));

	NpcTalkBox->AddMainText(L"�̺�! �ʹ� ��½ �����µ�? �̷��� '��'�� ���ھ�! ����!");
	NpcTalkBox->Off();

	TalkEventCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::UseEvent);
	TalkEventCol->SetColType(ColType::AABBBOX2D);
	TalkEventCol->GetTransform()->SetLocalScale(float4(200, 200, 1));
	TalkEventCol->GetTransform()->SetLocalPosition(float4(-101, 133));

	NoteActor = GetLevel()->CreateActor<FieldNoteActor>();
	NoteActor->GetTransform()->SetParent(GetTransform());
	NoteActor->GetTransform()->SetLocalPosition(float4(-100, 19, -100.0f));
	NoteActor->SetText("�� ��ȭ�ϱ�");
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
			NpcTalkBox->SetTalkMainText(L"�ٵ� ���� ������ ������� ������, �ʵ� �׷��� ������?", TalkEnd);
		};

		NpcTalkBox->SetTalkMainText(L"���� �ִ� Ÿ���� �Ű� ���� ��. ö���� � ���� ������ �߾���.", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"��! ��� ���� �� ��� ����?", TalkEnd);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"...", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"��� ��ٷ��� �غ��� �־�! �̰� �Ծ��. ���, ���� �ֳ�?", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"�ٵ� �� �׷��⿣ �ʹ� ������ ���� ���ִ°�!", TalkEnd);
		};

		NpcTalkBox->SetTalkMainText(L"��-���ϰ� �踦 ä����. ���� ����ؾ� �ο� �� �� �� �ִ� �ž�!", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"���� ����� ��� �Ӹ�, £�� ���ʸ��� ��￡ ���±���.", TalkEnd);
		};

		std::function<void()> Talk3 = [this, Talk4]()
		{
			NpcTalkBox->SetTalkMainText(L"��� �� �߷� �����̿� ��������µ�, ���ְ� �Ծ��� ����. ������ ��� ��������?", Talk4);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"�ƹ��� ���̶�����... �� ����� ��ũ�μ� ���� �״� ���� ���� �� ���� �ʰھ�? �������� ��ȣ�� �� �� �λ� �ְ��� ������ ������.", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"��� �� ����̵� ������ ���� ������? �ٴڿ� ������ �ִ� �ΰ��� �߰��߾�. ��½�� �ʴ����. ���� ����������, �׾��� �;� ������ ������ ����ֱ� �ϴ����? �ؽ��� �����������.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"�̽� �� �����ΰ�... �丮 ������ �ٴϰ� �־���. ���� ������ ������������ �ܶ� �ư� �����ϸ� �丮�� �ϰ� �־���.", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"���մԵ� ã�ƿͼ� ���� ��ð� ����, ���� �� ���� �Ӹ���!", TalkEnd);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"�������� ���� ���� ���� �����Ǹ� �˰� �ֱ⿡, � �� �������൵ �Ϻ��ϰ� �س��ٱ�!", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"������ �ϴ� �ͺ��� ����� ����Ḧ ���ϴ� �� �� �����.", Talk1);
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