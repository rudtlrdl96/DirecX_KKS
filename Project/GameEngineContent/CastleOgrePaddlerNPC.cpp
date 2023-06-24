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
	NpcTalkBox->AddButton("대화", [this]() {PlayNextScript(); });
	NpcTalkBox->AddButton("아이템 받기", [this]() {});

	NpcTalkBox->SetTalkBoxName("오우거 보부상", float4(2, 0));

	NpcTalkBox->AddMainText(L"용사 나쁘다. 내 돈. 다 가져갔다.");
	NpcTalkBox->AddMainText(L"너. 작다. 나. 크다.");
	NpcTalkBox->AddMainText(L"보물. 원해? 나, 화난다.");
	NpcTalkBox->Off();

	TalkEventCol = CreateComponent<GameEngineCollision>();
	TalkEventCol->SetColType(ColType::AABBBOX2D);
	TalkEventCol->GetTransform()->SetLocalScale(float4(160, 200, 1));
	TalkEventCol->GetTransform()->SetLocalPosition(float4(-25, -155));

	if (false == GameEngineInput::IsKey("UseKey"))
	{
		GameEngineInput::CreateKey("UseKey", 'F');
	}

	NoteActor = GetLevel()->CreateActor<FieldNoteActor>();
	NoteActor->GetTransform()->SetParent(GetTransform());
	NoteActor->GetTransform()->SetLocalPosition(float4(-25, -275, -100.0f));
	NoteActor->SetText("F 대화하기");
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

void CastleOgrePaddlerNPC::PlayNextScript()
{
	++ScriptNumber;

	if (TalkScripts.size() <= ScriptNumber)
	{
		ScriptNumber = 0;
	}

	TalkScripts[ScriptNumber]();
}

void CastleOgrePaddlerNPC::TalkEndCallback()
{
	NpcTalkBox->Off();
	GetContentLevel()->CallEvent("PlayerInputUnlock");
	GetContentLevel()->CallEvent("StoryFadeOut");
	GetContentLevel()->CallEvent("PlayerFrameActive");
}
