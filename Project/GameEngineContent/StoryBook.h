#pragma once
#include "StoryPage.h"

class StoryBook
{
	friend class StoryLevel;
public:
	StoryBook();
	~StoryBook();

	void InsertPage(const StoryPage& _Page);
	void ReadPage();

	inline bool IsBookEnd() const
	{
		return IsBookEndValue;
	}

	bool IsBookEndValue = false;

	void Update(float _DeltaTime);

	void Reset();

private:
	std::shared_ptr<FadeActor_UI> FadeImage = nullptr;
	std::shared_ptr<StoryTextureView> StoryView = nullptr;
	std::shared_ptr<StoryFontActor> FontActor = nullptr;

	StoryPage* CurPage = nullptr;
	size_t CurPageNumber = 0;

	std::vector<StoryPage> Pages;

	void NextPage();
};