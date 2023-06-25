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
	NpcTalkBox->AddButton("대화", [this]() {PlayNextScript(); });
	NpcTalkBox->AddButton("특성부여", [this]() {});

	NpcTalkBox->SetTalkBoxName("마녀", float4(3, 0));

	NpcTalkBox->AddMainText(L"그래요. 난 보기보다 나이가 매우 많아요. 왜 그런 걸 묻죠?");
	NpcTalkBox->AddMainText(L"마왕성은 보기보다 굉장히 유서 깊은 장소랍니다.");
	NpcTalkBox->AddMainText(L"무슨 일이죠 스컬? 나에게 할 말이라도?");
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
	NoteActor->SetText("ㅁ 대화하기");
	NoteActor->AddKeyImage("KeyUI_F.png", float4(-35, 0, -1));
	NoteActor->Off();

	NpcImageRender = CreateComponent<GameEngineUIRenderer>();
	NpcImageRender->SetScaleToTexture("Witch_UI_Talk.png");
	NpcImageRender->GetTransform()->SetLocalScale(NpcImageRender->GetTransform()->GetLocalScale() * 2.0f);

	NpcImageRender->GetTransform()->SetWorldPosition(float4(411, 40, -108));
	NpcImageRender->Off();

	CreateTalkScript();
	CreateBubbleScript();

	BubblePivot = CreateComponent<GameEngineComponent>();
	BubblePivot->GetTransform()->SetLocalPosition(float4(200, -15, -100));
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
		BubbleTalkTime += _DeltaTime;
		NpcImageRender->Off();
	}

	if (0.0f <= BubbleTalkTime)
	{
		PlayBubble();
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

void CastleWitchNPC::CreateBubbleScript()
{
	BubbleScripts.resize(5);

	BubbleScripts[0] = "다른 의원님들이 걱정될\n따름이에요.";
	BubbleScripts[1] = "믿기지 않겠지만, 이곳은 사실\n굉장히 고상한 장소였답니다.";
	BubbleScripts[2] = "검은 마석의 힘은 쉽게 생각하면\n안 됩니다.";
	BubbleScripts[3] = "혹시 통조림 하나 없을까요?";
	BubbleScripts[4] = "그들은 어떻게 마석을\n얻게 되었지..?";
}

void CastleWitchNPC::PlayBubble()
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

	BubbleTalkTime = -7.0f;
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
			NpcTalkBox->SetTalkMainText(L"그 자체만으로도 큰 위험성을 지녔기에 매우 조심해서 다뤄야 합니다. 올바르게 사용하지 못하는 자는 가까이 가기만 해도 악한 영향을 받게 되니까요.", TalkEnd);
		};

		NpcTalkBox->SetTalkMainText(L"마석에 심취하는 자는 아주 강력한 힘을 얻게 됩니다. 그러나 마석은 생명력을 갉아먹게 되고 이상을 잃게 만들어 이윽고 시전자의 주변에는 파멸만이 남게 됩니다.", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"혹시 갖고 있나요?", TalkEnd);
		};		
		
		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"그래서 스스로 고양이가 되어서 그 이유를 찾으려 했지만... 유일한 연구 성과는 통조림이 참 맛있다는 것 정도가 있겠네요.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"고양이들은 알 수 없는 행동을 자주 취하곤 해요. 그 이유를 50년 동안 연구해봤지만 알아내지 못했죠.", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"우리는 모든 종족이 하나가 되어 다시 끔 마왕성 수복을 위해 나가야 합니다.", TalkEnd);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"선대 마왕님이 보신다면 크게 노하실지도 모릅니다...", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"당신도 알겠지만 지금의 마왕성은 예전의 모습과 많이 달라졌어요.", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"그때 발을 헛디뎌 떨어진 의원 중 하나가 스켈레톤의 시초라는 소문이 있어요.", TalkEnd);
		};

		NpcTalkBox->SetTalkMainText(L"한때 이곳, 마왕성 최상층은 의원들로만 가득 차서 발 디딜 곳이 없을 정도였답니다.", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"스컬, 당신도 기회가 되면 넓은 세상을 나가보는 걸 추천할게요.", TalkEnd);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"정든 고향을 떠나 넓은 세상을 바라보니 자연스레 사고가 열렸답니다.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"저는 마왕성에 들어오기 이전, 대륙 이곳저곳을 떠돌며 많은 경험을 쌓았어요.", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"저는 그 두루마리들을 수집하여 연구하고 안전하게 보관한답니다. 그 힘이 우리 모두에게 도움이 될 수 있도록 유익하게 사용하려 노력하고 있어요.", TalkEnd);
		};

		NpcTalkBox->SetTalkMainText(L"하모니아 대륙 이곳저곳에는 고대 마법의 두루마리들이 잠들어 있답니다. 그 두루마리들에는 강력한 마법의 힘이 담겨있죠.", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"고향을 떠난 이유요? 후훗. 글쎄요... 누가 선을 넘었달까요?", TalkEnd);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"다행이도 저는 가족이란 굴레가 없었기에, 그 선택을 하는 게 어렵지가 않았죠.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"정든 고향을 떠나는 일은 힘든 일이에요 스컬.", Talk1);
		NpcTalkBox->ButtonDisable();
	};
}

void CastleWitchNPC::PlayNextScript()
{
	++TalkScriptNumber;

	if (TalkScripts.size() <= TalkScriptNumber)
	{
		TalkScriptNumber = 0;
	}

	TalkScripts[TalkScriptNumber]();
}

void CastleWitchNPC::TalkEndCallback()
{
	NpcTalkBox->Off();
	GetContentLevel()->CallEvent("PlayerInputUnlock");
	GetContentLevel()->CallEvent("StoryFadeOut");
	GetContentLevel()->CallEvent("PlayerFrameActive");
}
