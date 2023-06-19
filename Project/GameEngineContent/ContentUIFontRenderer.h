#pragma once
#include <GameEngineCore/GameEngineFontRenderer.h>

class ContentUIFontRenderer : public GameEngineFontRenderer
{
public:
	ContentUIFontRenderer();
	~ContentUIFontRenderer();

	ContentUIFontRenderer(const ContentUIFontRenderer& _Other) = delete;
	ContentUIFontRenderer(ContentUIFontRenderer&& _Other) noexcept = delete;
	ContentUIFontRenderer& operator=(const ContentUIFontRenderer& _Other) = delete;
	ContentUIFontRenderer& operator=(ContentUIFontRenderer&& _Other) noexcept = delete;

protected:
	void Start() override;

private:


};

