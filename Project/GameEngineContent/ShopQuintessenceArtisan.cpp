#include "PrecompileHeader.h"
#include "ShopQuintessenceArtisan.h"
#include "NPC_TalkBox.h"
#include "FieldNoteActor.h"

ShopQuintessenceArtisan::ShopQuintessenceArtisan()
{
}

ShopQuintessenceArtisan::~ShopQuintessenceArtisan()
{
}

void ShopQuintessenceArtisan::CallUseEvent()
{
	NpcTalkBox->ButtonActive();
	NpcTalkBox->On();
}

void ShopQuintessenceArtisan::Start()
{
	BaseNPC::Start();

	if (nullptr != GetLevel()->GetCamera((int)CameraOrder::MiniMap))
	{
		MinimapImageRender = CreateComponent<ContentMinimapRender>();
		MinimapImageRender->SetTexture("MinimapImage.png");
		MinimapImageRender->ColorOptionValue.PlusColor = float4(0.0f, 0.784f, 0.0f, 0.0f);
		MinimapImageRender->GetTransform()->SetLocalPosition(float4(-11, -76, 0));
		MinimapImageRender->GetTransform()->SetLocalScale(float4(65, 90, 1));
	}

	MainRender->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "QuintessenceArtisanIdle.png", .ScaleToTexture = true });

	PlayAnimation("Idle", false);
	NpcTalkBox = GetLevel()->CreateActor<NPC_TalkBox>();
	NpcTalkBox->GetTransform()->SetParent(GetTransform());
	NpcTalkBox->GetTransform()->SetWorldPosition(float4(0, -300, -110.0f));
	NpcTalkBox->SetButtonInterval(float4(0, 35));
	NpcTalkBox->AddButton("��ȭ", [this]() {PlayNextScript(); });

	NpcTalkBox->SetTalkBoxName("��������", float4(2, 0));

	NpcTalkBox->AddMainText(L"����... ���̷����� ������ ���µ�. �, ���� �־�?");
	NpcTalkBox->Off();

	TalkEventCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::UseEvent);
	TalkEventCol->SetColType(ColType::AABBBOX2D);
	TalkEventCol->GetTransform()->SetLocalScale(float4(185, 185, 1));
	TalkEventCol->GetTransform()->SetLocalPosition(float4(0, -21));

	NoteActor = GetLevel()->CreateActor<FieldNoteActor>();
	NoteActor->GetTransform()->SetParent(GetTransform());
	NoteActor->GetTransform()->SetLocalPosition(float4(-5, -127, -100.0f));
	NoteActor->SetText("�� ��ȭ�ϱ�");
	NoteActor->AddKeyImage("KeyUI_F.png", float4(-35, 0, -1));
	NoteActor->Off();

	CreateTalkScript();
}

void ShopQuintessenceArtisan::Update(float _DeltaTime)
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

void ShopQuintessenceArtisan::SpriteLoad()
{
	if (nullptr == GameEngineSprite::Find("QuintessenceArtisanIdle.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("7_Shop");
		Path.Move("Npc");
		Path.Move("QuintessenceArtisan");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("QuintessenceArtisanIdle.png").GetFullPath(), 4, 2);
	}
}

void ShopQuintessenceArtisan::CreateTalkScript()
{
	TalkScripts.resize(7);

	TalkScripts[0] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};

		std::function<void()> Talk4 = [this, TalkEnd]()
		{
			NpcTalkBox->SetTalkMainText(L"���� ��������� �ʳ�...", TalkEnd);
		};		
		
		std::function<void()> Talk3 = [this, Talk4]()
		{
			NpcTalkBox->SetTalkMainText(L"�׷��� ���̵��� ������ ���� ���� ���Ŀ� ������ ���� ������ ���ع��ȴ���. �ΰ��鿡�� �������� ���� �ʾҾ�.", Talk4);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"�� ��ÿ� �׳��, ���̵��� ������ ������ �׵��� ���ؼ� �������� �پ��� ��Ű���� ���������...", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"�׳డ ȣ������ �ӹ��� �� �� �̾߱⸦ ���� ���������µ� ���̾�. ���ռ��� ���� ��... ������ ������...", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"���ռ����� ������, �� ������� �� ģ���� �ְڱ�?", Talk1);
		NpcTalkBox->ButtonDisable();
	};

	TalkScripts[1] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};

		std::function<void()> Talk6 = [this, TalkEnd]()
		{
			NpcTalkBox->SetTalkMainText(L"��� �ְ��� ���� �Ҹ����, �ʴ� ������ ��ȭ�ϼ�.", TalkEnd);
		};

		std::function<void()> Talk5 = [this, Talk6]()
		{
			NpcTalkBox->SetTalkMainText(L"������ �帥 ��, �� �� ��Ҹ��� ���ο� ���� �ҽ��� ���ϰ� �Ǿ���. �ᱹ �½��屸�Ͽ� ���� �������� �Ǿ�����.", Talk6);
		};

		std::function<void()> Talk4 = [this, Talk5]()
		{
			NpcTalkBox->SetTalkMainText(L"������ ��Ҹ��� ����Ϸ��� ����, �� �༮�� Ȧ���� �������. ���� �����ٸ� �˾Ҵٴϱ�?", Talk5);
		};

		std::function<void()> Talk3 = [this, Talk4]()
		{
			NpcTalkBox->SetTalkMainText(L"�ƴ� �۽� ũ�Ⱑ ���� �巡���� ���̾�! ���� ���ΰ� �ؼ� ���� �ȹٷ� �߰� �ٶ�ôµ�... ������ ����� ���̷� �����Ĵ� ��Ҹ��� �鸮����.", Talk4);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"�׷��� ���̾�. Ŀ�ٶ� ������ ��Ⱦ�. �� �г��ϳ� ��ġ�� �ʾҾ��µ� ���̾�. ���������� �ñ��� ���� ��¦ ������. ��û���� ū �Ҹ��� �Բ� �巡���� ����������.", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"���� ���Ե� ����� �巡���� ���� ��� ���Ұ�, �� ���̶� ��������. ���� ���� ���Ҵٳ�.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"���ʳ� �����ΰ�? ������ ���Ͼ��� ĳ�� ���� �Ķ������� �� ���� �־���. �ʹ� ����� �� ������ �巡���� ������ �߰��ϰ� ���Ҵٳ�.", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"�ƹ��� �� �� �ִ� ���� �ƴϾ�. �츮 ������ �ƴ� �ڰ� �ߴٰ� ������ �� ��ȥ�� ��Ƽ�� ���Ұ�.", TalkEnd);
		};

		NpcTalkBox->SetTalkMainText(L"���⿡�� ������ �������� ������ �Ķ� �� Ư�� ���ϾϿ�. ������ ������ ��, �׸��� ������ ��Ʈ���� �ĺ���̼�!", Talk1);
		NpcTalkBox->ButtonDisable();
	};

	TalkScripts[3] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};

		std::function<void()> Talk3 = [this, TalkEnd]()
		{
			NpcTalkBox->SetTalkMainText(L"� �� ���´Կ��� ������ ��� ���� ���� �Ҹ��� ���� �� �ְ� �ؾ� �ϴµ� ���̾�.", TalkEnd);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"���� ���� ���� �ʹ� ���, �پ��� ������ ������ ���ϱ⿣ ���� ���� �����ϴٳ�.", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"���� ���� �����ؾ� �ϴµ�, �Ƶ���� �븦 ���� ������ ���� ����...", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"�� ����? ��� ���� �� �Ǿ��µ�, �����غ��� ���� �ľ�����.", Talk1);
		NpcTalkBox->ButtonDisable();
	};

	TalkScripts[4] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};

		std::function<void()> Talk1 = [this, TalkEnd]()
		{
			NpcTalkBox->SetTalkMainText(L"�� ���� ��� ����� ������ �ʾ�... �̷��� �ϸ� �����鿡�� �˸� ���� �ų� �ٸ�����.", TalkEnd);
		};

		NpcTalkBox->SetTalkMainText(L"�ƴϾ�.. �̰͵� �ƴϾ�... Ʋ�Ⱦ�. �� ����. ���� 30��°��.", Talk1);
		NpcTalkBox->ButtonDisable();
	};

	TalkScripts[5] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};

		std::function<void()> Talk2 = [this, TalkEnd]()
		{
			NpcTalkBox->SetTalkMainText(L"���� â�� �� �����鵵 ������� �� ����. ���ռ� ����� �������� �ɱ�?", TalkEnd);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"�׷��� ���ռ� ����� ��������, Į������ ��Ż�ذ���... ���� �� ����.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"�����鿡�� �⵵�ϸ� ��� �Ⱓ ������ ��ƿ԰�, ���� ���� ������ ������ ��������. �� ���� �ð� �� �Ϳ� �ںν��� ���� �ִٳ�.", Talk1);
		NpcTalkBox->ButtonDisable();
	};

	TalkScripts[6] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};
		
		std::function<void()> Talk3 = [this, TalkEnd]()
		{
			NpcTalkBox->SetTalkMainText(L"�� ���� �Բ� �ο�ٴ� ���. �׻� �ڶ������� �����ϱ� �ٶ��.", TalkEnd);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"�ܼ��ϰ� �������� ���Գ�. �׳� ��ó�� �������� ���� �� ������ �����̰�, ���翡 ���� �����̾������� �𸣴� ��!", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"������ ������ ����, ���� ������ ������ ���� �������� ���� �Ծ�. �� ������ ���� �������� �ڱ� ���� ���� �������� ����.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"�ڳ״� ������ ����� �� ��Ƽ�� ����̱�? ��κ��� ��� ������ �ٷ�� ������ ������ ������ ���� ���ѱ�� ��� ���̾�.", Talk1);
		NpcTalkBox->ButtonDisable();
	};
}

void ShopQuintessenceArtisan::PlayNextScript()
{
	++TalkScriptNumber;

	if (TalkScripts.size() <= TalkScriptNumber)
	{
		TalkScriptNumber = 0;
	}

	TalkScripts[TalkScriptNumber]();
}

void ShopQuintessenceArtisan::TalkEndCallback()
{
	NpcTalkBox->Off();
	GetContentLevel()->CallEvent("PlayerInputUnlock");
	GetContentLevel()->CallEvent("StoryFadeOut");
	GetContentLevel()->CallEvent("PlayerFrameActive");
	GetContentLevel()->CallEvent("UseKeyOn");
	GetContentLevel()->CallEvent("MinimapOn");
	GetContentLevel()->CallEvent("GoodsUIOn");
}