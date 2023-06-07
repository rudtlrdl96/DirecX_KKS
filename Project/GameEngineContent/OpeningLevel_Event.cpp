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
				TalkBoxPtr->SetMainText(L"지금 다른 스켈레톤들이 녀석들과 싸우고 있으니, 어서 오른쪽 방향키를 눌러서 인간들을 쫓아가.", SkeleTongTalk_3);
			};

			std::function<void()> SkeleTongTalk_1 = [this, SkeleTongTalk_2]()
			{
				TalkBoxPtr->SetMainText(L"인간 놈들의 습격이 시작되었어..!", SkeleTongTalk_2);
			};

			TalkBoxPtr->ActiveTalkBox("스켈레-통");
			TalkBoxPtr->SetMainText(L"뭐, 일단 정신 똑바로 차리고 들어!", SkeleTongTalk_1);
		});

	// 수켈레톤 이벤트

	AddEvent("Suekeleton_Script00", LevelCode, [this]()
		{
			std::function<void()> SuekeletonTalk_4 = [this]()
			{
				TalkBoxPtr->SetMainText(L"어, 어, 어서 이리 올라와..!", [this]()
					{
						MainCamCtrl.DisalbeForceLookAt();
						MainPlayer->ActivePlayerFrame();
						MainPlayer->InputUnlock();
						TalkBoxPtr->Off();
						CallEvent("StoryFadeOut");
						CallEvent("Suekeleton_Script00_End");
					});
			};

			std::function<void()> SuekeletonTalk_3 = [this, SuekeletonTalk_4]()
			{
				TalkBoxPtr->SetMainText(L"C를 눌러 점프할 수 있어. 두 번 누르면 2단 점프가 가능해.", SuekeletonTalk_4);
			};

			std::function<void()> SuekeletonTalk_2 = [this, SuekeletonTalk_3]()
			{
				TalkBoxPtr->SetMainText(L"너, 너, 너는 무사했구나..! 나, 나, 나는 더 이상 움질일 수가 어, 어, 없어..!", SuekeletonTalk_3);
			};

			std::function<void()> SuekeletonTalk_1 = [this, SuekeletonTalk_2]()
			{
				TalkBoxPtr->SetMainText(L"여, 여, 여기야..!", SuekeletonTalk_2);
			};

			MainCamCtrl.ActiveForceLookAt(float4(1880, 500));

			CallEvent("StoryFadeIn");
			TalkBoxPtr->ActiveTalkBox("수-켈레톤");
			TalkBoxPtr->SetMainText(L"오!!, 리, 리 리틀본!!", SuekeletonTalk_1);
			MainPlayer->InputLock();
			MainPlayer->DisablePlayerFrame();
		});

	AddEvent("PlayerMove_Suekeleton", LevelCode, [this]()
		{
			CallEvent("StoryFadeIn");
			MainPlayer->InputLock();
			MainPlayer->DisablePlayerFrame();

			MainPlayer->PlayStoryMove(float4(2210, 634), [this]()
				{
					CallEvent("Suekeleton_Script01");
					CallEvent("PlayerLookRight");
				});
		});

	AddEvent("Suekeleton_Script01", LevelCode, [this]()
		{
			std::function<void()> SuekeletonTalk_5 = [this]()
			{
				TalkBoxPtr->SetMainText(L"이, 이, 이걸 받아..!", [this]()
					{
						TalkBoxPtr->Off();
						CallEvent("Suekeleton_Script01_End");
					});
			};

			std::function<void()> SuekeletonTalk_4 = [this, SuekeletonTalk_5]()
			{
				TalkBoxPtr->SetMainText(L"네, 네, 네가 대신 마왕님과 의원님들을 구, 구, 구해줘..!", SuekeletonTalk_5);
			};

			std::function<void()> SuekeletonTalk_3 = [this, SuekeletonTalk_4]()
			{
				TalkBoxPtr->SetMainText(L"나, 나, 나는, 곧 마력이 다할 것 같아...", SuekeletonTalk_4);
			};

			std::function<void()> SuekeletonTalk_2 = [this, SuekeletonTalk_3]()
			{
				TalkBoxPtr->SetMainText(L"나, 나, 나랑 다른 스켈레톤들이 녀석들을 쪼, 쪼, 쫓고 있어..!", SuekeletonTalk_3);
			};

			std::function<void()> SuekeletonTalk_1 = [this, SuekeletonTalk_2]()
			{
				TalkBoxPtr->SetMainText(L"이, 이, 인간 놈들... 마왕성 꼭대기로 나, 나, 날아와 기습해올줄이야...", SuekeletonTalk_2);
			};

			TalkBoxPtr->ActiveTalkBox("수-켈레톤");
			TalkBoxPtr->SetMainText(L"크, 크, 큰일이야! 마왕님과 의원님들이 이, 이, 인간 놈들에게 잡혀가버렸어..!", SuekeletonTalk_1);
		});

	AddEvent("Suekeleton_Script02", LevelCode, [this]()
		{
			std::function<void()> SuekeletonTalk_2 = [this]()
			{
				TalkBoxPtr->SetMainText(L"꼭 마, 마, 마왕님과 의, 의, 의원님들을 구해줘..!", [this]()
					{
						TalkBoxPtr->Off();
						CallEvent("Suekeleton_Script02_End");
						CallEvent("StoryFadeOut");
						CallEvent("PlayerInputUnLock");

						MainPlayer->ActivePlayerFrame();
					});
			};

			std::function<void()> SuekeletonTalk_1 = [this, SuekeletonTalk_2]()
			{
				TalkBoxPtr->SetMainText(L"나, 나, 나한텐 남은 시간이 얼마 없나봐.", SuekeletonTalk_2);
			};

			TalkBoxPtr->ActiveTalkBox("수-켈레톤");
			TalkBoxPtr->SetMainText(L"내, 내, 다리뼈야..! X를 눌러 공격할 수 있어.", SuekeletonTalk_1);
		});

	// 경비대장 이벤트

	AddEvent("ChiefGuard_Script00", LevelCode, [this]()
		{
			std::function<void()> ScriptEnd = [this]()
			{
				CallEvent("ChiefGuard_Script00_End");
				TalkBoxPtr->Off();
			};

			std::function<void()> ChiefGuardTalk_9 = [this, ScriptEnd]()
			{
				TalkBoxPtr->SetMainText(L"그러니 내 머리를 가져가거라! 내 머리에 나의 모든 마력을 담아줄 테니 함께 싸워다오! 동포들을 구해야한다!", ScriptEnd);
			};

			std::function<void()> ChiefGuardTalk_8 = [this, ChiefGuardTalk_9]()
			{
				TalkBoxPtr->SetMainText(L"분하지만 난 더 이상 움직일 수가 없다!", ChiefGuardTalk_9);
			};

			std::function<void()> ChiefGuardTalk_7 = [this, ChiefGuardTalk_8]()
			{
				TalkBoxPtr->ActiveTalkBox("경비 대장");
				TalkBoxPtr->SetMainText(L"리틀본!", ChiefGuardTalk_8);
			};

			std::function<void()> WitchTalk_4 = [this, ChiefGuardTalk_7]()
			{
				TalkBoxPtr->ActiveTalkBox("마녀");
				TalkBoxPtr->SetMainText(L"검은.. 돌...", ChiefGuardTalk_7);
			};

			std::function<void()> ChiefGuardTalk_6 = [this, WitchTalk_4]()
			{
				TalkBoxPtr->SetMainText(L"그 녀석의 힘은, 제가 알던 오우거들과 비교할 수 없을정도로 너무나도 강력한 힘이었습니다...", WitchTalk_4);
			};

			std::function<void()> ChiefGuardTalk_5 = [this, ChiefGuardTalk_6]()
			{
				TalkBoxPtr->ActiveTalkBox("경비 대장");
				TalkBoxPtr->SetMainText(L"뭔가 이상했습니다. 몸에 검은 돌이 박혀있고 정신이 완전히 나간 듯, 저희 말을 전혀 듣지 못하였습니다.", ChiefGuardTalk_6);
			};

			std::function<void()> WitchTalk_3 = [this, ChiefGuardTalk_5]()
			{
				TalkBoxPtr->ActiveTalkBox("마녀");
				TalkBoxPtr->SetMainText(L"오우거? 오우거가 왜? 무슨소리를 하는거냥!", ChiefGuardTalk_5);
			};

			std::function<void()> ChiefGuardTalk_4 = [this, WitchTalk_3]()
			{
				TalkBoxPtr->SetMainText(L"오우거였습니다...", WitchTalk_3);
			};

			std::function<void()> ChiefGuardTalk_3 = [this, ChiefGuardTalk_4]()
			{
				TalkBoxPtr->ActiveTalkBox("경비 대장");
				TalkBoxPtr->SetMainText(L"인간이 아니었습니다.", ChiefGuardTalk_4);
			};

			std::function<void()> WitchTalk_2 = [this, ChiefGuardTalk_3]()
			{
				TalkBoxPtr->SetMainText(L"누가 그랬냥!? 대체 어떤 인간들이냥!?", ChiefGuardTalk_3);
			};

			std::function<void()> WitchTalk_1 = [this, WitchTalk_2]()
			{
				TalkBoxPtr->ActiveTalkBox("마녀");
				TalkBoxPtr->SetMainText(L"최고의 전투력을 가진 스켈레톤인 너를 이지경으로 만들다니...", WitchTalk_2);
			};

			std::function<void()> ChiefGuardTalk_2 = [this, WitchTalk_1]()
			{
				TalkBoxPtr->SetMainText(L"면목없습니다. 저희 스켈레톤 경비대는 전멸한 것 같습니다.", WitchTalk_1);
			};

			std::function<void()> ChiefGuardTalk_1 = [this, ChiefGuardTalk_2]()
			{
				TalkBoxPtr->SetMainText(L"그렇군 리틀본. 네가 구해드린 건가? 인간들과의 전투는 처음이었을 텐데, 대단하군!", ChiefGuardTalk_2);
			};

			std::function<void()> ChiefGuardTalk_0 = [this, ChiefGuardTalk_1]()
			{
				TalkBoxPtr->ActiveTalkBox("경비 대장");
				TalkBoxPtr->SetMainText(L"헉! 마녀님! 무사하셨군요!!", ChiefGuardTalk_1);
			};

			TalkBoxPtr->ActiveTalkBox("마녀");
			TalkBoxPtr->SetMainText(L"너는 경비대장이 아니냥? 이게 다 어떻게 된 일이다냥?", ChiefGuardTalk_0);
		});

	AddEvent("ChiefGuard_PlayerMove", LevelCode, [this]()
		{
			CallEvent("PlayerInputLock");
			CallEvent("StoryFadeIn");
			CallEvent("PlayerFrameDisable");

			MainPlayer->PlayStoryMove(float4(925, 250), [this]()
				{				
					CallEvent("ChiefGuard_Script00");
					CallEvent("PlayerLookRight");
				});
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