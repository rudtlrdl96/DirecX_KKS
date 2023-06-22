#include "PrecompileHeader.h"
#include "StoryLevel.h"

void StoryLevel::SetOpeningBook()
{
	StoryName Key = StoryName::Opening;
	StoryBook& BookRef = StoryBookDatas[Key];

	BookRef.StoryView = StoryView;
	BookRef.FadeImage = FadeImage;
	BookRef.FontActor = StoryFont;

	StoryPage::FlipCondition TimeAndKeyFlip = StoryPage::FlipCondition::None;
	TimeAndKeyFlip = static_cast<StoryPage::FlipCondition>((int)StoryPage::FlipCondition::AnyKey | (int)StoryPage::FlipCondition::Time);

	{
		StoryPage Page;	
		Page.SetFlip(StoryPage::FlipCondition::UnCondition);
		Page.Write_SetFade();
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::UnCondition);

		std::vector<StoryFontParameter> Datas = std::vector<StoryFontParameter>();
		Datas.resize(1);

		Datas[0].StoryText = "���� ���� ���ִ� ���̾����ϴ�.";

		Page.Write_WriteText(Datas);
		BookRef.InsertPage(Page); 
	}

	{
		StoryPage Page;
		Page.SetFlip(TimeAndKeyFlip, 3.0f);
		Page.Write_SetMainTex("Story_Opening_00.png", float4(375, -14));
		Page.Write_SetBackTex("Story_Back.png", float4(0, 50));
		Page.Write_FadeOut(0.5f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::UnCondition, 2.0f);

		std::vector<StoryFontParameter> Datas = std::vector<StoryFontParameter>();
		Datas.resize(3);

		Datas[0].StoryText = "�ҳ��� ����ؼ� �޷Ⱦ��.";
		Datas[0].Line = -0.5f;
		Datas[0].PosX = -100.0f;

		Datas[1].StoryText = "�� �ڸ� ���� ��ü�� �Ѿ���.";
		Datas[1].Line = -0.5f;
		Datas[1].PosX = 110.0f;

		Datas[2].StoryText = "���� �ٸ��� ������ ������ �������� �߰��ڴ� �ᱹ �ҳ��� ������Ҿ��.";
		Datas[2].Line = 0.5f;

		Page.Write_WriteText(Datas);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_MoveMainTex(float4(-1023, 0, 0, 0), 3000);
		Page.Write_ReadText();
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SetSubTex("Story_Opening_01.png", {0, 35});
		Page.Write_SwapTex();
		Page.Write_ReadText();
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_Opening_02.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);

		std::vector<StoryFontParameter> Datas = std::vector<StoryFontParameter>();
		Datas.resize(3);

		Datas[0].StoryText = "�ҳ��� �ᱹ ���� �������� ";
		Datas[0].Line = -0.5f;
		Datas[0].PosX = -130.0f;

		Datas[1].StoryText = "�׷� �ҳ��� ���� �׸��ڰ� �帮�������.";
		Datas[1].Line = -0.5f;
		Datas[1].PosX = 130.0f;

		Datas[2].StoryText = "�׸���...";
		Datas[2].Line = 0.5f;

		Page.Write_WriteText(Datas);

		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_Opening_03.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		Page.Write_ReadText();
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_ReadText();
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SetFade();
		Page.Write_ResetText();
		Page.Write_ResetText();
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_FadeOut(1.0f);
		Page.Write_SetMainTex("Story_Opening_04.png", { 0, -14 });
		Page.Write_SetSubTex("Empty.png", { 0, 0 });
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::Time, 1.0f);

		std::vector<StoryFontParameter> Datas = std::vector<StoryFontParameter>();
		Datas.resize(2);

		Datas[0].StoryText = "���� �� �ҳ��� �������� ���Ѻ��� �߾��.";
		Datas[0].Line = 0.0f;
		Datas[0].PosX = -40.0f;

		Datas[1].StoryText = "�ҽ��� ��..";
		Datas[1].Line = 0.0f;
		Datas[1].PosX = 165.0f;

		Page.Write_WriteText(Datas);

		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_Opening_05.png", { 508, 2 });
		Page.Write_FadeIntro(1.0f);
		Page.Write_ReadText();
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_FadeIn(0.33f);
		Page.Write_ResetText();
		BookRef.InsertPage(Page);
	}
}

void StoryLevel::SetForestOfHarmonyBook()
{
	StoryName Key = StoryName::ForestOfHarmony;
	StoryBook& BookRef = StoryBookDatas[Key];

	BookRef.StoryView = StoryView;
	BookRef.FadeImage = FadeImage;
	BookRef.FontActor = StoryFont;


	StoryPage::FlipCondition KeyAndTimeFlip = StoryPage::FlipCondition::None;
	KeyAndTimeFlip = static_cast<StoryPage::FlipCondition>((int)StoryPage::FlipCondition::AnyKey | (int)StoryPage::FlipCondition::Time);

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::UnCondition);
		Page.Write_SetFade();
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(KeyAndTimeFlip, 3.0f);

		std::vector<StoryFontParameter> Datas = std::vector<StoryFontParameter>();
		Datas.resize(1);

		Datas[0].StoryText = "�׳��� �������� �ۿ� �������.";
		Datas[0].Line = 0.0f;

		Page.Write_WriteText(Datas);
	}

	{
		StoryPage Page;

		Page.SetFlip(KeyAndTimeFlip, 3.0f);
		Page.Write_SetMainTex("Story_ForestOfHarmony_00.png", float4(0, 35));
		Page.Write_FadeOut(0.5f);

		std::vector<StoryFontParameter> Datas = std::vector<StoryFontParameter>();
		Datas.resize(3);

		Datas[0].StoryText = "���մ԰� �Բ� ��ȭ�� ���� ������ �־���.";
		Datas[0].Line = -0.5f;
		Datas[0].PosX = -220.0f;

		Datas[1].StoryText = "���������� Į���� ����� �ٽ� �ѹ� �����Ϸ� ���� ���̾����.";
		Datas[1].Line = -0.5f;
		Datas[1].PosX = 175.0f;

		Datas[2].StoryText = "Į���� ������ ������� ����, ���մ��� ���� ����ĥ ���� �Ǿ��ٴ� �̾߱⸦ �߾���.";
		Datas[2].Line = 0.5f;

		Page.Write_WriteText(Datas);

		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_ReadText();
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_ForestOfHarmony_01.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		Page.Write_ReadText();
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_ForestOfHarmony_02.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);

		std::vector<StoryFontParameter> Datas = std::vector<StoryFontParameter>();
		Datas.resize(2);

		Datas[0].StoryText = "�׶� �Ҿ� �ΰ� �ҳ� �ϳ��� ��Ÿ�����.";
		Datas[0].Line = -0.5f;

		Datas[1].StoryText = "��ġ ���� �� �� ���� �úҰ��� ����� �ϰ� �־���ϴ�.";
		Datas[1].Line = 0.5f;

		Page.Write_WriteText(Datas);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_ReadText();
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_ForestOfHarmony_03.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);

		std::vector<StoryFontParameter> Datas = std::vector<StoryFontParameter>();
		Datas.resize(2);

		Datas[0].StoryText = "���߰;��� ���信, ��������... ��� ���̿������?";
		Datas[0].Line = -0.5f;

		Datas[1].StoryText = "ó�� ���� �ҳ⿡ ��� ��������, ���մ��� �ƴ� ���� ���߾��.";
		Datas[1].Line = 0.5f;

		Page.Write_WriteText(Datas);

		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_ReadText();
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);

		std::vector<StoryFontParameter> Datas = std::vector<StoryFontParameter>();
		Datas.resize(2);

		Datas[0].StoryText = "�ҳ��� �츮�� ���鿡�� ������ ���Դ� �پ��� ��縦 ��ġ��, ���� ��� ��°� �ʹ���...";
		Datas[0].Line = -0.5f;

		Datas[1].StoryText = "�̵� ���� ���մԿ��� �޷������.";
		Datas[1].Line = 0.5f;

		Page.Write_WriteText(Datas);

		BookRef.InsertPage(Page);	
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_ForestOfHarmony_04.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		Page.Write_ReadText();
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_ForestOfHarmony_05.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);

		std::vector<StoryFontParameter> Datas = std::vector<StoryFontParameter>();
		Datas.resize(2);

		Datas[0].StoryText = "�� ���� ���ڰŸ� ��, �׵��� ���� ģ��ó�� ��ȭ�� ������ �����߾��.";
		Datas[0].Line = -0.5f;

		Datas[1].StoryText = "���հ� �������� �ΰ��̶�... ����ִ� �ҳ��̶� ��������.";
		Datas[1].Line = 0.5f;

		Page.Write_WriteText(Datas);

		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_ReadText();
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_ForestOfHarmony_06.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);

		std::vector<StoryFontParameter> Datas = std::vector<StoryFontParameter>();
		Datas.resize(3);

		Datas[0].StoryText = "�ҳ��� �ٽ� �ѹ� ��� ����� � ������ ����, ��簡 �ǰ� �ʹ� ���߾��.";
		Datas[0].Line = -0.5f;
		Datas[0].PosX = -170.0f;

		Datas[1].StoryText = "�ƹ����� �ڶ������� �Ƶ��� �ǰ� �ʹٸ鼭.";
		Datas[1].Line = -0.5f;
		Datas[1].PosX = 283.0f;

		Datas[2].StoryText = "���մ��� �����ϰ� ������ �׿��� �Ƿ��� ��簡 �� �� ���� �Ŷ� �ٵ������.";
		Datas[2].Line = 0.5f;

		Page.Write_WriteText(Datas);

		BookRef.InsertPage(Page);
	}


	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_ReadText();
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_ReadText();
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_ForestOfHarmony_07.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);

		std::vector<StoryFontParameter> Datas = std::vector<StoryFontParameter>();
		Datas.resize(2);

		Datas[0].StoryText = "��°�� ���մ��� ���� �ҳ��� ģ���ϰ� ���ϴ� ���� �� �� ������.";
		Datas[0].Line = -0.5f;

		Datas[1].StoryText = "��簡 �ǰ�ʹٴ� ���� �ǹ̸� �˰� �ֱ�� �Ѱ���...";
		Datas[1].Line = 0.5f;

		Page.Write_WriteText(Datas);

		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_ReadText();
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_ForestOfHarmony_08.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);

		std::vector<StoryFontParameter> Datas = std::vector<StoryFontParameter>();
		Datas.resize(3);

		Datas[0].StoryText = "�ҳ��� �츮���� �ۺ� �λ縦 �ǳ� �� �������.";
		Datas[0].Line = -0.5f;

		Datas[1].StoryText = "�װ� ���� ��, ���� �ҳ��� ��ü�� ���� �������.";
		Datas[1].Line = 0.5f;
		Datas[1].PosX = -240.0f;

		Datas[2].StoryText = "���� ��� �������� �ҳ�, ������ �����ϴ� ���� ������ �����ŵ��.";
		Datas[2].Line = 0.5f;
		Datas[2].PosX = 190.0f;

		Page.Write_WriteText(Datas);

		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_ReadText();
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_ReadText();
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_ForestOfHarmony_09.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);

		std::vector<StoryFontParameter> Datas = std::vector<StoryFontParameter>();
		Datas.resize(2);

		Datas[0].StoryText = "���մ��� �� �ҳ��� �� �� ���� ���� ������ �ִ� ������.";
		Datas[0].Line = -0.5f;

		Datas[1].StoryText = "�� ���� ���ռ��� Į����, �� ���ư� �ϸ�Ͼ� ����� ������ �� ���� �Ŷ� ���߾��.";
		Datas[1].Line = 0.5f;

		Page.Write_WriteText(Datas);

		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_ReadText();
		BookRef.InsertPage(Page);
	}

	{	
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);

		std::vector<StoryFontParameter> Datas = std::vector<StoryFontParameter>();
		Datas.resize(3);

		Datas[0].StoryText = "�� ���� �ҳ��� ������.";
		Datas[0].Line = -0.5f;
		Datas[0].PosX = -200.0f;

		Datas[1].StoryText = "�ҳ��� �Ƿ��� ��簡 �Ƿ��� �󸶳� ��ٷ��� �ұ��?";
		Datas[1].Line = -0.5f;
		Datas[1].PosX = 90.0f;

		Datas[2].StoryText = "�� ���� ����� �������� ���ӵ� �� �������?";
		Datas[2].Line = 0.5f;

		Page.Write_WriteText(Datas);

		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_ReadText();
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_ReadText();
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_ForestOfHarmony_10.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);

		std::vector<StoryFontParameter> Datas = std::vector<StoryFontParameter>();
		Datas.resize(1);

		Datas[0].StoryText = "���� �ҳ��� ��� ���Ѻ���� �߾��.";
		Datas[0].Line = -0.0f;

		Page.Write_WriteText(Datas);

		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_FadeIn(0.3f);
		Page.Write_ResetText();
		BookRef.InsertPage(Page);
	}
}

void StoryLevel::SetGrandHallBook()
{
	StoryName Key = StoryName::GranHall;
	StoryBook& BookRef = StoryBookDatas[Key];

	BookRef.StoryView = StoryView;
	BookRef.FadeImage = FadeImage;
	BookRef.FontActor = StoryFont;

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::UnCondition);
		Page.Write_SetFade();
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		StoryPage::FlipCondition Flip = StoryPage::FlipCondition::None;
		Flip = static_cast<StoryPage::FlipCondition>((int)StoryPage::FlipCondition::AnyKey | (int)StoryPage::FlipCondition::Time);

		Page.SetFlip(Flip, 3.0f);
		Page.Write_SetMainTex("Story_GrandHall_00.png", float4(0, 35));
		Page.Write_FadeOut(0.5f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_GrandHall_01.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_GrandHall_02.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_GrandHall_03.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_GrandHall_04.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_GrandHall_05.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_GrandHall_06.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_GrandHall_07.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_GrandHall_08.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_GrandHall_09.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_GrandHall_10.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_GrandHall_11.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_GrandHall_12.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_FadeIn(0.3f);
		BookRef.InsertPage(Page);
	}
}

void StoryLevel::SetHolyCourtyard()
{
	StoryName Key = StoryName::HolyCourtyard;
	StoryBook& BookRef = StoryBookDatas[Key];

	BookRef.StoryView = StoryView;
	BookRef.FadeImage = FadeImage;
	BookRef.FontActor = StoryFont;

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::UnCondition);
		Page.Write_SetFade();
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		StoryPage::FlipCondition Flip = StoryPage::FlipCondition::None;
		Flip = static_cast<StoryPage::FlipCondition>((int)StoryPage::FlipCondition::AnyKey | (int)StoryPage::FlipCondition::Time);

		Page.SetFlip(Flip, 3.0f);
		Page.Write_SetMainTex("Story_HolyCourtyard_00.png", float4(0, 35));
		Page.Write_FadeOut(0.5f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_HolyCourtyard_01.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_HolyCourtyard_02.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_HolyCourtyard_03.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_FortressOfFate_06.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_FortressOfFate_14.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_HolyCourtyard_03.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_FadeIn(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SetMainTex("Story_HolyCourtyard_07.png", { 0, 35 });
		Page.Write_FadeOut(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_HolyCourtyard_08.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_HolyCourtyard_09.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_HolyCourtyard_10.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_HolyCourtyard_11.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_HolyCourtyard_12.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_FadeIn(0.3f);
		BookRef.InsertPage(Page);
	}
}

void StoryLevel::SetEndingBook()
{
	StoryName Key = StoryName::Ending;
	StoryBook& BookRef = StoryBookDatas[Key];

	BookRef.StoryView = StoryView;
	BookRef.FadeImage = FadeImage;
	BookRef.FontActor = StoryFont;

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::UnCondition);
		Page.Write_SetFade();
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		StoryPage::FlipCondition Flip = StoryPage::FlipCondition::None;
		Flip = static_cast<StoryPage::FlipCondition>((int)StoryPage::FlipCondition::AnyKey | (int)StoryPage::FlipCondition::Time);

		Page.SetFlip(Flip, 3.0f);
		Page.Write_SetMainTex("Story_Ending_00.png", float4(0, 35));
		Page.Write_FadeOut(0.5f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_Ending_01.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_Ending_02.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_Ending_03.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_Ending_04.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_Ending_05.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_Ending_06.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_Ending_07.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_Ending_08.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_Ending_09.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_Ending_10.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_Ending_11.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_Ending_12.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_Ending_13.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}
	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_FadeIn(0.3f);
		BookRef.InsertPage(Page);
	}
}

