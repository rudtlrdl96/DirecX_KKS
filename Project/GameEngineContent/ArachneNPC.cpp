#include "PrecompileHeader.h"
#include "ArachneNPC.h"
#include "NPC_TalkBox.h"
#include "FieldNoteActor.h"

ArachneNPC::ArachneNPC()
{
}

ArachneNPC::~ArachneNPC()
{
}

void ArachneNPC::CallUseEvent()
{
	if (true == IsFirstTalk)
	{
		NpcTalkBox->On();
		PlayFirstTalkScript();
		IsFirstTalk = false;
	}
	else
	{
		NpcTalkBox->ButtonActive();
		NpcTalkBox->On();
	}
}

void ArachneNPC::Start()
{
	BaseNPC::Start();

	MainRender->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Arachne_Idle.png", .ScaleToTexture = true });
	MainRender->CreateAnimation({ .AnimationName = "Ready", .SpriteName = "Arachne_Ready.png", .ScaleToTexture = true });
	MainRender->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Arachne_Attack.png", .ScaleToTexture = true });


	PlayAnimation("Idle", false);

	NpcTalkBox = GetLevel()->CreateActor<NPC_TalkBox>();
	NpcTalkBox->GetTransform()->SetParent(GetTransform());
	NpcTalkBox->GetTransform()->SetWorldPosition(float4(0, -300, -110.0f));
	NpcTalkBox->SetButtonInterval(float4(0, 35));
	NpcTalkBox->AddButton("��ȭ", [this]() {PlayNextScript(); });
	NpcTalkBox->AddButton("����", [this]() {});

	NpcTalkBox->SetTalkBoxName("�ƶ�ũ��", float4(3, 0));

	NpcTalkBox->AddMainText(L"�׷�, ������. �������� �غ�Ǿ�����?");
	NpcTalkBox->Off();

	TalkEventCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::UseEvent);
	TalkEventCol->SetColType(ColType::AABBBOX2D);
	TalkEventCol->GetTransform()->SetLocalScale(float4(190, 200, 1));
	TalkEventCol->GetTransform()->SetLocalPosition(float4(-10, 101));

	NoteActor = GetLevel()->CreateActor<FieldNoteActor>();
	NoteActor->GetTransform()->SetParent(GetTransform());
	NoteActor->GetTransform()->SetLocalPosition(float4(-13, -20, -100.0f));
	NoteActor->SetText("�� ��ȭ�ϱ�");
	NoteActor->AddKeyImage("KeyUI_F.png", float4(-35, 0, -1));
	NoteActor->Off();

	CreateTalkScript();
	CreateBubbleScript();

	BubblePivot = CreateComponent<GameEngineComponent>();
	BubblePivot->GetTransform()->SetLocalPosition(float4(-25, 270, -100));
}

#include "GameEngineActorGUI.h"


void ArachneNPC::Update(float _DeltaTime)
{
	//std::shared_ptr<GameEngineActorGUI> Ptr = GameEngineGUI::FindGUIWindowConvert<GameEngineActorGUI>("GameEngineActorGUI");
	//
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

	if (0.0f <= BubbleTalkTime)
	{
		PlayBubble();
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

void ArachneNPC::SpriteLoad()
{
	if (nullptr == GameEngineSprite::Find("Arachne_Idle.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("3_ForestOfHarmony");
		Path.Move("Npc");
		Path.Move("Arachne");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Arachne_Idle.png").GetFullPath(), 9, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Arachne_Ready.png").GetFullPath(), 6, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Arachne_Attack.png").GetFullPath(), 8, 1);
	}

}

void ArachneNPC::CreateBubbleScript()
{
	BubbleScripts.resize(4);

	BubbleScripts[0] = "�׳డ �� ������ �ִٴ�...\n���� ������ ���̾�.";
	BubbleScripts[1] = "�������� ����ϴٸ�,\n���� ������.";
	BubbleScripts[2] = "���� ��ٷȴܴ�, ������.";
	BubbleScripts[3] = "����, ��ġ ���� �����ؼ�\n����� ���� ������.";
}

void ArachneNPC::PlayBubble()
{
	++BubbleScriptNumber;

	if (BubbleScripts.size() <= BubbleScriptNumber)
	{
		BubbleScriptNumber = 0;
	}

	if (nullptr != Bubble)
	{
		Bubble->Death();
		Bubble = nullptr;
	}

	Bubble = GetLevel()->CreateActor<SpeechBubble>();
	Bubble->GetTransform()->SetParent(GetTransform());

	Bubble->PlayBubble({
		.Target = DynamicThis<GameEngineActor>(),
		.Text = BubbleScripts[BubbleScriptNumber],
		.Pivot = BubblePivot->GetTransform()->GetLocalPosition(),
		.FontSize = 15,
		.LiveTime = 4.0f,
		.IsAutoScale = true });

	BubbleTalkTime = -10.0f;
}

void ArachneNPC::CreateTalkScript()
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
			NpcTalkBox->SetTalkMainText(L"�׳ุ �����ٸ� �� ������... ��, ������ ���� ���� ���� �ɷ� ���ַ�. ������.", TalkEnd);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"�ⲯ�ؾ� �ٸ��� �� ���ۿ� �ȵǴ� �༮����, �� �������� �ٶ󺸴� �� ������ �������� �ʾ�.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"�ΰ����� ���� ���ϴ� ������ ���� ������ ������ �ü��� ����������.", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"... �� �̾߱�� �ƴϴϱ� ���� �Ű� ���� �� ���� �ž�.", TalkEnd);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"�׷����� �Ծ࿡ ������ ä �Ϸ� �Ϸ� ��ư��� ���� ������ ������ �� ������.", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"�� �ͼ��� ��� �̴� ��� ���� �Ұ� ����� �Ź̰� �Ǿ� ������ ���ֹ��� ���� ��ƾ� ����.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"�츮 �Ẕ́������� ��Ʈ�� �� ���� �ͼ���� �Ծ��� �־�.", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"��, �� ���� �������� ��� ���ڰ� �޾Ƶ鿩�� ������ �ż��� �Ǿ����� ���̾�.", TalkEnd);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"��ġ �ȿ��� ���� ���� �Ͼ������ �ƹ��� ���� ������.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"�� �Ź��ٿ��� Ư���� ������ ���� �־�. �� �� �Ź��ٷ� ��ġ���� ����� ��.", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"���� ���� ��. ��� ��� �ϳ��ϳ��� ������ �ʰ� ����.", TalkEnd);
		};		

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"�׳�... �� ���� �ʰ�... ���� �� ���Դٴ� ����� ���࿡�� �����ֱ⳪ �ϸ� ��.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"�� ���� ����? ���� �ʴ� �� ���� �ž�.", Talk1);
		NpcTalkBox->ButtonDisable();
	};
}

void ArachneNPC::PlayNextScript()
{
	++TalkScriptNumber;

	if (TalkScripts.size() <= TalkScriptNumber)
	{
		TalkScriptNumber = 0;
	}

	TalkScripts[TalkScriptNumber]();
}

void ArachneNPC::TalkEndCallback()
{
	NpcTalkBox->Off();
	GetContentLevel()->CallEvent("PlayerInputUnlock");
	GetContentLevel()->CallEvent("StoryFadeOut");
	GetContentLevel()->CallEvent("PlayerFrameActive");
	GetContentLevel()->CallEvent("MinimapOn");
	GetContentLevel()->CallEvent("GoodsUIOn");
	GetContentLevel()->CallEvent("UseKeyOn");
}

void ArachneNPC::PlayFirstTalkScript()
{
	std::function<void()> TalkEnd = [this]()
	{
		TalkEndCallback();
	};

	std::function<void()> Talk8= [this, TalkEnd]()
	{
		NpcTalkBox->SetTalkMainText(L"�� ������ �޾Ҵٴ� ����... �ݵ�� �� ���࿡�� �����ϵ��� ��. ������ ���� ����. ���� �׸� ���� �������� ã�ƿ��Ŷ�.", TalkEnd);
	};
	std::function<void()> Talk7 = [this, Talk8]()
	{
		NpcTalkBox->SetTalkMainText(L"�װ� ������ �ٸ� �̵��� �Ӹ��� �������� �� �ٿ�, �׵��� ���� ���� ��ã���� ������. �׸��� �ϳ� ����ϵ���.", Talk8);
	};

	std::function<void()> Talk6 = [this, Talk7]()
	{
		NpcTalkBox->SetTalkMainText(L"�������� ��ƿ��ʶ�. ���� Ư���� ���� �����ָ�.", Talk7);
	};

	std::function<void()> Talk5 = [this, Talk6]()
	{
		NpcTalkBox->SetTalkMainText(L"�� ���� �� ������ ���ܶ�. ���� �ɷ��� �� ���� �༮��� ������ �� ������...", Talk6);
	};

	std::function<void()> Talk4 = [this, Talk5]()
	{
		NpcTalkBox->SetTalkMainText(L"�׷���... �� �տ� �� �Ӹ����� �ҽ��ϱ� ¦�� ������. ���� ���� ���̷��� �տ� �� ������ ���� ���� ������� ���ϰ� �ִٴ�...", Talk5);
	};


	std::function<void()> Talk3 = [this, Talk4]()
	{
		NpcTalkBox->SetTalkMainText(L"�� �ٸ� ���� �Ӹ��� �̿��Ͽ� ���� ��´���.", Talk4);
	};


	std::function<void()> Talk2 = [this, Talk3]()
	{
		NpcTalkBox->SetTalkMainText(L"��... �װ� �׷���.", Talk3);
	};

	std::function<void()> Talk1 = [this, Talk2]()
	{
		NpcTalkBox->SetTalkMainText(L"��ٸ��� �־���. ��... �����ֱ�� �߰ŵ�. ������ ���� �ʾ����� ���ھ�. �װ� ����� �׷��� ���� �ƴϴϱ� �Ű� ������.", Talk2);
	};

	NpcTalkBox->SetTalkMainText(L"�׷�, �ʱ���. �׳డ ���ϴ� ���� ���̷�����.", Talk1);
	NpcTalkBox->ButtonDisable();
}