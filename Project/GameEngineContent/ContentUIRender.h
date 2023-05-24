#pragma once
#include "ContentSpriteRenderer.h"
 
class ContentUIRender : public ContentSpriteRenderer
{
public:
	ContentUIRender();
	~ContentUIRender();

	ContentUIRender(const ContentUIRender& _Other) = delete;
	ContentUIRender(ContentUIRender&& _Other) noexcept = delete;
	ContentUIRender& operator=(const ContentUIRender& _Other) = delete;
	ContentUIRender& operator=(ContentUIRender&& _Other) noexcept = delete;

protected:
	void Start() override;

private:


};

