#include "PrecompileHeader.h"
#include "ForestOfHarmonyLevel.h"
#include "TalkBox.h"
#include "Player.h"
#include "Tilemap.h"

void ForestOfHarmonyLevel::CreateForestOfHarmonyEvent()
{
	AddEvent("BossIntroDown", LevelCode, [this]()
		{
			static bool FirstCheck = false;

			if (false == FirstCheck)
			{
				MainCamCtrl.SetMaxHeight(1460);
				FirstCheck = true;
			}
			else
			{
				MainCamCtrl.DisalbeForceLookAt();
			}
		});

	AddEvent("BossIntroUp", LevelCode, [this]()
		{
			MainCamCtrl.SetLookatSpeed(1.0f);
			MainCamCtrl.SetMaxHeight(7000);

			MainCamCtrl.ActiveForceLookAt(float4(1536, 1600, 0));
			IntroTilemap->FadeOut(1.0f);
		});

	AddEvent("BossIntroUpOut", LevelCode, [this]()
		{
			MainCamCtrl.SetLookatSpeed(7.0f);
			IntroTilemap->FadeIn(1.0f);
		});

	// �߽� ���

	AddEvent("RookieHero_Death", LevelCode, [this]()
		{
			MainCamCtrl.SetLookatSpeed();
			MainCamCtrl.DisalbeForceLookAt();
		});

	AddEvent("RookieHero_Script00", LevelCode, [this]()
		{
			std::function<void()> Talk11 = [this]()
			{
				CallEvent("RookieHero_IntroPotion");
				TalkBoxPtr->SetMainText(L"�Ŀ�... �� �� �ִ�...", [this]()
					{
						TalkBoxPtr->Off();
						CallEvent("PlayerInputUnlock");
						CallEvent("PlayerFrameActive");
						CallEvent("StoryFadeOut");
						CallEvent("RookieHero_Script00_End");
					});
			};
			
			std::function<void()> Talk10 = [this, Talk11]()
			{
				TalkBoxPtr->SetMainText(L"����� �����̶�� ������ ù �������� �Ǹ��� �Ǿ��ٴ°�, �����ϰ� �����ϵ���!", Talk11);
			};

			std::function<void()> Talk09 = [this, Talk10]()
			{
				TalkBoxPtr->SetMainText(L"�� �׷��� ���� ���������� �� �༮���� �ʿ��ߴµ� �� �Ǿ���.", Talk10);
			};

			std::function<void()> Talk08 = [this, Talk09]()
			{
				TalkBoxPtr->SetMainText(L"�̰� �� ���̷����̳�!", Talk09);
			};
			
			std::function<void()> Talk07 = [this, Talk08]()
			{
				CallEvent("RookieHero_IntroWho");
				TalkBoxPtr->SetMainText(L"����! ��", Talk08);
			};

			std::function<void()> Talk06 = [this, Talk07]()
			{			
				CallEvent("RookieHero_Introlol_End");
				TalkBoxPtr->SetMainText(L".....", Talk07);
			};

			std::function<void()> Talk05 = [this, Talk06]()
			{
				TalkBoxPtr->SetMainText(L"�ʴ� ���Ե� �� ������ �˾��ֽð���. ���� ����ƺ�� ���Ⱦ�.", Talk06);
			};

			std::function<void()> Talk04 = [this, Talk05]()
			{
				CallEvent("RookieHero_Introlol");
				TalkBoxPtr->SetMainText(L"������...", Talk05);
			};

			std::function<void()> Talk03 = [this, Talk04]()
			{
				CallEvent("RookieHero_IntroYeah");
				TalkBoxPtr->SetMainText(L"�¾�! ������! ���� �ٷ� �� ����Դϴ�! �Ǽ��� ���������, ������ �����մϴ�!", Talk04);
			};

			std::function<void()> Talk02 = [this, Talk03]()
			{
				TalkBoxPtr->SetMainText(L"���� ����.. �̷��� �������� ������...", Talk03);
			};
						
			std::function<void()> Talk01 = [this, Talk02]()
			{
				CallEvent("RookieHero_IntroComboB");
				TalkBoxPtr->SetMainText(L"�̰ͱ��� �غ���.. �ϳ� �� ��... ��! ���~����!", Talk02);
			};

			CallEvent("RookieHero_IntroComboA");
			TalkBoxPtr->ActiveTalkBox("�߽� ���");
			TalkBoxPtr->SetMainText(L"�ϳ��� ��! �ϳ��� ��!", Talk01);
		});

	AddEvent("RookieHero_Intro", LevelCode, [this]()
		{
			CallEvent("PlayerInputLock");
			CallEvent("PlayerFrameDisable");
			CallEvent("StoryFadeIn");
			MainPlayer->PlayStoryMove(float4(1430, 250, 1), [this]()
				{
					CallEvent("PlayerLookRight");
				});

			MainCamCtrl.SetLookatSpeed(2.0f);
			MainCamCtrl.ActiveForceLookAt(float4(1888, 250, 1));
		
			TimeEvent.AddEvent(2.5f, [this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*)
				{
					CallEvent("RookieHero_Script00");
				});
		});

	// ���� ���
	AddEvent("VeteranHero_Death", LevelCode, [this]()
		{
			CallEvent("PlayerInputLock");
			CallEvent("PlayerFrameDisable");
			CallEvent("StoryFadeIn");
			CallEvent("FadeOut_White");

			ClearWaitTime = 0.0f;
			IsBossClear = true;
		});

	AddEvent("VeteranHero_Script02", LevelCode, [this]()
		{
			ShowBossName("�߽����", "Į������ ���");

			TalkBoxPtr->ActiveTalkBox("�߽� ���");
			TalkBoxPtr->SetMainText(L"������ ���� ���� �غ�� �Ǿ���?", [this]()
				{
					CallEvent("PlayerInputUnlock");
					CallEvent("PlayerFrameActive");
					CallEvent("StoryFadeOut");
					MainCamCtrl.SetLookatSpeed();

					CallEvent("VeteranHero_Script02_End");
					TalkBoxPtr->Off();
				});
		});

	AddEvent("VeteranHero_Script01", LevelCode, [this]()
		{
			std::function<void()> VeteranHeroTalk06 = [this]()
			{
				TalkBoxPtr->SetMainText(L"���� ������ ����� �÷Ȱڴ�. �� �̻� ������ �ʰھ�.", [this]()
					{
						CallEvent("VeteranHero_Script01_End");
						TalkBoxPtr->Off();
					});
			};

			std::function<void()> VeteranHeroTalk05 = [this, VeteranHeroTalk06]()
			{
				TalkBoxPtr->SetMainText(L"�װ� �ƴϸ� ���� �й��� ������ ���ݾ�? ������ ���̷��� ������ ���� ������ �̰ܸ��� ������ �ϴٴ�.", VeteranHeroTalk06);
			};

			std::function<void()> VeteranHeroTalk04 = [this, VeteranHeroTalk05]()
			{
				TalkBoxPtr->SetMainText(L"�� ����̶���?", VeteranHeroTalk05);
			};

			std::function<void()> VeteranHeroTalk03 = [this, VeteranHeroTalk04]()
			{
				TalkBoxPtr->SetMainText(L"���� �� �й�������? ������ �����غþ�. ������ �� �ϳ���.", VeteranHeroTalk04);
			};

			std::function<void()> VeteranHeroTalk02 = [this, VeteranHeroTalk03]()
			{
				TalkBoxPtr->SetMainText(L"��ġ������ �������̾���.", VeteranHeroTalk03);
			};

			std::function<void()> VeteranHeroTalk01 = [this, VeteranHeroTalk02]()
			{
				TalkBoxPtr->SetMainText(L"ù ���迡�� ���� ���̷��� �� �������� �й��ߴٴ� �ҹ��� ������, �ƹ��� �� ������ ���� �ʴ���... �׵��� ���� ������ ���� ���ε��� �غ��ߴµ� ���̾�.", VeteranHeroTalk02);
			};

			TalkBoxPtr->ActiveTalkBox("�߽� ���");
			TalkBoxPtr->SetMainText(L"���̷��� ������ ������� ���ٴ�! ��ħ ���� ȥ���� �� ������ �����̾�. �������� ���� �������� ������ �� �ְھ�.", VeteranHeroTalk01);
		});

	AddEvent("VeteranHero_Script00", LevelCode, [this]()
		{			
			TalkBoxPtr->ActiveTalkBox("�߽� ���");
			TalkBoxPtr->SetMainText(L"���� ������!", [this]()
				{
					CallEvent("VeteranHero_Script00_End");
					TalkBoxPtr->Off();
				});
		});

	AddEvent("VeteranHero_Intro", LevelCode, [this]()
		{
			CallEvent("PlayerInputLock");
			CallEvent("PlayerFrameDisable");
			CallEvent("StoryFadeIn");
			MainPlayer->PlayStoryMove(float4(1480, 250, 1), [this]()
				{
					CallEvent("PlayerLookRight");
				});

			MainCamCtrl.SetLookatSpeed(2.0f);
			MainCamCtrl.ActiveForceLookAt(float4(2016, 250, 1));

			TimeEvent.AddEvent(2.5f, [this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*)
				{
					CallEvent("VeteranHero_Script00");
				});
		});

	//1, 377.5
}