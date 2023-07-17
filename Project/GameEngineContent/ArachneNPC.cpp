#include "PrecompileHeader.h"
#include "ArachneNPC.h"
#include "NPC_TalkBox.h"
#include "FieldNoteActor.h"
#include "Inventory.h"
#include "Player.h"

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
	MainRender->CreateAnimation({ .AnimationName = "Ready", .SpriteName = "Arachne_Ready.png", .FrameInter = 0.12f, .Loop = false, .ScaleToTexture = true });
	MainRender->CreateAnimation({ .AnimationName = "Attack", .SpriteName = "Arachne_Attack.png", .FrameInter = 0.11f, .Loop = false, .ScaleToTexture = true });

	PlayAnimation("Idle", false);

	NpcTalkBox = GetLevel()->CreateActor<NPC_TalkBox>();
	NpcTalkBox->GetTransform()->SetParent(GetTransform());
	NpcTalkBox->GetTransform()->SetWorldPosition(float4(0, -300, -110.0f));
	NpcTalkBox->SetButtonInterval(float4(0, 35));
	NpcTalkBox->AddButton("대화", [this]() {PlayNextScript(); });
	NpcTalkBox->AddButton("각성", [this]() 
		{
			SkullUpgrade();
		});

	NpcTalkBox->SetTalkBoxName("아라크네", float4(3, 0));

	NpcTalkBox->AddMainText(L"그래, 꼬마야. 뼛조각은 준비되었겠지?");
	NpcTalkBox->Off();

	TalkEventCol = CreateComponent<GameEngineCollision>((int)CollisionOrder::UseEvent);
	TalkEventCol->SetColType(ColType::AABBBOX2D);
	TalkEventCol->GetTransform()->SetLocalScale(float4(190, 200, 1));
	TalkEventCol->GetTransform()->SetLocalPosition(float4(-10, 101));

	NoteActor = GetLevel()->CreateActor<FieldNoteActor>();
	NoteActor->GetTransform()->SetParent(GetTransform());
	NoteActor->GetTransform()->SetLocalPosition(float4(-13, -20, -100.0f));
	NoteActor->SetText("ㅁ 대화하기");
	NoteActor->AddKeyImage("KeyUI_F.png", float4(-35, 0, -1));
	NoteActor->Off();

	CreateTalkScript();
	CreateBubbleScript();

	BubblePivot = CreateComponent<GameEngineComponent>();
	BubblePivot->GetTransform()->SetLocalPosition(float4(-25, 270, -100));

	// Test Debug
	IsFirstTalk = false;

	LegendaryLights.reserve(3);

	if (nullptr != GetLevel()->GetCamera((int)CameraOrder::MiniMap))
	{
		MinimapImageRender = CreateComponent<ContentMinimapRender>();
		MinimapImageRender->SetTexture("MinimapImage.png");
		MinimapImageRender->ColorOptionValue.PlusColor = float4(0.004f, 0.9568f, 0.9882f, 0.0f);
		MinimapImageRender->GetTransform()->SetLocalPosition(float4(0, 70, 0));
		MinimapImageRender->GetTransform()->SetLocalScale(float4(100, 140, 1));
	}

}

void ArachneNPC::Update(float _DeltaTime)
{
	if (true == IsUpgradePlay)
	{
		if (nullptr == PlayerPtr)
		{
			MsgAssert_Rtti<ArachneNPC>(" - 몬가 몬가 몬가가 잘못됐음");
			return;
		}

		if (false == IsAttack && true == MainRender->IsAnimationEnd())
		{
			IsAttack = true;
			MainRender->ChangeAnimation("Attack");
			PlayerPtr->MainSkullOff();

			GameEngineSound::Play("Arachne_Cocoon.wav");

			CocoonRender = CreateComponent<GameEngineSpriteRenderer>();
			CocoonRender->SetScaleRatio(2.0f);
			CocoonRender->CreateAnimation({ .AnimationName = "Legendary", .SpriteName = "CocoonLegendaryAnim.png", .FrameInter = 0.06f, .Loop = false, .ScaleToTexture = true });
			CocoonRender->CreateAnimation({ .AnimationName = "Idle", .SpriteName = "Cocoon.png", .FrameInter = 0.1f, .Loop = false, .ScaleToTexture = true });
			CocoonRender->ChangeAnimation("Idle");

			float4 PlayerPos = PlayerPtr->GetTransform()->GetWorldPosition();

			PlayerPos.z = GetTransform()->GetWorldPosition().z + 1;
			CocoonRender->GetTransform()->SetWorldPosition(PlayerPos);

			Inventory::SetMainSkull(UpgradeData);
			CocoonTime = 0.0f;
			IsLegendaryEffect = false;
			IsLegendaryCamEffect = false;
			LegendaryEffectWaitTime = 0.0f;
		}
		
		if (nullptr != CocoonRender)
		{
			CocoonTime += _DeltaTime;

			if (true == IsLegendaryEffect && false == IsLegendaryCamEffect && 14 == CocoonRender->GetCurrentFrame())
			{
				GetContentLevel()->GetCamCtrl().CameraShake(2, 60, 1000);
				IsLegendaryCamEffect = true;
			}

			if (true == IsLegendaryEffect && 0 == LegendaryLights.size() && 15 == CocoonRender->GetCurrentFrame())
			{
				std::shared_ptr<EffectActor> LightEffect = EffectManager::PlayEffect({ .EffectName = "CocoonLegendaryLightEffect"
					,.Position = CocoonRender->GetTransform()->GetWorldPosition() + float4(391, 72, 1),
					.Triger = EffectDeathTrigger::None,
					.IntroFadeSpeed = 2.0f, .IsFadeIntro = true,
					});
			
				float4 LightPos = LightEffect->GetTransform()->GetWorldPosition();
				LightPos.z = CocoonRender->GetTransform()->GetWorldPosition().z + 1;
				LightEffect->GetTransform()->SetWorldPosition(LightPos);

				LightEffect->GetTransform()->SetLocalRotation(float4(0, 0, -81));
				LegendaryLights.push_back(LightEffect);
			}
			
			if (true == IsLegendaryEffect && 1 == LegendaryLights.size() && 21 == CocoonRender->GetCurrentFrame())
			{
				std::shared_ptr<EffectActor> LightEffect = EffectManager::PlayEffect({ .EffectName = "CocoonLegendaryLightEffect"
					,.Position = CocoonRender->GetTransform()->GetWorldPosition() + float4(106, 455, 1),
					.Triger = EffectDeathTrigger::None,
					.IntroFadeSpeed = 2.0f, .IsFadeIntro = true,
					});
			
				float4 LightPos = LightEffect->GetTransform()->GetWorldPosition();
				LightPos.z = CocoonRender->GetTransform()->GetWorldPosition().z + 1;
				LightEffect->GetTransform()->SetWorldPosition(LightPos);

				LightEffect->GetTransform()->SetLocalRotation(float4(0, 0, -14));
				LegendaryLights.push_back(LightEffect);
			}
			
			if (true == IsLegendaryEffect && 2 == LegendaryLights.size() && 27 == CocoonRender->GetCurrentFrame())
			{
				std::shared_ptr<EffectActor> LightEffect = EffectManager::PlayEffect({ .EffectName = "CocoonLegendaryLightEffect"
					,.Position = CocoonRender->GetTransform()->GetWorldPosition() + float4(-373, 152, 1),
					.Triger = EffectDeathTrigger::None,
					.IntroFadeSpeed = 2.0f, .IsFadeIntro = true,
					});
			
				float4 LightPos = LightEffect->GetTransform()->GetWorldPosition();
				LightPos.z = CocoonRender->GetTransform()->GetWorldPosition().z + 1;
				LightEffect->GetTransform()->SetWorldPosition(LightPos);

				LightEffect->GetTransform()->SetWorldRotation(float4(0, 0, 71));
				LegendaryLights.push_back(LightEffect);
			}

			if (true == IsLegendaryEffect && true == CocoonRender->IsAnimationEnd())
			{
				LegendaryEffectWaitTime += _DeltaTime;

				if (0.5f <= LegendaryEffectWaitTime)
				{
					EffectManager::PlayEffect({ .EffectName = "CocoonEffect", .Position = CocoonRender->GetTransform()->GetWorldPosition() + float4(0, 50) });
					EffectManager::PlayEffect({ .EffectName = "CocoonLegendarySmokeEffect", .Position = CocoonRender->GetTransform()->GetWorldPosition() });
					EffectManager::PlayEffect({ .EffectName = "CocoonLegendaryThunder", .Position = CocoonRender->GetTransform()->GetWorldPosition() + float4(0, 300)});


					GameEngineSound::Play("Arachne_Release.wav");
					GameEngineSound::Play("Arachene_LegendaryAwake_Done.wav");

					PlayerPtr->SetInventoryData();
					CocoonRender->Death();
					CocoonRender = nullptr;
					TalkEndCallback();
					MainRender->ChangeAnimation("Idle");
					IsUpgradePlay = false;
					GetContentLevel()->GetCamCtrl().CameraShake(0, 1, 0);

					for (size_t i = 0; i < LegendaryLights.size(); i++)
					{
						LegendaryLights[i]->Death();
						LegendaryLights[i] = nullptr;
					}

					LegendaryLights.clear();
				}
			}

			if (SkullGrade::Legendary == UpgradeData.Grade && 0.5f <= CocoonTime && false == IsLegendaryEffect)
			{
				CocoonRender->ChangeAnimation("Legendary");
				GameEngineSound::Play("Arachene_LegendaryAwake.wav");
				IsLegendaryEffect = true;
			}
			else if (1.5f <= CocoonTime && false == IsLegendaryEffect)
			{
				EffectManager::PlayEffect({ .EffectName = "CocoonEffect", .Position = CocoonRender->GetTransform()->GetWorldPosition() + float4(0, 50) });

				GameEngineSound::Play("Arachne_Release.wav");
				GameEngineSound::Play("Default_Upgrade.wav");

				PlayerPtr->SetInventoryData();
				CocoonRender->Death();
				CocoonRender = nullptr;
				TalkEndCallback();
				MainRender->ChangeAnimation("Idle");
				IsUpgradePlay = false;
			}
		}
	}

	if (nullptr != PlayerPtr && PlayerPtr->IsDeath())
	{
		PlayerPtr = nullptr;
	}

	if (nullptr == PlayerPtr)
	{
		std::shared_ptr<GameEngineCollision> Col = TalkEventCol->Collision((int)CollisionOrder::Player, ColType::AABBBOX2D, ColType::AABBBOX2D);

		if (nullptr != Col)
		{
			PlayerPtr = Col->GetActor()->DynamicThis<Player>().get();
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

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("Cocoon.png").GetFullPath(), 1, 1);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("CocoonLegendaryAnim.png").GetFullPath(), 8, 6);

		GameEngineSprite::LoadSheet(Path.GetPlusFileName("CocoonEffect.png").GetFullPath(), 5, 6);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("CocoonLegendaryLightEffect.png").GetFullPath(), 23, 2);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("CocoonLegendarySmokeEffect.png").GetFullPath(), 4, 8);
		GameEngineSprite::LoadSheet(Path.GetPlusFileName("CocoonLegendaryThunder.png").GetFullPath(), 8, 3);

		EffectManager::CreateMetaData("CocoonEffect", { .SpriteName = "CocoonEffect.png",
			.AnimStart = 0, .AnimEnd = 25, .AnimInter = 0.035f, .ScaleRatio = 2.0f,});

		EffectManager::CreateMetaData("CocoonLegendaryLightEffect", { .SpriteName = "CocoonLegendaryLightEffect.png",
			.AnimStart = 0, .AnimEnd = 44, .AnimInter = 0.07f, .ScaleRatio = 2.0f, });

		EffectManager::CreateMetaData("CocoonLegendarySmokeEffect", { .SpriteName = "CocoonLegendarySmokeEffect.png",
			.AnimStart = 0, .AnimEnd = 30, .AnimInter = 0.035f, .ScaleRatio = 2.0f, });		
		
		EffectManager::CreateMetaData("CocoonLegendaryThunder", { .SpriteName = "CocoonLegendaryThunder.png",
			.AnimStart = 0, .AnimEnd = 22, .AnimInter = 0.045f, .ScaleRatio = 2.0f, });
	}

}

void ArachneNPC::ResetBehavior()
{
	IsSkullUpgradeEnd = false;
}

void ArachneNPC::CreateBubbleScript()
{
	BubbleScripts.resize(4);

	BubbleScripts[0] = "그녀가 잘 지내고 있다니...\n조금 섭섭한 일이야.";
	BubbleScripts[1] = "뼛조각만 충분하다면,\n쉬운 일이지.";
	BubbleScripts[2] = "오래 기다렸단다, 꼬마야.";
	BubbleScripts[3] = "후후, 고치 안은 따뜻해서\n기분이 좋단 말이지.";
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
			NpcTalkBox->SetTalkMainText(L"그녀만 없었다면 난 여전히... 아, 마지막 말은 듣지 않은 걸로 해주렴. 꼬마야.", TalkEnd);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"기껏해야 다리도 두 개밖에 안되는 녀석들이, 날 벌레보듯 바라보는 그 눈빛이 잊히지가 않아.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"인간들이 나를 대하는 감정은 증오 내지는 혐오의 시선에 가깝더구나.", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"... 내 이야기는 아니니까 이제 신경 끄는 게 좋을 거야.", TalkEnd);
		};

		std::function<void()> Talk2 = [this, Talk3]()
		{
			NpcTalkBox->SetTalkMainText(L"그렇지만 규약에 얽매인 채 하루 하루 살아가는 것이 진정한 저주인 것 같구나.", Talk3);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"이 맹세를 어긴 이는 모든 힘을 잃고 평범한 거미가 되어 평생토록 저주받은 삶을 살아야 하지.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"우리 거미굴에서는 깨트릴 수 없는 맹세라는 규약이 있어.", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"뭐, 이 힘을 누군가는 기분 나쁘게 받아들여서 떠돌이 신세가 되었지만 말이야.", TalkEnd);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"고치 안에서 무슨 일이 일어났는지는 아무도 알지 못하지.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"내 거미줄에는 특별한 마법의 힘이 있어. 난 이 거미줄로 고치들을 만들곤 해.", Talk1);
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
			NpcTalkBox->SetTalkMainText(L"절대 잊지 마. 모든 사실 하나하나를 빼먹지 않고 전해.", TalkEnd);
		};		

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"그냥... 넌 잊지 않고... 내가 널 도왔다는 사실을 마녀에게 전해주기나 하면 돼.", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"널 돕는 이유? 묻지 않는 게 좋을 거야.", Talk1);
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
		NpcTalkBox->SetTalkMainText(L"내 도움을 받았다는 것을... 반드시 그 마녀에게 전달하도록 해. 이유는 묻지 말고. 이제 그만 가서 뼛조각을 찾아오거라.", TalkEnd);
	};
	std::function<void()> Talk7 = [this, Talk8]()
	{
		NpcTalkBox->SetTalkMainText(L"네가 가져온 다른 이들의 머리에 뼛조각을 잘 붙여, 그들의 본래 힘을 되찾도록 해주지. 그리고 하나 약속하도록.", Talk8);
	};

	std::function<void()> Talk6 = [this, Talk7]()
	{
		NpcTalkBox->SetTalkMainText(L"뼛조각을 모아오너라. 나의 특별한 힘을 보태주마.", Talk7);
	};

	std::function<void()> Talk5 = [this, Talk6]()
	{
		NpcTalkBox->SetTalkMainText(L"날 만난 걸 감사히 여겨라. 나의 능력은 너 같은 녀석들과 궁합이 잘 맞으니...", Talk6);
	};

	std::function<void()> Talk4 = [this, Talk5]()
	{
		NpcTalkBox->SetTalkMainText(L"그런데... 네 손에 들어간 머리들은 불쌍하기 짝이 없구나. 약해 빠진 스켈레톤 손에 들어가 본연의 힘을 전혀 사용하지 못하고 있다니...", Talk5);
	};


	std::function<void()> Talk3 = [this, Talk4]()
	{
		NpcTalkBox->SetTalkMainText(L"넌 다른 이의 머리를 이용하여 힘을 얻는다지.", Talk4);
	};


	std::function<void()> Talk2 = [this, Talk3]()
	{
		NpcTalkBox->SetTalkMainText(L"뭐... 그건 그렇고.", Talk3);
	};

	std::function<void()> Talk1 = [this, Talk2]()
	{
		NpcTalkBox->SetTalkMainText(L"기다리고 있었다. 널... 도와주기로 했거든. 이유는 묻지 않았으면 좋겠어. 네가 가엾어서 그런건 전혀 아니니까 신경 끄도록.", Talk2);
	};

	NpcTalkBox->SetTalkMainText(L"그래, 너구나. 그녀가 말하던 작은 스켈레톤이.", Talk1);
	NpcTalkBox->ButtonDisable();
}

void ArachneNPC::SkullUpgrade()
{

	const SkullData& Data = Inventory::GetMainSkull();

	if (0 == Data.Index)
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};

		std::function<void()> Talk2 = [this, TalkEnd]()
		{
			NpcTalkBox->SetTalkMainText(L"뼛조각으로 만든 모자가 필요한 게 아니라면, 다른 머리를 들고 오는 게 좋을 것 같구나.", TalkEnd);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"지금의 네 머리는 그냥 너잖아. 심지어 지금 보다 강했던 적도 없어 보이고...", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"말 했을 텐데... 네가 가져온 머리의 본래 주인이 가졌었던 힘을 찾게 해주겠다고.", Talk1);
		NpcTalkBox->ButtonDisable();
	}

	else if (static_cast<size_t>(-1) == Data.UpgradeIndex)
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};

		NpcTalkBox->SetTalkMainText(L"그 머리는 불가능해, 꼬마야. 이미 머리가 가진 모든 힘을 사용하고 있어.\n더 이상은 뼛조각도 도움이 되지 않을 거야.", TalkEnd);
		NpcTalkBox->ButtonDisable();
	}
	else
	{
		UpgradeData = ContentDatabase<SkullData, SkullGrade>::GetData(Data.UpgradeIndex);

		size_t Price = 0;

		switch (UpgradeData.Grade)
		{
		case SkullGrade::Rare:
			Price = 10;
			break;

		case SkullGrade::Unique:
			Price = 30;
			break;

		case SkullGrade::Legendary:
			Price = 100;
			break;
		default:
			break;
		}

		NpcTalkBox->YesOrNoActive(L"결심했나 보구나. 좋아, 지금 상태를 보아하니... " + std::to_wstring(Price) + L"개 정도의 뼛조각이라면 충분히 강해질 수 있겠는데?",
			[this, Price]() // Yes Callback
			{
				if (Inventory::GetGoodsCount_Bone() < Price)
				{
					std::function<void()> TalkEnd = [this]()
					{
						TalkEndCallback();
					};

					NpcTalkBox->SetTalkMainText(L"아무리 내가 뛰어나도, 없는걸 창조해 낼 수는 없어.지금 네가 가진 뼛조각들로는 턱없이 부족해.", TalkEnd);
					NpcTalkBox->YesOrNoDisable();
				}
				else
				{
					std::function<void()> TalkEnd = [this, Price]()
					{

						if (nullptr == PlayerPtr)
						{
							MsgAssert_Rtti<ArachneNPC>(" - 몬가 몬가 잘못됐음");
							return;
						}

						float4 PlayerPos = PlayerPtr->GetTransform()->GetWorldPosition();
						float4 DestPos = GetTransform()->GetWorldPosition() + float4(-190, 0);
						DestPos.z = PlayerPos.z;

						PlayerPtr->PlayStoryMove(DestPos, [this, Price]()
							{
								GetContentLevel()->CallEvent("PlayerLookRight");
								IsUpgradePlay = true;

								Inventory::AddGoods_Bone(-static_cast<int>(Price));
								MainRender->ChangeAnimation("Ready");
								IsAttack = false;
							});

						NpcTalkBox->Off();
					};

					NpcTalkBox->SetTalkMainText(L"좋아, 충분하구나. 뼛조각을 들고 내 앞에 서라.", TalkEnd);
					NpcTalkBox->YesOrNoDisable();

					IsSkullUpgradeEnd = true;
				}
			},
			[this]() // No Callback
			{
				TalkEndCallback();
			}
		);
	}
}
