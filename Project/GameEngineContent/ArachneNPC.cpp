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
	NpcTalkBox->AddButton("��ȭ", [this]() {PlayNextScript(); });
	NpcTalkBox->AddButton("����", [this]() 
		{
			SkullUpgrade();
		});

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
			MsgAssert_Rtti<ArachneNPC>(" - �� �� �󰡰� �߸�����");
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
			NpcTalkBox->SetTalkMainText(L"���������� ���� ���ڰ� �ʿ��� �� �ƴ϶��, �ٸ� �Ӹ��� ��� ���� �� ���� �� ������.", TalkEnd);
		};

		std::function<void()> Talk1 = [this, Talk2]()
		{
			NpcTalkBox->SetTalkMainText(L"������ �� �Ӹ��� �׳� ���ݾ�. ������ ���� ���� ���ߴ� ���� ���� ���̰�...", Talk2);
		};

		NpcTalkBox->SetTalkMainText(L"�� ���� �ٵ�... �װ� ������ �Ӹ��� ���� ������ �������� ���� ã�� ���ְڴٰ�.", Talk1);
		NpcTalkBox->ButtonDisable();
	}

	else if (static_cast<size_t>(-1) == Data.UpgradeIndex)
	{
		std::function<void()> TalkEnd = [this]()
		{
			TalkEndCallback();
		};

		NpcTalkBox->SetTalkMainText(L"�� �Ӹ��� �Ұ�����, ������. �̹� �Ӹ��� ���� ��� ���� ����ϰ� �־�.\n�� �̻��� �������� ������ ���� ���� �ž�.", TalkEnd);
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

		NpcTalkBox->YesOrNoActive(L"����߳� ������. ����, ���� ���¸� �����ϴ�... " + std::to_wstring(Price) + L"�� ������ �������̶�� ����� ������ �� �ְڴµ�?",
			[this, Price]() // Yes Callback
			{
				if (Inventory::GetGoodsCount_Bone() < Price)
				{
					std::function<void()> TalkEnd = [this]()
					{
						TalkEndCallback();
					};

					NpcTalkBox->SetTalkMainText(L"�ƹ��� ���� �پ��, ���°� â���� �� ���� ����.���� �װ� ���� ��������δ� �ξ��� ������.", TalkEnd);
					NpcTalkBox->YesOrNoDisable();
				}
				else
				{
					std::function<void()> TalkEnd = [this, Price]()
					{

						if (nullptr == PlayerPtr)
						{
							MsgAssert_Rtti<ArachneNPC>(" - �� �� �߸�����");
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

					NpcTalkBox->SetTalkMainText(L"����, ����ϱ���. �������� ��� �� �տ� ����.", TalkEnd);
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
