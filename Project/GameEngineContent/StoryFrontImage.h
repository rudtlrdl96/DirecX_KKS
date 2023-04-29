#pragma once
#include "BaseContentActor.h"

class StoryFrontImage : public BaseContentActor
{
public:
	StoryFrontImage();
	~StoryFrontImage();

	StoryFrontImage(const StoryFrontImage& _Other) = delete;
	StoryFrontImage(StoryFrontImage&& _Other) noexcept = delete;
	StoryFrontImage& operator=(const StoryFrontImage& _Other) = delete;
	StoryFrontImage& operator=(StoryFrontImage&& _Other) noexcept = delete;

protected:
	void Start() override;

private:
	std::shared_ptr<GameEngineSpriteRenderer> TextureRenderer = nullptr;

};

