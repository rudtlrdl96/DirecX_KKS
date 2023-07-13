#pragma once
#include <GameEngineCore/GameEngineSpriteRenderer.h>

class ContentMinimapRender : public GameEngineSpriteRenderer
{
public:
	ContentMinimapRender();
	~ContentMinimapRender();

	ContentMinimapRender(const ContentMinimapRender& _Other) = delete;
	ContentMinimapRender(ContentMinimapRender&& _Other) noexcept = delete;
	ContentMinimapRender& operator=(const ContentMinimapRender& _Other) = delete;
	ContentMinimapRender& operator=(ContentMinimapRender&& _Other) noexcept = delete;

protected:
	void Start() override;

private:


};

