#pragma once
#include "BaseContentActor.h"

class RectFontActor : public BaseContentActor
{
public:
	RectFontActor();
	~RectFontActor();

	RectFontActor(const RectFontActor& _Other) = delete;
	RectFontActor(RectFontActor&& _Other) noexcept = delete;
	RectFontActor& operator=(const RectFontActor& _Other) = delete;
	RectFontActor& operator=(RectFontActor&& _Other) noexcept = delete;

	void Reset();
	void WriteText(const std::string_view& _Text);
	void RemoveText();
	void SkipText();

protected:
	void Start() override;

private:
	std::shared_ptr<GameEngineFontRenderer> TextRender = nullptr;
	std::string Text = "";

	int ReadIndex = 0;
	float ReadSpeed = 1.0f;

	float FontSize = 16.0f;

	//RECT TextBox
};

