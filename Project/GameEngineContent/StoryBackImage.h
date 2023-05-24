#pragma once
#include "BaseContentActor.h"

class StoryBackImage : public BaseContentActor
{
public:
	StoryBackImage();
	~StoryBackImage();

	StoryBackImage(const StoryBackImage& _Other) = delete;
	StoryBackImage(StoryBackImage&& _Other) noexcept = delete;
	StoryBackImage& operator=(const StoryBackImage& _Other) = delete;
	StoryBackImage& operator=(StoryBackImage&& _Other) noexcept = delete;

protected:
	void Start() override;
	
private:
	std::shared_ptr<class ContentUIRender> TextureRenderer = nullptr;
	ColorBuffer Buffer = ColorBuffer();
};

