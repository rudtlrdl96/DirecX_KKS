#include "PrecompileHeader.h"
#include "OpeningLevel.h"
#include "TalkBox.h"
#include "Player.h"
#include "FadeActor.h"

void OpeningLevel::CreateOpeningEvent()
{
	// ���̷��� �̺�Ʈ
	AddEvent("SkeleTong_Script00", LevelCode, [this]()
		{
			std::function<void()> SkeleTongTalk_4 = [this]()
			{
				TalkBoxPtr->SetMainText(L"�̳� �׾���� �ǰ�... �� �༮ �׾����� �� �Ǵ°ǵ�...", [this]()
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
				TalkBoxPtr->SetMainText(L"��!! ��Ʋ��!", SkeleTongTalk_3);
			};

			std::function<void()> SkeleTongTalk_1 = [this, SkeleTongTalk_2]()
			{
				TalkBoxPtr->SetMainText(L"��������! �������� �ȵ�!", SkeleTongTalk_2);
			};

			CallEvent("StoryFadeIn");
			TalkBoxPtr->ActiveTalkBox("???");
			TalkBoxPtr->SetMainText(L"����! �Ͼ!", SkeleTongTalk_1);
			MainPlayer->InputLock();
			MainPlayer->DisablePlayerFrame();
		});

	AddEvent("SkeleTong_Script01", LevelCode, [this]()
		{
			std::function<void()> SkeleTongTalk_1 = [this]()
			{
				TalkBoxPtr->SetMainText(L"��¦ ��� ������ �Ҿ�������, �ٺ�������! ��������! ���Ⱑ ����� �� �� ����?", [this]()
					{
						TalkBoxPtr->Off();
						CallEvent("SkeleTong_Script01_End");
					});
			};

			TalkBoxPtr->ActiveTalkBox("���̷�-��");
			TalkBoxPtr->SetMainText(L"��!! �����̴�. ���� ����־�����...", SkeleTongTalk_1);
		});

	AddEvent("SkeleTong_Script02", LevelCode, [this]()
		{
			TalkBoxPtr->ActiveTalkBox("���̷�-��");
			TalkBoxPtr->SetMainText(L"�̻��� ���̳�... �ƹ�ư �����̾�.", [this]()
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
				TalkBoxPtr->SetMainText(L"�༮���� ������ ȸ���� �� �ִ� ������ε� ���Ǵ� ���� ��!", SkeleTongTalk_6);
			};

			std::function<void()> SkeleTongTalk_4 = [this, SkeleTongTalk_5]()
			{
				TalkBoxPtr->SetMainText(L"���! Z�� ������ �� ���� ������ �� ������! �ð��� ����!", SkeleTongTalk_5);
			};

			std::function<void()> SkeleTongTalk_3 = [this, SkeleTongTalk_4]()
			{
				TalkBoxPtr->SetMainText(L"�� ������ ���� ����. �ٸ� ������ ��𼱰� �ϳ� �����ͼ� ���̸� �Ǵϱ�.", SkeleTongTalk_4);
			};

			std::function<void()> SkeleTongTalk_2 = [this, SkeleTongTalk_3]()
			{
				TalkBoxPtr->SetMainText(L"���� �ٸ� ���̷������ �༮��� �ο�� ������, � ������ ����Ű�� ������ �ΰ����� �Ѿư�.", SkeleTongTalk_3);
			};

			std::function<void()> SkeleTongTalk_1 = [this, SkeleTongTalk_2]()
			{
				TalkBoxPtr->SetMainText(L"�ΰ� ����� ������ ���۵Ǿ���..!", SkeleTongTalk_2);
			};

			TalkBoxPtr->ActiveTalkBox("���̷�-��");
			TalkBoxPtr->SetMainText(L"��, �ϴ� ���� �ȹٷ� ������ ���!", SkeleTongTalk_1);
		});

	// ���̷��� �̺�Ʈ

	AddEvent("Suekeleton_Script00", LevelCode, [this]()
		{
			std::function<void()> SuekeletonTalk_4 = [this]()
			{
				TalkBoxPtr->SetMainText(L"��, ��, � �̸� �ö��..!", [this]()
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
				TalkBoxPtr->SetMainText(L"C�� ���� ������ �� �־�. �� �� ������ 2�� ������ ������.", SuekeletonTalk_4);
			};

			std::function<void()> SuekeletonTalk_2 = [this, SuekeletonTalk_3]()
			{
				TalkBoxPtr->SetMainText(L"��, ��, �ʴ� �����߱���..! ��, ��, ���� �� �̻� ������ ���� ��, ��, ����..!", SuekeletonTalk_3);
			};

			std::function<void()> SuekeletonTalk_1 = [this, SuekeletonTalk_2]()
			{
				TalkBoxPtr->SetMainText(L"��, ��, �����..!", SuekeletonTalk_2);
			};

			MainCamCtrl.ActiveForceLookAt(float4(1880, 500));

			CallEvent("StoryFadeIn");
			TalkBoxPtr->ActiveTalkBox("��-�̷���");
			TalkBoxPtr->SetMainText(L"��!!, ��, �� ��Ʋ��!!", SuekeletonTalk_1);
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
				TalkBoxPtr->SetMainText(L"��, ��, �̰� �޾�..!", [this]()
					{
						TalkBoxPtr->Off();
						CallEvent("Suekeleton_Script01_End");
					});
			};

			std::function<void()> SuekeletonTalk_4 = [this, SuekeletonTalk_5]()
			{
				TalkBoxPtr->SetMainText(L"��, ��, �װ� ��� ���մ԰� �ǿ��Ե��� ��, ��, ������..!", SuekeletonTalk_5);
			};

			std::function<void()> SuekeletonTalk_3 = [this, SuekeletonTalk_4]()
			{
				TalkBoxPtr->SetMainText(L"��, ��, ����, �� ������ ���� �� ����...", SuekeletonTalk_4);
			};

			std::function<void()> SuekeletonTalk_2 = [this, SuekeletonTalk_3]()
			{
				TalkBoxPtr->SetMainText(L"��, ��, ���� �ٸ� ���̷������ �༮���� ��, ��, �Ѱ� �־�..!", SuekeletonTalk_3);
			};

			std::function<void()> SuekeletonTalk_1 = [this, SuekeletonTalk_2]()
			{
				TalkBoxPtr->SetMainText(L"��, ��, �ΰ� ���... ���ռ� ������ ��, ��, ���ƿ� ����ؿ����̾�...", SuekeletonTalk_2);
			};

			TalkBoxPtr->ActiveTalkBox("��-�̷���");
			TalkBoxPtr->SetMainText(L"ũ, ũ, ū���̾�! ���մ԰� �ǿ��Ե��� ��, ��, �ΰ� ��鿡�� ���������Ⱦ�..!", SuekeletonTalk_1);
		});

	AddEvent("Suekeleton_Script02", LevelCode, [this]()
		{
			std::function<void()> SuekeletonTalk_2 = [this]()
			{
				TalkBoxPtr->SetMainText(L"�� ��, ��, ���մ԰� ��, ��, �ǿ��Ե��� ������..!", [this]()
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
				TalkBoxPtr->SetMainText(L"��, ��, ������ ���� �ð��� �� ������.", SuekeletonTalk_2);
			};

			TalkBoxPtr->ActiveTalkBox("��-�̷���");
			TalkBoxPtr->SetMainText(L"��, ��, �ٸ�����..! X�� ���� ������ �� �־�.", SuekeletonTalk_1);
		});

	// ������ �̺�Ʈ

	AddEvent("ChiefGuard_Script00", LevelCode, [this]()
		{
			std::function<void()> ScriptEnd = [this]()
			{
				CallEvent("ChiefGuard_Script00_End");
				TalkBoxPtr->Off();
			};

			std::function<void()> ChiefGuardTalk_9 = [this, ScriptEnd]()
			{
				TalkBoxPtr->SetMainText(L"�׷��� �� �Ӹ��� �������Ŷ�! �� �Ӹ��� ���� ��� ������ ����� �״� �Բ� �ο��ٿ�! �������� ���ؾ��Ѵ�!", ScriptEnd);
			};

			std::function<void()> ChiefGuardTalk_8 = [this, ChiefGuardTalk_9]()
			{
				TalkBoxPtr->SetMainText(L"�������� �� �� �̻� ������ ���� ����!", ChiefGuardTalk_9);
			};

			std::function<void()> ChiefGuardTalk_7 = [this, ChiefGuardTalk_8]()
			{
				TalkBoxPtr->ActiveTalkBox("��� ����");
				TalkBoxPtr->SetMainText(L"��Ʋ��!", ChiefGuardTalk_8);
			};

			std::function<void()> WitchTalk_4 = [this, ChiefGuardTalk_7]()
			{
				TalkBoxPtr->ActiveTalkBox("����");
				TalkBoxPtr->SetMainText(L"����.. ��...", ChiefGuardTalk_7);
			};

			std::function<void()> ChiefGuardTalk_6 = [this, WitchTalk_4]()
			{
				TalkBoxPtr->SetMainText(L"�� �༮�� ����, ���� �˴� ����ŵ�� ���� �� ���������� �ʹ����� ������ ���̾����ϴ�...", WitchTalk_4);
			};

			std::function<void()> ChiefGuardTalk_5 = [this, ChiefGuardTalk_6]()
			{
				TalkBoxPtr->ActiveTalkBox("��� ����");
				TalkBoxPtr->SetMainText(L"���� �̻��߽��ϴ�. ���� ���� ���� �����ְ� ������ ������ ���� ��, ���� ���� ���� ���� ���Ͽ����ϴ�.", ChiefGuardTalk_6);
			};

			std::function<void()> WitchTalk_3 = [this, ChiefGuardTalk_5]()
			{
				TalkBoxPtr->ActiveTalkBox("����");
				TalkBoxPtr->SetMainText(L"�����? ����Ű� ��? �����Ҹ��� �ϴ°ų�!", ChiefGuardTalk_5);
			};

			std::function<void()> ChiefGuardTalk_4 = [this, WitchTalk_3]()
			{
				TalkBoxPtr->SetMainText(L"����ſ����ϴ�...", WitchTalk_3);
			};

			std::function<void()> ChiefGuardTalk_3 = [this, ChiefGuardTalk_4]()
			{
				TalkBoxPtr->ActiveTalkBox("��� ����");
				TalkBoxPtr->SetMainText(L"�ΰ��� �ƴϾ����ϴ�.", ChiefGuardTalk_4);
			};

			std::function<void()> WitchTalk_2 = [this, ChiefGuardTalk_3]()
			{
				TalkBoxPtr->SetMainText(L"���� �׷���!? ��ü � �ΰ����̳�!?", ChiefGuardTalk_3);
			};

			std::function<void()> WitchTalk_1 = [this, WitchTalk_2]()
			{
				TalkBoxPtr->ActiveTalkBox("����");
				TalkBoxPtr->SetMainText(L"�ְ��� �������� ���� ���̷����� �ʸ� ���������� ����ٴ�...", WitchTalk_2);
			};

			std::function<void()> ChiefGuardTalk_2 = [this, WitchTalk_1]()
			{
				TalkBoxPtr->SetMainText(L"�������ϴ�. ���� ���̷��� ����� ������ �� �����ϴ�.", WitchTalk_1);
			};

			std::function<void()> ChiefGuardTalk_1 = [this, ChiefGuardTalk_2]()
			{
				TalkBoxPtr->SetMainText(L"�׷��� ��Ʋ��. �װ� ���ص帰 �ǰ�? �ΰ������ ������ ó���̾��� �ٵ�, ����ϱ�!", ChiefGuardTalk_2);
			};

			std::function<void()> ChiefGuardTalk_0 = [this, ChiefGuardTalk_1]()
			{
				TalkBoxPtr->ActiveTalkBox("��� ����");
				TalkBoxPtr->SetMainText(L"��! �����! �����ϼ̱���!!", ChiefGuardTalk_1);
			};

			TalkBoxPtr->ActiveTalkBox("����");
			TalkBoxPtr->SetMainText(L"�ʴ� �������� �ƴϳ�? �̰� �� ��� �� ���̴ٳ�?", ChiefGuardTalk_0);
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


	// �� �̺�Ʈ
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
				TalkBoxPtr->ActiveTalkBox("�����");
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
				TalkBoxPtr->SetMainText(L"�̺� �ű�-!?", MongalTalk_0);
			};

			MainPlayer->InputLock();
			TalkBoxPtr->ActiveTalkBox("����");
			TalkBoxPtr->SetMainText(L"���� ���տ� ���ִ� �� �������� ���� ���찡 �ƴϳ�-!?", WitchTalk_1);
		});

	AddEvent("MongalWalkUp_Talk", LevelCode, [this]()
		{
			std::function<void()> WitchTalk_2 = [this]()
			{
				TalkBoxPtr->SetMainText(L"�� ������ ������ ���δٳ�-! �ϴ� ���ϴ� ������ ���� �̾߱� ���ڳ�-!!", [this]()
					{
						CallEvent("Mongal_Laugh");
						TalkBoxPtr->Off();
					});
			};

			std::function<void()> WitchTalk_1 = [this, WitchTalk_2]()
			{
				TalkBoxPtr->SetMainText(L"���� �������-!", WitchTalk_2);
			};

			TalkBoxPtr->ActiveTalkBox("����");
			TalkBoxPtr->SetMainText(L"�������� ���� ����Ű� �̳༮�̾���.", WitchTalk_1);
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
				TalkBoxPtr->SetMainText(L"������ ���� �ڽĵ�...", [this]()
					{
						CallEvent("Story_FirstHeroTalk0_End");
						TalkBoxPtr->Off();
					});
			};

			std::function<void()> FirstHeroTalk_0 = [this, FirstHeroTalk_1]()
			{
				TalkBoxPtr->ActiveTalkBox("�ʴ� ���");
				TalkBoxPtr->SetMainText(L"������� �༮... ���� ���̷��濡�� ���ϴٴ�.", FirstHeroTalk_1);
			};

			TalkBoxPtr->ActiveTalkBox("����");
			TalkBoxPtr->SetMainText(L"��..���!?", FirstHeroTalk_0);
		});

	AddEvent("PlayerMove_MongalWalkup", LevelCode, [this]()
		{
			CallEvent("PlayerLookRight");

			MainCamCtrl.SetCameraPos(float4(1480, 250));
			MainPlayer->GetTransform()->SetLocalPosition(float4(1480, 250));
		});
}