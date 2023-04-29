#include "PrecompileHeader.h"
#include "StoryBook.h"

StoryBook::StoryBook()
{
	Pages.reserve(16);
}

StoryBook::~StoryBook()
{
}

void StoryBook::InsertPage(const StoryPage& _Page)
{
	Pages.push_back(_Page);
}

void StoryBook::ReadPage()
{
	if (Pages.size() == 0)
	{
		MsgAssert_Rtti<StoryBook>(" - Page 정보가 존재하지 않습니다");
		return;
	}

	if (nullptr == CurPage)
	{
		NextPage();
	}

	if (nullptr == CurPage)
	{
		return;
	}

	if (true == CurPage->IsFlipCheck())
	{
		if (nullptr == FadeImage)
		{
			MsgAssert_Rtti<StoryPage>(" - FadeImage가 존재하지 않습니다");
			return;
		}

		if (nullptr == StoryView)
		{
			MsgAssert_Rtti<StoryPage>(" - StoryView가 존재하지 않습니다");
			return;
		}

		CurPage->PageRead(FadeImage.get(), StoryView.get());
		NextPage();
	}
}

void StoryBook::Update(float _DeltaTime)
{
	if (true == FadeImage->IsDeath())
	{
		FadeImage = nullptr;
	}

	if (true == StoryView->IsDeath())
	{
		StoryView = nullptr;
	}

	ReadPage();

	if (nullptr != CurPage)
	{
		CurPage->Update(_DeltaTime);
	}
}

void StoryBook::Reset()
{
	CurPage = nullptr;
	CurPageNumber = 0;

	for (size_t i = 0; i < Pages.size(); i++)
	{
		Pages[i].Reset();
	}
}

void StoryBook::NextPage()
{
	if (nullptr == CurPage)
	{
		if (0 == CurPageNumber)
		{
			CurPage = &Pages[0];
		}
	}
	else
	{
		++CurPageNumber;

		if (Pages.size() <= CurPageNumber)
		{
			CurPage = nullptr;
			IsBookEndValue = true;
			return;
		}

		CurPage = &Pages[CurPageNumber];
	}
}
