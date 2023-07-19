#pragma once
#include "ContentSpriteUIRenderer.h"

class ContentSpriteUIRenderer_Clear : public ContentSpriteUIRenderer
{
public:
	ContentSpriteUIRenderer_Clear();
	~ContentSpriteUIRenderer_Clear();

	ContentSpriteUIRenderer_Clear(const ContentSpriteUIRenderer_Clear& _Other) = delete;
	ContentSpriteUIRenderer_Clear(ContentSpriteUIRenderer_Clear&& _Other) noexcept = delete;
	ContentSpriteUIRenderer_Clear& operator=(const ContentSpriteUIRenderer_Clear& _Other) = delete;
	ContentSpriteUIRenderer_Clear& operator=(ContentSpriteUIRenderer_Clear&& _Other) noexcept = delete;

protected:
	void Render(float _DeltaTime) override;
	
private:


};

