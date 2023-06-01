#pragma once
#include "ContentSpriteRenderer.h"

class ContentSpriteUIRenderer : public ContentSpriteRenderer
{
public:
	ContentSpriteUIRenderer();
	~ContentSpriteUIRenderer();

	ContentSpriteUIRenderer(const ContentSpriteUIRenderer& _Other) = delete;
	ContentSpriteUIRenderer(ContentSpriteUIRenderer&& _Other) noexcept = delete;
	ContentSpriteUIRenderer& operator=(const ContentSpriteUIRenderer& _Other) = delete;
	ContentSpriteUIRenderer& operator=(ContentSpriteUIRenderer&& _Other) noexcept = delete;

protected:
	
private:

	void Start() override;

};

