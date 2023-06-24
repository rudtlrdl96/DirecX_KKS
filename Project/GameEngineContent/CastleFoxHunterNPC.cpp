#include "PrecompileHeader.h"
#include "CastleFoxHunterNPC.h"
#include "NPC_TalkBox.h"
#include "FieldNoteActor.h"

CastleFoxHunterNPC::CastleFoxHunterNPC()
{
}

CastleFoxHunterNPC::~CastleFoxHunterNPC()
{
}

void CastleFoxHunterNPC::Start()
{
	BaseNPC::Start();

	if (nullptr == GameEngineTexture::Find("FoxHunter_UI_Talk.png"))
	{
		GameEngineDirectory Path;
		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("2_Castle");
		Path.Move("Npc");
		Path.Move("FoxHunter");
		Path.Move("FoxHunter_UI_Talk");

		GameEngineTexture::Load(Path.GetPlusFileName("FoxHunter_UI_Talk.png").GetFullPath());
	}


	MainRender->CreateAnimation({.AnimationName = "Idle", .SpriteName = "FoxHunter_CastleIdle.png", .ScaleToTexture = true});
	PlayAnimation("Idle", false);
	NpcTalkBox = GetLevel()->CreateActor<NPC_TalkBox>();
	NpcTalkBox->GetTransform()->SetParent(GetTransform());
	NpcTalkBox->GetTransform()->SetWorldPosition(float4(0, -300, -110.0f));
	NpcTalkBox->SetButtonInterval(float4(0, 35));
	NpcTalkBox->AddButton("��ȭ", [this]() {PlayNextScript(); });
	NpcTalkBox->AddButton("�Ӹ� �ޱ�", [this]() {});

	NpcTalkBox->SetTalkBoxName("��ȣ�� ��ɲ�", float4(2, 0));

	NpcTalkBox->AddMainText(L"���� ���� ���� �ɷȴµ�, �̷��� �ϳ��� �����ִ� ���� �ݹ� ����������.");
	NpcTalkBox->AddMainText(L"�� �༮�� �Ӹ����� ���Ƴ���� ���� �߿����� �ʾ�.");
	NpcTalkBox->AddMainText(L"�� �װ� Ư���ϴٰ� �����ϳ�? �� ���� �ִ� ����� �� ������ Ư������ ���� �ڰ� ��� ����?");
	NpcTalkBox->AddMainText(L"������ ������ ������ ���ҳ�?");
	NpcTalkBox->Off();

	TalkEventCol = CreateComponent<GameEngineCollision>();
	TalkEventCol->SetColType(ColType::AABBBOX2D);
	TalkEventCol->GetTransform()->SetLocalScale(float4(130, 150, 1));
	TalkEventCol->GetTransform()->SetLocalPosition(float4(-15, -180));

	if (false == GameEngineInput::IsKey("UseKey"))
	{
		GameEngineInput::CreateKey("UseKey", 'F');
	}

	NoteActor = GetLevel()->CreateActor<FieldNoteActor>();
	NoteActor->GetTransform()->SetParent(GetTransform());
	NoteActor->GetTransform()->SetLocalPosition(float4(-15, -275, -100.0f));
	NoteActor->SetText("F ��ȭ�ϱ�");
	NoteActor->Off();

	NpcImageRender = CreateComponent<GameEngineUIRenderer>();
	NpcImageRender->SetScaleToTexture("FoxHunter_UI_Talk.png");
	NpcImageRender->GetTransform()->SetLocalScale(NpcImageRender->GetTransform()->GetLocalScale() * 2.0f);

	NpcImageRender->GetTransform()->SetWorldPosition(float4(408, 67, -108));
	NpcImageRender->Off();

	GetContentLevel()->AddEvent("CastleReborn", GetActorCode(), [this]()
		{
			IsGiveItem = true;
		});

	CreateTalkScript();
}

void CastleFoxHunterNPC::Update(float _DeltaTime)
{
	if (true == NpcTalkBox->IsUpdate())
	{
		NpcImageRender->On();
		NoteActor->Off();
		return;
	}
	else
	{
		NpcImageRender->Off();
	}

	if (nullptr == TalkEventCol->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D))
	{
		NoteActor->Off();
		return;
	}
	else
	{
		NoteActor->On();
	}

	if (true == GameEngineInput::IsDown("UseKey"))
	{
		if (true == IsGiveItem)
		{
			IsGiveItem = false;
		}
		else
		{
			NpcTalkBox->ButtonActive();
			NpcTalkBox->On();
		}
	}
}

void CastleFoxHunterNPC::SpriteLoad()
{
	if (nullptr == GameEngineSprite::Find("FoxHunter_CastleIdle.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("2_Castle");
		Path.Move("Npc");
		Path.Move("FoxHunter");
		Path.Move("Sheet");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("FoxHunter_CastleIdle.png").GetFullPath(), 8, 1);
	}

}

void CastleFoxHunterNPC::Destroy()
{
	GetContentLevel()->RemoveEvent("CastleReborn", GetActorCode());
}

void CastleFoxHunterNPC::CreateTalkScript()
{
	TalkScripts.resize(3);

	TalkScripts[0] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};

		std::function<void()> Talk1 = [this, TalkEnd]()
		{
			NpcTalkBox->SetTalkMainText(L"�Ѷ��� �״�� �����ͼ� �����ϴ� ����� ����غôµ�, ���մԲ� ũ�� ȥ�� ���ķ� ������ �� ��.", TalkEnd);
		};

		NpcTalkBox->SetTalkMainText(L"�ΰ� ��� �Ӹ����� �� �̷��� ���� ����? �Ʊ��ڱ��� ���� �־� ��� ������ �ȴٰ�", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"�׸� �⸮���� �ϴ� ������ ���� �Ӹ��� ��� �Ծ�. ����?", TalkEnd);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"�˵� �� �ֵθ���, Ȱ�� �ſ� �� ���, �Ӹ��� ��Ư�ߴµ�... ���� ������ ���� �����Ѱ�...", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"���� ���� �� ģ���� �ſ� ������ ���簡 �־��µ�, �̻��� ������ �ɷ��� 3�� ���� ���ο��ϴٰ� ���� �ŵ׾�.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"�Ѷ��� �뺴�� �Ǿ� �ϸ�Ͼ� �̰������� ������ ������ �����߾���.", Talk1);
		NpcTalkBox->ButtonDisable();
	};

	TalkScripts[2] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};

		std::function<void()> Talk2 = [this, TalkEnd]()
		{
			NpcTalkBox->SetTalkMainText(L"���� �� �׾���.", TalkEnd);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"�ٵ� �ڱ� �ڽ��� ���� �߿��ϴٰ� �����ؼ� ����ũ�� ����. ���� �������� �󸶳� ��������.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"�Ѷ��� ���� �� �������� ���߾���. ��ũ, ������, ������� �� ���Ҵµ� �츮 ȣ������ ���� ������ �� �����.", Talk1);
		NpcTalkBox->ButtonDisable();
	};
}

void CastleFoxHunterNPC::PlayNextScript()
{
	++ScriptNumber;

	if (TalkScripts.size() <= ScriptNumber)
	{
		ScriptNumber = 0;
	}

	TalkScripts[ScriptNumber]();
}

void CastleFoxHunterNPC::TalkEndCallback()
{
	NpcTalkBox->Off();
	GetContentLevel()->CallEvent("PlayerInputUnlock");
	GetContentLevel()->CallEvent("StoryFadeOut");
	GetContentLevel()->CallEvent("PlayerFrameActive");
}
