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
			MainCamCtrl.SetLookatSpeed(0.5f);
			MainCamCtrl.SetMaxHeight(7000);

			MainCamCtrl.ActiveForceLookAt(float4(896, 1600, 0));
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
			MainPlayer->PlayStoryMove(float4(790, 250, 1), [this]()
				{
					CallEvent("PlayerLookRight");
				});

			MainCamCtrl.SetLookatSpeed(2.0f);
			MainCamCtrl.ActiveForceLookAt(float4(1248, 250, 1));
		
			TimeEvent.AddEvent(2.5f, [this](GameEngineTimeEvent::TimeEvent&, GameEngineTimeEvent*)
				{
					CallEvent("RookieHero_Script00");
				});
		});
}