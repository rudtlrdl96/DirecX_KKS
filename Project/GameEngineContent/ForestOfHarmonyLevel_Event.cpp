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

	// 견습 용사

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
				TalkBoxPtr->SetMainText(L"후우... 할 수 있다...", [this]()
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
				TalkBoxPtr->SetMainText(L"용사의 모험이라는 전설의 첫 페이지에 실리게 되었다는걸, 감사하게 생각하도록!", Talk11);
			};

			std::function<void()> Talk09 = [this, Talk10]()
			{
				TalkBoxPtr->SetMainText(L"안 그래도 실전 연습용으로 네 녀석들이 필요했는데 잘 되었군.", Talk10);
			};

			std::function<void()> Talk08 = [this, Talk09]()
			{
				TalkBoxPtr->SetMainText(L"이게 웬 스켈레톤이냐!", Talk09);
			};
			
			std::function<void()> Talk07 = [this, Talk08]()
			{
				CallEvent("RookieHero_IntroWho");
				TalkBoxPtr->SetMainText(L"뭐야! 넌", Talk08);
			};

			std::function<void()> Talk06 = [this, Talk07]()
			{			
				CallEvent("RookieHero_Introlol_End");
				TalkBoxPtr->SetMainText(L".....", Talk07);
			};

			std::function<void()> Talk05 = [this, Talk06]()
			{
				TalkBoxPtr->SetMainText(L"초대 용사님도 이 정도면 알아주시겠지. 이제 허수아비는 질렸어.", Talk06);
			};

			std::function<void()> Talk04 = [this, Talk05]()
			{
				CallEvent("RookieHero_Introlol");
				TalkBoxPtr->SetMainText(L"흐흐흐...", Talk05);
			};

			std::function<void()> Talk03 = [this, Talk04]()
			{
				CallEvent("RookieHero_IntroYeah");
				TalkBoxPtr->SetMainText(L"맞아! 저예요! 제가 바로 그 용사입니다! 악수는 곤란하지만, 사인은 가능합니다!", Talk04);
			};

			std::function<void()> Talk02 = [this, Talk03]()
			{
				TalkBoxPtr->SetMainText(L"좋아 좋아.. 이렇게 마무리한 다음에...", Talk03);
			};
						
			std::function<void()> Talk01 = [this, Talk02]()
			{
				CallEvent("RookieHero_IntroComboB");
				TalkBoxPtr->SetMainText(L"이것까지 해볼까.. 하나 둘 셋... 넷! 용사~등장!", Talk02);
			};

			CallEvent("RookieHero_IntroComboA");
			TalkBoxPtr->ActiveTalkBox("견습 용사");
			TalkBoxPtr->SetMainText(L"하나둘 셋! 하나둘 셋!", Talk01);
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

	// 각성 용사
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
			ShowBossName("견습용사", "칼레온의 희망");

			TalkBoxPtr->ActiveTalkBox("견습 용사");
			TalkBoxPtr->SetMainText(L"정의의 검을 받을 준비는 되었나?", [this]()
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
				TalkBoxPtr->SetMainText(L"이제 레벨도 충분히 올렸겠다. 더 이상 봐주지 않겠어.", [this]()
					{
						CallEvent("VeteranHero_Script01_End");
						TalkBoxPtr->Off();
					});
			};

			std::function<void()> VeteranHeroTalk05 = [this, VeteranHeroTalk06]()
			{
				TalkBoxPtr->SetMainText(L"그게 아니면 내가 패배할 이유는 없잖아? 같잖은 스켈레톤 주제에 감히 용사님을 이겨먹을 생각을 하다니.", VeteranHeroTalk06);
			};

			std::function<void()> VeteranHeroTalk04 = [this, VeteranHeroTalk05]()
			{
				TalkBoxPtr->SetMainText(L"내 방심이랄까?", VeteranHeroTalk05);
			};

			std::function<void()> VeteranHeroTalk03 = [this, VeteranHeroTalk04]()
			{
				TalkBoxPtr->SetMainText(L"내가 왜 패배했을까? 곰곰이 생각해봤어. 이유는 딱 하나야.", VeteranHeroTalk04);
			};

			std::function<void()> VeteranHeroTalk02 = [this, VeteranHeroTalk03]()
			{
				TalkBoxPtr->SetMainText(L"수치스러운 나날들이었다.", VeteranHeroTalk03);
			};

			std::function<void()> VeteranHeroTalk01 = [this, VeteranHeroTalk02]()
			{
				TalkBoxPtr->SetMainText(L"첫 모험에서 고작 스켈레톤 한 마리에게 패배했다는 소문이 퍼지자, 아무도 날 인정해 주지 않더군... 그들을 위해 무수히 많은 사인들을 준비했는데 말이야.", VeteranHeroTalk02);
			};

			TalkBoxPtr->ActiveTalkBox("견습 용사");
			TalkBoxPtr->SetMainText(L"스켈레톤 주제에 여기까지 오다니! 마침 내가 혼자일 때 만나서 다행이야. 개인적인 빚을 이제서야 갚아줄 수 있겠어.", VeteranHeroTalk01);
		});

	AddEvent("VeteranHero_Script00", LevelCode, [this]()
		{			
			TalkBoxPtr->ActiveTalkBox("견습 용사");
			TalkBoxPtr->SetMainText(L"드디어 만났군!", [this]()
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