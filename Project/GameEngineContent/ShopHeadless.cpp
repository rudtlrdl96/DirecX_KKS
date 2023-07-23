#include "PrecompileHeader.h"
#include "ShopHeadless.h"
#include "NPC_TalkBox.h"
#include "FieldNoteActor.h"


ShopHeadless::ShopHeadless()
{
}

ShopHeadless::~ShopHeadless()
{
}


void ShopHeadless::CallUseEvent()
{
	NpcTalkBox->ButtonActive();
	NpcTalkBox->On();
}

void ShopHeadless::Start()
{
	BaseNPC::Start();

	if (nullptr != GetLevel()->GetCamera((int)CameraOrder::MiniMap))
	{
		MinimapImageRender = CreateComponent<ContentMinimapRender>();
		MinimapImageRender->SetTexture("MinimapImage.png");
		MinimapImageRender->ColorOptionValue.PlusColor = float4(0.0f, 0.784f, 0.0f, 0.0f);
		MinimapImageRender->GetTransform()->SetLocalPosition(float4(34, 52, 0));
		MinimapImageRender->GetTransform()->SetLocalScale(float4(65, 90, 1));
	}

	MainRender->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Headless_Idle.png", .ScaleToTexture = true });
	MainRender->CreateAnimation({ .AnimationName = "WithHead", .SpriteName = "Headless_WithHead.png", .ScaleToTexture = true });
	PlayAnimation("Idle", false);
	NpcTalkBox = GetLevel()->CreateActor<NPC_TalkBox>();
	NpcTalkBox->GetTransform()->SetParent(GetTransform());
	NpcTalkBox->GetTransform()->SetWorldPosition(float4(0, -300, -110.0f));
	NpcTalkBox->SetButtonInterval(float4(0, 35));
	NpcTalkBox->AddButton("대화", [this]() {PlayNextScript(); });

	NpcTalkBox->SetTalkBoxName("헤드리스", float4(2, 0));

	NpcTalkBox->AddMainText(L"안녕 친구! 내 이야기 한 번 들어 볼래?");
	NpcTalkBox->Off();

	TalkEventCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::UseEvent);
	TalkEventCol->SetColType(ColType::AABBBOX2D);
	TalkEventCol->GetTransform()->SetLocalScale(float4(165, 165, 1));
	TalkEventCol->GetTransform()->SetLocalPosition(float4(50, 93));

	NoteActor = GetLevel()->CreateActor<FieldNoteActor>();
	NoteActor->GetTransform()->SetParent(GetTransform());
	NoteActor->GetTransform()->SetLocalPosition(float4(46, 0, -100.0f));
	NoteActor->SetText("ㅁ 대화하기");
	NoteActor->AddKeyImage("KeyUI_F.png", float4(-35, 0, -1));
	NoteActor->Off();

	CreateTalkScript();
}

//#include "GameEngineActorGUI.h"

void ShopHeadless::Update(float _DeltaTime)
{
	//std::shared_ptr<GameEngineActorGUI> Ptr = GameEngineGUI::FindGUIWindowConvert<GameEngineActorGUI>("GameEngineActorGUI");
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

void ShopHeadless::SpriteLoad()
{
	if (nullptr == GameEngineSprite::Find("Headless_Idle.png"))
	{
		GameEngineDirectory Path;

		Path.MoveParentToDirectory("Resources");
		Path.Move("Resources");
		Path.Move("Texture");
		Path.Move("7_Shop");
		Path.Move("Npc");
		Path.Move("Headless");

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Headless_Idle.png").GetFullPath(), 8, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Headless_WithHead.png").GetFullPath(), 8, 1);
	}
}

void ShopHeadless::CreateTalkScript()
{
	TalkScripts.resize(8);

	TalkScripts[0] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};

		std::function<void()> Talk3 = [this, TalkEnd]()
		{
			NpcTalkBox->SetTalkMainText(L"잠을 자는 도중에 하고 싶은 일을 한다니 정말 대단해. 나도 잠을 잔 적이 꽤 된것 같은데, 그런데 너 지금 잘 시간 아니니?", TalkEnd);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"심지어 이불까지 덮고 있더라니까? 정말 멋지지 않아? 하고 싶은 말을 다 하면서 잠까지 자는거야!", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"두 번째로는 어디선가 만났던 감시자..라고 했던가? 뭔가를 감시하고 있댔어. 뭔지는 잘 모르겠지만 계속 감시한다 하더라고. 근데 말은 그렇게 하고 있는데 녀석이 잠을 자고 있는 게 아니겠어?", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"들어봐. 내가 살면서 가장 멋지다고 생각한 스켈레톤이 셋 있어. 첫 번째로는 너희 마왕성에 있는 경비대장이야. 그의 든든함과 유려한 칼 솜씨에 반해버렸달까? 머리 모양도 멋있고 말이야.", Talk1);
		NpcTalkBox->ButtonDisable();
	};

	TalkScripts[1] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};

		std::function<void()> Talk4 = [this, TalkEnd]()
		{
			NpcTalkBox->SetTalkMainText(L"화살을 쏜 사람은 누굴까? 그러고 보니 그 여우도 활좀 쏘는데, 녀석에게 안부 전해줘!", TalkEnd);
		};

		std::function<void()> Talk3 = [this, Talk4]()
		{
			NpcTalkBox->SetTalkMainText(L"마법 포격과 화살들이 빗발치는 전장에서 겪는 그 공포. 어제 머리가 있었을 때만 해도 화살이 내 머리에 꽃힐뻔했다니까.", Talk4);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"그렇게 높은 곳에 있으면 얼마나 무서울까? 아니다. 무섭기로 하면 전장에서 겪는 죽음의 공포만 하겠어.", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"위치적으로 말고, 권력의 체계라고 해야 되나? 그러고 보니 위치적으로도 맨 위에 있네. 난 사실 고소공포증이 있거든.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"잘 들어봐, 난 지금 마왕성의 규율에 대해 심각한 문제가 있다고 생각해. 봐. 지금 마왕이 마왕성에서 제일 높은 위치에 있지?", Talk1);
		NpcTalkBox->ButtonDisable();
	};

	TalkScripts[2] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};

		std::function<void()> Talk3 = [this, TalkEnd]()
		{
			NpcTalkBox->SetTalkMainText(L"나도 두 눈으로 직접 보고 나서 섬길지 말지를 결정해야 하거든. 물론 난 스켈레톤이라 두 눈이 없지만! 그리고 지금은 머리조차 없지만!", TalkEnd);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"결투의 신이라... 신을 섬기는 자들은 정말 많이 보았는데 어째서 신은 한 번도 보지 못한 걸까? 신을 직접 눈으로 확인한 자들이 있다면 그들과 이야기를 나눠 보고 싶어!", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"정말 대단하지 않아? 만 번 싸우기도 쉽지 않은데 세 번의 패배밖에 없다니. 결투의 신이 세상에 존재한다면 내가 아닐까?", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"들어봐 진지한 이야기를 해 줄게. 나는 스켈레톤의 몸으로 무려 만 번의 결투를 했지. 만 번의 결투 중 패배한 적은 단 세 번뿐.", Talk1);
		NpcTalkBox->ButtonDisable();
	};

	TalkScripts[3] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};

		std::function<void()> Talk4 = [this, TalkEnd]()
		{
			NpcTalkBox->SetTalkMainText(L"네 가치관은 어떻게 되나 친구?", TalkEnd);
		};

		std::function<void()> Talk3 = [this, Talk4]()
		{
			NpcTalkBox->SetTalkMainText(L"복잡하긴 또 생각해보니 저 오크 녀석 레시피도 마찬가지긴 해. 대체 요리에 어떤 가치관을 가지고 있는지 모르겠네.", Talk4);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"사실 제일 유명한 건 그 용사 말고도 몇 있지 칼레온의 마법사나 마녀들이라던가. 그들 마법이 복잡하기로 유명하거든.", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"머리가 왜 없어졌냐면 난 그놈과 열심히 싸웠어. 그놈은 누군지 알지? 그 칼레온에서 제일 유명하다는 용사 있잖아.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"들어봐, 난 분명히 어제까지 머리가 있었어 친구.", Talk1);
		NpcTalkBox->ButtonDisable();
	};

	TalkScripts[4] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};

		std::function<void()> Talk3 = [this, TalkEnd]()
		{
			NpcTalkBox->SetTalkMainText(L"기분이 나빠서 식사 자리에 가지 말까 했는데, 그래서 너에게 이 말만은 꼭 해야겠다. 어떻게 입어야 조금 더 멋질까?", TalkEnd);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"차려입는다라... 그러고 보니 난 수집가 녀석과 식사하러 가기로 했는데, 나보고 차려입으라고 하더라고. 난 이미 차려입었는데 말이야.", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"옷을 왜 입어야 하냐고? 그걸 질문이라고 하는건가. 너 속뼈 다 보이잖아! 망측하기는. 날 봐. 머리가 없을 뿐이지 전부 차려입었어.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"들어봐! 아직 네가 아이라는 걸 알지만 그래도 이 말만은 꼭 해야겠다. 밖을 나설 때는 옷을 입고 나가야 하는 거야 이 바보야!", Talk1);
		NpcTalkBox->ButtonDisable();
	};

	TalkScripts[5] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};

		std::function<void()> Talk4 = [this, TalkEnd]()
		{
			NpcTalkBox->SetTalkMainText(L"다르다는 건 틀리다는 것과 차이가 있는데, 넌 어떻게 생각해?", TalkEnd);
		};

		std::function<void()> Talk3 = [this, Talk4]()
		{
			NpcTalkBox->SetTalkMainText(L"마녀가 예전에 말해줬거든. 아카데미에는 많은 수습생들이 있다고. 수습생으로 지내는 건 힘들꺼야. 사실상 민간인들과 다를 바가 없으니까.", Talk4);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"용사의 노란 검기가 날아오는데 빛으로 가득 찬 느낌이랄까? 녀석도 마법을 어디선가 배운거겠지. 칼레온에는 세가지 마법 아카데미가 있다는 소문이 있어.", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"근데 막상 칼레온 녀석들과 맞닥뜨리고 나니 식욕이 뚝 떨어지고, 싸우고 싶은 마음만 가득찼지. 그리고 용사를 만났어.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"들어봐 들어봐. 어제 내가 출정하기 전에 분명히 오크 녀석이 준 도시락을 싸가지고 갔다구.", Talk1);
		NpcTalkBox->ButtonDisable();
	};

	TalkScripts[6] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};

		std::function<void()> Talk4 = [this, TalkEnd]()
		{
			NpcTalkBox->SetTalkMainText(L"정말 놀라워. 어서 내 슬라임에 대한 연구 자료를 발표해야겠어.", TalkEnd);
		};

		std::function<void()> Talk3 = [this, Talk4]()
		{
			NpcTalkBox->SetTalkMainText(L"그 이유가 뭔지 알아? 슬라임들은 뼈가 없어! 그렇지만 더욱 놀라운 사실. 슬라임들은 뼈가 없어도 움직일 수 있다는 거야!", Talk4);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"뼈가 있는 존재들만 스켈레톤이 된다는 게 정말 놀랍지 않아? 놀라운 건 한 가지 더 있어. 슬라임들은 스켈레톤이 되지 않는다는 사실!", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"스켈레톤들은 어째서 스켈레톤이 되는지 알아? 내가 알아냈지. 이유는 정말 심플했어. 우리는 뼈가 있기 때문이야.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"들어봐 들어봐. 난 스켈레톤에 대한 연구를 발표할 예정이야.", Talk1);
		NpcTalkBox->ButtonDisable();
	};

	TalkScripts[7] = [this]()
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};

		std::function<void()> Talk4 = [this, TalkEnd]()
		{
			NpcTalkBox->SetTalkMainText(L"그리고 여기 돌아왔는데 그녀가 그러더군. 네 머리 어딨어?", TalkEnd);
		};

		std::function<void()> Talk3 = [this, Talk4]()
		{
			NpcTalkBox->SetTalkMainText(L"그때 노란빛의 공격을 보고 재빠르게 피했지. 그 후 궁수들의 화살 세례를 버텨내고 안전하게 퇴각했어.", Talk4);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"그녀가 꽤 매력 있는 건 인정해. 그렇지만 그렇게 쉽게 인정할 순 없지. 난 절대 쉽지 않아. 칼레온 병사 수십 명에게 둘러쌓였을때도 용맹함을 잃지 않았어.", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"두근댄다는 건 누군가와 사랑에 빠졌을 때도 나는 소리라는데, 혹시 내가 누군가를? 저 밑에 있는 수집가 녀석은 아니겠지?", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"들었어? 나에게서 나는 심장박동 소리. 나는 분명히 스켈레톤이고, 심장은 없을 텐데 어디선가 계속 두근대는 소리가 나네.", Talk1);
		NpcTalkBox->ButtonDisable();
	};
}

void ShopHeadless::PlayNextScript()
{
	++TalkScriptNumber;

	if (TalkScripts.size() <= TalkScriptNumber)
	{
		TalkScriptNumber = 0;
	}

	TalkScripts[TalkScriptNumber]();
}

void ShopHeadless::TalkEndCallback()
{
	NpcTalkBox->Off();
	GetContentLevel()->CallEvent("PlayerInputUnlock");
	GetContentLevel()->CallEvent("StoryFadeOut");
	GetContentLevel()->CallEvent("PlayerFrameActive");
	GetContentLevel()->CallEvent("UseKeyOn");
}