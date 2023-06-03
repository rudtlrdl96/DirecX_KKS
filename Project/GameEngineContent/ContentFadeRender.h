#pragma once
#include "ContentSpriteRenderer.h"


class ContentFadeRender : public ContentSpriteRenderer
{
public:
	ContentFadeRender();
	~ContentFadeRender();

	ContentFadeRender(const ContentFadeRender& _Other) = delete;
	ContentFadeRender(ContentFadeRender&& _Other) noexcept = delete;
	ContentFadeRender& operator=(const ContentFadeRender& _Other) = delete;
	ContentFadeRender& operator=(ContentFadeRender&& _Other) noexcept = delete;

protected:
	void Start() override;
	
private:


};

