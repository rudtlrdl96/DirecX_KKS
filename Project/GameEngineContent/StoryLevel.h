#pragma once
#include "UILevel.h"
#include "StoryBook.h"

class StoryLevel : public UILevel
{
public:
	enum class StoryName
	{
		Opening,
		ForestOfHarmony,
		GranHall,
		HolyCourtyard,
		Ending
	};
public:
	StoryLevel();
	~StoryLevel();

	StoryLevel(const StoryLevel& _Other) = delete;
	StoryLevel(StoryLevel&& _Other) noexcept = delete;
	StoryLevel& operator=(const StoryLevel& _Other) = delete;
	StoryLevel& operator=(StoryLevel&& _Other) noexcept = delete;

	void SetSotoryName(StoryName _Name)
	{
		CurStoryName = _Name;
		StoryReset();
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void LevelChangeStart() override;
private:
	std::shared_ptr<class FadeActor> FadeImage = nullptr;
	std::shared_ptr<class StoryFrontImage> FrontImage = nullptr;
	std::shared_ptr<class StoryBackImage> BackImage = nullptr;
	std::shared_ptr<class StoryTextureView> StoryView = nullptr;

	StoryName CurStoryName = StoryName::Opening;

	std::map<StoryName, StoryBook> StoryBookDatas;

	void SetOpeningBook();
	void SetForestOfHarmonyBook();
	void SetGrandHallBook();
	void SetHolyCourtyard();
	void SetEndingBook();

	void StoryReset();
};