#include "PrecompileHeader.h"
#include "CastleWitchNPC.h"
#include "NPC_TalkBox.h"
#include "FieldNoteActor.h"

CastleWitchNPC::CastleWitchNPC()
{
}

CastleWitchNPC::~CastleWitchNPC()
{
}

void CastleWitchNPC::Start()
{
	BaseNPC::Start();

	if (nullptr == GameEngineTexture::Find("Witch_UI_Talk.png"))
	{
		GameEngineDirectory Path;
		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("2_Castle");
		Path.Move("Npc");
		Path.Move("Witch");
		Path.Move("Witch_UI_Talk");

		GameEngineTexture::Load(Path.GetPlusFileName("Witch_UI_Talk.png").GetFullPath());
	}

	MainRender->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Witch_Castle_Idle.png", .ScaleToTexture = true });
	PlayAnimation("Idle", false);
	NpcTalkBox = GetLevel()->CreateActor<NPC_TalkBox>();
	NpcTalkBox->GetTransform()->SetParent(GetTransform());
	NpcTalkBox->GetTransform()->SetWorldPosition(float4(0, -300, -110.0f));
	NpcTalkBox->SetButtonInterval(float4(0, 35));
	NpcTalkBox->AddButton("��ȭ", [this]() {PlayNextScript(); });
	NpcTalkBox->AddButton("Ư���ο�", [this]() {});

	NpcTalkBox->SetTalkBoxName("����", float4(3, 0));

	NpcTalkBox->AddMainText(L"�׷���. �� ���⺸�� ���̰� �ſ� ���ƿ�. �� �׷� �� ����?");
	NpcTalkBox->AddMainText(L"���ռ��� ���⺸�� ������ ���� ���� ��Ҷ��ϴ�.");
	NpcTalkBox->AddMainText(L"���� ������ ����? ������ �� ���̶�?");
	NpcTalkBox->Off();

	TalkEventCol = CreateComponent<GameEngineCollision>();
	TalkEventCol->SetColType(ColType::AABBBOX2D);
	TalkEventCol->GetTransform()->SetLocalScale(float4(120, 200, 1));
	TalkEventCol->GetTransform()->SetLocalPosition(float4(185, -155));

	if (false == GameEngineInput::IsKey("UseKey"))
	{
		GameEngineInput::CreateKey("UseKey", 'F');
	}

	NoteActor = GetLevel()->CreateActor<FieldNoteActor>();
	NoteActor->GetTransform()->SetParent(GetTransform());
	NoteActor->GetTransform()->SetLocalPosition(float4(185, -270, -100.0f));
	NoteActor->SetText("F ��ȭ�ϱ�");
	NoteActor->Off();

	NpcImageRender = CreateComponent<GameEngineUIRenderer>();
	NpcImageRender->SetScaleToTexture("Witch_UI_Talk.png");
	NpcImageRender->GetTransform()->SetLocalScale(NpcImageRender->GetTransform()->GetLocalScale() * 2.0f);

	NpcImageRender->GetTransform()->SetWorldPosition(float4(411, 40, -108));
	NpcImageRender->Off();

	CreateTalkScript();
}

void CastleWitchNPC::Update(float _DeltaTime)
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
		NpcTalkBox->ButtonActive();
		NpcTalkBox->On();
	}
}

void CastleWitchNPC::SpriteLoad()
{
	if (nullptr == GameEngineSprite::Find("Witch_Castle_Idle.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("2_Castle");
		Path.Move("Npc");
		Path.Move("Witch");
		Path.Move("Sheet");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Witch_Castle_Idle.png").GetFullPath(), 6, 1);
	}

}

void CastleWitchNPC::CreateTalkScript()
{
	TalkScripts.resize(7);

	TalkScripts[0] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};

		std::function<void()> Talk1 = [this, TalkEnd]()
		{
			NpcTalkBox->SetTalkMainText(L"�� ��ü�����ε� ū ���輺�� ����⿡ �ſ� �����ؼ� �ٷ�� �մϴ�. �ùٸ��� ������� ���ϴ� �ڴ� ������ ���⸸ �ص� ���� ������ �ް� �Ǵϱ��.", TalkEnd);
		};

		NpcTalkBox->SetTalkMainText(L"������ �����ϴ� �ڴ� ���� ������ ���� ��� �˴ϴ�. �׷��� ������ ������� ���Ƹ԰� �ǰ� �̻��� �Ұ� ����� ������ �������� �ֺ����� �ĸ길�� ���� �˴ϴ�.", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"Ȥ�� ���� �ֳ��� ?", TalkEnd);
		};		
		
		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"�׷��� ������ ����̰� �Ǿ �� ������ ã���� ������... ������ ���� ������ �������� �� ���ִٴ� �� ������ �ְڳ׿�.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"����̵��� �� �� ���� �ൿ�� ���� ���ϰ� �ؿ�. �� ������ 50�� ���� �����غ����� �˾Ƴ��� ������.", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"�츮�� ��� ������ �ϳ��� �Ǿ� �ٽ� �� ���ռ� ������ ���� ������ �մϴ�.", TalkEnd);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"���� ���մ��� ���Ŵٸ� ũ�� ���Ͻ����� �𸨴ϴ�...", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"��ŵ� �˰����� ������ ���ռ��� ������ ����� ���� �޶������.", Talk1);
		NpcTalkBox->ButtonDisable();
	};

	TalkScripts[3] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};

		std::function<void()> Talk1 = [this, TalkEnd]()
		{
			NpcTalkBox->SetTalkMainText(L"�׶� ���� ��� ������ �ǿ� �� �ϳ��� ���̷����� ���ʶ�� �ҹ��� �־��.", TalkEnd);
		};

		NpcTalkBox->SetTalkMainText(L"�Ѷ� �̰�, ���ռ� �ֻ����� �ǿ���θ� ���� ���� �� ��� ���� ���� ��������ϴ�.", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"����, ��ŵ� ��ȸ�� �Ǹ� ���� ������ �������� �� ��õ�ҰԿ�.", TalkEnd);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"���� ������ ���� ���� ������ �ٶ󺸴� �ڿ����� ��� ���ȴ�ϴ�.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"���� ���ռ��� ������ ����, ��� �̰������� ������ ���� ������ �׾Ҿ��.", Talk1);
		NpcTalkBox->ButtonDisable();
	};

	TalkScripts[5] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};

		std::function<void()> Talk1 = [this, TalkEnd]()
		{
			NpcTalkBox->SetTalkMainText(L"���� �� �η縶������ �����Ͽ� �����ϰ� �����ϰ� �����Ѵ�ϴ�. �� ���� �츮 ��ο��� ������ �� �� �ֵ��� �����ϰ� ����Ϸ� ����ϰ� �־��.", TalkEnd);
		};

		NpcTalkBox->SetTalkMainText(L"�ϸ�Ͼ� ��� �̰��������� ��� ������ �η縶������ ���� �ִ�ϴ�. �� �η縶���鿡�� ������ ������ ���� �������.", Talk1);
		NpcTalkBox->ButtonDisable();
	};

	TalkScripts[6] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};

		std::function<void()> Talk2 = [this, TalkEnd]()
		{
			NpcTalkBox->SetTalkMainText(L"������ ���� ������? ����. �۽��... ���� ���� �Ѿ��ޱ��?", TalkEnd);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"�����̵� ���� �����̶� ������ �����⿡, �� ������ �ϴ� �� ������� �ʾ���.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"���� ������ ������ ���� ���� ���̿��� ����.", Talk1);
		NpcTalkBox->ButtonDisable();
	};
}

void CastleWitchNPC::PlayNextScript()
{
	++ScriptNumber;

	if (TalkScripts.size() <= ScriptNumber)
	{
		ScriptNumber = 0;
	}

	TalkScripts[ScriptNumber]();
}

void CastleWitchNPC::TalkEndCallback()
{
	NpcTalkBox->Off();
	GetContentLevel()->CallEvent("PlayerInputUnlock");
	GetContentLevel()->CallEvent("StoryFadeOut");
	GetContentLevel()->CallEvent("PlayerFrameActive");
}
