#include "PrecompileHeader.h"
#include "CastleOgrePaddlerNPC.h"
#include "NPC_TalkBox.h"
#include "FieldNoteActor.h"

CastleOgrePaddlerNPC::CastleOgrePaddlerNPC()
{
}

CastleOgrePaddlerNPC::~CastleOgrePaddlerNPC()
{
}

void CastleOgrePaddlerNPC::CallUseEvent()
{
	if (true == IsGiveItem)
	{
		NpcTalkBox->On();
		PlayNextGiveItemScript();

		IsGiveItem = false;
	}
	else
	{
		NpcTalkBox->ButtonActive();
		NpcTalkBox->On();
	}
}

void CastleOgrePaddlerNPC::Start()
{
	BaseNPC::Start();

	if (nullptr == GameEngineTexture::Find("OgrePeddler_UI_Talk.png"))
	{
		GameEngineDirectory Path;
		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("2_Castle");
		Path.Move("Npc");
		Path.Move("OgrePeddler");
		Path.Move("OgrePeddler_UI_Talk");

		GameEngineTexture::Load(Path.GetPlusFileName("OgrePeddler_UI_Talk.png").GetFullPath());
	}

	MainRender->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "OgrePeddler_Idle.png", .ScaleToTexture = true });
	PlayAnimation("Idle", false);
	NpcTalkBox = GetLevel()->CreateActor<NPC_TalkBox>();
	NpcTalkBox->GetTransform()->SetParent(GetTransform());
	NpcTalkBox->GetTransform()->SetWorldPosition(float4(0, -300, -110.0f));
	NpcTalkBox->SetButtonInterval(float4(0, 35));
	NpcTalkBox->AddButton("대화", [this]() {PlayNextTalkScript(); });
	NpcTalkBox->AddButton("아이템 받기", [this]() {PlayNextGiveItemScript(); });

	NpcTalkBox->SetTalkBoxName("오우거 보부상", float4(2, 0));

	NpcTalkBox->AddMainText(L"용사 나쁘다. 내 돈. 다 가져갔다.");
	NpcTalkBox->AddMainText(L"너. 작다. 나. 크다.");
	NpcTalkBox->AddMainText(L"보물. 원해? 나, 화난다.");
	NpcTalkBox->Off();

	TalkEventCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::UseEvent);
	TalkEventCol->SetColType(ColType::AABBBOX2D);
	TalkEventCol->GetTransform()->SetLocalScale(float4(160, 200, 1));
	TalkEventCol->GetTransform()->SetLocalPosition(float4(-25, -155));

	NoteActor = GetLevel()->CreateActor<FieldNoteActor>();
	NoteActor->GetTransform()->SetParent(GetTransform());
	NoteActor->GetTransform()->SetLocalPosition(float4(-25, -275, -100.0f));
	NoteActor->SetText("ㅁ 대화하기");
	NoteActor->AddKeyImage("KeyUI_F.png", float4(-35, 0, -1));
	NoteActor->Off();

	NpcImageRender = CreateComponent<GameEngineUIRenderer>();
	NpcImageRender->SetScaleToTexture("OgrePeddler_UI_Talk.png");
	NpcImageRender->GetTransform()->SetLocalScale(NpcImageRender->GetTransform()->GetLocalScale() * 2.0f);

	NpcImageRender->GetTransform()->SetWorldPosition(float4(445, 36, -108));
	NpcImageRender->Off();

	GetContentLevel()->AddEvent("CastleReborn", GetActorCode(), [this]()
		{
			IsGiveItem = true;
		});

	CreateTalkScript();
	CreateGiveItemScript();
	CreateBubbleScript();

	BubblePivot = CreateComponent<GameEngineComponent>();
	BubblePivot->GetTransform()->SetLocalPosition(float4(-30, -15, -100));
}

void CastleOgrePaddlerNPC::Update(float _DeltaTime)
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

void CastleOgrePaddlerNPC::SpriteLoad()
{
	if (nullptr == GameEngineSprite::Find("OgrePeddler_Idle.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("2_Castle");
		Path.Move("Npc");
		Path.Move("OgrePeddler");
		Path.Move("Sheet");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("OgrePeddler_Idle.png").GetFullPath(), 8, 1);
	}

}

void CastleOgrePaddlerNPC::Destroy()
{
	GetContentLevel()->RemoveEvent("CastleReborn", GetActorCode());
}

void CastleOgrePaddlerNPC::CreateBubbleScript()
{
	BubbleScripts.resize(3);

	BubbleScripts[0] = "친구들. 보고싶다.";
	BubbleScripts[1] = "내 보물, 손 못댄다.";
	BubbleScripts[2] = "배가 고프다.";
}

void CastleOgrePaddlerNPC::PlayBubble()
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

	BubbleTalkTime = -20.0f;
}

void CastleOgrePaddlerNPC::CreateTalkScript()
{
	TalkScripts.resize(1);

	TalkScripts[0] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};

		std::function<void()> Talk1 = [this, TalkEnd]()
		{
			NpcTalkBox->SetTalkMainText(L"워어어!", TalkEnd);
		};

		NpcTalkBox->SetTalkMainText(L"난 말할 수 있다. 앤 못한다 말. 맞다! 애도 말한다. 이렇게. '워어어'", Talk1);
		NpcTalkBox->ButtonDisable();
	};
}

void CastleOgrePaddlerNPC::PlayNextTalkScript()
{
	++TalkScriptNumber;

	if (TalkScripts.size() <= TalkScriptNumber)
	{
		TalkScriptNumber = 0;
	}

	TalkScripts[TalkScriptNumber]();
}

void CastleOgrePaddlerNPC::TalkEndCallback()
{
	NpcTalkBox->Off();
	GetContentLevel()->CallEvent("PlayerInputUnlock");
	GetContentLevel()->CallEvent("StoryFadeOut");
	GetContentLevel()->CallEvent("PlayerFrameActive");
	GetContentLevel()->CallEvent("UseKeyOn");
}

void CastleOgrePaddlerNPC::CreateGiveItemScript()
{
	GiveItemScritps.resize(4);

	GiveItemScritps[0] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			GiveItemEndCallback();
		};

		NpcTalkBox->SetTalkMainText(L"원래는 난 내 보물 안 준다. 너한테는 준다. 너 착하다.", TalkEnd);
		NpcTalkBox->ButtonDisable();
	};

	GiveItemScritps[1] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			GiveItemEndCallback();
		};

		NpcTalkBox->SetTalkMainText(L"마녀한테는 비밀이다. 그녀가 그랬다. 자주 주면 버릇 나빠진다고.", TalkEnd);
		NpcTalkBox->ButtonDisable();
	};

	GiveItemScritps[2] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			GiveItemEndCallback();
		};

		NpcTalkBox->SetTalkMainText(L"네 행색 웃기다. 하하. 받아라 이거.", TalkEnd);
		NpcTalkBox->ButtonDisable();
	};

	GiveItemScritps[3] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			GiveItemEndCallback();
		};

		NpcTalkBox->SetTalkMainText(L"너 많이 조촐하다. 선물 줄게.", TalkEnd);
		NpcTalkBox->ButtonDisable();
	};
}

void CastleOgrePaddlerNPC::PlayNextGiveItemScript()
{
	++GiveItemScriptNumber;

	if (GiveItemScritps.size() <= GiveItemScriptNumber)
	{
		GiveItemScriptNumber = 0;
	}

	GiveItemScritps[GiveItemScriptNumber]();
}

void CastleOgrePaddlerNPC::GiveItemEndCallback()
{
	NpcTalkBox->Off();
	GetContentLevel()->CallEvent("PlayerInputUnlock");
	GetContentLevel()->CallEvent("StoryFadeOut");
	GetContentLevel()->CallEvent("PlayerFrameActive");
	GetContentLevel()->CallEvent("UseKeyOff");
}