#include "PrecompileHeader.h"
#include "CastleFoxHunterNPC.h"
#include "NPC_TalkBox.h"
#include "FieldNoteActor.h"
#include "SkullGear.h"

CastleFoxHunterNPC::CastleFoxHunterNPC()
{
}

CastleFoxHunterNPC::~CastleFoxHunterNPC()
{
}

void CastleFoxHunterNPC::CallUseEvent()
{
	if (true == IsGiveItem)
	{
		NpcTalkBox->On();
		PlayNextGiveHeadScript();

		IsGiveItem = false;
	}
	else
	{
		NpcTalkBox->ButtonActive();
		NpcTalkBox->On();
	}
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
	NpcTalkBox->AddButton("대화", [this]() {PlayNextScript(); });
	NpcTalkBox->AddButton("머리 받기", [this]() {PlayNextGiveHeadScript(); });

	NpcTalkBox->SetTalkBoxName("인호족 사냥꾼", float4(2, 0));

	NpcTalkBox->AddMainText(L"모을 때는 한참 걸렸는데, 이렇게 하나씩 나눠주다 보면 금방 떨어지더라.");
	NpcTalkBox->AddMainText(L"네 녀석이 머리통을 갈아끼우든 말든 중요하지 않아.");
	NpcTalkBox->AddMainText(L"넌 네가 특별하다고 생각하냐? 이 성에 있는 사람들 중 그정도 특별하지 않은 자가 어디 있지?");
	NpcTalkBox->AddMainText(L"아직도 나에게 볼일이 남았나?");
	NpcTalkBox->Off();

	TalkEventCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::UseEvent);
	TalkEventCol->SetColType(ColType::AABBBOX2D);
	TalkEventCol->GetTransform()->SetLocalScale(float4(130, 150, 1));
	TalkEventCol->GetTransform()->SetLocalPosition(float4(-15, -180));

	NoteActor = GetLevel()->CreateActor<FieldNoteActor>();
	NoteActor->GetTransform()->SetParent(GetTransform());
	NoteActor->GetTransform()->SetLocalPosition(float4(-15, -275, -100.0f));
	NoteActor->SetText("ㅁ 대화하기");
	NoteActor->AddKeyImage("KeyUI_F.png", float4(-35, 0, -1));
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
	CreateGiveHeadScript();
	CreateBubbleScript();

	BubblePivot = CreateComponent<GameEngineComponent>();
	BubblePivot->GetTransform()->SetLocalPosition(float4(-20, -85, -100));
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
		BubbleTalkTime += _DeltaTime;
		NpcImageRender->Off();
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

void CastleFoxHunterNPC::CreateBubbleScript()
{
	BubbleScripts.resize(4);

	BubbleScripts[0] = "조금만 더 모았으면 132개인데...";
	BubbleScripts[1] = "여기서 불이라도 좀 쬐던가.";
	BubbleScripts[2] = "축축한 마왕성보단 전장이 좋아.";
	BubbleScripts[3] = "여우 맞아. 늑대는 아니고.";
}


void CastleFoxHunterNPC::PlayBubble()
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

	BubbleTalkTime = -13.0f;
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
			NpcTalkBox->SetTalkMainText(L"한때는 그대로 가져와서 박제하는 방법을 사용해봤는데, 마왕님께 크게 혼난 이후론 박제는 안 해.", TalkEnd);
		};

		NpcTalkBox->SetTalkMainText(L"인간 놈들 머리통은 왜 이렇게 작은 거지? 아기자기한 맛이 있어 계속 모으게 된다고", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"그를 기리고자 하는 마음에 여기 머리만 들고 왔어. 볼래?", TalkEnd);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"검도 잘 휘두르고, 활도 매우 잘 쏘고, 머리도 영특했는데... 역시 마법이 제일 강력한가...", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"작전 수행 중 친해진 매우 강력한 전사가 있었는데, 이상한 마법에 걸려서 3일 동안 괴로워하다가 숨을 거뒀어.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"한때는 용병이 되어 하모니아 이곳저곳의 수많은 전투에 참여했었지.", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"물론 다 죽었어.", TalkEnd);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"다들 자기 자신이 가장 중요하다고 생각해서 팀워크가 없어. 서로 도왔으면 얼마나 좋았을까.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"한때는 마왕 군 교관으로 일했었지. 오크, 가고일, 웨어울프 다 좋았는데 우리 호인족은 말을 더럽게 안 듣더라.", Talk1);
		NpcTalkBox->ButtonDisable();
	};
}

void CastleFoxHunterNPC::PlayNextScript()
{
	++TalkScriptNumber;

	if (TalkScripts.size() <= TalkScriptNumber)
	{
		TalkScriptNumber = 0;
	}

	TalkScripts[TalkScriptNumber]();
}

void CastleFoxHunterNPC::TalkEndCallback()
{
	NpcTalkBox->Off();
	GetContentLevel()->CallEvent("PlayerInputUnlock");
	GetContentLevel()->CallEvent("StoryFadeOut");
	GetContentLevel()->CallEvent("PlayerFrameActive");
	GetContentLevel()->CallEvent("UseKeyOn");
}

void CastleFoxHunterNPC::CreateGiveHeadScript()
{
	GiveHeadScritps.resize(4);

	GiveHeadScritps[0] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			GiveHeadEndCallback();
		};

		NpcTalkBox->SetTalkMainText(L"머리를 갈아 끼운다니 웃니는 놈이야. 이걸로도 한번 해봐.", TalkEnd);
		NpcTalkBox->ButtonDisable();
	};

	GiveHeadScritps[1] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			GiveHeadEndCallback();
		};

		NpcTalkBox->SetTalkMainText(L"그거 별로 좋아 보이진 않네. 이게 더 어울려.", TalkEnd);
		NpcTalkBox->ButtonDisable();
	};

	GiveHeadScritps[2] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			GiveHeadEndCallback();
		};

		NpcTalkBox->SetTalkMainText(L"그 얼굴로 밖에 나가겠다고? 농담이지?", TalkEnd);
		NpcTalkBox->ButtonDisable();
	};

	GiveHeadScritps[3] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			GiveHeadEndCallback();
		};

		NpcTalkBox->SetTalkMainText(L"모을 때는 한참 걸렸는데, 이렇게 하나씩 나눠주다 보면 금방 떨어지더라.", TalkEnd);
		NpcTalkBox->ButtonDisable();
	};
}

void CastleFoxHunterNPC::PlayNextGiveHeadScript()
{
	++GiveHeadScriptNumber;

	if (GiveHeadScritps.size() <= GiveHeadScriptNumber)
	{
		GiveHeadScriptNumber = 0;
	}

	GiveHeadScritps[GiveHeadScriptNumber]();
}

void CastleFoxHunterNPC::GiveHeadEndCallback()
{
	std::vector<float> RandPer = {50.0f, 50.0f};

	SkullGrade RandGrade = ContentFunc::RandEnum<SkullGrade>(RandPer);

	std::vector<SkullData> GradeDatas;

	ContentDatabase<SkullData, SkullGrade>::CopyGradeDatas(RandGrade, GradeDatas);

	size_t RandIndex = GameEngineRandom::MainRandom.RandomInt(0, static_cast<int>(GradeDatas.size()) - 1);

	std::shared_ptr<SkullGear> Gear = GetLevel()->CreateActor<SkullGear>();

	Gear->DropGear(GetTransform()->GetWorldPosition() + float4(0, -100, -1));
	Gear->Init(GradeDatas[RandIndex]);

	if (RandGrade == SkullGrade::Legendary)
	{
		Gear->LegendaryGearEffectOn();
	}

	NpcTalkBox->Off();
	GetContentLevel()->CallEvent("PlayerInputUnlock");
	GetContentLevel()->CallEvent("StoryFadeOut");
	GetContentLevel()->CallEvent("PlayerFrameActive");
	GetContentLevel()->CallEvent("UseKeyOn");
}
