#include "PrecompileHeader.h"
#include "OpeningLevel.h"
#include "TalkBox.h"
#include "Player.h"
#include "FadeActor.h"

void OpeningLevel::CreateOpeningEvent()
{
	// 스켈레통 이벤트
	AddEvent("SkeleTong_Script00", LevelCode, [this]()
		{
			std::function<void()> SkeleTongTalk_4 = [this]()
			{
				TalkBoxPtr->SetMainText(L"이놈도 죽어버린 건가... 이 녀석 죽었으면 안 되는건데...", [this]()
				{
					TalkBoxPtr->Off();
					CallEvent("SkeleTong_Script00_End");
				});
			};

			std::function<void()> SkeleTongTalk_3 = [this, SkeleTongTalk_4]()
			{
				TalkBoxPtr->SetMainText(L"...", SkeleTongTalk_4);
			};

			std::function<void()> SkeleTongTalk_2 = [this, SkeleTongTalk_3]()
			{
				TalkBoxPtr->SetMainText(L"야!! 리틀본!", SkeleTongTalk_3);
			};

			std::function<void()> SkeleTongTalk_1 = [this, SkeleTongTalk_2]()
			{
				TalkBoxPtr->SetMainText(L"정신차려! 쓰러지면 안돼!", SkeleTongTalk_2);
			};

			CallEvent("StoryFadeIn");
			TalkBoxPtr->ActiveTalkBox("???");
			TalkBoxPtr->SetMainText(L"스컬! 일어나!", SkeleTongTalk_1);
			MainPlayer->InputLock();
			MainPlayer->DisablePlayerFrame();
		});

	AddEvent("SkeleTong_Script01", LevelCode, [this]()
		{
			std::function<void()> SkeleTongTalk_1 = [this]()
			{
				TalkBoxPtr->SetMainText(L"깜짝 놀라서 정신을 잃었나보군, 바보같으니! 정신차려! 여기가 어딘지 알 것 같니?", [this]()
					{
						TalkBoxPtr->Off();
						CallEvent("SkeleTong_Script01_End");
					});
			};

			TalkBoxPtr->ActiveTalkBox("스켈레-통");
			TalkBoxPtr->SetMainText(L"오!! 다행이다. 아직 살아있었구나...", SkeleTongTalk_1);
		});

	AddEvent("SkeleTong_Script02", LevelCode, [this]()
		{
			TalkBoxPtr->ActiveTalkBox("스켈레-통");
			TalkBoxPtr->SetMainText(L"이상한 놈이네... 아무튼 다행이야.", [this]()
				{
					TalkBoxPtr->Off();
					CallEvent("SkeleTong_Script02_End");
				});
		});

	AddEvent("SkeleTong_Script03", LevelCode, [this]()
		{
			std::function<void()> SkeleTongTalk_6 = [this]()
			{
				TalkBoxPtr->Off();
				CallEvent("SkeleTong_Script03_End");
			};

			std::function<void()> SkeleTongTalk_5 = [this, SkeleTongTalk_6]()
			{
				TalkBoxPtr->SetMainText(L"녀석들의 공격을 회피할 수 있는 방법으로도 사용되니 잊지 마!", SkeleTongTalk_6);
			};

			std::function<void()> SkeleTongTalk_4 = [this, SkeleTongTalk_5]()
			{
				TalkBoxPtr->SetMainText(L"어서가! Z를 누르면 더 빨리 움직일 수 있으니! 시간이 없어!", SkeleTongTalk_5);
			};

			std::function<void()> SkeleTongTalk_3 = [this, SkeleTongTalk_4]()
			{
				TalkBoxPtr->SetMainText(L"내 걱정은 하지 말고. 다리 정도는 어디선가 하나 가져와서 붙이면 되니까.", SkeleTongTalk_4);
			};

			std::function<void()> SkeleTongTalk_2 = [this, SkeleTongTalk_3]()
			{
				TalkBoxPtr->SetMainText(L"지금 다른 스켈레톤들이 녀석들과 싸우고 있으니, 어서 아래 방향키를 눌러서 인간들을 쫓아가.", SkeleTongTalk_3);
			};

			std::function<void()> SkeleTongTalk_1 = [this, SkeleTongTalk_2]()
			{
				TalkBoxPtr->SetMainText(L"인간 놈들의 습격이 시작되었어..!", SkeleTongTalk_2);
			};

			TalkBoxPtr->ActiveTalkBox("스켈레-통");
			TalkBoxPtr->SetMainText(L"뭐, 일단 정신 똑바로 차리고 들어!", SkeleTongTalk_1);
		});

	// 몬갈 이벤트
	AddEvent("MongalDeath_Appear", LevelCode, [this]()
		{
			if (true == IsMongalEncounter)
			{
				return;
			}

			IsMongalEncounter = true;

			CallEvent("StoryFadeIn");
			MainCamCtrl.SetLookatSpeed(3.5F);
			MainCamCtrl.ActiveForceLookAt(float4(1800, 250));

			std::function<void()> MongalTalk_0 = [this]()
			{
				TalkBoxPtr->ActiveTalkBox("오우거");
				TalkBoxPtr->SetMainText(L"...", [this]()
					{
						MainCamCtrl.SetLookatSpeed();
						MainPlayer->InputUnlock();
						TalkBoxPtr->Off();
						CallEvent("UnLockCam");
						CallEvent("StoryFadeOut");
					});
			};


			std::function<void()> WitchTalk_1 = [this, MongalTalk_0]()
			{
				TalkBoxPtr->SetMainText(L"이봐 거기-!?", MongalTalk_0);
			};

			MainPlayer->InputLock();
			TalkBoxPtr->ActiveTalkBox("마녀");
			TalkBoxPtr->SetMainText(L"저기 성앞에 서있는 게 경비대장이 말한 오우가 아니냥-!?", WitchTalk_1);
		});

	AddEvent("MongalWalkUp_Talk", LevelCode, [this]()
		{
			std::function<void()> WitchTalk_2 = [this]()
			{
				TalkBoxPtr->SetMainText(L"뭐 지금은 괜찮아 보인다냥-! 일단 급하니 성으로 들어가서 이야기 하자냥-!!", [this]()
					{
						CallEvent("Mongal_Laugh");
						TalkBoxPtr->Off();
					});
			};

			std::function<void()> WitchTalk_1 = [this, WitchTalk_2]()
			{
				TalkBoxPtr->SetMainText(L"정신 차리라냥-!", WitchTalk_2);
			};

			TalkBoxPtr->ActiveTalkBox("마녀");
			TalkBoxPtr->SetMainText(L"경비대장이 말한 오우거가 이녀석이었냥.", WitchTalk_1);
		});

	AddEvent("MongalDeath", LevelCode, [this]()
		{
			MainPlayer->InputLock();

			FadeActorPtr->SetSpeed(1.5f);
			FadeActorPtr->SetWaitTime(0.0f);

			FadeActorPtr->FadeIn([this]()
				{
					FadeActorPtr->FadeOut([this]()
						{
							FadeActorPtr->Reset();
							FadeActorPtr->SetWaitTime(0.5f);
						}, float4::One);
				}, float4::One);
		});


	AddEvent("Story_FirstHeroTalk0", LevelCode, [this]()
		{
			std::function<void()> FirstHeroTalk_1 = [this]()
			{
				TalkBoxPtr->SetMainText(L"더러운 마족 자식들...", [this]()
					{
						CallEvent("Story_FirstHeroTalk0_End");
						TalkBoxPtr->Off();
					});
			};

			std::function<void()> FirstHeroTalk_0 = [this, FirstHeroTalk_1]()
			{
				TalkBoxPtr->ActiveTalkBox("초대 용사");
				TalkBoxPtr->SetMainText(L"쓸모없는 녀석... 고작 스켈레톤에게 패하다니.", FirstHeroTalk_1);
			};

			TalkBoxPtr->ActiveTalkBox("마녀");
			TalkBoxPtr->SetMainText(L"요..용사!?", FirstHeroTalk_0);
		});

	AddEvent("PlayerMove_MongalWalkup", LevelCode, [this]()
		{
			CallEvent("PlayerLookRight");

			MainCamCtrl.SetCameraPos(float4(1480, 250));
			MainPlayer->GetTransform()->SetLocalPosition(float4(1480, 250));
		});
}