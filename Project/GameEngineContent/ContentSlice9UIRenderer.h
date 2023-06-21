#pragma once
#include "ContentSlice9Renderer.h"

class ContentSlice9UIRenderer : public ContentSlice9Renderer
{
public:
	ContentSlice9UIRenderer();
	~ContentSlice9UIRenderer();

	ContentSlice9UIRenderer(const ContentSlice9UIRenderer& _Other) = delete;
	ContentSlice9UIRenderer(ContentSlice9UIRenderer&& _Other) noexcept = delete;
	ContentSlice9UIRenderer& operator=(const ContentSlice9UIRenderer& _Other) = delete;
	ContentSlice9UIRenderer& operator=(ContentSlice9UIRenderer&& _Other) noexcept = delete;

	void Start() override;

protected:
	
private:


};

