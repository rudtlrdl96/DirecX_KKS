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
	NpcTalkBox->AddButton("��ȭ", [this]() {PlayNextScript(); });

	NpcTalkBox->SetTalkBoxName("������", float4(2, 0), float4(130, 34));

	NpcTalkBox->AddMainText(L"��𿡼��� �� �� ���ǵ��� �ž�! �� ���� ���� �� ���� ��ȯ�Ѵٴϱ�!");
	NpcTalkBox->Off();

	TalkEventCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::UseEvent);
	TalkEventCol->SetColType(ColType::AABBBOX2D);
	TalkEventCol->GetTransform()->SetLocalScale(float4(160, 160, 1));
	TalkEventCol->GetTransform()->SetLocalPosition(float4(3, -80));

	NoteActor = GetLevel()->CreateActor<FieldNoteActor>();
	NoteActor->GetTransform()->SetParent(GetTransform());
	NoteActor->GetTransform()->SetLocalPosition(float4(0, -171, -100.0f));
	NoteActor->SetText("�� ��ȭ�ϱ�");
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
			NpcTalkBox->SetTalkMainText(L"����� ���� ���� ������.", TalkEnd);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"���ž��� ����ġ�� ���� �쿬���� �̰����� ���Դµ�, �ٵ� ģ���ϰ� �����ֳ�. �� �����̾�.", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"ó������ ���� ���������� �� �� �ǿ��ٰ� �׷� �� �˾Ҵµ�, ���߿��� ���õ����� �����ϴ����.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"ó���� ���ϰ� ������ ���� ���ͼ� ���� ������. �ٵ� ��Ʈ���� ��� �� �ѾƳ��� �ϴ� �ž�.", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"�ƹ��� ��� �� ��... �ƹ���...", TalkEnd);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"�� �׾������, �³׵� ���� ì������?", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"�³׵� ū ���� ǰ�� �� ������ ������ �������� �� ��������? ���� �׷��� �ʴ� ��縸ŭ�� ������ ��ģ �̰� ���̳� �־�?", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"�� ���谡�� ���ݾ�? ��¥ �ҽ��� ����̴�. ���� ���� ��� ������ �������� �Ӹ��� �̻����� �ž�.", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"�׳�� ������ �ٷ�����, �� �׷������� �� �𸣰ڳ�.", TalkEnd);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"���� ��¥�� �޾ư��� �ʾ�. ������ ��� ���� ���ִ����. ���� ����! ������ �𸣴� ������ �����ε� ���̾�. �׳� �ܿ��� �ƹ��� ��� ���� �ʴµ�.", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"������ �� ����ó�� ���� �༮�� ���� �̰��� ���� ��. �׸��� �����Լ� ���� �������� �޾ư�.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"������ ������ ����? ���� �߿��� ������ ����.", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"�׷��� ���� ������ �� ����.", TalkEnd);
		};

		std::function<void()> Talk4 = [this, Talk5]()
		{
			NpcTalkBox->SetTalkMainText(L"�����̶�⿣... �� ����?", Talk5);
		};

		std::function<void()> Talk3 = [this, Talk4]()
		{
			NpcTalkBox->SetTalkMainText(L"...", Talk4);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"���� ��������.", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"�༮���� ����� �����ϸ鼭 ����! �̰��� Į������ �����̴�! �ϰ� �ڶ��ϴµ�, �װ� ��� ���� �־�?", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"��... �¾�. ���� ���� Į���¿��� ������ �� ���ƾ�. �׷��� ��� �� �ʹ��Ѵ�.", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"Ȥ�� ���� ���� ������ �׷����� �� �� �� �ְڴ�?", TalkEnd);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"�ΰ� ������ ���� �ӹ��� �� �־ �׷� �ǰ�? �ƴϸ� ������ ������ �����ϰ� ���� �ӹ����� �� �����?", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"���� ���� ���� �� ģ������ �ξ� �̻��� ���̴� �� ���� ������.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"���� �ִ� ģ������ �׷��µ�, ���� ���� �̻��ϴٳ�.", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"��ü �׳�� ������ �ٽ� ������...", TalkEnd);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"���� �׳� ��� �ָӴϷ� ����... ���� ���� ���� ���� �ɱ�.", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"�� ���� ������ ���� �������ϸ� �����ϴٴ� ���� �ϴ���. �� �ƹ������� �ʾ�. �ƹ��͵� �������� �ʴ´ٰ�.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"�׳డ ������ ������ Ư���� ���� �����ٰ� �ϴ���.", Talk1);
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