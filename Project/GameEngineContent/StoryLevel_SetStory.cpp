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

		Page.Wirte_Text(Datas);
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

	//{
	//	StoryPage Page;
	//	Page.SetFlip(StoryPage::FlipCondition::AnyKey);
	//	Page.Wirte_ResetText();
	//	BookRef.InsertPage(Page);
	//}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_MoveMainTex(float4(-1023, 0, 0, 0), 3000);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SetSubTex("Story_Opening_01.png", {0, 35});
		Page.Write_SwapTex();
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_Opening_02.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_Opening_03.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SetFade();
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
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_Opening_05.png", { 508, 2 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_FadeIn(0.33f);
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
		Page.Write_SetMainTex("Story_ForestOfHarmony_00.png", float4(0, 35));
		Page.Write_FadeOut(0.5f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_ForestOfHarmony_01.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_ForestOfHarmony_02.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_ForestOfHarmony_03.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_ForestOfHarmony_04.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_ForestOfHarmony_05.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_ForestOfHarmony_06.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_ForestOfHarmony_07.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_ForestOfHarmony_08.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_ForestOfHarmony_09.png", { 0, 35 });
		Page.Write_FadeIntro(1.0f);
		BookRef.InsertPage(Page);
	}

	{
		StoryPage Page;
		Page.SetFlip(StoryPage::FlipCondition::AnyKey, 5.0f);
		Page.Write_SwapTex();
		Page.Write_SetMainTex("Story_ForestOfHarmony_10.png", { 0, 35 });
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

