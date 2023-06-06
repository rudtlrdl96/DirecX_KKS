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
				TalkBoxPtr->SetMainText(L"���� �ٸ� ���̷������ �༮��� �ο�� ������, � �Ʒ� ����Ű�� ������ �ΰ����� �Ѿư�.", SkeleTongTalk_3);
			};

			std::function<void()> SkeleTongTalk_1 = [this, SkeleTongTalk_2]()
			{
				TalkBoxPtr->SetMainText(L"�ΰ� ����� ������ ���۵Ǿ���..!", SkeleTongTalk_2);
			};

			TalkBoxPtr->ActiveTalkBox("���̷�-��");
			TalkBoxPtr->SetMainText(L"��, �ϴ� ���� �ȹٷ� ������ ���!", SkeleTongTalk_1);
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