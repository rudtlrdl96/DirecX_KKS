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

		Datas[0].StoryText = "밝은 달이 떠있던 밤이었습니다.";

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

		Datas[0].StoryText = "소년은 계속해서 달렸어요.";
		Datas[0].Line = -0.5f;
		Datas[0].PosX = -100.0f;

		Datas[1].StoryText = "그 뒤를 검은 형체가 쫓았죠.";
		Datas[1].Line = -0.5f;
		Datas[1].PosX = 110.0f;

		Datas[2].StoryText = "아픈 다리로 열심히 도망쳐 보았지만 추격자는 결국 소년을 따라잡았어요.";
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

		Datas[0].StoryText = "소년은 결국 지쳐 쓰러졌고 ";
		Datas[0].Line = -0.5f;
		Datas[0].PosX = -130.0f;

		Datas[1].StoryText = "그런 소년의 위에 그림자가 드리워졌어요.";
		Datas[1].Line = -0.5f;
		Datas[1].PosX = 130.0f;

		Datas[2].StoryText = "그리고...";
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

		Datas[0].StoryText = "저는 그 소년의 마지막을 지켜보려 했어요.";
		Datas[0].Line = 0.0f;
		Datas[0].PosX = -40.0f;

		Datas[1].StoryText = "불쌍한 것..";
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

		Datas[0].StoryText = "그날은 오랜만에 밖에 나갔어요.";
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

		Datas[0].StoryText = "마왕님과 함께 조화의 숲을 지나고 있었죠.";
		Datas[0].Line = -0.5f;
		Datas[0].PosX = -220.0f;

		Datas[1].StoryText = "지긋지긋한 칼레온 놈들을 다시 한번 설득하러 가는 길이었어요.";
		Datas[1].Line = -0.5f;
		Datas[1].PosX = 175.0f;

		Datas[2].StoryText = "칼레온 성문에 가까워질 무렵, 마왕님이 슬슬 마주칠 때가 되었다는 이야기를 했었죠.";
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

		Datas[0].StoryText = "그때 불쑥 인간 소년 하나가 나타났어요.";
		Datas[0].Line = -0.5f;

		Datas[1].StoryText = "마치 용사라도 된 것 마냥 꼴불견인 모습을 하고 있었답니다.";
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

		Datas[0].StoryText = "보잘것없는 망토에, 나뭇가지... 용사 놀이였을까요?";
		Datas[0].Line = -0.5f;

		Datas[1].StoryText = "처음 보는 소년에 놀란 저였지만, 마왕님은 아는 얼굴인 듯했어요.";
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

		Datas[0].StoryText = "소년은 우리가 용사들에게 수없이 들어왔던 다양한 대사를 외치고, 멋진 포즈를 잡는가 싶더니...";
		Datas[0].Line = -0.5f;

		Datas[1].StoryText = "겁도 없이 마왕님에게 달려들었죠.";
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

		Datas[0].StoryText = "몇 번의 투닥거림 후, 그들은 오랜 친구처럼 대화를 나누기 시작했어요.";
		Datas[0].Line = -0.5f;

		Datas[1].StoryText = "마왕과 사이좋은 인간이라... 재미있는 소년이라 생각했죠.";
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

		Datas[0].StoryText = "소년은 다시 한번 포즈를 잡더니 어서 모험을 떠나, 용사가 되고 싶다 말했어요.";
		Datas[0].Line = -0.5f;
		Datas[0].PosX = -170.0f;

		Datas[1].StoryText = "아버지께 자랑스러운 아들이 되고 싶다면서.";
		Datas[1].Line = -0.5f;
		Datas[1].PosX = 283.0f;

		Datas[2].StoryText = "마왕님은 씁쓸하게 웃으며 그에게 훌룡한 용사가 될 수 있을 거라 다독였어요.";
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

		Datas[0].StoryText = "어째서 마왕님이 저런 소년을 친절하게 대하는 건지 알 수 없었죠.";
		Datas[0].Line = -0.5f;

		Datas[1].StoryText = "용사가 되고싶다는 말의 의미를 알고 있기는 한건지...";
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

		Datas[0].StoryText = "소년은 우리에게 작별 인사를 건넨 뒤 떠났어요.";
		Datas[0].Line = -0.5f;

		Datas[1].StoryText = "그가 떠난 후, 저는 소년의 정체에 대해 물었어요.";
		Datas[1].Line = 0.5f;
		Datas[1].PosX = -240.0f;

		Datas[2].StoryText = "그저 용사 지망생인 소년, 모험을 좋아하는 꼬마 정도로 보였거든요.";
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

		Datas[0].StoryText = "마왕님은 그 소년이 알 수 없는 힘을 가지고 있다 말했죠.";
		Datas[0].Line = -0.5f;

		Datas[1].StoryText = "그 힘이 마왕성과 칼레온, 더 나아가 하모니아 대륙을 구원할 수 있을 거라 말했어요.";
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

		Datas[0].StoryText = "그 작은 소년이 말이죠.";
		Datas[0].Line = -0.5f;
		Datas[0].PosX = -200.0f;

		Datas[1].StoryText = "소년이 훌룡한 용사가 되려면 얼마나 기다려야 할까요?";
		Datas[1].Line = -0.5f;
		Datas[1].PosX = 90.0f;

		Datas[2].StoryText = "두 분의 관계는 언제까지 지속될 수 있을까요?";
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

		Datas[0].StoryText = "저는 소년을 계속 지켜보기로 했어요.";
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

