#include "PrecompileHeader.h"
#include "ShopCollector.h"
#include "NPC_TalkBox.h"
#include "FieldNoteActor.h"
#include "MapPlatform.h"
#include "ShopItemGear.h"
#include "ShopCollector_Reroll.h"
#include "Inventory.h"

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

	if (nullptr != GetLevel()->GetCamera((int)CameraOrder::MiniMap))
	{
		MinimapImageRender = CreateComponent<ContentMinimapRender>();
		MinimapImageRender->SetTexture("MinimapImage.png");
		MinimapImageRender->ColorOptionValue.PlusColor = float4(0.0f, 0.784f, 0.0f, 0.0f);
		MinimapImageRender->GetTransform()->SetLocalPosition(float4(367, 45, 0));
		MinimapImageRender->GetTransform()->SetLocalScale(float4(65, 90, 1));
	}

	MainRender->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Collector_Idle.png", .ScaleToTexture = true });
	PlayAnimation("Idle", false);
	NpcTalkBox = GetLevel()->CreateActor<NPC_TalkBox>();
	NpcTalkBox->GetTransform()->SetParent(GetTransform());
	NpcTalkBox->GetTransform()->SetWorldPosition(float4(0, -300, -110.0f));
	NpcTalkBox->SetButtonInterval(float4(0, 35));
	NpcTalkBox->AddButton("��ȭ", [this]() {PlayNextScript(); });

	RerollBox = GetLevel()->CreateActor<ShopCollector_Reroll>();
	RerollBox->GetTransform()->SetParent(GetTransform());
	RerollBox->GetTransform()->SetLocalPosition(float4(246, 60));
	RerollBox->SetCallback([this]() {RerollItem(false); });

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

	ItemPlatforms.resize(4);

	{
		ItemPlatforms[0] = CreateComponent<GameEngineCollision>((int)CollisionOrder::Platform_Half);
		ItemPlatforms[0]->GetTransform()->SetLocalPosition(float4(-402, 78, 0));
		ItemPlatforms[0]->GetTransform()->SetLocalScale(float4(70, 15, 1));
		ItemPlatforms[0]->SetColType(ColType::AABBBOX2D);
	
		ItemPlatforms[1] = CreateComponent<GameEngineCollision>((int)CollisionOrder::Platform_Half);
		ItemPlatforms[1]->GetTransform()->SetLocalPosition(float4(-233, 78, 0));
		ItemPlatforms[1]->GetTransform()->SetLocalScale(float4(70, 15, 1));
		ItemPlatforms[1]->SetColType(ColType::AABBBOX2D);

		ItemPlatforms[2] = CreateComponent<GameEngineCollision>((int)CollisionOrder::Platform_Half);
		ItemPlatforms[2]->GetTransform()->SetLocalPosition(float4(-65, 78, 0));
		ItemPlatforms[2]->GetTransform()->SetLocalScale(float4(70, 15, 1));
		ItemPlatforms[2]->SetColType(ColType::AABBBOX2D);

		ItemPlatforms[3] = CreateComponent<GameEngineCollision>((int)CollisionOrder::Platform_Half);
		ItemPlatforms[3]->GetTransform()->SetLocalPosition(float4(105, 78, 0));
		ItemPlatforms[3]->GetTransform()->SetLocalScale(float4(70, 15, 1));
		ItemPlatforms[3]->SetColType(ColType::AABBBOX2D);
	}

	ItemPrice.resize(4);

	for (size_t i = 0; i < ItemPrice.size(); i++)
	{
		ItemPrice[i] = CreateComponent<GameEngineFontRenderer>();
		ItemPrice[i]->SetFont("�ؽ�Lv2���");
		ItemPrice[i]->SetFontFlag(static_cast<FW1_TEXT_FLAG>(FW1_TEXT_FLAG::FW1_CENTER | FW1_TEXT_FLAG::FW1_VCENTER));
		ItemPrice[i]->SetScale(19);
		ItemPrice[i]->SetColor(float4(1, 1, 1, 1));
		ItemPrice[i]->SetText("");

		float4 PlatformPos = ItemPlatforms[i]->GetTransform()->GetLocalPosition();
		ItemPrice[i]->GetTransform()->SetLocalPosition(PlatformPos + float4(2, -61, -10));
	}

	ItemGears.resize(4);
	CreateTalkScript();
}

void ShopCollector::Update(float _DeltaTime)
{
	RerollBox->SetPrice(RerollPrice);

	for (size_t i = 0; i < ItemPrice.size(); i++)
	{
		if (ItemGears[i] != nullptr && ItemGears[i]->IsDeath())
		{
			ItemGears[i] = nullptr;
		}

		if (nullptr != ItemGears[i])
		{
			ItemPrice[i]->SetText(std::to_string(ItemGears[i]->GetPrice()));

			if (ItemGears[i]->GetPrice() <= Inventory::GetGoodsCount_Gold())
			{
				ItemPrice[i]->SetColor(float4(1, 1, 1, 1));
			}
			else
			{
				ItemPrice[i]->SetColor(float4(1, 0, 0, 1));
			}
		}
		else
		{
			ItemPrice[i]->SetText("");
		}
	}

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
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Reroll_Idle.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Reroll_Interact.png").GetFullPath(), 3, 2);
	}
}

void ShopCollector::PlayBehavior()
{
	ReleaseItem();
	RerollItem(true);
	RerollPrice = 40;
}

void ShopCollector::ResetBehavior()
{
	ReleaseItem();
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
	GetContentLevel()->CallEvent("MinimapOn");
	GetContentLevel()->CallEvent("GoodsUIOn");
}

void ShopCollector::RerollItem(bool _IsInitReroll)
{
	ReleaseItem();
	ItemGears.resize(4);

	std::vector<float> Per = { 35.0f, 30.0f, 20.0f, 15.0f };
	GameEngineRandom& Rand = GameEngineRandom::MainRandom;

	for (size_t i = 0; i < ItemGears.size(); i++)
	{
		ItemGrade RandItem = ContentFunc::RandEnum<ItemGrade>(Per);

		std::vector<ItemData> CopyData;
		ContentDatabase<ItemData, ItemGrade>::CopyGradeDatas(RandItem, CopyData);

		int RandomIndex = Rand.RandomInt(0, (int)CopyData.size() - 1);

		std::shared_ptr<ShopItemGear> NewGear = GetLevel()->CreateActor<ShopItemGear>();
		NewGear->GetTransform()->SetParent(GetTransform());
		NewGear->Init(CopyData[RandomIndex]);

		if (ItemGrade::Legendary == RandItem)
		{
			NewGear->LegendaryGearEffectOn();
		}

		float4 PlatformPos = ItemPlatforms[i]->GetTransform()->GetLocalPosition();
		NewGear->GetTransform()->SetLocalPosition(PlatformPos + float4(15, 50, -10));
		NewGear->WaveOn();

		ItemGears[i] = NewGear;
	}

	if (false == _IsInitReroll)
	{
		RerollPrice += 60;

		if (MaxRerollPrice < RerollPrice)
		{
			RerollPrice = MaxRerollPrice;
		}
	}
}

void ShopCollector::ReleaseItem()
{
	for (size_t i = 0; i < ItemGears.size(); i++)
	{
		if (nullptr != ItemGears[i])
		{
			ItemGears[i]->Death();
			ItemGears[i] = nullptr;
		}
	}

	ItemGears.clear();
}
