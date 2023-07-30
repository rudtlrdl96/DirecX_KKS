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
	NpcTalkBox->AddButton("대화", [this]() {PlayNextScript(); });

	NpcTalkBox->SetTalkBoxName("정수장인", float4(2, 0));

	NpcTalkBox->AddMainText(L"흐음... 스켈레톤의 정수는 없는데. 어때, 생각 있어?");
	NpcTalkBox->Off();

	TalkEventCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::UseEvent);
	TalkEventCol->SetColType(ColType::AABBBOX2D);
	TalkEventCol->GetTransform()->SetLocalScale(float4(185, 185, 1));
	TalkEventCol->GetTransform()->SetLocalPosition(float4(0, -21));

	NoteActor = GetLevel()->CreateActor<FieldNoteActor>();
	NoteActor->GetTransform()->SetParent(GetTransform());
	NoteActor->GetTransform()->SetLocalPosition(float4(-5, -127, -100.0f));
	NoteActor->SetText("ㅁ 대화하기");
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
			NpcTalkBox->SetTalkMainText(L"정말 비극적이지 않나...", TalkEnd);
		};		
		
		std::function<void()> Talk3 = [this, Talk4]()
		{
			NpcTalkBox->SetTalkMainText(L"그런데 아이들이 끔찍한 일을 겪은 이후에 보았을 때는 완전히 변해버렸더군. 인간들에게 눈길조차 주지 않았어.", Talk4);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"그 당시에 그녀는, 아이들을 굉장히 좋아해 그들을 위해서 마법으로 다양한 쿠키들을 만들곤했지...", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"그녀가 호숫가에 머무를 때 꽤 이야기를 많이 나누었었는데 말이야. 마왕성에 들어가기 전... 오래전 일이지...", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"마왕성에서 왔으면, 그 마녀랑도 꽤 친분이 있겠군?", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"대륙 최강의 용사라 불리우는, 초대 용사와의 일화일세.", TalkEnd);
		};

		std::function<void()> Talk5 = [this, Talk6]()
		{
			NpcTalkBox->SetTalkMainText(L"세월이 흐른 뒤, 난 그 목소리의 주인에 대한 소식을 접하게 되었어. 결국 승승장구하여 아주 유명인이 되었더군.", Talk6);
		};

		std::function<void()> Talk4 = [this, Talk5]()
		{
			NpcTalkBox->SetTalkMainText(L"떨리는 목소리로 대답하려는 찰나, 그 녀석은 홀연히 사라졌어. 정말 꿈인줄만 알았다니까?", Talk5);
		};

		std::function<void()> Talk3 = [this, Talk4]()
		{
			NpcTalkBox->SetTalkMainText(L"아니 글쎄 크기가 어마어마한 드래곤이 말이야! 무슨 일인가 해서 눈을 똑바로 뜨고 바라봤는데... 날리는 흙먼지 사이로 괜찮냐는 목소리가 들리더군.", Talk4);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"그런데 말이야. 커다란 굉음이 들렸어. 난 털끝하나 다치지 않았었는데 말이야. 무슨일인지 궁금해 눈을 살짝 떠보니. 엄청나게 큰 소리와 함께 드래곤이 쓰러지더군.", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"운이 없게도 배고픈 드래곤의 눈에 띄고 말았고, 난 끝이라 생각했지. 눈을 질끈 감았다네.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"오십년 전쯤인가? 부족한 설록암을 캐러 직접 파란산으로 간 적이 있었지. 너무 깊숙히 들어간 나머지 드래곤의 둥지를 발견하고 말았다네.", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"아무나 할 수 있는 일이 아니야. 우리 일족이 아닌 자가 했다간 정수의 기운에 영혼이 버티질 못할걸.", TalkEnd);
		};

		NpcTalkBox->SetTalkMainText(L"보기에는 간단해 보일지도 모르지만 파란 산 특제 설록암에. 강력한 선조의 힘, 그리고 세심한 컨트롤의 컴비네이션!", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"어서 내 스승님에게 보내서 어엿한 정수 장인 소리를 들을 수 있게 해야 하는데 말이야.", TalkEnd);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"손주 놈은 아직 너무 어리고, 다양한 일족의 정수를 대하기엔 아직 힘이 부족하다네.", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"이제 슬슬 은퇴해야 하는데, 아들놈은 대를 이을 생각이 없는 건지...", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"내 나이? 세어본 지는 꽤 되었는데, 생각해보니 정말 늙었구먼.", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"영 맘에 드는 모습이 나오질 않아... 이렇게 하면 선조들에게 죄를 짓는 거나 다름없어.", TalkEnd);
		};

		NpcTalkBox->SetTalkMainText(L"아니야.. 이것도 아니야... 틀렸어. 이 정수. 벌써 30개째야.", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"가끔 창고에 둔 정수들도 사라지는 것 같아. 마왕성 놈들이 가져가는 걸까?", TalkEnd);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"그런데 마왕성 놈들이 빌려가고, 칼레온이 약탈해가고... 이제 몇 없지.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"선조들에게 기도하며 몇백 년간 꾸준히 깎아왔고, 수백 가지 일족의 정수를 관리했지. 이 일을 맡게 된 것에 자부심을 갖고 있다네.", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"그 힘과 함께 싸운다는 사실. 항상 자랑스럽게 생각하길 바라네.", TalkEnd);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"단순하게 접근하지 말게나. 그냥 돌처럼 보일지는 몰라도 한 일족의 영웅이고, 역사에 남을 마족이었을지도 모르는 일!", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"모험을 떠나다 보면, 세상 곳곳에 버려진 많은 정수들이 보일 게야. 다 주인의 힘이 떨어지자 자기 길을 떠난 정수들인 게지.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"자네는 정수의 기운을 잘 버티는 모양이군? 대부분의 경우 정수를 다루는 역량이 부족해 오히려 힘을 빼앗기기 쉬운데 말이야.", Talk1);
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